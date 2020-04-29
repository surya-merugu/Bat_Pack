/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_can_int_callback.c
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
#include "main/main.h"
#include "re_can_int_callback.h"


extern CAN_RxHeaderTypeDef RxHeader;
extern CAN_HandleTypeDef hcan1_t;
extern uint32_t CAN_BaseID;

uint32_t offset = 0;
uint8_t DataLen = 0;
uint32_t TxMailbox;
uint8_t HighFreqTxFlag = 0;
uint8_t MidFreqTxFlag  = 0;

extern RE_StatusTypeDef RE_CAN_SendBatInfo (uint8_t *pTxMsg);
extern uint32_t RE_SoC_ReadGaugeData (void);
extern RE_StatusTypeDef RE_OpenLatch(void);
    
/**
  ==============================================================================
                          ##### Callback functions #####
  ==============================================================================
    [..]
    This subsection provides the following callback functions:
      ( ) HAL_CAN_TxMailbox0CompleteCallback
      ( ) HAL_CAN_TxMailbox1CompleteCallback
      ( ) HAL_CAN_TxMailbox2CompleteCallback
      ( ) HAL_CAN_TxMailbox0AbortCallback
      ( ) HAL_CAN_TxMailbox1AbortCallback
      ( ) HAL_CAN_TxMailbox2AbortCallback
      (+) HAL_CAN_RxFifo0MsgPendingCallback
      ( ) HAL_CAN_RxFifo0FullCallback
      ( ) HAL_CAN_RxFifo1MsgPendingCallback
      ( ) HAL_CAN_RxFifo1FullCallback
      ( ) HAL_CAN_SleepCallback
      ( ) HAL_CAN_WakeUpFromRxMsgCallback
      ( ) HAL_CAN_ErrorCallback
  ==============================================================================
*/

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  uint8_t rcvd_msg[8];

  if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&RxHeader,rcvd_msg) != HAL_OK)
  {
    RE_Error_Handler(__FILE__, __LINE__);
  }
  
  /** @ToDo - send id as data with same data */
  if (RxHeader.ExtId==0x3E8 && RxHeader.RTR == 1)
  {
    //SEND_CAN_BaseId(CAN_BaseID);
  }
  
  if (RxHeader.ExtId==0xABC && RxHeader.RTR == 1)
  {
      HighFreqTxFlag = 1;
  }
  
  if (RxHeader.ExtId==0xABC && RxHeader.RTR == 1)
  {
      MidFreqTxFlag = 1;
  }
  if (RxHeader.ExtId == CAN_BaseID && RxHeader.RTR == 1)
  {
      RE_OpenLatch ();
  }

#if 0 
  if (RxHeader.ExtId==0x3EA && RxHeader.RTR == 1) 
  {

    /*           read SoC and send Data             */
    /** Get SoC parameter into @pGauge_Param_t */
    if (RE_SoC_ReadGaugeData() != 0)
    {
      RE_Error_Handler(__FILE__, __LINE__);
    }
    /* Format CAN data frames and send data*/
    offset = 1;
    DataLen = 7;
    RE_CAN_SendBatInfo((uint8_t*)&can_msg_1); // Transmit high priority message 
    
    DataLen = 4;
    offset=2;
    RE_CAN_SendBatInfo((uint8_t*)&can_msg_2);  // Transmit medium priority message  
    
    DataLen = 6;
    offset=3;
    RE_CAN_SendBatInfo((uint8_t*)&can_msg_3);  // Transmit low priority message
  }
#endif
  
}

/************************ (C) COPYRIGHT RACEnergy **********END OF FILE********/
