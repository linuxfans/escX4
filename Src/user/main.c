/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-September-2012
  * @brief   This file provides main program functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
//#include "gl_mgr.h"
#include "global_includes.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_core.h"
#include "fet_driver.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//const uint32_t test[4096*32] = {0xff};


void vApplicationMallocFailedHook( void )
{
    return;
}

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
 
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;


extern uint16_t VCP_DataTx (uint8_t* Buf, uint32_t Len);

int main(void)
{
    uint8_t buf[10] = "abcdefg";
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    FET_Driver_Init();
    
    
    // high side N-FET is inactive low
    /* FET_A_H_OFF; */
    /* FET_B_H_OFF; */
    /* FET_C_H_OFF; */
  

    // low side N-FET is inactive low
    /* FET_A_L_OFF; */
    /* FET_B_L_OFF; */
    /* FET_C_L_OFF; */
    L_ALL_OFF(1);
    L_ALL_OFF(2);
    L_ALL_OFF(3);
    L_ALL_OFF(4);

    H_ALL_OFF(1);
    H_ALL_OFF(2);
    H_ALL_OFF(3);
    H_ALL_OFF(4);
    

    /* USBD_Init(&USB_OTG_dev, */
    /*           USB_OTG_FS_CORE_ID, */
    /*           &USR_desc,  */
    /*           &DFU_cb,  */
    /*           &USR_cb); */
    //test();
    USBD_Init(&USB_OTG_dev,
              USB_OTG_FS_CORE_ID,
              &USR_desc,
              &USBD_CDC_cb,
              &USR_cb);

    ADC_DMA_Init();


    for (;;) {
        /* Test on DMA1 channel1 transfer complete flag */
        while(!DMA_GetFlagStatus(DMA2_Stream0, DMA_FLAG_TCIF0));
        /* Clear DMA1 channel1 transfer complete flag */
        DMA_ClearFlag(DMA2_Stream0, DMA_FLAG_TCIF0);

//        VCP_DataTx(buf, 4);
    }
  

          
  
//  test();
  
}

void uDelay(const uint32_t usec) 
{
    USB_OTG_BSP_uDelay(usec * 2);
}
void mDelay(const uint32_t msec) 
{
    uDelay(msec * 1000);
}
uint32_t freq_tab[9] = {256, 288, 320, 341, 384, 427, 480, 512
};

void fetBeep(const uint32_t freq, const uint32_t msec)
{
    uint32_t delay;
    uint32_t cycle;
    uint32_t i;
    delay = 1000000 / freq - 20; 
    cycle = msec * 1000 / delay;
//    FET_C_L_ON;    
    L_ON(2, C);
    for (i = 0; i < cycle; i++) {
//        FET_A_H_ON;
        H_ON(2, A);
        uDelay (20);
        H_OFF(2, A);
//        FET_A_H_OFF;
        uDelay (delay);
    }
    L_OFF(2, C);
//    FET_C_L_OFF;    

}

uint32_t play(const uint32_t buf[], const uint32_t len) 
{
    for (int i = 0; i < len; i++) {
        fetBeep(freq_tab[buf[i]], 500);
        mDelay(10);
    }
}



void test() 
{
    uint32_t buf[16] = {1, 2, 3, 1, 1, 2, 3, 1, 3, 4, 5, 5, 3, 4, 5, 5};
    play(buf, 16);
    /* fetBeep(1000, 500); */
    /* mDelay(1000); */
    /* fetBeep(2000, 500); */
    /* mDelay(1000); */
    /* fetBeep(3000, 500); */
    /* mDelay(1000); */
    
    while(1);
}


/**
  * @brief  Background task
  * @param  pvParameters not used
  * @retval None
  */


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
