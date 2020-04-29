#include "eeprom_api.h"

#define EEPROM_ADDRESS 0xA0

extern System_Config_t *pSystem_Config;
extern System_Config_t System_Config;
extern uint8_t I2C_StructReceiveBuffer[sizeof(System_Config_t)];
extern I2C_HandleTypeDef hi2c2_t;


void RE_NVS_WriteStruct(uint16_t MemAddress, System_Config_t *pSystem_Config)
{
    uint8_t* addressOfStruct = (uint8_t*)(&System_Config);
    uint16_t sizeOfStruct = sizeof(System_Config_t);
    if(HAL_I2C_Mem_Write (&hi2c2_t, EEPROM_ADDRESS, MemAddress, I2C_MEMADD_SIZE_16BIT, addressOfStruct,\
                            sizeOfStruct, 100) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }   
}

void RE_NVS_ReadStruct(uint16_t MemAddress, System_Config_t *pSystem_Config)
{
    uint16_t sizeOfStruct = sizeof(System_Config_t);
    if(HAL_I2C_Mem_Read (&hi2c2_t, EEPROM_ADDRESS, MemAddress, I2C_MEMADD_SIZE_16BIT, I2C_StructReceiveBuffer,\
                            sizeOfStruct, 100) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
}

void RE_NVS_WriteByte(uint16_t MemAddress, uint8_t Data, uint8_t Offset)
{
    uint8_t sizeofData = sizeof(Data);
    if(HAL_I2C_Mem_Write(&hi2c2_t, EEPROM_ADDRESS, MemAddress+Offset, I2C_MEMADD_SIZE_8BIT, (uint8_t *)Data, sizeofData,\
                            100) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
}

void RE_NVS_ReadByte(uint16_t MemAddress, uint8_t Data, uint8_t Offset)
{
    uint8_t sizeofData = sizeof(Data);
    if(HAL_I2C_Mem_Read(&hi2c2_t, EEPROM_ADDRESS, MemAddress+Offset, I2C_MEMADD_SIZE_8BIT, (uint8_t *)Data, sizeofData,\
                            100) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
}
//int *p1 = (int*)malloc(sizeof(int)*size);

void RE_NVS_WriteString(uint16_t MemAddress, char * pData, uint8_t Offset, uint8_t DataLength)
{   
    uint8_t i = 0;
    uint8_t *DataBuffer = (uint8_t *)malloc(DataLength * sizeof(uint8_t));
    while(*pData)
    {
        (DataBuffer[i++]) = (uint8_t)(*pData++);
    }
    if(HAL_I2C_Mem_Write(&hi2c2_t, EEPROM_ADDRESS, MemAddress+Offset, I2C_MEMADD_SIZE_8BIT, DataBuffer, DataLength,\
                            100) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    } 
    free(DataBuffer);
}

void RE_NVS_ReadString(uint16_t MemAddress, char * pData, uint8_t Offset, uint8_t DataLength)
{
    uint8_t *DataBuffer = (uint8_t *)malloc(DataLength * sizeof(uint8_t));
    uint8_t i = 0;
    if(HAL_I2C_Mem_Read(&hi2c2_t, EEPROM_ADDRESS, MemAddress, I2C_MEMADD_SIZE_8BIT, DataBuffer, DataLength,\
                            100) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    while(DataBuffer[i])
    {
        (*pData++) = DataBuffer[i++];
    }
    free(DataBuffer);
}

void RE_NVS_WriteBytes(uint16_t MemAddress, uint8_t *pData,uint16_t TxBufferSize)
{
	/*
	 * program just get the DevAddress of the Slave (not master) and for the next step
	 * You know that the most of the EEprom address start with 0xA0
	 * give MemAddress for the location you want to write to
	 * give Data buffer so it can write Data on this location
	 */
	//Note that this function works properly to 31 bytes
	if(MemAddress + TxBufferSize > 16)
	{
		//Write to 16bytes
		while(HAL_I2C_Mem_Write(&hi2c2_t, EEPROM_ADDRESS, (uint16_t)MemAddress,I2C_MEMADD_SIZE_8BIT,pData,\
                       (uint16_t)16-MemAddress, 1000)!= HAL_OK);
		//write remaining bytes
		*pData = *pData + (16-MemAddress);
		while(HAL_I2C_Mem_Write(&hi2c2_t, EEPROM_ADDRESS, (uint16_t)16, I2C_MEMADD_SIZE_8BIT, pData,\
                        (uint16_t)((MemAddress+TxBufferSize)-16), 1000)!= HAL_OK);

	}
	else
	{
			while( (TxBufferSize - 16) > 0 )
			{
				//if your data is more than 16 bytes,you are here
				 while(HAL_I2C_Mem_Write(&hi2c2_t, EEPROM_ADDRESS, (uint16_t)MemAddress,\
                                        I2C_MEMADD_SIZE_8BIT, pData, (uint16_t)16, 1000)!= HAL_OK);
				 TxBufferSize = TxBufferSize - 16;
				 pData = pData + 16;
				 MemAddress = MemAddress + 16;
			}
			//remaining data
			while(HAL_I2C_Mem_Write(&hi2c2_t, EEPROM_ADDRESS, (uint16_t)MemAddress, I2C_MEMADD_SIZE_8BIT,\
                                 pData, (uint16_t)TxBufferSize, 1000)!= HAL_OK);
	}
}


void RE_NVS_ReadBytes(uint16_t MemAddress, uint8_t *pData,uint16_t RxBufferSize)
{
	int TimeOut;
	/*
	 * program just get the DevAddress of the Slave (not master) and for the next step
	 * You know that the most of the EEprom address start with 0xA0
	 * get the MemAddress for the location you want to write data on it
	 * get the Data buffer so it can write Data on this location
	 */
	//Note that this function works properly to 31bytes

			while( (RxBufferSize - 16) > 0 )
			{
				//if your data is more than 16 bytes,you are here
				TimeOut = 0;
				 while(HAL_I2C_Mem_Read(&hi2c2_t, EEPROM_ADDRESS, (uint16_t)MemAddress,\
                                         I2C_MEMADD_SIZE_8BIT, pData, (uint16_t)16,1000)!= HAL_OK && TimeOut < 10)
				 {
						TimeOut++;
				 }

				 RxBufferSize = RxBufferSize - 16;
				 pData = pData + 16;
				 MemAddress = MemAddress + 16;
			}
//			//remaining data
			TimeOut = 0;
			while(HAL_I2C_Mem_Read(&hi2c2_t, EEPROM_ADDRESS, (uint16_t)MemAddress, I2C_MEMADD_SIZE_8BIT,\
                                  pData, (uint16_t)RxBufferSize, 1000)!= HAL_OK && TimeOut < 10)
			{
				TimeOut++;
			}
}
