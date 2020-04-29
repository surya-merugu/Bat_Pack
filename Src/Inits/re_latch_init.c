/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_latch_init.c
  * Origin Date           :   28/04/2020
  * Compiler              :   Specify compiler used
  * Hardware              :   Optocoupler Relay
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

/* Includes */
#include "re_latch_init.h"

/**
 * @brief  Latch GPIO Initialization
 * This function configures the GPIO pins used by  Latch
 * @param None
 * @retval Exit status
 */
RE_StatusTypeDef RE_Latch_GpioInit (void)
{
    GPIO_InitTypeDef LatchControl, Latchstatus_pin;
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**
    * PC1 : Latch status Pin
    * PC0 : Latch control Pin
    */

     LatchControl.Pin               = GPIO_PIN_0;
     LatchControl.Mode              = GPIO_MODE_OUTPUT_PP;
     LatchControl.Speed             = GPIO_SPEED_FAST;
     LatchControl.Pull              = GPIO_NOPULL;
     HAL_GPIO_Init(GPIOC, &LatchControl);

     Latchstatus_pin.Pin         = GPIO_PIN_1 ;
     Latchstatus_pin.Mode        = GPIO_MODE_INPUT;
     Latchstatus_pin.Speed       = GPIO_SPEED_FAST;
     Latchstatus_pin.Pull        = GPIO_PULLDOWN;
     HAL_GPIO_Init(GPIOC, &Latchstatus_pin);

     return RE_OK;
}

