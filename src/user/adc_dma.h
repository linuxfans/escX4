#ifndef __ADC_DMA_H
#define __ADC_DMA_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "global_includes.h"
#include "motor.h"
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

typedef struct 
{
    GPIO_TypeDef *port;
    uint32_t pin;
} ADC_Pin_TypeDef;

#define ADC_PIN_NUM 16
    
void ADC_DMA_Init();
     

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



