/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_app_soc.c
  * Origin Date           :   14/04/2020
  * Compiler              :   Specify compiler used
  * Hardware              :   bq34z100
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
#include "soc_meter/re_app_soc.h"


extern I2C_HandleTypeDef hi2c1_t;

uint32_t CAN_BaseID;
Gauge_Param_t Gauge_Param;
DataBlock_config_t Block;                     // Data Block config structure to read SoC-meter data in blocks format
HighFreqData_t HighFreqData;
MidFreqData_t MidFreqData;
LowFreqData_t LowFreqData;

uint8_t *pGaugeData = NULL;
uint32_t CAN_BaseID;

static uint8_t  RE_SoC_ConfigDataBlock (uint8_t block_num);
static RE_StatusTypeDef RE_SoC_I2CReadDataBlock (uint8_t block_num);
static uint16_t RE_Byte_Swap (uint16_t msb, uint16_t lsb);
static uint32_t  RE_SoC_MapGaugeData (uint8_t block_num);

static uint8_t RE_SoC_ConfigDataBlock(uint8_t block_num)
{

  #ifdef BLOCK0      /* Block: 0 */
    if (block_num == 0)
    {
      Block.Addr  = 0x02;
      Block.Len   = 18;
    }
  #endif
  #ifdef BLOCK1      /* Block: 1 */
    if (block_num == 1)
    {
      Block.Addr  = 0x18;
      Block.Len   = 8;
    }
  #endif
  #ifdef BLOCK2      /* Block: 2 */
    if  (block_num == 2)
    {
      Block.Addr  = 0x24;
      Block.Len   = 16;
    }
  #endif
  #ifdef BLOCK3      /* Block: 3 */
    if (block_num == 3)
    {
      Block.Addr  = 0x3A;
      Block.Len   = 60;
    }
  #endif
    return Block.Len;
}

/**
  * @brief  Read Gauge data blocks into array
  * @param  block_num : Block Number
  * @retval None  
  */
static RE_StatusTypeDef RE_SoC_I2CReadDataBlock (uint8_t block_num)
{
  
  RE_SoC_ConfigDataBlock(block_num);    /* Configure blocks first */
  
  pGaugeData = malloc(Block.Len);    /* Allocate the memory bytes to array : pGaugeData */
  /* Master write address to Slave */
  if (HAL_I2C_Master_Transmit (&hi2c1_t, BQ_WR_ADDR, &Block.Addr, sizeof(Block.Addr), 1000)!=HAL_OK)
  {
    RE_Error_Handler(__FILE__, __LINE__);
  }
  /* Master request Slave for data */
  if (HAL_I2C_Master_Receive (&hi2c1_t, BQ_RD_ADDR, &pGaugeData[0], Block.Len, 1000)!=HAL_OK)
  {
    RE_Error_Handler(__FILE__, __LINE__);
  }
 /* Map array data to structure */
  RE_SoC_MapGaugeData(block_num);
  /* Release memory allocated to PGaugeData */
  free(pGaugeData); 
  return RE_OK;
}

/**
  * @brief  Swap MSB and LSB 
  * @param  msb: Most Significant Byte
  * @param  lsb: Least Significant Byte
  * @retval swap_byte: Bytes after swapping  
  */
static uint16_t RE_Byte_Swap (uint16_t msb, uint16_t lsb)
{
  uint16_t swap_data;
  swap_data = ((lsb << 8) & (0xFF00))| ((msb) & (0x00FF)) ; 
  return swap_data;
}

/**
  * @brief  Map array data into Gauge_Param_t 
  * @param  block_num Block Number
  * @retval None  
  */
