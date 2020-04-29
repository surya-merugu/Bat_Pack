/**
  *****************************************************************************
  * Title                 :   CONVERSION KIT
  * Filename              :   re_app_dock_latch.c
  * Origin Date           :   15/02/2020
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
  * Written by Team RACEnergy, FEB 2020
  *****************************************************************************
  */

/* Includes */
#include "latch/re_app_latch.h"

/**
 * @brief RE open latch
 * This function opens the dock
 * @param  None
 * @retval Exit Status
 */
RE_StatusTypeDef RE_OpenLatch(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
    HAL_Delay(1000);
    RE_CloseLatch();
    return RE_OK;
}

/**
 * @brief RE close latch
 * This function closes the dock
 * @param  None
 * @retval Exit Status
 */
RE_StatusTypeDef RE_CloseLatch(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
    return RE_OK;
}

/************************ (C) COPYRIGHT RACEnergy **********END OF FILE********/