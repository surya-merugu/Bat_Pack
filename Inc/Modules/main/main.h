/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   main.h
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

#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f4xx_hal.h"
#include "eeprom/re_app_eeprom.h"
#include "bms/re_app_bms.h"
#include "can/re_app_can.h"
#include "latch/re_app_latch.h"
#include "rcps/re_app_rcps.h"
#include "soc_meter/re_app_soc.h"
#include "tamper/re_app_tamper.h"
#include "temperature/re_app_temperature.h"
#include "timers/re_app_timers.h"
#include "re_std_def.h"
#include "re_sys_clk_config.h"
#include "stm32f4xx_it.h"
#include "re_adc_init.h"
#include "re_can_init.h"
#include "re_i2c_init.h"
#include "re_timer_init.h"
#include "re_latch_init.h"

#endif /* __MAIN_H */

/***************************** END OF FILE ************************************/