static uint32_t RE_SoC_MapGaugeData(uint8_t block_num)
{
  #ifdef BLOCK0
    if (block_num == 0)
    {
//    pGauge_Param.Control              = RE_Byte_Swap(pGaugeData[0], pGaugeData[1]);
      Gauge_Param.StateOfCharge        = pGaugeData[0];
      Gauge_Param.MaxError             = pGaugeData[1];
      Gauge_Param.RemainingCapacity    = RE_Byte_Swap(pGaugeData[2], pGaugeData[3]);
      Gauge_Param.FullChargeCapacity   = RE_Byte_Swap(pGaugeData[4], pGaugeData[5]);
      Gauge_Param.Voltage              = RE_Byte_Swap(pGaugeData[6], pGaugeData[7]);
      Gauge_Param.AvgCurrent           = RE_Byte_Swap(pGaugeData[8], pGaugeData[9]);
      Gauge_Param.Temperature          = RE_Byte_Swap(pGaugeData[10], pGaugeData[11]);
      Gauge_Param.Flags                = RE_Byte_Swap(pGaugeData[12], pGaugeData[13]);
      Gauge_Param.Current              = RE_Byte_Swap(pGaugeData[14], pGaugeData[15]);
      Gauge_Param.FlagsB               = RE_Byte_Swap(pGaugeData[16], pGaugeData[17]);
    }
  #endif
  #ifdef BLOCK1
    if (block_num == 1)
    {
      Gauge_Param.AvgTimeToEmpty       = RE_Byte_Swap(pGaugeData[0], pGaugeData[1]);
      Gauge_Param.AvgTimeToFull        = RE_Byte_Swap(pGaugeData[2], pGaugeData[3]);
      Gauge_Param.PassedCharge         = RE_Byte_Swap(pGaugeData[4], pGaugeData[5]);                          
      Gauge_Param.DoD0Time             = RE_Byte_Swap(pGaugeData[6], pGaugeData[7]);
    }
  #endif
  #ifdef BLOCK2
    if (block_num == 2)
    {
      Gauge_Param.AvailableEnergy      = RE_Byte_Swap(pGaugeData[0], pGaugeData[1]);
      Gauge_Param.AvgPower             = RE_Byte_Swap(pGaugeData[2], pGaugeData[3]);
      Gauge_Param.SerialNumber         = RE_Byte_Swap(pGaugeData[4], pGaugeData[5]);
      Gauge_Param.InternalTemperature  = RE_Byte_Swap(pGaugeData[6], pGaugeData[7]);
      Gauge_Param.CycleCount           = RE_Byte_Swap(pGaugeData[8], pGaugeData[9]);
      Gauge_Param.StateOfHealth        = RE_Byte_Swap(pGaugeData[10], pGaugeData[11]);
      Gauge_Param.ChargeVoltage        = RE_Byte_Swap(pGaugeData[12], pGaugeData[13]);
      Gauge_Param.ChargeCurrent        = RE_Byte_Swap(pGaugeData[14], pGaugeData[15]);
    }
  #endif
  #ifdef BLOCK3
    if (block_num == 3)
    {
      Gauge_Param.PackConfiguration    = RE_Byte_Swap(pGaugeData[0], pGaugeData[1]);
      Gauge_Param.DesignCapacity       = RE_Byte_Swap(pGaugeData[2], pGaugeData[3]);
      Gauge_Param.DataFlashClass       = pGaugeData[4];
      Gauge_Param.DataFlashBlock       = pGaugeData[5];
      Gauge_Param.AuthenticateData0    = pGaugeData[6];
      Gauge_Param.AuthenticateData1    = pGaugeData[7];
      Gauge_Param.AuthenticateData2    = pGaugeData[8];
      Gauge_Param.AuthenticateData3    = pGaugeData[9];
      Gauge_Param.AuthenticateData4    = pGaugeData[10];
      Gauge_Param.AuthenticateData5    = pGaugeData[11];
      Gauge_Param.AuthenticateData6    = pGaugeData[12];
      Gauge_Param.AuthenticateData7    = pGaugeData[13];
      Gauge_Param.AuthenticateData8    = pGaugeData[14];
      Gauge_Param.AuthenticateData9    = pGaugeData[15];
      Gauge_Param.AuthenticateData10   = pGaugeData[16];
      Gauge_Param.AuthenticateData11   = pGaugeData[17];
      Gauge_Param.AuthenticateData12   = pGaugeData[18];
      Gauge_Param.AuthenticateData13   = pGaugeData[19];
      Gauge_Param.AuthenticateData14   = pGaugeData[20];
      Gauge_Param.AuthenticateData15   = pGaugeData[21];
      Gauge_Param.AuthenticateData16   = pGaugeData[22];
      Gauge_Param.AuthenticateData17   = pGaugeData[23];
      Gauge_Param.AuthenticateData18   = pGaugeData[24];
      Gauge_Param.AuthenticateData19   = pGaugeData[25];
      Gauge_Param.AuthenticateChecksum = pGaugeData[26];
      Gauge_Param.BlockData0           = pGaugeData[27];
      Gauge_Param.BlockData1           = pGaugeData[28];
      Gauge_Param.BlockData2           = pGaugeData[29];
      Gauge_Param.BlockData3           = pGaugeData[30];
      Gauge_Param.BlockData4           = pGaugeData[31];
      Gauge_Param.BlockData5           = pGaugeData[32];
      Gauge_Param.BlockData6           = pGaugeData[33];
      Gauge_Param.BlockData7           = pGaugeData[34];
      Gauge_Param.BlockData8           = pGaugeData[35];
      Gauge_Param.BlockData9           = pGaugeData[36];
      Gauge_Param.BlockData10          = pGaugeData[37];
      Gauge_Param.BlockDataChecksum    = pGaugeData[38];
      Gauge_Param.BlockDataControl     = pGaugeData[39];
      Gauge_Param.GridNumber           = pGaugeData[40];
      Gauge_Param.LearnedStatus        = pGaugeData[41];
      Gauge_Param.DoDatEoC             = RE_Byte_Swap(pGaugeData[42], pGaugeData[43]);
      Gauge_Param.QStart               = RE_Byte_Swap(pGaugeData[44], pGaugeData[45]);
      Gauge_Param.TrueRC               = RE_Byte_Swap(pGaugeData[46], pGaugeData[47]);
      Gauge_Param.TrueFCC              = RE_Byte_Swap(pGaugeData[48], pGaugeData[49]);
      Gauge_Param.StateTime            = RE_Byte_Swap(pGaugeData[50], pGaugeData[51]);
      Gauge_Param.QMaxPassedQ          = RE_Byte_Swap(pGaugeData[52], pGaugeData[53]);
      Gauge_Param.DOD0                 = RE_Byte_Swap(pGaugeData[54], pGaugeData[55]);
      Gauge_Param.QMaxDOD0             = RE_Byte_Swap(pGaugeData[56], pGaugeData[57]);
      Gauge_Param.QMaxTime             = RE_Byte_Swap(pGaugeData[58], pGaugeData[59]); 
    }
  #endif
  return 0;
}

