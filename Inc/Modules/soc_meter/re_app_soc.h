/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_app_soc.h
  * Origin Date           :   13/04/2020
  * Compiler              :   Specify compiler used
  * Hardware              :   bq34z100
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

#ifndef __RE_APP_SOC_H
#define __RE_APP_SOC_H

#include "stm32f4xx_hal.h"
#include "re_std_def.h"
#include "stdlib.h"

#define BQ_WR_ADDR      ((uint8_t) 0xAA)       // I2C address for reading: 7bit address (0x55) + [0] write bit (0xAA)
#define BQ_RD_ADDR      ((uint8_t) 0xAB)       // I2C address for writing: 7bit address (0x55) + [1] read bit  (0xAB) 

#define TRUE 1
#define FALSE 0
#define BLOCK0
#define BLOCK1
#define BLOCK2
#define BLOCK3
 
 
/* Gauge Data Block Config Structure */
typedef struct {
  uint8_t Addr;                // Start Address of the DataBlock to read
  uint8_t Len;                 // Length of the DataBlock in bytes to read
}DataBlock_config_t;

typedef struct{  
  /**
    * Uncomment the data needed
    */
  /* Standard Data Commands */    
  #ifdef BLOCK0
    /* Data_Block_0 - start_address = 0x02 and data_len = 18 (bytes) */
    /* uint16_t Control;                                // 0x00  array[0] */
    uint8_t  StateOfCharge;                          // 0x02  array[2]      m = 1
    uint8_t  MaxError;                               // 0x03  array[3]      m = 3
    uint16_t RemainingCapacity;                      // 0x04  array[4]      m = 3
    uint16_t FullChargeCapacity;                     // 0x06  array[6]      m = 3+
    uint16_t Voltage;                                // 0x08  array[8]      m = 1
    uint16_t AvgCurrent;                             // 0x0A  array[10]     m = 2
    uint16_t Temperature;                            // 0x0C  array[12]     m = 2
    uint16_t Flags;                                  // 0x0E  array[14] x
    uint16_t Current;                                // 0x10  array[16]     m = 1
    uint16_t FlagsB;                                 // 0x12  array[18] x
    /* End of Standard Data Commands */
  #endif
  /* Blank Window */  
  #ifdef BLOCK1
    /* Data_Block_1 - Extended Data Commands - Block_2 - start_address = 0x18 and data_len = 8 (bytes) */
    uint16_t AvgTimeToEmpty;                         // 0x18  array[20]
    uint16_t AvgTimeToFull;                          // 0x1A  array[22]
    uint16_t PassedCharge;                           // 0x1C  array[24]
    uint16_t DoD0Time;                               // 0x1E  array[26]
  #endif
  /* Blank Window */
  #ifdef BLOCK2
    /* Data_Block_2 - start_address = 0x24 and data_len = 16 (bytes) */ 
    uint16_t AvailableEnergy;                        // 0x24  array[28]      m = 2
    uint16_t AvgPower;                               // 0x26  array[30]      m = 2
    uint16_t SerialNumber;                           // 0x28  array[32]      m = 3
    uint16_t InternalTemperature;                    // 0x2A  array[34] x
    uint16_t CycleCount;                             // 0x2C  array[36]      m = 3
    uint16_t StateOfHealth;                          // 0x2E  array[38]      m = 3+
    uint16_t ChargeVoltage;                          // 0x30  array[40] x
    uint16_t ChargeCurrent;                          // 0x32  array[42] x
  #endif
  /* Blank Window */
  #ifdef BLOCK3
    /* Data_Block_3 - start_address = 0x3A and data_len = 60 (bytes) */
    uint16_t PackConfiguration;                      // 0x3A  array[44]
    uint16_t DesignCapacity;                         // 0x3C  array[46]
    uint8_t  DataFlashClass;                         // 0x3E  array[48]
    uint8_t  DataFlashBlock;                         // 0x3F  array[49]
    uint8_t  AuthenticateData0;                      // 0x40  array[50]
    uint8_t  AuthenticateData1;                      // 0x41  array[51]
    uint8_t  AuthenticateData2;                      // 0x42  array[52]
    uint8_t  AuthenticateData3;                      // 0x43  array[53]
    uint8_t  AuthenticateData4;                      // 0x44  array[54]
    uint8_t  AuthenticateData5;                      // 0x45  array[55]
    uint8_t  AuthenticateData6;                      // 0x46  array[56]
    uint8_t  AuthenticateData7;                      // 0x47  array[57]
    uint8_t  AuthenticateData8;                      // 0x48  array[58]
    uint8_t  AuthenticateData9;                      // 0x49  array[59]
    uint8_t  AuthenticateData10;                     // 0x4A  array[60]
    uint8_t  AuthenticateData11;                     // 0x4B  array[61]
    uint8_t  AuthenticateData12;                     // 0x4C  array[62]
    uint8_t  AuthenticateData13;                     // 0x4D  array[63]
    uint8_t  AuthenticateData14;                     // 0x4E  array[64]
    uint8_t  AuthenticateData15;                     // 0x4F  array[65]
    uint8_t  AuthenticateData16;                     // 0x50  array[66]
    uint8_t  AuthenticateData17;                     // 0x51  array[67]
    uint8_t  AuthenticateData18;                     // 0x52  array[68]
    uint8_t  AuthenticateData19;                     // 0x53  array[69]
    uint8_t  AuthenticateChecksum;                   // 0x54  array[70]
    uint8_t  BlockData0;                             // 0x55  array[71]
    uint8_t  BlockData1;                             // 0x56  array[72]
    uint8_t  BlockData2;                             // 0x57  array[73]
    uint8_t  BlockData3;                             // 0x58  array[74]
    uint8_t  BlockData4;                             // 0x59  array[75]
    uint8_t  BlockData5;                             // 0x5A  array[76]
    uint8_t  BlockData6;                             // 0x5B  array[77]
    uint8_t  BlockData7;                             // 0x5C  array[78]
    uint8_t  BlockData8;                             // 0x5D  array[79]
    uint8_t  BlockData9;                             // 0x5E  array[80]
    uint8_t  BlockData10;                            // 0x5F  array[81]
    uint8_t  BlockDataChecksum;                      // 0x60  array[82]
    uint8_t  BlockDataControl;                       // 0x61  array[83]
    uint8_t  GridNumber;                             // 0x62  array[84]
    uint8_t  LearnedStatus;                          // 0x63  array[85]
    uint16_t DoDatEoC;                               // 0x64  array[86]
    uint16_t QStart;                                 // 0x66  array[88]
    uint16_t TrueRC;                                 // 0x68  array[90]
    uint16_t TrueFCC;                                // 0x6A  array[92]
    uint16_t StateTime;                              // 0x6C  array[94]
    uint16_t QMaxPassedQ;                            // 0x6E  array[96]
    uint16_t DOD0;                                   // 0x70  array[98]
    uint16_t QMaxDOD0;                               // 0x72  array[100]
    uint16_t QMaxTime;                               // 0x74  array[102]
    /* End of Extended Data Commands */
  #endif
}Gauge_Param_t;

