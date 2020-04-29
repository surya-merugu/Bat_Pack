/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_adc_init_callback.c
  * Origin Date           :   14/03/2020
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
#include "re_adc_int_callback.h"

extern ADC_HandleTypeDef hadc1_t;
extern uint16_t TamperData_Buffer[7];
extern uint16_t TemperatureData_Buffer[7];
extern uint8_t Temperature_Flag;
extern uint8_t Tamper_Flag;

uint16_t Bat_TamperSensor[4];
uint16_t Bat_Ext_TempSensor[3];



/**
 * @brief ADC conversion complete callback
 * this function handles the interupt callbacks of ADC
 * @param hadc1_t ADC handler typedef
 * @retval None
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(HAL_ADC_Stop_DMA(&hadc1_t) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    if(Temperature_Flag == 1)
    {
        Bat_Ext_TempSensor[0] = TemperatureData_Buffer[0];
        Bat_Ext_TempSensor[1] = TemperatureData_Buffer[1];
        Bat_Ext_TempSensor[2] = TemperatureData_Buffer[2];
        Temperature_Flag = 0;
    }
    else if(Tamper_Flag == 1)
    {
        Bat_TamperSensor[0]   = TamperData_Buffer[3];
        Bat_TamperSensor[1]   = TamperData_Buffer[4];
        Bat_TamperSensor[2]   = TamperData_Buffer[5];
        Bat_TamperSensor[3]   = TamperData_Buffer[6];
        for(uint8_t i=0; i<4; i++)
        {
            if(Bat_TamperSensor[i] > 0xABC)
            {
                //  RE_SendTamperMessage(Bat_TamperSensor[i]);
            }
        }
        Tamper_Flag = 0;
    }
    else 
    {
        __NOP();
    }
}
/************************ (C) COPYRIGHT RACEnergy **********END OF FILE********/