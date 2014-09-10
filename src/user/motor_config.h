#include "motor.h"
#include "motor_bsp.h"


/*
ADC1 M1_A VB   M3_A M2_A VB   M4_C
ADC2 M1_B M3_P M3_B M2_C M4_P M4_B
ADC3 M1_C M1_P M3_C M2_B M2_P M4_A
*/
const MOTOR motor_default[MOTOR_NUM] = {
    {
        .state = STATE_SELF_TEST,
        .stimu_voltage_offset_table = {0, 1, 2, 3, 4, 5, 6},

    },
    {
        .state = STATE_SELF_TEST,
        .phase = 0,
        .start_counter = 0,
        .start_round_num = 3,
        .pwm_on_duty = 1000,
        .zero_cross_period = US_TO_UNIT(100),
        
        .sense_voltage_offset_table = {M2_A_SENS, M2_C_SENS, M2_B_SENS, M2_A_SENS, 
                                       M2_C_SENS, M2_B_SENS, M2_A_SENS},
        .stimu_voltage_offset_table = {M2_A_SENS, M2_A_SENS, M2_A_SENS, M2_B_SENS, 
                                       M2_B_SENS, M2_C_SENS, M2_C_SENS},
        .power_voltage_offset = 3,
        .commutate_timer = &(M2_COMM_TIMER),
        .commutate_counter = &(M2_COMM_COUNTER),
        .phase_a_pwm = &(M2_A_PWM_TIMER),
        .phase_b_pwm = &(M2_B_PWM_TIMER),
        .phase_c_pwm = &(M2_C_PWM_TIMER),
        .debug_counter_max = 10000,
        .comm_lost_temp_counter = 0,
        .comm_lost_total_counter = 0,
        .low_side_table = {
            {M2_A_L_OFF, M2_B_L_OFF, M2_C_L_OFF},
            {M2_C_L_OFF, M2_A_L_OFF, M2_B_L_ON},
            {M2_A_L_OFF, M2_B_L_OFF, M2_C_L_ON},
            {M2_A_L_OFF, M2_B_L_OFF, M2_C_L_ON},
            {M2_B_L_OFF, M2_C_L_OFF, M2_A_L_ON},
            {M2_B_L_OFF, M2_C_L_OFF, M2_A_L_ON},
            {M2_C_L_OFF, M2_A_L_OFF, M2_B_L_ON}},
        .high_side_table = {
            M2_A_PWM_CTRL_1,
            M2_A_PWM_CTRL_0,
            M2_B_PWM_CTRL_1,
            M2_B_PWM_CTRL_0,
            M2_C_PWM_CTRL_1,
            M2_C_PWM_CTRL_0,
        }
    },

    {
        .state = STATE_SELF_TEST,
        .stimu_voltage_offset_table = {0, 1, 2, 3, 4, 5, 6},

    },

    {
        .state = STATE_SELF_TEST,
        .stimu_voltage_offset_table = {0, 1, 2, 3, 4, 5, 6},

    },
    
};

