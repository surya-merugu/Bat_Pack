/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_timer_init.h
  * Origin Date           :   13/04/2020
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
#ifndef _RE_TIMER_INIT_H
#define _RE_TIMER_INIT_H

/* Includes */
#include "re_std_def.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_it.h"

extern TIM_HandleTypeDef htim2_t;

/* Exported API */
RE_StatusTypeDef RE_TIMER2_Init(void);

#endif
/**************************** END OF FILE *************************************/