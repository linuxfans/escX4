#include "fet_driver.h"
static void FET_Driver_LowLevel_Init(void);


extern volatile uint8_t step_2;

void FET_Driver_Init(void)
{
    FET_Driver_LowLevel_Init();
}
/* 
   M1_A_H	B8	TIM4_3
   M1_B_H	B9	TIM4_4
   M1_C_H	B7	TIM4_2

   M2_A_H	B4	TIM3_1
   M2_B_H	B6	TIM4_1
   M2_C_H	B5	TIM3_2

   M3_A_H	C6	TIM8_1
   M3_B_H	C7	TIM8_2
   M3_C_H	C8	TIM8_3

   M4_A_H	A10	TIM1_3
   M4_B_H	C9	TIM8_4
   M4_C_H	A8	TIM1_1

 */
uint8_t H_TAB[7][3] = {
    {
        0, 0, 0
    },
    {
        1, 0, 0
    },
    {
        0, 1, 0
    },
    {
        0, 1, 0
    },
    {
        0, 0, 1
    },
    {
        0, 0, 1
    },
    {
        1, 0, 0
    }
};

uint32_t* M2_L_TAB[7][3] = {
    {
        M2_A_L_OFF, M2_B_L_OFF, M2_C_L_OFF
    },
    {
        M2_A_L_OFF, M2_B_L_OFF, M2_C_L_ON
    },
    {
        M2_A_L_OFF, M2_B_L_OFF, M2_C_L_ON
    },
    {
        M2_B_L_OFF, M2_C_L_OFF, M2_A_L_ON
    },
    {
        M2_B_L_OFF, M2_C_L_OFF, M2_A_L_ON
    },
    {
        M2_C_L_OFF, M2_A_L_OFF, M2_B_L_ON
    },
    {
        M2_C_L_OFF, M2_A_L_OFF, M2_B_L_ON
    }
};

void FET_Driver_LowLevel_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA , ENABLE);  
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB , ENABLE);  
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC , ENABLE);  
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD , ENABLE);  
    // setup low side gates
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
    FET_L_PIN_INIT;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
    FET_H_PIN_INIT;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    /* Enable the TIM10 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Setup Timers 1, 3, 4, 8, 9, 10, 11, 12*/
    TIM_TimeBaseStructure.TIM_Period = 3999; /* 15kHz */
    TIM_TimeBaseStructure.TIM_Prescaler = 0; /* unit is 1/60MHz */
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    /* TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); */
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);
    TIM_PrescalerConfig(TIM3, 0, TIM_PSCReloadMode_Immediate); /* 60MHz clock */
    TIM_PrescalerConfig(TIM4, 0, TIM_PSCReloadMode_Immediate);

    TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = 0; /* unit is 3/4us */
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM11, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);
    TIM_PrescalerConfig(TIM10, 89, TIM_PSCReloadMode_Immediate); /* 120MHz clock */
    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    /* Motor 2 */
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Disable);
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);
    TIM_OC1Init(TIM10, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM10 , TIM_OCPreload_Disable);

    TIM_ITConfig(TIM10, TIM_IT_CC1, ENABLE);
}
void TIM1_UP_TIM10_IRQHandler(void) 
{
    TIM10->SR = (uint16_t)~TIM_IT_CC1;

    *M2_A_PWM_CTRL_1 = H_TAB[step_2][0];
    *M2_A_PWM_CTRL_0 = !H_TAB[step_2][0];
    *M2_B_PWM_CTRL_1 = H_TAB[step_2][1];
    *M2_B_PWM_CTRL_0 = !H_TAB[step_2][1];
    *M2_C_PWM_CTRL_1 = H_TAB[step_2][2];
    *M2_C_PWM_CTRL_0 = !H_TAB[step_2][2];
    

    *M2_L_TAB[step_2][0] = 1;
    *M2_L_TAB[step_2][1] = 1;
    *M2_L_TAB[step_2][2] = 1;
}






