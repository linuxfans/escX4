/**
  ******************************************************************************
  * @file    bsp.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-September-2012
  * @brief   This file provides targets hardware configuration 
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
#include "bsp.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
* @brief  Inititialize the target hardware.
* @param  None
* @retval None
*/
uint32_t BSP_Init (void)
{


//  CONSOLE_LOG((uint8_t *)"[SYSTEM] Data RAM Init : OK.");
  /* Initialize the LCD */
//  GL_LCD_Init();
//  CONSOLE_LOG((uint8_t *)"[SYSTEM] LCD Init : OK.");
  /* Initialize the TSC */
//  GL_TSC_Init();
//  CONSOLE_LOG((uint8_t *)"[SYSTEM] Touchscreen Init : OK.");
  /* Initialize the Joystick */
//  GL_JOY_Init();
//  CONSOLE_LOG((uint8_t *)"[SYSTEM] Joystick Init : OK.");
  /* Initialize the PSRAM */
//  SRAM_Init();
//  CONSOLE_LOG((uint8_t *)"[SYSTEM] SRAM Init: OK.");

/*   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_BKPSRAM, ENABLE); */
/* //  CONSOLE_LOG((uint8_t *)"[SYSTEM] BKPSRAM Init : OK."); */

/*   SYSCFG_CompensationCellCmd(ENABLE); */

/*   /\* Enable RNG clock source *\/ */
/*   RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE); */

/*   /\* RNG Peripheral enable *\/ */
/*   RNG_Cmd(ENABLE); */
  /* Initialize the LEDs */


  return 0;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
