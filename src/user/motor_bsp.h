#define M2_COMM_TIMER (TIM10->CCR1)
#define M2_COMM_COUNTER (TIM10->CNT)
#define M2_A_PWM_TIMER (TIM3->CCR1)
#define M2_B_PWM_TIMER (TIM4->CCR1)
#define M2_C_PWM_TIMER (TIM3->CCR2)

#define M1_A_SENS	0
#define M1_B_SENS	1
#define M1_C_SENS	2
#define M2_A_SENS	9
#define M2_B_SENS	11
#define M2_C_SENS	10
#define M3_A_SENS	6
#define M3_B_SENS	7
#define M3_C_SENS	8
#define M4_A_SENS	17
#define M4_B_SENS	16
#define M4_C_SENS	15

#define M1_A_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0x800) << 5) + (15 << 2)))
#define M1_B_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0x800) << 5) + (14 << 2)))
#define M1_C_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0x800) << 5) + (13 << 2)))
#define M2_A_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0xc00) << 5) + ( 2 << 2)))
#define M2_B_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0x800) << 5) + (11 << 2)))
#define M2_C_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0x800) << 5) + (12 << 2)))
#define M3_A_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0x800) << 5) + (10 << 2)))
#define M3_B_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0x400) << 5) + ( 2 << 2)))
#define M3_C_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0x400) << 5) + (13 << 2)))
#define M4_A_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0x400) << 5) + (15 << 2)))
#define M4_B_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0x400) << 5) + (12 << 2)))
#define M4_C_L_ON	((uint32_t *)(0x42000000 + ((0x20018 + 0x400) << 5) + (14 << 2)))
#define M1_A_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0x800) << 5) + (15 << 2)))
#define M1_B_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0x800) << 5) + (14 << 2)))
#define M1_C_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0x800) << 5) + (13 << 2)))
#define M2_A_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0xc00) << 5) + ( 2 << 2)))
#define M2_B_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0x800) << 5) + (11 << 2)))
#define M2_C_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0x800) << 5) + (12 << 2)))
#define M3_A_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0x800) << 5) + (10 << 2)))
#define M3_B_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0x400) << 5) + ( 2 << 2)))
#define M3_C_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0x400) << 5) + (13 << 2)))
#define M4_A_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0x400) << 5) + (15 << 2)))
#define M4_B_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0x400) << 5) + (12 << 2)))
#define M4_C_L_OFF	((uint32_t *)(0x42000000 + ((0x2001A + 0x400) << 5) + (14 << 2)))
#define M1_A_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + (16 << 2)))
#define M1_A_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + (17 << 2)))
#define M1_B_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + (18 << 2)))
#define M1_B_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + (19 << 2)))
#define M1_C_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + (14 << 2)))
#define M1_C_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + (15 << 2)))
#define M2_A_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + ( 8 << 2)))
#define M2_A_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + ( 9 << 2)))
#define M2_B_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + (12 << 2)))
#define M2_B_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + (13 << 2)))
#define M2_C_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + (10 << 2)))
#define M2_C_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x400) << 5) + (11 << 2)))
#define M3_A_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x800) << 5) + (12 << 2)))
#define M3_A_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x800) << 5) + (13 << 2)))
#define M3_B_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x800) << 5) + (14 << 2)))
#define M3_B_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x800) << 5) + (15 << 2)))
#define M3_C_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x800) << 5) + (16 << 2)))
#define M3_C_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x800) << 5) + (17 << 2)))
#define M4_A_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x0) << 5) + (20 << 2)))
#define M4_A_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x0) << 5) + (21 << 2)))
#define M4_B_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x800) << 5) + (18 << 2)))
#define M4_B_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x800) << 5) + (19 << 2)))
#define M4_C_PWM_CTRL_0	((uint32_t *)(0x42000000 + ((0x20000 + 0x0) << 5) + (16 << 2)))
#define M4_C_PWM_CTRL_1	((uint32_t *)(0x42000000 + ((0x20000 + 0x0) << 5) + (17 << 2)))
