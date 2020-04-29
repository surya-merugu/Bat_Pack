/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_app_eeprom.c
  * Origin Date           :   20/04/2020
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
#include "eeprom/re_app_eeprom.h"

#define EEPROM_ADDRESS 0xA0

extern System_Config_t System_Config;
extern I2C_HandleTypeDef hi2c2_t;

extern void RE_NVS_ReadStruct(uint16_t Address, System_Config_t *pSystem_Config);

System_Config_t *pSystem_Config;
uint8_t I2C_StructReceiveBuffer[sizeof(System_Config_t)];



RE_StatusTypeDef RE_NVS_LoadSysConfig(void)
{
    RE_NVS_ReadStruct (0x00, &System_Config);
    pSystem_Config = (System_Config_t *)(I2C_StructReceiveBuffer);
    return RE_OK;
}

/************************ (C) COPYRIGHT RACEnergy **********END OF FILE********/