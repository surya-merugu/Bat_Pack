/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_app_can.h
  * Origin Date           :   dd/mm/yyyy
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
  * Written by Team RACEnergy, MONTH YEAR
  *****************************************************************************
  */

#ifndef __RE_APP_CAN_H
#define __RE_APP_CAN_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_can.h"
#include "re_std_def.h"
#include "soc_meter/re_app_soc.h"
#include "string.h"

RE_StatusTypeDef RE_CAN_SendBatInfo (uint8_t *pTxMsg);
RE_StatusTypeDef RE_SendTamperMessage(uint16_t Bat_TamperValue);
RE_StatusTypeDef RE_TransmitHighFreqData(void);
RE_StatusTypeDef RE_TransmitMidFreqData(void);
RE_StatusTypeDef RE_TransmitLowFreqData(void);

#endif

/***************************** END OF FILE ************************************/
