/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_std_def.h
  * Origin Date           :   13/04/2020
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _RE_STD_DEF_H
#define _RE_STD_DEF_H

/* Includes */
#include <stdint.h>
#include "stdio.h"
/**
  * @brief  Application Status structures definition
  */
typedef enum
{
    RE_OK      = 0x00U,
    RE_ERROR   = 0x01U,
    RE_BUSY    = 0x02U,
    RE_TIMEOUT = 0x03U
} RE_StatusTypeDef;

void RE_Error_Handler (const char* pfile, uint16_t line);
#endif

/***************************** END OF FILE ************************************/

