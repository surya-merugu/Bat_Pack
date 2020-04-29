/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_app_eeprom.h
  * Origin Date           :   20/04/2020
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

#ifndef __RE_APP_EEPROM_H
#define __RE_APP_EEPROM_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "re_std_def.h"
#include "stdbool.h"
    
typedef struct __attribute__((packed))
{
    uint32_t FW_Version_Info;
    uint32_t Can_ID;
    uint32_t Physical_ID;
    bool G2G;
    bool Charge_FET_Status;
    bool Discharge_FET_Status;
    bool Alert_Flag;
    bool Bat_err;
    bool Soc_err;
    bool CAN_err;
    bool Tamper_err;
    bool Temp_err;
    bool Latch_err;
    bool FET_err;
}System_Config_t;

RE_StatusTypeDef RE_NVS_LoadSysConfig(void);

#endif 
/***************************** END OF FILE ************************************/
