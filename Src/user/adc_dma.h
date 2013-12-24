#ifndef __ADC_DMA_H
#define __ADC_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "global_includes.h"
/** @addtogroup Utilities
  * @{
  */

/**
  * @}
  */
  
/** @defgroup STM32F4_DISCOVERY_LIS302DL_Exported_Constants
  * @{
  */

/* Uncomment the following line to use the default LIS302DL_TIMEOUT_UserCallback() 
   function implemented in stm32f4_discovery_lis302dl.c file.
   LIS302DL_TIMEOUT_UserCallback() function is called whenever a timeout condition 
   occure during communication (waiting transmit data register empty flag(TXE)
   or waiting receive data register is not empty flag (RXNE)). */   
/* #define USE_DEFAULT_TIMEOUT_CALLBACK */

/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define ADC_CDR_ADDRESS    ((uint32_t)0x40012308)

/* ADC sample order, P for power/current, VB for Vbat */
/* ADC1 VB 1C 2B 2P 3A 3C */
/* ADC2 1A 2A 2C 4B 3B 3P */
/* ADC3 1B 1P 4A 4C 4P    */

/*
ADC1 M1_A VB   M3_A M2_A VB   M4_C
ADC2 M1_B M3_P M3_B M2_C M4_P M4_B
ADC3 M1_C M1_P M3_C M2_B M2_P M4_A

M1_A	ADC123_IN11
M1_B	ADC123_IN1
M1_C	ADC123_IN2
M1_P	ADC123_IN10

M2_A	ADC12_IN15
M2_B	ADC123_IN13
M2_C	ADC12_IN14
M2_P	ADC123_IN12

M3_A	ADC12_IN9
M3_B	ADC12_IN8
M3_C	ADC123_IN3
M3_P	ADC12_IN5

M4_A	ADC123_IN0
M4_B	ADC12_IN4
M4_C	ADC12_IN7
M4_P	ADC12_IN6

*/

/* ADC1 V_BAT C3_S1 C2_S2 CU_S2 C1_S3 C3_S3 */
/* ADC2 C1_S1 C1_S2 C3_S2 C2_S4 C2_S3 CU_S3 */
/* ADC3 C2_S1 CU_S1 C1_S4 C3_S4 CU_S4       */






#define ADC_CHANNEL_NUM 12
uint8_t adcOrder[3][ADC_CHANNEL_NUM] = 
{
    {
        ADC_Channel_11,
        ADC_Channel_18,
        ADC_Channel_9,
        ADC_Channel_15,
        ADC_Channel_18,
        ADC_Channel_7,
        ADC_Channel_11,
        ADC_Channel_18,
        ADC_Channel_9,
        ADC_Channel_15,
        ADC_Channel_18,
        ADC_Channel_7
    },
    {
        ADC_Channel_1,
        ADC_Channel_5,
        ADC_Channel_8,
        ADC_Channel_14,
        ADC_Channel_6,
        ADC_Channel_4,
        ADC_Channel_1,
        ADC_Channel_5,
        ADC_Channel_8,
        ADC_Channel_14,
        ADC_Channel_6,
        ADC_Channel_4
    },
    {
        ADC_Channel_2,
        ADC_Channel_10,
        ADC_Channel_3,
        ADC_Channel_13,
        ADC_Channel_12,
        ADC_Channel_0,
        ADC_Channel_2,
        ADC_Channel_10,
        ADC_Channel_3,
        ADC_Channel_13,
        ADC_Channel_12,
        ADC_Channel_0
    }
};

typedef struct 
{
    GPIO_TypeDef *port;
    uint32_t pin;
} ADC_Pin_TypeDef;

#define ADC_PIN_NUM 16

ADC_Pin_TypeDef adcPin[ADC_PIN_NUM] = {
    {
        GPIOA, GPIO_Pin_0
    },
    {
        GPIOA, GPIO_Pin_1
    },
    {
        GPIOA, GPIO_Pin_2
    },
    {
        GPIOA, GPIO_Pin_3
    },
    {
        GPIOA, GPIO_Pin_4
    },
    {
        GPIOA, GPIO_Pin_5
    },
    {
        GPIOA, GPIO_Pin_6
    },
    {
        GPIOA, GPIO_Pin_7
    },
    {
        GPIOB, GPIO_Pin_0
    },
    {
        GPIOB, GPIO_Pin_1
    },
    {
        GPIOC, GPIO_Pin_0
    },
    {
        GPIOC, GPIO_Pin_1
    },
    {
        GPIOC, GPIO_Pin_2
    },
    {
        GPIOC, GPIO_Pin_3
    },
    {
        GPIOC, GPIO_Pin_4
    },
    {
        GPIOC, GPIO_Pin_5
    }
};
    


#ifdef __cplusplus
}
#endif

#endif /* __CC2540_DRIVER_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 



