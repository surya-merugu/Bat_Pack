/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_app_can.c
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
#include "can/re_app_can.h"

extern uint32_t CAN_BaseID;
extern CAN_TxHeaderTypeDef TxHeader;
extern CAN_HandleTypeDef hcan1_t;
extern HighFreqData_t HighFreqData;
extern MidFreqData_t MidFreqData;
extern LowFreqData_t LowFreqData;

extern uint32_t offset;
extern uint8_t DataLen;
extern uint16_t Bat_TamperSensor[4];

#if 0
RE_StatusTypeDef RE_CAN_SendBatInfo (uint8_t *pTxMsg)
{
      uint32_t TxMailbox;
      TxHeader.DLC   = DataLen;//sizeof(pTxMsg);
       
      /* Uncomment the required ext.id */
      TxHeader.ExtId = CAN_BaseID + offset;
      TxHeader.IDE   = CAN_ID_EXT;
      TxHeader.RTR   = CAN_RTR_DATA;

      if (HAL_CAN_AddTxMessage(&hcan1_t,&TxHeader,pTxMsg,&TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }  
      return RE_OK;
}
#endif

RE_StatusTypeDef RE_SendTamperMessage(uint16_t Bat_TamperValue)
{
      uint32_t TxMailbox;
      TxHeader.DLC   = 2;
      TxHeader.ExtId = 0xABC;
      TxHeader.IDE   = CAN_ID_EXT;
      TxHeader.RTR   = CAN_RTR_DATA;
    
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)Bat_TamperValue, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }  
      return RE_OK;    
}

RE_StatusTypeDef RE_TransmitHighFreqData(void)
{
      uint16_t HighFreq_MsgID; 
      uint16_t HighFreqData_Buffer[4];
      uint32_t TxMailbox;
      TxHeader.ExtId = 0xABC;
      TxHeader.IDE   = CAN_ID_EXT;
      TxHeader.RTR   = CAN_RTR_DATA;
      
      TxHeader.DLC           = 8;
      HighFreq_MsgID         = 101;
      HighFreqData_Buffer[0] = HighFreq_MsgID;
      HighFreqData_Buffer[1] = HighFreqData.Bat_SoC;
      HighFreqData_Buffer[2] = HighFreqData.Bat_Volt;
      HighFreqData_Buffer[3] = HighFreqData.Bat_AvgCurrent;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)HighFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      
      memset(HighFreqData_Buffer, 0, sizeof(HighFreqData_Buffer));
      TxHeader.DLC           = 4;
      HighFreq_MsgID         = 102;
      HighFreqData_Buffer[0] = HighFreq_MsgID;
      HighFreqData_Buffer[1] = HighFreqData.Bat_Current;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)HighFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      return RE_OK;
}

RE_StatusTypeDef RE_TransmitMidFreqData(void)
{
      uint16_t MidFreq_MsgID; 
      uint16_t MidFreqData_Buffer[4];
      uint32_t TxMailbox;
      TxHeader.ExtId = 0xABC;
      TxHeader.IDE   = CAN_ID_EXT;
      TxHeader.RTR   = CAN_RTR_DATA;
      
      TxHeader.DLC          = 8;
      MidFreq_MsgID         = 201;
      MidFreqData_Buffer[0] = MidFreq_MsgID;
      MidFreqData_Buffer[1] = MidFreqData.Bat_RemainingCapacity;
      MidFreqData_Buffer[2] = MidFreqData.Bat_Temperature;
      MidFreqData_Buffer[3] = MidFreqData.Bat_AvgTimeToEmpty;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)MidFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }

      memset(MidFreqData_Buffer, 0, sizeof(MidFreqData_Buffer));
      TxHeader.DLC          = 8;
      MidFreq_MsgID         = 202;
      MidFreqData_Buffer[0] = MidFreq_MsgID;
      MidFreqData_Buffer[1] = MidFreqData.Bat_AvgTimeToFull;
      MidFreqData_Buffer[2] = MidFreqData.Bat_PassedCharge;
      MidFreqData_Buffer[3] = MidFreqData.Bat_AvailableEnergy;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)MidFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      
      memset(MidFreqData_Buffer, 0, sizeof(MidFreqData_Buffer));
      TxHeader.DLC          = 6;
      MidFreq_MsgID         = 203;
      MidFreqData_Buffer[0] = MidFreq_MsgID;
      MidFreqData_Buffer[1] = MidFreqData.Bat_AvgPower;
      MidFreqData_Buffer[2] = MidFreqData.Bat_InternalTemperature;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)MidFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }      
      return RE_OK;
}

