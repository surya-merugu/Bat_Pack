/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   main.c
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
/* Includes ------------------------------------------------------------------*/
#include "main/main.h"

extern TIM_HandleTypeDef htim2_t;
extern uint8_t TimerFlag;
System_Config_t System_Config;

RE_StatusTypeDef RE_SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
      HAL_Init();
      RE_SystemClock_Config();
      RE_SoC_I2C1_Init();
      RE_NVS_I2C2_Init();
      RE_SoC_GetCanID();
      RE_ADC1_Init();
      RE_DMA_Init();
      RE_CAN1_Init();
      RE_CAN1_Filter_Config();
      RE_CAN1_Start_Interrupt();
      //RE_NVS_LoadSysConfig();
      RE_Latch_GpioInit ();
      RE_TIMER2_Init();
      if(HAL_TIM_Base_Start_IT(&htim2_t) != HAL_OK)
      {
          RE_Error_Handler(__FILE__, __LINE__);
      }
      while (1)
      {
            if(TimerFlag == 1)
            {
                RE_Timer_ISR ();
                TimerFlag = 0;
            }
      }
      return 0;
}

/***************************** END OF FILE ************************************/