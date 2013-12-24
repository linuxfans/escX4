/**
  ******************************************************************************
  * @file    global_conf.h
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-September-2012
  * @brief   Global configuration file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied
  * See the License for the specific language governing permissions and
  * limitations under the License
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GLOBAL_CONF__H__
#define __GLOBAL_CONF__H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Global Demo Parameter */

#if defined (STM32F2XX)
 #define DEMO_REV                     "1.0.1"
 #define DEMO_BOARD                   "Board : STM322xG-EVAL"
 #define DEMO_CORE                    "Core : Cortex-M3"
 #define DEMO_DEVICE                  "Device: STM32F207"
 #define DEMO_CPU_SPEED               "CPU Speed: 120 MHz"
 #define DEMO_MEMORY_RESOURCE         "Flash : 1MB / RAM : 128 KB"
#elif defined (STM32F4XX)
 #define DEMO_REV                     "1.0.1"
 #define DEMO_BOARD                   "Board : STM324xG-EVAL"
 #define DEMO_CORE                    "Core : Cortex-M4F"
 #define DEMO_DEVICE                  "Device: STM32F407"
 #define DEMO_CPU_SPEED               "CPU Speed: 168 MHz"
 #define DEMO_MEMORY_RESOURCE         "Flash : 1MB / RAM : 128 + 64 KB"
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __GLOBAL_CONF__H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
