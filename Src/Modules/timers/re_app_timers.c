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
#include "timers/re_app_timers.h"

extern DMA_HandleTypeDef hdma_adc1_t;
extern ADC_HandleTypeDef hadc1_t;

extern RE_StatusTypeDef RE_ReadTemperatureSensorData(void);
extern RE_StatusTypeDef RE_ReadTamperSensorData(void);

uint8_t TimeElapsedFlag = 0;
extern uint8_t HighFreqTxFlag;
extern uint8_t MidFreqTxFlag;

/* @brief RE Timer ISR
 * this function handles interrupts of timer
 * @param  None
 * @retval Exit Status
 */
RE_StatusTypeDef RE_Timer_ISR (void)
{
    TimeElapsedFlag++;
    RE_ReadTamperSensorData();
    RE_ReadTemperatureSensorData();
    if(TimeElapsedFlag == 3)
    {
       // RE_TransmitHighFreqData();
    }
    if(TimeElapsedFlag == 5 && HighFreqTxFlag == 1)
    {
      //  RE_TransmitMidFreqData();
    }
    if(TimeElapsedFlag == 7 && MidFreqTxFlag == 1)
    {
       // RE_TransmitLowFreqData();
        TimeElapsedFlag = 0;
    }
    if(TimeElapsedFlag > 8)
    {
        TimeElapsedFlag = 0;
    }
    return RE_OK;
}

/************************ (C) COPYRIGHT RACEnergy **********END OF FILE********/