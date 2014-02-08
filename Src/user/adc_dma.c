/* Includes ------------------------------------------------------------------*/
#include "adc_dma.h"
#include "fet_driver.h"
/** @addtogroup Utilities
 * @{
 */ 

/** @addtogroup STM32F4_DISCOVERY
 * @{
 */ 

/** @addtogroup STM32F4_DISCOVERY_CC2540
 * @{
 */


/** @defgroup STM32F4_DISCOVERY_CC2540_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup STM32F4_DISCOVERY_CC2540_Private_Defines
 * @{
 */

/**
 * @}
 */

/** @defgroup STM32F4_DISCOVERY_CC2540_Private_Macros
 * @{
 */

/**
 * @}
 */ 
  
/** @defgroup STM32F4_DISCOVERY_CC2540_Private_Variables
 * @{
 */ 

/**
 * @}
 */

/** @defgroup STM32F4_DISCOVERY_CC2540_Private_FunctionPrototypes
 * @{
 */
static void ADC_DMA_LowLevel_Init(void);
static void DMA_Config(void);
static void ADC_Config(void);
#define ADC_BUF_SIZE (ADC_CHANNEL_NUM * 3)
__ALIGN_END ;
uint16_t adcBuf[2][ADC_BUF_SIZE];
uint32_t *pAdcBuf;

volatile uint8_t state_2;
volatile uint8_t step_2;
volatile uint8_t l_side_state_2;
volatile uint8_t h_side_state_2;
volatile uint32_t abs_base_time;
volatile uint32_t half_zc_period;
volatile uint32_t pulse_width;
volatile uint8_t running_state;
volatile uint32_t start_counter;

volatile uint32_t previous_zc_time;
volatile uint32_t current_zc_time;
volatile uint32_t next_detect_time;
volatile uint32_t previous_valid_A;
volatile uint32_t previous_valid_B;
volatile uint32_t previous_valid_C;
volatile uint32_t previous_valid_T;


/**
 * @}
 */

/** @defgroup STM32F4_DISCOVERY_CC2540_Private_Functions
 * @{
 */


/**
 * @brief  Set ADC DMA Initialization.
 * @param  None
 * @retval None
 */
void ADC_DMA_Init()
{
    /* Configure the low level interface ---------------------------------------*/
    ADC_DMA_LowLevel_Init();
    DMA_Config();
    ADC_Config();


    next_detect_time = 0;
    state_2 = 1;
    l_side_state_2 = 0;
    h_side_state_2 = 0;
    abs_base_time = 0;
    running_state = 0;
    start_counter = 0;
    previous_valid_T = 0xFFFFFFFF;                                      
    
    TIM3->CCR1 = 0xffff;
    TIM3->CCR2 = 0xffff;
    TIM4->CCR1 = 0xffff;
    
    TIM_Cmd(TIM3, ENABLE);    
    TIM_Cmd(TIM4, ENABLE);    
    TIM_Cmd(TIM10, ENABLE);    

    ADC_SoftwareStartConv(ADC1);
}

static void DMA_Config()
{
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;  

    /* Enable the ADC gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


    /* DMA2 Stream0 channel0 configuration */
    DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC_CDR_ADDRESS;
//    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)adcBuf;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = ADC_BUF_SIZE;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);

    DMA_MemoryTargetConfig(DMA2_Stream0, adcBuf[0], DMA_Memory_0);
    DMA_MemoryTargetConfig(DMA2_Stream0, adcBuf[1], DMA_Memory_1);
    DMA_DoubleBufferModeCmd(DMA2_Stream0, ENABLE);

    DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);

    /* DMA2_Stream0 enable */
    DMA_Cmd(DMA2_Stream0, ENABLE);
}

static void ADC_Config(void) 
{
    int i;
    
    ADC_InitTypeDef       ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;



    /* ADC Common configuration *************************************************/
    ADC_CommonInitStructure.ADC_Mode = ADC_TripleMode_RegSimult;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;  
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2; /* 60MHz / 2 = 30MHz */
    ADC_CommonInit(&ADC_CommonInitStructure);

    /* ADC1 regular channel 8 configuration ************************************/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = ADC_CHANNEL_NUM;

    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_Init(ADC2, &ADC_InitStructure);
    ADC_Init(ADC3, &ADC_InitStructure);

    for (i = 0; i < ADC_CHANNEL_NUM; i++) {
        ADC_RegularChannelConfig(ADC1, adcOrder[0][i], i + 1, ADC_SampleTime_3Cycles);      
        ADC_RegularChannelConfig(ADC2, adcOrder[1][i], i + 1, ADC_SampleTime_3Cycles);      
        ADC_RegularChannelConfig(ADC3, adcOrder[2][i], i + 1, ADC_SampleTime_3Cycles);      
    }
    /* Enable VBAT sensing */
    ADC_VBATCmd(ENABLE);
    
    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);

    /* Enable DMA request after last transfer (multi-ADC mode) ******************/
    ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);

    //ADC_ITConfig(ADC2, ADC_IT_EOC, ENABLE);

    /* Enable ADC1, 2, 3*********************************************************/
    ADC_VBATCmd(ENABLE);
    ADC_Cmd(ADC1, ENABLE);
    ADC_Cmd(ADC2, ENABLE);
    ADC_Cmd(ADC3, ENABLE);
}


