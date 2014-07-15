#ifndef __FET_DRIVER_H
#define __FET_DRIVER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "global_includes.h"
/** @addtogroup Utilities
  * @{
  */

/**
  * @}
  */


#define M1_A_L_PORT		GPIOC
#define M1_B_L_PORT		GPIOC
#define M1_C_L_PORT		GPIOC

#define M1_A_L_PIN		GPIO_Pin_15
#define M1_B_L_PIN		GPIO_Pin_14
#define M1_C_L_PIN		GPIO_Pin_13

#define M2_A_L_PORT		GPIOD
#define M2_B_L_PORT		GPIOC
#define M2_C_L_PORT		GPIOC

#define M2_A_L_PIN		GPIO_Pin_2
#define M2_B_L_PIN		GPIO_Pin_11
#define M2_C_L_PIN		GPIO_Pin_12

#define M3_A_L_PORT		GPIOC
#define M3_B_L_PORT		GPIOB
#define M3_C_L_PORT		GPIOB

#define M3_A_L_PIN		GPIO_Pin_10
#define M3_B_L_PIN		GPIO_Pin_2
#define M3_C_L_PIN		GPIO_Pin_13

#define M4_A_L_PORT		GPIOB
#define M4_B_L_PORT		GPIOB
#define M4_C_L_PORT		GPIOB

#define M4_A_L_PIN		GPIO_Pin_15
#define M4_B_L_PIN		GPIO_Pin_12
#define M4_C_L_PIN		GPIO_Pin_14


#define M1_A_H_PORT		GPIOB
#define M1_B_H_PORT		GPIOB
#define M1_C_H_PORT		GPIOB

#define M1_A_H_PIN		GPIO_Pin_8
#define M1_B_H_PIN		GPIO_Pin_9
#define M1_C_H_PIN		GPIO_Pin_7

#define M1_A_H_PIN_SOURCE	GPIO_PinSource8
#define M1_B_H_PIN_SOURCE	GPIO_PinSource9
#define M1_C_H_PIN_SOURCE	GPIO_PinSource7

#define M1_A_H_AF		GPIO_AF_TIM4
#define M1_B_H_AF		GPIO_AF_TIM4
#define M1_C_H_AF		GPIO_AF_TIM4

#define M2_A_H_PORT		GPIOB
#define M2_B_H_PORT		GPIOB
#define M2_C_H_PORT		GPIOB

#define M2_A_H_PIN		GPIO_Pin_4
#define M2_B_H_PIN		GPIO_Pin_6
#define M2_C_H_PIN		GPIO_Pin_5

#define M2_A_H_PIN_SOURCE	GPIO_PinSource4
#define M2_B_H_PIN_SOURCE	GPIO_PinSource6
#define M2_C_H_PIN_SOURCE	GPIO_PinSource5

#define M2_A_H_AF		GPIO_AF_TIM3
#define M2_B_H_AF		GPIO_AF_TIM4
#define M2_C_H_AF		GPIO_AF_TIM3


#define M3_A_H_PORT		GPIOC
#define M3_B_H_PORT		GPIOC
#define M3_C_H_PORT		GPIOC

#define M3_A_H_PIN		GPIO_Pin_6
#define M3_B_H_PIN		GPIO_Pin_7
#define M3_C_H_PIN		GPIO_Pin_8

#define M3_A_H_PIN_SOURCE	GPIO_PinSource6
#define M3_B_H_PIN_SOURCE	GPIO_PinSource7
#define M3_C_H_PIN_SOURCE	GPIO_PinSource8

#define M3_A_H_AF		GPIO_AF_TIM8
#define M3_B_H_AF		GPIO_AF_TIM8
#define M3_C_H_AF		GPIO_AF_TIM8

#define M4_A_H_PORT		GPIOA
#define M4_B_H_PORT		GPIOC
#define M4_C_H_PORT		GPIOA

#define M4_A_H_PIN		GPIO_Pin_10
#define M4_B_H_PIN		GPIO_Pin_9
#define M4_C_H_PIN		GPIO_Pin_8


#define M4_A_H_PIN_SOURCE	GPIO_PinSource10
#define M4_B_H_PIN_SOURCE	GPIO_PinSource9
#define M4_C_H_PIN_SOURCE	GPIO_PinSource8

#define M4_A_H_AF		GPIO_AF_TIM1
#define M4_B_H_AF		GPIO_AF_TIM8
#define M4_C_H_AF		GPIO_AF_TIM1


// #define M2_A_PWM_CTRL_0	((uint32_t *)(0x42000000 + (0x20400 << 5) + (4 << 3)))
// #define M2_A_PWM_CTRL_1	((uint32_t *)(0x42000000 + (0x20400 << 5) + (4 << 3) + 4))
// #define M2_B_PWM_CTRL_0	((uint32_t *)(0x42000000 + (0x20400 << 5) + (6 << 3)))
// #define M2_B_PWM_CTRL_1	((uint32_t *)(0x42000000 + (0x20400 << 5) + (6 << 3) + 4))
// #define M2_C_PWM_CTRL_0	((uint32_t *)(0x42000000 + (0x20400 << 5) + (5 << 3)))
// #define M2_C_PWM_CTRL_1	((uint32_t *)(0x42000000 + (0x20400 << 5) + (5 << 3) + 4))

