/* Includes ------------------------------------------------------------------*/
#include "adc_dma.h"
#include "fet_driver.h"
#include "motor.h"
#include "shell.h"
static void ADC_DMA_LowLevel_Init(void);
static void DMA_Config(void);
static void ADC_Config(void);
#define ADC_CHANNEL_NUM 12
#define ADC_BUF_SIZE (ADC_CHANNEL_NUM * 3)

uint16_t adcBuf[2][ADC_BUF_SIZE] __attribute__ ((aligned(4)));


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

ADC_Pin_TypeDef adcPin[ADC_PIN_NUM] = {
    {GPIOA, GPIO_Pin_0},
    {GPIOA, GPIO_Pin_1},
    {GPIOA, GPIO_Pin_2},
    {GPIOA, GPIO_Pin_3},
    {GPIOA, GPIO_Pin_4},
    {GPIOA, GPIO_Pin_5},
    {GPIOA, GPIO_Pin_6},
    {GPIOA, GPIO_Pin_7},
    {GPIOB, GPIO_Pin_0},
    {GPIOB, GPIO_Pin_1},
    {GPIOC, GPIO_Pin_0},
    {GPIOC, GPIO_Pin_1},
    {GPIOC, GPIO_Pin_2},
    {GPIOC, GPIO_Pin_3},
    {GPIOC, GPIO_Pin_4},
    {GPIOC, GPIO_Pin_5}
};
    

/* volatile uint8_t state_2; */
/* volatile uint8_t step_2; */
 volatile uint32_t abs_base_time; 
/* volatile uint32_t half_zc_period; */
/* volatile uint32_t pulse_width; */
/* volatile uint8_t running_state; */
/* volatile uint32_t start_counter; */

/* volatile uint32_t previous_zc_time; */
/* volatile uint32_t current_zc_time; */
/* volatile uint32_t next_detect_time; */
/* volatile uint32_t previous_valid_A; */
/* volatile uint32_t previous_valid_B; */
/* volatile uint32_t previous_valid_C; */
/* volatile uint32_t previous_valid_T; */


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

    abs_base_time = 0;
    /* next_detect_time = 0; */
    /* state_2 = 1; */
    /* abs_base_time = 0; */
    /* running_state = 0; */
    /* start_counter = 0; */
    /* previous_valid_T = 0xFFFFFFFF;                                       */
    
    /* TIM3->CCR1 = 0xffff; */
    /* TIM3->CCR2 = 0xffff; */
    /* TIM4->CCR1 = 0xffff; */
    
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
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
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


void DMA2_Stream0_IRQHandler() 
{
    uint16_t* pBuf;
    int i;
    static int j;
    
#define RESERVED_MASK (uint32_t)0x0F7D0F7D
    if (DMA2->LISR & RESERVED_MASK & DMA_IT_TCIF0) {
        DMA2->LIFCR = (uint32_t) ( RESERVED_MASK & DMA_IT_TCIF0);
        pBuf = adcBuf[(DMA2_Stream0->CR & DMA_SxCR_CT) == 0];

        j++;
        if ((j % (4096 * 4)) == 1) {
            for (i = 0; i < 18; i++) {
                printf("%lu\t", pBuf[i]);
            }
            pBuf += 18;
            for (i = 0; i < 18; i++) {
                printf("%lu\t", pBuf[i]);
            }
            printf("\r\n");
        }

        
#if 0
//        pBuf = adcBuf[!DMA_GetCurrentMemoryTarget(DMA2_Stream0)];
        motor_zero_cross_detect(&(motor[M1_IDX]), pBuf, abs_base_time);
        abs_base_time += TICKS_TO_UNIT(4);
        motor_zero_cross_detect(&(motor[M3_IDX]), pBuf, abs_base_time);
        abs_base_time += TICKS_TO_UNIT(2);
        motor_zero_cross_detect(&(motor[M2_IDX]), pBuf, abs_base_time);
        abs_base_time += TICKS_TO_UNIT(4);
        motor_zero_cross_detect(&(motor[M4_IDX]), pBuf, abs_base_time);
        abs_base_time += TICKS_TO_UNIT(2);
        pBuf += 18;
        motor_zero_cross_detect(&(motor[M1_IDX]), pBuf, abs_base_time);
        abs_base_time += TICKS_TO_UNIT(4);
        motor_zero_cross_detect(&(motor[M3_IDX]), pBuf, abs_base_time);
        abs_base_time += TICKS_TO_UNIT(2);
        motor_zero_cross_detect(&(motor[M2_IDX]), pBuf, abs_base_time);
        abs_base_time += TICKS_TO_UNIT(4);
        motor_zero_cross_detect(&(motor[M4_IDX]), pBuf, abs_base_time);
        abs_base_time += TICKS_TO_UNIT(2);
#endif
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
  


