#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f4xx.h"
#include "global_includes.h"
#include "fet_driver.h"

typedef enum motor_state {
    STATE_SELF_TEST = 0,
    STATE_FAILED,
    STATE_READY,
    STATE_START,
    STATE_RUNNING
} MOTOR_STATE;

#define M1_IDX	0
#define M2_IDX	1
#define M3_IDX	2
#define M4_IDX	3

// 1 TICKS = 0.25us
// 1 TICKS = 256 UNIT
// 1 UNIT = 0.25us / 256 = 1us / 1024

#define INT32_TICKS_FRAC		8
#define UNIT_TO_TICKS(x)		((uint32_t)(x) >> (INT32_TICKS_FRAC))
#define TICKS_TO_UNIT(x)		((uint32_t)(x) << (INT32_TICKS_FRAC))
#define INT32_US_FRAC			10
#define UNIT_TO_US(x)			((uint32_t)(x) >> (INT32_US_FRAC))
#define US_TO_UNIT(x)			((uint32_t)(x) << (INT32_US_FRAC))

#define TICKS_TO_US(x)			((uint32_t)(x) >> (INT32_US_FRAC - INT32_TICKS_FRAC))
#define US_TO_TICKS(x)			((uint32_t)(x) << (INT32_US_FRAC - INT32_TICKS_FRAC))

#define PHASE_NUM 7

typedef struct motor
{
    MOTOR_STATE state;
    uint8_t phase;


    uint32_t start_counter;
    uint32_t start_round_num;
    uint32_t pwm_on_duty;
    uint32_t zero_cross_period;
    uint32_t next_detect_time;
    uint32_t detect_lost_time;
    uint32_t prev_zero_cross_time;
    uint32_t prev_comm_ticks;

    uint8_t stimu_voltage_offset; 
    uint8_t sense_voltage_offset;
    uint8_t power_voltage_offset;
    uint8_t stimu_voltage_offset_table[PHASE_NUM];
    uint8_t sense_voltage_offset_table[PHASE_NUM];

    uint8_t bemf_rising;
    
    uint32_t prev_valid_time;
    uint32_t prev_valid_stimu_voltage;
    uint32_t prev_valid_sense_voltage;

    uint32_t comm_lost_temp_counter;
    uint32_t comm_good_temp_counter;
    uint32_t comm_lost_total_counter;

    uint32_t debug_counter;
    uint32_t debug_counter_max;

    volatile uint32_t* commutate_timer;
    volatile uint32_t* commutate_counter;
    volatile uint32_t* phase_a_pwm;
    volatile uint32_t* phase_b_pwm;
    volatile uint32_t* phase_c_pwm;

    volatile uint32_t* low_side_table[PHASE_NUM][3];
    volatile uint32_t* high_side_table[6];
} MOTOR;

#define MOTOR_NUM 4
extern volatile MOTOR motor[MOTOR_NUM];



// phase 	1	2	3	4	5	6
// stimu	A	A	B	B	C	C
// sense	C	B	A	C	B	A

    
void motor_init(void);

#define TIME_LESS_THEN(x, y)	(((x) - (y)) > 0x80000000)

        
#endif