RE_StatusTypeDef RE_TransmitLowFreqData(void)
{
      uint16_t LowFreq_MsgID; 
      uint16_t LowFreqData_Buffer[4];
      uint32_t TxMailbox;
      TxHeader.ExtId = 0xABC;
      TxHeader.IDE   = CAN_ID_EXT;
      TxHeader.RTR   = CAN_RTR_DATA;
      
      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 301;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_MaxError;
      LowFreqData_Buffer[2] = LowFreqData.Bat_FullChargeCapacity;
      LowFreqData_Buffer[3] = LowFreqData.Bat_SerialNumber;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      
      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 302;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_CycleCount;
      LowFreqData_Buffer[2] = LowFreqData.Bat_StateOfHealth;
      LowFreqData_Buffer[3] = LowFreqData.Bat_ChargeVoltage;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }      

      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 303;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_ChargeCurrent;
      LowFreqData_Buffer[2] = LowFreqData.Bat_PackConfiguration;
      LowFreqData_Buffer[3] = LowFreqData.Bat_AuthenticateData0;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      } 
      
      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 304;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_AuthenticateData1;
      LowFreqData_Buffer[2] = LowFreqData.Bat_AuthenticateData2;
      LowFreqData_Buffer[3] = LowFreqData.Bat_AuthenticateData3;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }

      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 305;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_AuthenticateData4;
      LowFreqData_Buffer[2] = LowFreqData.Bat_AuthenticateData5;
      LowFreqData_Buffer[3] = LowFreqData.Bat_AuthenticateData6;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      
      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 306;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_AuthenticateData7;
      LowFreqData_Buffer[2] = LowFreqData.Bat_AuthenticateData8;
      LowFreqData_Buffer[3] = LowFreqData.Bat_AuthenticateData9;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      
      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 307;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_AuthenticateData10;
      LowFreqData_Buffer[2] = LowFreqData.Bat_AuthenticateData11;
      LowFreqData_Buffer[3] = LowFreqData.Bat_AuthenticateData12;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
     
      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 308;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_AuthenticateData13;
      LowFreqData_Buffer[2] = LowFreqData.Bat_AuthenticateData14;
      LowFreqData_Buffer[3] = LowFreqData.Bat_AuthenticateData15;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      
      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 309;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_AuthenticateData16;
      LowFreqData_Buffer[2] = LowFreqData.Bat_AuthenticateData17;
      LowFreqData_Buffer[3] = LowFreqData.Bat_AuthenticateData18;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }

      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 310;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_AuthenticateData19;
      LowFreqData_Buffer[2] = LowFreqData.Bat_BlockData0;
      LowFreqData_Buffer[3] = LowFreqData.Bat_BlockData1;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      
      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 311;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_AuthenticateData19;
      LowFreqData_Buffer[2] = LowFreqData.Bat_BlockData0;
      LowFreqData_Buffer[3] = LowFreqData.Bat_BlockData1;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      
      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 312;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_BlockData2;
      LowFreqData_Buffer[2] = LowFreqData.Bat_BlockData3;
      LowFreqData_Buffer[3] = LowFreqData.Bat_BlockData4;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      
      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 313;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_BlockData5;
      LowFreqData_Buffer[2] = LowFreqData.Bat_BlockData6;
      LowFreqData_Buffer[3] = LowFreqData.Bat_BlockData7;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      
      TxHeader.DLC          = 8;
      LowFreq_MsgID         = 314;
      LowFreqData_Buffer[0] = LowFreq_MsgID;
      LowFreqData_Buffer[1] = LowFreqData.Bat_BlockData8;
      LowFreqData_Buffer[2] = LowFreqData.Bat_BlockData9;
      LowFreqData_Buffer[3] = LowFreqData.Bat_BlockData10;
      if (HAL_CAN_AddTxMessage(&hcan1_t, &TxHeader, (uint8_t *)LowFreqData_Buffer, &TxMailbox) != HAL_OK)
      {
        RE_Error_Handler(__FILE__, __LINE__);
      }
      return RE_OK;
}

/************************ (C) COPYRIGHT RACEnergy **********END OF FILE********/