/**
 * @brief  Initializes the low level interface used to drive the ADC DMA
 * @param  None
 * @retval None
 */
static void ADC_DMA_LowLevel_Init(void)
{

    GPIO_InitTypeDef      GPIO_InitStructure;
    int i;
    
    ADC_DMACmd(ADC1, DISABLE);
    ADC_Cmd(ADC1, DISABLE);
    ADC_Cmd(ADC2, DISABLE);
    ADC_Cmd(ADC3, DISABLE);
    DMA_Cmd(DMA2_Stream0, DISABLE);
    /* Enable peripheral clocks */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA |
                           RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, 
                           ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2| RCC_APB2Periph_ADC3, ENABLE);


    for (i = 0; i < ADC_PIN_NUM; i++) {
        GPIO_InitStructure.GPIO_Pin = adcPin[i].pin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
        GPIO_Init(adcPin[i].port, &GPIO_InitStructure);
    }
}
extern uint16_t VCP_DataTx (uint8_t* Buf, uint32_t Len);
uint8_t buf[32];



void to_hex8(uint8_t *src, uint8_t *dst, uint16_t len) 
{
    uint16_t i;
    uint8_t tmp;
    
    for(i = 0; i < len; i++) {
        tmp = (src[i] >> 4) & 0x0F;
        if (tmp < 0x0a) {
            dst[i * 2 + 0] = 0x30 + tmp;
        } else {
            dst[i * 2 + 0] = 'A' + tmp - 0x0a;
        }
        tmp = (src[i] >> 0) & 0x0F;
        if (tmp < 0x0a) {
            dst[i * 2 + 1] = 0x30 + tmp;
        } else {
            dst[i * 2 + 1] = 'A' + tmp - 0x0a;
        }
    }
}



uint8_t zc_found;

#define INT32_TIME_FRAC		8
#define UNIT_TO_TIME(x)		((uint32_t)(x) << (INT32_TIME_FRAC))
#define TIME_TO_UNIT(x)		((uint32_t)(x) >> (INT32_TIME_FRAC))
#define ZC_FOUND do{                                                    \
    half_zc_period = (6 * half_zc_period + current_zc_time - previous_zc_time) >> 3; \
    next_detect_time = abs_base_time + half_zc_period + UNIT_TO_TIME(16);                  \
    TIM10->CCR1 = TIME_TO_UNIT(current_zc_time + half_zc_period);       \
    previous_valid_T = 0xFFFFFFFF;                                      \
    step_2 = state_2;                                                   \
    state_2++;                                                      \
if (state_2 > 6) state_2 = 1;                                   \
if (state_2 % 2 == 0) L_ON(3, A);                               \
else L_OFF(3, A);                                              \
} while(0)

