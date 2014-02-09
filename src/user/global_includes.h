/**
  ******************************************************************************
  * @file    global_includes.h 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-September-2012
  * @brief   general includes for all the project files
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
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GLOBAL_INCLUDES_H__
#define __GLOBAL_INCLUDES_H__

/* Includes ------------------------------------------------------------------*/
#include "global_conf.h"
#if defined (STM32F2XX)
 #include "stm32f2xx.h"
 #include "stm322xg_eval.h"
 #include "stm322xg_eval_lcd.h"
 #include "stm322xg_eval_ioe.h"
 #include "stm322xg_eval_fsmc_sram.h"
 #include "stm322xg_eval_sdio_sd.h"
 #include "stm32f2x7_eth.h"
 #include "stm32f2xx_usart.h"

#elif defined (STM32F4XX)
 #include "stm32f4xx.h"
 #include "stm32f4xx_usart.h"
#endif
/* Exported types ------------------------------------------------------------*/
typedef union _SYSTEM_CONFIG_TypeDef
{
  uint32_t d32;
  struct
  {
    uint32_t DistantControlEnabled :
      1;
    uint32_t BackgroundModeEnabled :
      1;
    uint32_t LowPowerModeEnabled :
      1;
    uint32_t LCDPowerSavingEnabled :
      1;
    uint32_t Configuration_Changed :
      1;   
    uint32_t Force_Background_Refresh :
      1;       
    uint32_t Reserved :
      26;
  }
  b;
} SYSTEM_CONFIG_TypeDef ;  
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >>8)) 
/* Exported types ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __GLOBAL_INCLUDES_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

