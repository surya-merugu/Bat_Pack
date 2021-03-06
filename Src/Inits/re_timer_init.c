/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_timer_init.c
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

/* Includes */
#include "re_timer_init.h"

TIM_HandleTypeDef htim2_t;

/**
 * @brief Timer Base Init
 * This function configures clock and set priority for the timer
 * @param  htim3_t: timer handle typedef
 * @retval Exit status
 */
void HAL_TIM_Base_MspInit (TIM_HandleTypeDef* htim_base)
{   
    __HAL_RCC_TIM2_CLK_ENABLE();
    if(htim_base->Instance == TIM2)
    { 
        HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
}

/**
 * @brief Timer Initialization
 * This function configures the internal timer
 * @param  void
 * @retval Exit status
 */
RE_StatusTypeDef RE_TIMER2_Init (void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;
    htim2_t.Instance                             = TIM2;
    htim2_t.Init.Prescaler                       = 41999;
    htim2_t.Init.CounterMode                     = TIM_COUNTERMODE_UP;
    htim2_t.Init.Period                          = 6000;
    htim2_t.Init.ClockDivision                   = TIM_CLOCKDIVISION_DIV1;
    htim2_t.Init.AutoReloadPreload               = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2_t) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }

    sClockSourceConfig.ClockSource             = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&htim2_t, &sClockSourceConfig);

    sMasterConfig.MasterOutputTrigger          = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode              = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2_t, &sMasterConfig) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    return RE_OK;
}
/************************ (C) COPYRIGHT RACEnergy **********END OF FILE********/
