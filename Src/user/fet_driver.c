#include "fet_driver.h"
static void FET_Driver_LowLevel_Init(void);

extern uint32_t next_falling_edge_2;
extern uint32_t next_rising_edge_2;
extern volatile uint8_t l_side_state_2;
extern volatile uint8_t h_side_state_2;


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

    /* Enable the TIM3 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the TIM4 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Setup Timers 1, 3, 4, 8, 9, 10, 11, 12*/
    TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = 44; /* unit is 3/4us */
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    /* TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); */
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM11, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);
    TIM_PrescalerConfig(TIM3, 44, TIM_PSCReloadMode_Immediate); /* 60MHz clock */
    TIM_PrescalerConfig(TIM4, 44, TIM_PSCReloadMode_Immediate);
    TIM_PrescalerConfig(TIM10, 89, TIM_PSCReloadMode_Immediate); /* 120MHz clock */
    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
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

    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
    TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);
    TIM_ITConfig(TIM10, TIM_IT_CC1, ENABLE);
}



void TIM3_IRQHandler(void) 
{
    if (TIM3->SR & TIM_IT_CC1) {
        TIM3->SR = (uint16_t)~TIM_IT_CC1;
        switch(h_side_state_2) {
        case 0:
            TIM3->CCMR1 = TIM3->CCMR1 & 0xFF8F | 0x0020;
            TIM3->CCR1 = next_falling_edge_2;
            h_side_state_2 = 1;
            break;
        case 1:
            TIM3->CCMR1 = TIM3->CCMR1 & 0xFF8F | 0x0010;
            TIM3->CCR1 = next_rising_edge_2;
            h_side_state_2 = 2;
            break;
        case 2:
            TIM3->CCMR1 = TIM3->CCMR1 & 0xFF8F | 0x0020;
            TIM3->CCR1 = next_falling_edge_2;
            h_side_state_2 = 3;
            break;
        case 3:
            TIM3->CCMR1 = TIM3->CCMR1 & 0xFF8F | 0x0040;
            TIM4->CCR1 = next_rising_edge_2;
            h_side_state_2 = 0;
            break;
        default:
            break;
        }
        return;                 /* These two interrupts can't be triggered at the same time, so... */
    }
    if (TIM3->SR & TIM_IT_CC2) {
        TIM3->SR = (uint16_t)~TIM_IT_CC2;
        switch(h_side_state_2) {
        case 0:
            TIM3->CCMR1 = TIM3->CCMR1 & 0x8FFF | 0x2000;
            TIM3->CCR2 = next_falling_edge_2;
            h_side_state_2 = 1;
            break;
        case 1:
            TIM3->CCMR1 = TIM3->CCMR1 & 0x8FFF | 0x1000;
            TIM3->CCR2 = next_rising_edge_2;
            h_side_state_2 = 2;
            break;
        case 2:
            TIM3->CCMR1 = TIM3->CCMR1 & 0x8FFF | 0x2000;
            TIM3->CCR2 = next_falling_edge_2;
            h_side_state_2 = 3;
            break;
        case 3:
            TIM3->CCMR1 = TIM3->CCMR1 & 0x8FFF | 0x4000;
            TIM3->CCR1 = next_rising_edge_2;
            h_side_state_2 = 0;
            break;
        default:
            break;
        }
        return;
    }
}
void TIM4_IRQHandler(void) 
{
    if (TIM4->SR & TIM_IT_CC1) {
        TIM4->SR = (uint16_t)~TIM_IT_CC1;
        switch(h_side_state_2) {
        case 0:
            TIM4->CCMR1 = TIM4->CCMR1 & 0xFF8F | 0x0020;
            TIM4->CCR1 = next_falling_edge_2;
            h_side_state_2 = 1;
            break;
        case 1:
            TIM4->CCMR1 = TIM4->CCMR1 & 0xFF8F | 0x0010;
            TIM4->CCR1 = next_rising_edge_2;
            h_side_state_2 = 2;
            break;
        case 2:
            TIM4->CCMR1 = TIM4->CCMR1 & 0xFF8F | 0x0020;
            TIM4->CCR1 = next_falling_edge_2;
            h_side_state_2 = 3;
            break;
        case 3:
            TIM4->CCMR1 = TIM4->CCMR1 & 0xFF8F | 0x0040;
            TIM3->CCR2 = next_rising_edge_2;
            h_side_state_2 = 0;
            break;
        default:
            break;
        }
    }
}
uint8_t buf[32];
void TIM1_UP_TIM10_IRQHandler(void) 
{
    TIM10->SR = (uint16_t)~TIM_IT_CC1;
    L_OFF(2, A);
    L_OFF(2, B);
    L_OFF(2, C);

    switch(l_side_state_2) {
    case 0:
        L_ON(2, A);
        break;
    case 1:
        L_ON(2, B);
        break;
    case 2:
        L_ON(2, C);
        break;
    default:
        break;
    }
}






