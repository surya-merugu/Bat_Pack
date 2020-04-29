/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_dma_init.h
  * Origin Date           :   14/04/2020
  * Compiler              :   Specify compiler used
  * Hardware              :   None
  * Target                :   STM32F407-DISCOVERY
  * Notes                 :   None
  *****************************************************************************
  * @attention
  *
  * <h2><center>&copy;Copyright (C) RACEnergy, Inc - All Rights Reserved.
  * </center></h2>
  *
  * Unauthorized copying of this file, via any medium is strictly prohibited
  * Proprietary and confidential
  *
  * Written by Team RACEnergy, APR 2020
  *****************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _RE_DMA_INIT_H
#define _RE_DMA_INIT_H

/* Includes */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "re_std_def.h"
   
extern DMA_HandleTypeDef hdma_adc1_t;

/* Exported API's */
RE_StatusTypeDef RE_DMA_Init(void);

#endif

/**************************** END OF FILE *************************************/
