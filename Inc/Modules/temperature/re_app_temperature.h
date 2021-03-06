/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_app_temperature.h
  * Origin Date           :   16/04/2020
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

#ifndef __RE_APP_TEMPERATURE_H
#define __RE_APP_TEMPERATURE_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"
#include "re_std_def.h"

RE_StatusTypeDef RE_Read_TemperatureSensor_Data(void);

#endif 

/***************************** END OF FILE ************************************/