/*                  High Priority SoC Data                    */

typedef struct   __attribute__((packed))   
{                                        //dont use pointers for individual elements
	uint8_t  Bat_SoC ;
	uint16_t Bat_Volt;
	uint16_t Bat_AvgCurrent;
	uint16_t Bat_Current;
}HighFreqData_t;

/*                 Medium Priority SoC Data                   */
typedef struct   __attribute__((packed))
{
	uint16_t Bat_RemainingCapacity;
        uint16_t Bat_Temperature;
        uint16_t Bat_AvgTimeToEmpty;
        uint16_t Bat_AvgTimeToFull;
        uint16_t Bat_PassedCharge;
        uint16_t Bat_AvailableEnergy;
        uint16_t Bat_AvgPower;
        uint16_t Bat_InternalTemperature;
}MidFreqData_t;

/*                 Low Priority SoC Data                      */
typedef struct    __attribute__((packed))
{ 
        uint8_t  Bat_MaxError;
        uint16_t Bat_FullChargeCapacity;
        uint16_t Bat_SerialNumber;
        uint16_t Bat_CycleCount;
        uint16_t Bat_StateOfHealth;
        uint16_t Bat_ChargeVoltage;
        uint16_t Bat_ChargeCurrent;
        uint16_t Bat_PackConfiguration;
        uint8_t  Bat_AuthenticateData0;
        uint8_t  Bat_AuthenticateData1;
        uint8_t  Bat_AuthenticateData2;
        uint8_t  Bat_AuthenticateData3;
        uint8_t  Bat_AuthenticateData4;
        uint8_t  Bat_AuthenticateData5;
        uint8_t  Bat_AuthenticateData6;
        uint8_t  Bat_AuthenticateData7;
        uint8_t  Bat_AuthenticateData8;
        uint8_t  Bat_AuthenticateData9;
        uint8_t  Bat_AuthenticateData10;
        uint8_t  Bat_AuthenticateData11;
        uint8_t  Bat_AuthenticateData12;
        uint8_t  Bat_AuthenticateData13;
        uint8_t  Bat_AuthenticateData14;
        uint8_t  Bat_AuthenticateData15;
        uint8_t  Bat_AuthenticateData16;
        uint8_t  Bat_AuthenticateData17;
        uint8_t  Bat_AuthenticateData18;
        uint8_t  Bat_AuthenticateData19;
        uint8_t  Bat_BlockData0;
        uint8_t  Bat_BlockData1;
        uint8_t  Bat_BlockData2;
        uint8_t  Bat_BlockData3;
        uint8_t  Bat_BlockData4;
        uint8_t  Bat_BlockData5;
        uint8_t  Bat_BlockData6;
        uint8_t  Bat_BlockData7;
        uint8_t  Bat_BlockData8;
        uint8_t  Bat_BlockData9;
        uint8_t  Bat_BlockData10;
}LowFreqData_t;

uint32_t RE_SoC_ReadGaugeData (void);
RE_StatusTypeDef RE_SoC_GetCanID(void);

#endif 

/***************************** END OF FILE ************************************/
