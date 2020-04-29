/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_adc_init.c
  * Origin Date           :   14/04/2020
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

/* Includes */
#include "re_adc_init.h"

ADC_HandleTypeDef hadc1_t;
extern DMA_HandleTypeDef hdma_adc1_t;

static RE_StatusTypeDef RE_ADC_GpioInit(ADC_HandleTypeDef *hadc);

/**
 * @brief Timer Base Init
 * This function configures clock and set priority for the timer
 * @param  htim3_t: timer handle typedef
 * @retval Exit status
 */
static RE_StatusTypeDef RE_ADC_GpioInit(ADC_HandleTypeDef *hadc)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hadc -> Instance == ADC1)
    {
        __HAL_RCC_ADC1_CLK_ENABLE();
  
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**ADC1 GPIO Configuration    
        PA1     ------> ADC1_IN1
        PA2     ------> ADC1_IN2
        PA3     ------> ADC1_IN3
        PA4     ------> ADC1_IN4
        PA5     ------> ADC1_IN5
        PA6     ------> ADC1_IN6
        PA7     ------> ADC1_IN7 
        */
        GPIO_InitStruct.Pin     = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4  | GPIO_PIN_5 | GPIO_PIN_6 |\
                                   GPIO_PIN_7;
        GPIO_InitStruct.Mode    = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull    = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* ADC1 DMA Init */
        /* ADC1 Init */
        hdma_adc1_t.Instance                          = DMA2_Stream0;
        hdma_adc1_t.Init.Channel                      = DMA_CHANNEL_0;
        hdma_adc1_t.Init.Direction                    = DMA_PERIPH_TO_MEMORY;
        hdma_adc1_t.Init.PeriphInc                    = DMA_PINC_DISABLE;
        hdma_adc1_t.Init.MemInc                       = DMA_MINC_ENABLE;
        hdma_adc1_t.Init.PeriphDataAlignment          = DMA_PDATAALIGN_WORD;
        hdma_adc1_t.Init.MemDataAlignment             = DMA_MDATAALIGN_WORD;
        hdma_adc1_t.Init.Mode                         = DMA_CIRCULAR;
        hdma_adc1_t.Init.Priority                     = DMA_PRIORITY_VERY_HIGH;
        hdma_adc1_t.Init.FIFOMode                     = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_adc1_t) != HAL_OK)
        {
            RE_Error_Handler(__FILE__, __LINE__);
        }
        __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc1_t);
        
        HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(ADC_IRQn);
      }
    return RE_OK;
}

/**
 * @brief ADC Initialization
 * This function configures the ADC
 * @param  void
 * @retval Exit status
 */
RE_StatusTypeDef RE_ADC1_Init (void)
{
    ADC_ChannelConfTypeDef sConfig = {0};

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
    hadc1_t.Instance                      = ADC1;
    hadc1_t.Init.ClockPrescaler           = ADC_CLOCK_SYNC_PCLK_DIV8;
    hadc1_t.Init.Resolution               = ADC_RESOLUTION_12B;
    hadc1_t.Init.ScanConvMode             = ENABLE;
    hadc1_t.Init.ContinuousConvMode       = ENABLE;
    hadc1_t.Init.DiscontinuousConvMode    = DISABLE;
    hadc1_t.Init.ExternalTrigConvEdge     = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1_t.Init.ExternalTrigConv         = ADC_SOFTWARE_START;
    hadc1_t.Init.DataAlign                = ADC_DATAALIGN_RIGHT;
    hadc1_t.Init.NbrOfConversion          = 7;
    hadc1_t.Init.DMAContinuousRequests    = ENABLE;
    hadc1_t.Init.EOCSelection             = ADC_EOC_SINGLE_CONV;
    if (RE_ADC_GpioInit(&hadc1_t) != RE_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    if (HAL_ADC_Init(&hadc1_t) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
    sConfig.Channel        = ADC_CHANNEL_1;
    sConfig.Rank           = 1;
    sConfig.SamplingTime   = ADC_SAMPLETIME_480CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1_t, &sConfig) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
    sConfig.Channel       = ADC_CHANNEL_2;
    sConfig.Rank          = 2;
    if (HAL_ADC_ConfigChannel(&hadc1_t, &sConfig) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
    sConfig.Channel        = ADC_CHANNEL_3;
    sConfig.Rank           = 3;
    if (HAL_ADC_ConfigChannel(&hadc1_t, &sConfig) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
    sConfig.Channel       = ADC_CHANNEL_4;
    sConfig.Rank          = 4;
    if (HAL_ADC_ConfigChannel(&hadc1_t, &sConfig) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
    sConfig.Channel       = ADC_CHANNEL_5;
    sConfig.Rank          = 5;
    if (HAL_ADC_ConfigChannel(&hadc1_t, &sConfig) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
    sConfig.Channel       = ADC_CHANNEL_6;
    sConfig.Rank          = 6;
    if (HAL_ADC_ConfigChannel(&hadc1_t, &sConfig) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
    sConfig.Channel        = ADC_CHANNEL_7;
    sConfig.Rank           = 7;
    if (HAL_ADC_ConfigChannel(&hadc1_t, &sConfig) != HAL_OK)
    {
        RE_Error_Handler(__FILE__, __LINE__);
    }
    return RE_OK;
}
/************************ (C) COPYRIGHT RACEnergy **********END OF FILE********/