// #define M2_A_L_ON	((uint32_t *)(0x42000000 + (0x20C18 << 5) + (2 << 2)))
// #define M2_B_L_ON	((uint32_t *)(0x42000000 + (0x20818 << 5) + (11 << 2)))
// #define M2_C_L_ON	((uint32_t *)(0x42000000 + (0x20818 << 5) + (12 << 2)))

// #define M2_A_L_OFF	((uint32_t *)(0x42000000 + (0x20C1A << 5) + (2 << 2)))
// #define M2_B_L_OFF	((uint32_t *)(0x42000000 + (0x2081A << 5) + (11 << 2)))
// #define M2_C_L_OFF	((uint32_t *)(0x42000000 + (0x2081A << 5) + (12 << 2)))



#define L_OFF(motor, channel) do {                                      \
         M##motor##_##channel##_L_PORT->BSRRH = M##motor##_##channel##_L_PIN; \
     } while(0)

#define L_ON(motor, channel) do {                                       \
         M##motor##_##channel##_L_PORT->BSRRL = M##motor##_##channel##_L_PIN; \
     } while(0)

#define H_OFF(motor, channel) do {                                      \
         M##motor##_##channel##_H_PORT->BSRRH = M##motor##_##channel##_H_PIN; \
     } while(0)

#define H_ON(motor, channel) do {                                       \
         M##motor##_##channel##_H_PORT->BSRRL = M##motor##_##channel##_H_PIN; \
     } while(0)

#define L_ALL_OFF(motor) do {                   \
         L_OFF(motor, A);                       \
         L_OFF(motor, B);                       \
         L_OFF(motor, C);                       \
     } while(0)

#define H_ALL_OFF(motor) do {                   \
         H_OFF(motor, A);                       \
         H_OFF(motor, B);                       \
         H_OFF(motor, C);                       \
     } while(0)

#define FET_PIN_CONFIG(motor, channel, side) do {                       \
         GPIO_InitStructure.GPIO_Pin = M##motor##_##channel##_##side##_PIN; \
             GPIO_Init(M##motor##_##channel##_##side##_PORT, &GPIO_InitStructure); \
     } while(0)                                                                   

#define FET_AF_PIN_CONFIG(motor, channel) do {                  \
         GPIO_PinAFConfig(M##motor##_##channel##_H_PORT,        \
                          M##motor##_##channel##_H_PIN_SOURCE,  \
                          M##motor##_##channel##_H_AF);         \
     } while(0)
     

#define FET_L_PIN_INIT do{                      \
         FET_PIN_CONFIG(1, A, L);               \
         FET_PIN_CONFIG(1, B, L);               \
         FET_PIN_CONFIG(1, C, L);               \
         FET_PIN_CONFIG(2, A, L);               \
         FET_PIN_CONFIG(2, B, L);               \
         FET_PIN_CONFIG(2, C, L);               \
         FET_PIN_CONFIG(3, A, L);               \
         FET_PIN_CONFIG(3, B, L);               \
         FET_PIN_CONFIG(3, C, L);               \
         FET_PIN_CONFIG(4, A, L);               \
         FET_PIN_CONFIG(4, B, L);               \
         FET_PIN_CONFIG(4, C, L);               \
     } while(0)

#define FET_H_PIN_INIT do{                      \
         FET_AF_PIN_CONFIG(1, A);               \
         FET_AF_PIN_CONFIG(1, B);               \
         FET_AF_PIN_CONFIG(1, C);               \
         FET_AF_PIN_CONFIG(2, A);               \
         FET_AF_PIN_CONFIG(2, B);               \
         FET_AF_PIN_CONFIG(2, C);               \
         FET_AF_PIN_CONFIG(3, A);               \
         FET_AF_PIN_CONFIG(3, B);               \
         FET_AF_PIN_CONFIG(3, C);               \
         FET_AF_PIN_CONFIG(4, A);               \
         FET_AF_PIN_CONFIG(4, B);               \
         FET_AF_PIN_CONFIG(4, C);               \
         FET_PIN_CONFIG(1, A, H);               \
         FET_PIN_CONFIG(1, B, H);               \
         FET_PIN_CONFIG(1, C, H);               \
         FET_PIN_CONFIG(2, A, H);               \
         FET_PIN_CONFIG(2, B, H);               \
         FET_PIN_CONFIG(2, C, H);               \
         FET_PIN_CONFIG(3, A, H);               \
         FET_PIN_CONFIG(3, B, H);               \
         FET_PIN_CONFIG(3, C, H);               \
         FET_PIN_CONFIG(4, A, H);               \
         FET_PIN_CONFIG(4, B, H);               \
         FET_PIN_CONFIG(4, C, H);               \
     } while(0)

void FET_Driver_Init(void);


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



