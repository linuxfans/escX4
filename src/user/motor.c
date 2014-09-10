#include <motor.h>
#include <string.h>
#include <motor_config.h>
#include "shell.h"
volatile MOTOR motor[MOTOR_NUM];
void motor_init()
{
    memcpy(motor, motor_default, sizeof(motor));
}

void motor_start(MOTOR *p) 
{
    p->state = STATE_START;
    p->phase = 1;
    p->start_counter = 0;
    *(p->phase_a_pwm) = 800;
    *(p->phase_b_pwm) = 800;
    *(p->phase_c_pwm) = 800;
    p->start_comm_period =  US_TO_TICKS(10000);
    commutate(p);
//    TIM_ITConfig(TIM10, TIM_IT_CC1, ENABLE);
    TIM10->DIER |= TIM_IT_CC1;
    *(p->commutate_timer) = *(p->commutate_counter) + p->start_comm_period;
    p->prev_comm_ticks = *(p->commutate_timer);
    p->start_comm_period = ((p->start_comm_period * 15) >> 4);
}

extern volatile uint32_t abs_base_time;
volatile uint32_t zcp;

void motor_start_procedure(MOTOR* p)
{
    uint32_t tmp_time = abs_base_time;
    if (p->state == STATE_START) {
        *(p->commutate_timer) = p->prev_comm_ticks + p->start_comm_period;
        p->prev_comm_ticks = *(p->commutate_timer);
        p->start_comm_period = ((p->start_comm_period * 15) >> 4);
        p->start_counter++;
        p->phase++;
        if (p->phase > 6) {
            p->phase = 1;
        }
        if (p->start_counter > p->start_round_num * 6) {
            p->state = STATE_RUNNING;
            p->zero_cross_period = US_TO_UNIT(3000);
            p->prev_zero_cross_time = tmp_time - (p->zero_cross_period >> 1);
            p->next_detect_time = tmp_time + (p->zero_cross_period >> 2);
            p->detect_lost_time = p->next_detect_time + (p->zero_cross_period >> 1);
            *(p->commutate_timer) = UNIT_TO_TICKS(tmp_time + p->zero_cross_period);
            p->phase = 1;
            p->bemf_rising = 0;
            p->prev_valid_time = 0xFFFFFFFF;
            p->stimu_voltage_offset = p->stimu_voltage_offset_table[p->phase];
            p->sense_voltage_offset = p->sense_voltage_offset_table[p->phase];
            p->debug_counter = 0;
        }
    }
}


void motor_zero_cross_detect(MOTOR* p, uint16_t* base, uint32_t abs_ref_time)
{
    uint32_t stimu_voltage;
    uint32_t sense_voltage;
    uint32_t power_voltage;
    uint32_t curr_zero_cross_time;

    if (p->state != STATE_RUNNING) return;
    if (TIME_LESS_THEN(abs_ref_time, p->next_detect_time)) {
        return;
    }
    if (TIME_LESS_THEN(p->detect_lost_time, abs_ref_time)) {
        p->comm_good_temp_counter = 0;
        p->comm_lost_temp_counter++;
        p->comm_lost_total_counter++;
        if (p->comm_lost_temp_counter > 10) {
            p->comm_lost_temp_counter = 0;
            p->state = STATE_SELF_TEST;
            p->phase = 0;
            commutate(p);
            TIM10->DIER &= ~TIM_IT_CC1;
            printf("comm lost %d, valid_time %d, total lost %d\r\n", p->zero_cross_period, p->prev_valid_time, p->comm_lost_total_counter);
//            printf("comm lost %d\r\n", p->zero_cross_period);
            return;
        }
        goto zero_cross_found;
    }

    stimu_voltage = base[p->stimu_voltage_offset];
    sense_voltage = base[p->sense_voltage_offset];
    power_voltage = base[p->power_voltage_offset] * 12;

    // stimulate voltage > power voltage * 3 / 4, it's a valid sample

    if (stimu_voltage > power_voltage) {
        if (((sense_voltage << 1) < stimu_voltage) ^ p->bemf_rising) {
            p->comm_good_temp_counter++;
            if (p->comm_good_temp_counter > 6) {
                p->comm_good_temp_counter = 6;
                p->comm_lost_temp_counter = 0;
            }
            goto zero_cross_found;
        }
        p->prev_valid_stimu_voltage = stimu_voltage;
        p->prev_valid_sense_voltage = sense_voltage;
        p->prev_valid_time = abs_ref_time;
    }
    return;    
    
zero_cross_found:

    if (p->prev_valid_time != 0xFFFFFFFF) {
        curr_zero_cross_time = ((abs_ref_time - p->prev_valid_time) / 2)+ p->prev_valid_time;
    } else {
        curr_zero_cross_time = abs_ref_time;
    }
    p->zero_cross_period = (7 * p->zero_cross_period + curr_zero_cross_time - p->prev_zero_cross_time) >> 3;

    p->prev_zero_cross_time = curr_zero_cross_time;
    p->next_detect_time = curr_zero_cross_time + (p->zero_cross_period >> 3) * 5;
    p->detect_lost_time = p->next_detect_time + p->zero_cross_period;
    *(p->commutate_timer) = UNIT_TO_TICKS(curr_zero_cross_time + (p->zero_cross_period >> 1));

    p->bemf_rising = !(p->bemf_rising);
    p->phase++;
    if (p->phase > 6) {
        p->phase = 1;
    }
    p->prev_valid_time = 0xFFFFFFFF;
    p->stimu_voltage_offset = p->stimu_voltage_offset_table[p->phase];
    p->sense_voltage_offset = p->sense_voltage_offset_table[p->phase];
    p->debug_counter++;

    if (p->debug_counter > p->debug_counter_max) {
        printf("finished %d, valid_time %d\r\n", p->zero_cross_period, p->prev_valid_time);
//        printf("finished %d\r\n", p->zero_cross_period);
        p->comm_lost_temp_counter = 0;
        p->state = STATE_SELF_TEST;
        p->phase = 0;
        commutate(p);
        TIM10->DIER &= ~TIM_IT_CC1;
//        TIM_ITConfig(TIM10, TIM_IT_CC1, DISABLE);
    }
    return;
}


/* uint8_t H_TAB[7][3] = { */
/*     {0, 0, 0}, */
/*     {1, 0, 0}, */
/*     {0, 1, 0}, */
/*     {0, 1, 0}, */
/*     {0, 0, 1}, */
/*     {0, 0, 1}, */
/*     {1, 0, 0} */
/* }; */

uint8_t H_TAB[7][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 0, 1},
    {0, 0, 1}
};

inline void commutate(MOTOR* p) 
{
    uint8_t phase;
    phase = p->phase;

    *(p->high_side_table[0]) = H_TAB[phase][0];
    *(p->high_side_table[1]) = !H_TAB[phase][0];
    *(p->high_side_table[2]) = H_TAB[phase][1];
    *(p->high_side_table[3]) = !H_TAB[phase][1];
    *(p->high_side_table[4]) = H_TAB[phase][2];
    *(p->high_side_table[5]) = !H_TAB[phase][2];
    
    *(p->low_side_table[phase][0]) = 1;
    *(p->low_side_table[phase][1]) = 1;
    *(p->low_side_table[phase][2]) = 1;
}


void TIM1_UP_TIM10_IRQHandler(void) 
{
    MOTOR *p;
    TIM10->SR = (uint16_t)~TIM_IT_CC1;
    p = &(motor[M2_IDX]);
    if (p->state == STATE_SELF_TEST) return;
    commutate(p);
    if (p->state == STATE_START) {
        motor_start_procedure(p);
    }
}
