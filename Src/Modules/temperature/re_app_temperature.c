/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_app_int_timer.c
  * Origin Date           :   14/04/2020
  * Compiler              :   Specify compiler used
  * Hardware              :   None
  * Target                :   STM32F407-DISC
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
#include "temperature/re_app_temperature.h"

extern DMA_HandleTypeDef hdma_adc1_t;
extern ADC_HandleTypeDef hadc1_t;
uint16_t TemperatureData_Buffer[7];
uint8_t Temperature_Flag;
/* @brief RE Timer ISR
 * this function handles interrupts of timer
 * @param  None
 * @retval Exit Status
 */
RE_StatusTypeDef RE_ReadTemperatureSensorData (void)
{
    Temperature_Flag = 1;
    if(HAL_ADC_Start_DMA(&hadc1_t, (uint32_t *)TemperatureData_Buffer, sizeof(TemperatureData_Buffer)) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    return RE_OK;
}

/************************ (C) COPYRIGHT RACEnergy **********END OF FILE********/