uint32_t RE_SoC_ReadGaugeData (void)
{
      if ( sizeof(pGaugeData) != NULL)
      {
        free(pGaugeData);
      }

      /* Read data block 0 from bq34z100 */
      RE_SoC_I2CReadDataBlock(0);
      HighFreqData.Bat_SoC                 = Gauge_Param.StateOfCharge ;
      HighFreqData.Bat_Volt                = Gauge_Param.Voltage;
      HighFreqData.Bat_AvgCurrent          = Gauge_Param.AvgCurrent;
      HighFreqData.Bat_Current             = Gauge_Param.Current;
      MidFreqData.Bat_RemainingCapacity    = Gauge_Param.RemainingCapacity;
      MidFreqData.Bat_Temperature          = Gauge_Param.Temperature;
      LowFreqData.Bat_FullChargeCapacity   = Gauge_Param.FullChargeCapacity;
      LowFreqData.Bat_MaxError             = Gauge_Param.MaxError;

      /* Read data block 1 from bq34z100 */
      RE_SoC_I2CReadDataBlock(1);
      MidFreqData.Bat_AvgTimeToEmpty      = Gauge_Param.AvgTimeToEmpty;
      MidFreqData.Bat_AvgTimeToFull       = Gauge_Param.AvgTimeToFull;
      MidFreqData.Bat_PassedCharge        = Gauge_Param.PassedCharge;
      
      
      /* Read data block 2 from bq34z100 */
      RE_SoC_I2CReadDataBlock(2);
      MidFreqData.Bat_AvailableEnergy      = Gauge_Param.AvailableEnergy;
      MidFreqData.Bat_AvgPower             = Gauge_Param.AvgPower;
      MidFreqData.Bat_InternalTemperature  = Gauge_Param.InternalTemperature;
      LowFreqData.Bat_SerialNumber         = Gauge_Param.SerialNumber;
      LowFreqData.Bat_CycleCount           = Gauge_Param.CycleCount;
      LowFreqData.Bat_StateOfHealth        = Gauge_Param.StateOfHealth;
      LowFreqData.Bat_ChargeVoltage        = Gauge_Param.ChargeVoltage;
      LowFreqData.Bat_ChargeCurrent        = Gauge_Param.ChargeCurrent;
           
      /* Read data block 3 from bq34z100 */
      RE_SoC_I2CReadDataBlock(3);
      LowFreqData.Bat_PackConfiguration   = Gauge_Param.PackConfiguration;
      LowFreqData.Bat_AuthenticateData0   = Gauge_Param.AuthenticateData0;
      LowFreqData.Bat_AuthenticateData1   = Gauge_Param.AuthenticateData1;
      LowFreqData.Bat_AuthenticateData2   = Gauge_Param.AuthenticateData2;
      LowFreqData.Bat_AuthenticateData3   = Gauge_Param.AuthenticateData3;
      LowFreqData.Bat_AuthenticateData4   = Gauge_Param.AuthenticateData4;
      LowFreqData.Bat_AuthenticateData5   = Gauge_Param.AuthenticateData5;
      LowFreqData.Bat_AuthenticateData6   = Gauge_Param.AuthenticateData6;
      LowFreqData.Bat_AuthenticateData7   = Gauge_Param.AuthenticateData7;
      LowFreqData.Bat_AuthenticateData8   = Gauge_Param.AuthenticateData8;
      LowFreqData.Bat_AuthenticateData9   = Gauge_Param.AuthenticateData9;
      LowFreqData.Bat_AuthenticateData10  = Gauge_Param.AuthenticateData10;
      LowFreqData.Bat_AuthenticateData11  = Gauge_Param.AuthenticateData11;
      LowFreqData.Bat_AuthenticateData12  = Gauge_Param.AuthenticateData12;
      LowFreqData.Bat_AuthenticateData13  = Gauge_Param.AuthenticateData13;
      LowFreqData.Bat_AuthenticateData14  = Gauge_Param.AuthenticateData14;
      LowFreqData.Bat_AuthenticateData15  = Gauge_Param.AuthenticateData15;
      LowFreqData.Bat_AuthenticateData16  = Gauge_Param.AuthenticateData16;
      LowFreqData.Bat_AuthenticateData17  = Gauge_Param.AuthenticateData17;
      LowFreqData.Bat_AuthenticateData18  = Gauge_Param.AuthenticateData18;
      LowFreqData.Bat_AuthenticateData19  = Gauge_Param.AuthenticateData19;
      LowFreqData.Bat_BlockData0          = Gauge_Param.BlockData0;
      LowFreqData.Bat_BlockData1          = Gauge_Param.BlockData1;
      LowFreqData.Bat_BlockData2          = Gauge_Param.BlockData2;
      LowFreqData.Bat_BlockData3          = Gauge_Param.BlockData3;
      LowFreqData.Bat_BlockData4          = Gauge_Param.BlockData4;
      LowFreqData.Bat_BlockData5          = Gauge_Param.BlockData5;
      LowFreqData.Bat_BlockData6          = Gauge_Param.BlockData6;
      LowFreqData.Bat_BlockData7          = Gauge_Param.BlockData7;
      LowFreqData.Bat_BlockData8          = Gauge_Param.BlockData8;
      LowFreqData.Bat_BlockData9          = Gauge_Param.BlockData9;
      LowFreqData.Bat_BlockData10         = Gauge_Param.BlockData10;
      return 0;
}


