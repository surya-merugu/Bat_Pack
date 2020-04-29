/**
  *****************************************************************************
  * Title                 :   Bat_Pack_Gen1
  * Filename              :   re_i2c_init.c
  * Origin Date           :   17/04/2020
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
#include "re_i2c_init.h"

I2C_HandleTypeDef hi2c1_t, hi2c2_t;

static RE_StatusTypeDef RE_I2C_GpioInit(I2C_HandleTypeDef *hi2c);
/** 
 * @brief I2C GPIO Initialization
 * This function configures the GPIO pins used by I2C
 * @param hi2c1: I2C handle pointer
 * @retval Exit status
 */
static RE_StatusTypeDef RE_I2C_GpioInit(I2C_HandleTypeDef *hi2c)
{
    GPIO_InitTypeDef I2C_GPIO = {0};
    if (hi2c->Instance == I2C1)
    {
        /* Peripheral clock enable */
        __HAL_RCC_I2C1_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /** I2C1 GPIO Configuration
         * PB6   ------> I2C1_SCL
         * PB7   ------> I2C1_SDA
         */
        I2C_GPIO.Pin               = GPIO_PIN_6 | GPIO_PIN_7;
        I2C_GPIO.Mode              = GPIO_MODE_OUTPUT_OD;
        I2C_GPIO.Pull              = GPIO_PULLUP;
        I2C_GPIO.Speed             = GPIO_SPEED_FAST;
        I2C_GPIO.Alternate         = GPIO_AF4_I2C1;
        HAL_GPIO_Init(GPIOB, &I2C_GPIO);
    }
    else if (hi2c->Instance == I2C2)
    {
        /* Peripheral clock enable */
        __HAL_RCC_I2C2_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /** I2C1 GPIO Configuration
         * PB10   ------> I2C1_SCL
         * PB11   ------> I2C1_SDA
         */
        I2C_GPIO.Pin               = GPIO_PIN_10 | GPIO_PIN_11;
        I2C_GPIO.Mode              = GPIO_MODE_OUTPUT_OD;
        I2C_GPIO.Pull              = GPIO_PULLUP;
        I2C_GPIO.Speed             = GPIO_SPEED_FAST;
        I2C_GPIO.Alternate         = GPIO_AF4_I2C1;
        HAL_GPIO_Init(GPIOB, &I2C_GPIO);
    }
    return RE_OK;
}

/**
 * @brief Initialize the I2C1 peripheral
 * @param None
 * @retval Exit status
 */
RE_StatusTypeDef RE_SoC_I2C1_Init(void)
{
    __HAL_RCC_I2C1_CLK_ENABLE();
    hi2c1_t.Instance                    = I2C1;                                /* I2C1 register definition */
    hi2c1_t.Init.AddressingMode         = I2C_ADDRESSINGMODE_7BIT;  /* 7-bit addressing mode */
    hi2c1_t.Init.ClockSpeed             = 100000; /* SCL frequency set to 100Khz (standard mode) */
    hi2c1_t.Init.OwnAddress1            = 0;
    hi2c1_t.Init.OwnAddress2            = 0;
    hi2c1_t.Init.DualAddressMode        = I2C_DUALADDRESS_DISABLE; /* Dual addressing mode disabled */
    hi2c1_t.Init.DutyCycle              = I2C_DUTYCYCLE_2;               /* 50% duty cycle */
    hi2c1_t.Init.GeneralCallMode        = I2C_GENERALCALL_DISABLE; /* 0 : Disable */
    hi2c1_t.Init.NoStretchMode          = I2C_NOSTRETCH_DISABLE;     /* 0 : Disable */
    if (RE_I2C_GpioInit(&hi2c1_t) == RE_OK)
    {
        if (HAL_I2C_Init(&hi2c1_t) != HAL_OK)
        {
            RE_Error_Handler(__FILE__, __LINE__);
        }
    }
    return RE_OK;
}

/**
 * @brief Initialize the I2C1 peripheral
 * @param None
 * @retval Exit status
 */
RE_StatusTypeDef RE_NVS_I2C2_Init (void)
{
    __HAL_RCC_I2C2_CLK_ENABLE();
    hi2c2_t.Instance                    = I2C2;                                /* I2C1 register definition */
    hi2c2_t.Init.AddressingMode         = I2C_ADDRESSINGMODE_7BIT;  /* 7-bit addressing mode */
    hi2c2_t.Init.ClockSpeed             = 100000; /* SCL frequency set to 100Khz (standard mode) */
    hi2c2_t.Init.OwnAddress1            = 0;
    hi2c2_t.Init.OwnAddress2            = 0;
    hi2c2_t.Init.DualAddressMode        = I2C_DUALADDRESS_DISABLE; /* Dual addressing mode disabled */
    hi2c2_t.Init.DutyCycle              = I2C_DUTYCYCLE_2;               /* 50% duty cycle */
    hi2c2_t.Init.GeneralCallMode        = I2C_GENERALCALL_DISABLE; /* 0 : Disable */
    hi2c2_t.Init.NoStretchMode          = I2C_NOSTRETCH_DISABLE;     /* 0 : Disable */
    if (RE_I2C_GpioInit(&hi2c2_t) == RE_OK)
    {
        if (HAL_I2C_Init(&hi2c2_t) != HAL_OK)
        {
            RE_Error_Handler(__FILE__, __LINE__);
        }
    }
    return RE_OK;
}

/************************ (C) COPYRIGHT RACEnergy **********END OF FILE********/