#define TIME_LESS_THEN(x, y)	(((x) - (y)) > 0x80000000)
    

    
void zero_crossing_detector(uint32_t A, uint32_t B, uint32_t C, uint32_t V)
{

    if(start_counter >= 500000) {
        TIM3->CCR1 = 1;
        TIM4->CCR1 = 1;
        TIM3->CCR2 = 1;
        L_OFF(2, A);
        L_OFF(2, B);
        L_OFF(2, C);
        return;
    }
    start_counter++;    
            
    if (TIME_LESS_THEN(abs_base_time, next_detect_time)) return;
    if (TIME_LESS_THEN(next_detect_time + half_zc_period * 8, abs_base_time)) {
        previous_zc_time = current_zc_time;
        current_zc_time = abs_base_time;                    
        ZC_FOUND;
        L_OFF(3, A); 
        return;
    }
    switch(state_2) {
    case 1:
        if(A > ((V * 3) >> 2)) {
            if((C << 1) < A) {
                previous_zc_time = current_zc_time;
                if (previous_valid_T != 0xFFFFFFFF) {
                    current_zc_time = (abs_base_time - previous_valid_T) / 2 + abs_base_time;
                } else {
                    current_zc_time = abs_base_time;                    
                }
                ZC_FOUND;
            } else {
                previous_valid_A = A;
                previous_valid_C = C;
                previous_valid_T = abs_base_time;
            }
        }
        break;
    case 2:
        if(A > ((V * 3) >> 2)) {
            if((B << 1) > A) {
                previous_zc_time = current_zc_time;
                if (previous_valid_T != 0xFFFFFFFF) {
                    current_zc_time = (abs_base_time - previous_valid_T) / 2 + abs_base_time;
                } else {
                    current_zc_time = abs_base_time;                    
                }
                ZC_FOUND;
            } else {
                previous_valid_A = A;
                previous_valid_B = B;
                previous_valid_T = abs_base_time;
            }
        }
        break;
    case 3:
        if(B > ((V * 3) >> 2)) {
            if((A << 1) < B) {
                previous_zc_time = current_zc_time;
                if (previous_valid_T != 0xFFFFFFFF) {
                    current_zc_time = (abs_base_time - previous_valid_T) / 2 + abs_base_time;
                } else {
                    current_zc_time = abs_base_time;                    
                }
                ZC_FOUND;
            } else {
                previous_valid_A = A;
                previous_valid_B = B;
                previous_valid_T = abs_base_time;
            }
        }
        break;
    case 4:
        if(B > ((V * 3) >> 2)) {
            if((C << 1) > B) {
                previous_zc_time = current_zc_time;
                if (previous_valid_T != 0xFFFFFFFF) {
                    current_zc_time = (abs_base_time - previous_valid_T) / 2 + abs_base_time;
                } else {
                    current_zc_time = abs_base_time;                    
                }
                ZC_FOUND;
            } else {
                previous_valid_B = B;
                previous_valid_C = C;
                previous_valid_T = abs_base_time;
            }
        }
        break;
    case 5:
        if(C > ((V * 3) >> 2)) {
            if((B << 1) < C) {
                previous_zc_time = current_zc_time;
                if (previous_valid_T != 0xFFFFFFFF) {
                    current_zc_time = (abs_base_time - previous_valid_T) / 2 + abs_base_time;
                } else {
                    current_zc_time = abs_base_time;                    
                }
                ZC_FOUND;
            } else {
                previous_valid_B = B;
                previous_valid_C = C;
                previous_valid_T = abs_base_time;
            }
        }
        break;
    case 6:
        if(C > ((V * 3) >> 2)) {
            if((A << 1) > C) {
                previous_zc_time = current_zc_time;
                if (previous_valid_T != 0xFFFFFFFF) {
                    current_zc_time = (abs_base_time - previous_valid_T) / 2 + abs_base_time;
                } else {
                    current_zc_time = abs_base_time;                    
                }
                ZC_FOUND;
            } else {
                previous_valid_A = A;
                previous_valid_C = C;
                previous_valid_T = abs_base_time;
            }
        }
        break;
    }
}

void DMA2_Stream0_IRQHandler() 
{
    uint16_t* pBuf;

#define RESERVED_MASK (uint32_t)0x0F7D0F7D
    if (DMA2->LISR & RESERVED_MASK & DMA_IT_TCIF0) {
        DMA2->LIFCR = (uint32_t) ( RESERVED_MASK & DMA_IT_TCIF0);

        if(running_state == 0) {
            half_zc_period = UNIT_TO_TIME(2000);
            pulse_width = 600;
            abs_base_time += UNIT_TO_TIME(8);         /* unit is 3/4us, 6us is 8 */
            /* if (DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0) != RESET) { */
            /*     DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0); */
            TIM3->CCR1 = pulse_width;
            TIM4->CCR1 = pulse_width;
            TIM3->CCR2 = pulse_width;

    
            if (TIME_LESS_THEN(next_detect_time, abs_base_time)) {
                step_2 = state_2;
                state_2++;
                if (state_2 > 6) {
                    state_2 = 1;
                    start_counter++;
                }
                if (start_counter > 4) {
                    running_state = 1;
                    start_counter = 0;
                    half_zc_period = UNIT_TO_TIME(2000);
                }
                previous_zc_time = current_zc_time;
                current_zc_time = abs_base_time;
                next_detect_time = abs_base_time + half_zc_period * 2;
                TIM10->CCR1 = TIME_TO_UNIT(abs_base_time + half_zc_period);
            }
            
        } else {
            pBuf = adcBuf[!DMA_GetCurrentMemoryTarget(DMA2_Stream0)];
            abs_base_time += UNIT_TO_TIME(4);         /* unit is 3/4us, 3us is 4 */
            zero_crossing_detector(pBuf[9], pBuf[11], pBuf[10], pBuf[12] << 1);
            abs_base_time += UNIT_TO_TIME(4);         /* unit is 3/4us, 3us is 4 */
            zero_crossing_detector(pBuf[9 + 18], pBuf[11 + 18], pBuf[10 + 18], pBuf[12 + 18] << 1);
        }
        
        /* if (i % 1000000 == 0) { */
        /*     to_hex8((uint8_t *)(adcBuf
        /*     VCP_DataTx((uint8_t *)buf, 144); */
        /*     buf[0] = '\r'; */
        /*     buf[1] = '\n'; */
        /*     VCP_DataTx((uint8_t *)buf, 2); */
        /* } */
        /* pAdcBuf += ADC_CHANNEL_NUM * 3; */
        /* if (pAdcBuf >= (adcBuf + ADC_BUF_SIZE)) { */
        /*     pAdcBuf = adcBuf; */
        /* } */
    }
}



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
  