RE_StatusTypeDef RE_SoC_GetCanID(void)
{
      uint32_t  DataFlash     = 0x00003A3E;
      uint16_t DataCommand    = 0x3A00;
      uint8_t  CAN_Id_Addr    = 0x5C;
      if (HAL_I2C_Master_Transmit (&hi2c1_t, BQ_WR_ADDR, (uint8_t*)&DataFlash , 3*sizeof(uint8_t), 1000) != HAL_OK)
      {
          RE_Error_Handler(__FILE__, __LINE__);
      }
      HAL_Delay(10);
      if (HAL_I2C_Master_Transmit (&hi2c1_t, BQ_WR_ADDR, &CAN_Id_Addr, sizeof(CAN_Id_Addr), 1000) != HAL_OK)
      {
          RE_Error_Handler(__FILE__, __LINE__);
      }
      if (HAL_I2C_Master_Receive (&hi2c1_t, BQ_RD_ADDR, (uint8_t*)&CAN_BaseID, 0x04 , 1000) != HAL_OK)
      {
          RE_Error_Handler(__FILE__, __LINE__);
      }
      CAN_BaseID = ((CAN_BaseID&0x000000FF)<<0x18)|((CAN_BaseID&0x0000FF00)<<0x08)|((CAN_BaseID&0x00FF0000)>>0x08)|\
                    ((CAN_BaseID&0xFF000000)>>0x18);
      return RE_OK;
}


/************************ (C) COPYRIGHT RACEnergy **********END OF FILE********/