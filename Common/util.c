
/**
 ******************************************************************************
 * @file    util.c
 * @author  MCU Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   util function
 ******************************************************************************
 */
#include "util.h"
#include "io_mapping.h"
#include "zb32l03x_hal.h"
//=============================================================================
//                  Constant Definition
//=============================================================================

//=============================================================================
//                  Macro Definition
//=============================================================================

//=============================================================================
//                  Structure Definition
//=============================================================================

//=============================================================================
//                  Global Data Definition
//=============================================================================

//=============================================================================
//                  Private Function Definition
//=============================================================================

//=============================================================================
//                  Public Function Definition
//=============================================================================
void Util_Error_Handler(void)
{
    /* User can add his own implementation here */
}

/**
  * @brief  System Clock Configuration
  * @note   Default System Clock is around 4MHz
  * @retval None
  */
__weak void SystemClock_Config(void)
{
    RCC_OscInitTypeDef  RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef  RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType       = RCC_OSCILLATORTYPE_HIRC;
    RCC_OscInitStruct.HIRCState            = RCC_HIRC_ON;
    RCC_OscInitStruct.HIRCCalibrationValue = RCC_HIRCCALIBRATION_DEFAULT;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Util_Error_Handler();
    }

    /* Initializes the CPU, AHB and APB busses clocks */
    RCC_ClkInitStruct.ClockType     = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK;
    RCC_ClkInitStruct.SYSCLKSource  = RCC_SYSCLKSOURCE_HIRC;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APBCLKDivider = RCC_PCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
    {
        Util_Error_Handler();
    }
}

void delay(unsigned int delay_ticks)
{
    delay_ticks >>= 2;
    delay_ticks = (delay_ticks) ? delay_ticks : 1;
    while( delay_ticks-- ) {}
    return;
}
