/**
 ******************************************************************************
 * @file    zb32l03x_hal_rcc.c
 * @author  MCU Software Team
 * @Version V1.1.0
 * @Date    2022/01/19
 * @brief   RCC HAL module driver.
 *          This file provides firmware functions to manage the following
 *          functionalities of the Reset and Clock Control (RCC) peripheral:
 *
 @verbatim
 **/


#include "zb32l03x_hal.h"

/** @addtogroup ZB32L03x_HAL_Driver
 * @{
 */

/** @defgroup RCC RCC
 * @brief RCC HAL module driver
 * @{
 */

#if defined(HAL_RCC_MODULE_ENABLED)

/** @defgroup RCC_Private_Constants RCC Private Constants
 * @{
 */

/**
 * @}
 */

/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */

#if defined(CONFIG_USE_ZB32L003S)
    #define MCO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()
    #define MCO_GPIO_PORT        GPIOC
    #define MCO_PIN              GPIO_PIN_4
    #define MCO_GPIO_AF          GPIO_AF_MODE_7

#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    #if 1
    /* PB0 */
    #define MCO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
    #define MCO_GPIO_PORT        GPIOB
    #define MCO_PIN              GPIO_PIN_0
    #define MCO_GPIO_AF          GPIO_AF_MODE_7

    #elif (0)
    /* PC5*/
    #define MCO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()
    #define MCO_GPIO_PORT        GPIOC
    #define MCO_PIN              GPIO_PIN_5
    #define MCO_GPIO_AF          GPIO_AF_MODE_6

    #else
    /* PD1 */
    #define MCO_CLK_ENABLE()     __HAL_RCC_GPIOD_CLK_ENABLE()
    #define MCO_GPIO_PORT        GPIOD
    #define MCO_PIN              GPIO_PIN_1
    #define MCO_GPIO_AF          GPIO_AF_MODE_7
    #endif
#endif  /* CONFIG_USE_ZB32L030 || CONFIG_USE_ZB32L032 */

/**
 * @}
 */

/** @defgroup RCC_Private_Variables RCC Private Variables
 * @{
 */
/**
 * @}
 */

/** @addtogroup RCC_Private_Functions
 * @{
 */


/**
 * @brief  This function provides delay (in milliseconds) based on CPU cycles method.
 * @param  mdelay: specifies the delay time length, in milliseconds.
 * @retval None
 */
static void RCC_Delay(uint32_t mdelay)
{
    __IO uint32_t Delay = mdelay * (SystemCoreClock / 8U / 1000U);
    do {
        __NOP();
    } while (Delay --);
    return;
}

/**
 * @}
 */ /* End of group RCC_Private_Functions */


/** @defgroup RCC_Exported_Functions RCC Exported Functions
 * @{
 */

/** @defgroup RCC_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
 @verbatim
 ===============================================================================
          ##### Initialization and de-initialization functions #####
 ===============================================================================
   [..]
     This section provides functions allowing to configure the internal/external oscillators
     (HIRC, HXT, SIRC, LXT and MCO) and the System buses clocks (SYSCLK, AHB, APB).
 @endverbatim
 * @{
 */

/**
 * @brief  Resets the RCC clock configuration to the default reset state.
 * @note   The default reset state of the clock configuration is given below:
 *            - HIRC ON and used as system clock source
 *            - HXT are OFF
 *            - AHB, APB prescaler set to 1.
 *            - MCO OFF
 * @note   This function does not modify the configuration of the
 *            - Peripheral clocks
 *            - SIRC, LXT clocks
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_RCC_DeInit(void)
{
    uint32_t tickstart;

    /* Get Start Tick */
    tickstart = HAL_GetTick();

    /* Set HIRCEN bit */
    __HAL_RCC_HIRC_ENABLE();

    /* Wait till HSI is ready */
    while (READ_BIT(RCC->HIRCCR, RCC_HIRCCR_HIRCRDY) == RESET)
    {
        if ((HAL_GetTick() - tickstart) > HIRC_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    /* Get Start Tick */
    tickstart = HAL_GetTick();

    /* Reset SYSCLKSEL register */
    __HAL_RCC_SYSCLK_CONFIG(RCC_SYSCLKSOURCE_HIRC);

    /* Wait till clock switch is ready */
    while (READ_BIT(RCC->SYSCLKSEL, RCC_SYSCLKSOURCE_HIRC) != RESET)
    {
        if ((HAL_GetTick() - tickstart) > CLOCKSWITCH_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    /* Update the SystemCoreClock global variable */
    SystemCoreClock = HIRC_VALUE_4M;

    /* Adapt Systick interrupt period */
    if(HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK)
    {
        return HAL_ERROR;
    }

    /* Get Start Tick */
    tickstart = HAL_GetTick();

    /* Reset HXTEN & HXTBYP bits */
    __HAL_RCC_HXT_CONFIG(RCC_HXT_DEFAULT);

    /* Wait till HXT is disabled */
    while (READ_BIT(RCC->HXTCR, RCC_HXTCR_HXTRDY) != RESET)
    {
        if ((HAL_GetTick() - tickstart) > HXT_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    /* Get Start Tick */
    tickstart = HAL_GetTick();

    /* Reset SIRCEN bits */
    __HAL_RCC_SIRC_DISABLE();

    /* Wait till SIRC is disabled */
    while (READ_BIT(RCC->SIRCCR, RCC_SIRCCR_SIRCRDY) != RESET)
    {
        if ((HAL_GetTick() - tickstart) > SIRC_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    CLEAR_REG(RCC->MCOCR);

    return HAL_OK;
}

/**
 * @brief  Initializes the RCC Oscillators according to the specified parameters in the
 *         RCC_OscInitTypeDef.
 * @param  RCC_OscInitStruct pointer to an RCC_OscInitTypeDef structure that
 *         contains the configuration information for the RCC Oscillators.
 * @note   IMPORTANT! PACKAGE Macro SHOULD be defined to select the right calibaration value if TSSOP-20 and QFN-20 packaged
 *                   products are used. Otherwise if the KGD(wafer) products are used, the PACKAGE Macro SHOULD NOT be defined. For more
 *                   details please refer to chapter 6.4.10 in User Manual.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
    uint32_t tickstart = 0U;

    /* Check the parameters */
    assert_param(RCC_OscInitStruct != NULL);
    assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));

    /*----------------------------- HIRC Configuration --------------------------*/
    if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HIRC) == RCC_OSCILLATORTYPE_HIRC)
    {
        /* Check the parameters */
        assert_param(IS_RCC_HIRC(RCC_OscInitStruct->HIRCState));
        assert_param(IS_RCC_CALIBRATION_VALUE(RCC_OscInitStruct->HIRCCalibrationValue));

        /* Check if HIRC is used as system clock*/
        if(__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_HIRC)
        {
            /* When HIRC is used as system clock it will not disabled */
            if((__HAL_RCC_GET_FLAG(RCC_FLAG_HIRCRDY) != SET) && ((RCC_OscInitStruct->HIRCState) != RCC_HIRC_ON))
            {
                return HAL_ERROR;
            }
            /* Otherwise, just the calibration is allowed */
            else
            {
                /* Adjusts the Internal High Speed oscillator (HIRC) calibration value.*/
                __HAL_RCC_HIRC_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HIRCCalibrationValue);
            }
        }
        else
        {
            /* Check the HIRC State */
            if(RCC_OscInitStruct->HIRCState != RCC_HIRC_OFF)
            {
                /* Adjusts the Internal High Speed oscillator (HIRC) calibration value.*/
                __HAL_RCC_HIRC_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HIRCCalibrationValue);

                /* Enable the Internal High Speed oscillator (HIRC). */
                __HAL_RCC_HIRC_ENABLE();

                /* Get Start Tick */
                tickstart = HAL_GetTick();

                /* Wait till HIRC is ready */
                while(__HAL_RCC_GET_FLAG(RCC_FLAG_HIRCRDY) == RESET)
                {
                    if((HAL_GetTick() - tickstart ) > HIRC_TIMEOUT_VALUE)
                    {
                        return HAL_TIMEOUT;
                    }
                }
            }
            else
            {
                /* Disable the Internal High Speed oscillator (HIRC). */
                __HAL_RCC_HIRC_DISABLE();

                /* Get Start Tick */
                tickstart = HAL_GetTick();

                /* Wait till HIRC is disabled */
                while(__HAL_RCC_GET_FLAG(RCC_FLAG_HIRCRDY) != RESET)
                {
                    if((HAL_GetTick() - tickstart ) > HIRC_TIMEOUT_VALUE)
                    {
                        return HAL_TIMEOUT;
                    }
                }
            }
        }
    }

    /*------------------------------ SIRC Configuration -------------------------*/
    if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_SIRC) == RCC_OSCILLATORTYPE_SIRC)
    {
        /* Check the parameters */
        assert_param(IS_RCC_SIRC(RCC_OscInitStruct->SIRCState));

        /* Check the SIRC State */
        if(RCC_OscInitStruct->SIRCState != RCC_SIRC_OFF)
        {
            __HAL_RCC_SIRC_STARTUP_CONFIG(RCC_OscInitStruct->SIRCStartupValue);

            /* Adjusts the Internal Low Speed oscillator (SIRC) calibration value.*/
            __HAL_RCC_SIRC_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->SIRCCalibrationValue);

            /* Enable the Internal Low Speed oscillator (SIRC). */
            __HAL_RCC_SIRC_ENABLE();

            /* Get Start Tick */
            tickstart = HAL_GetTick();

            /* Wait till SIRC is ready */
            while(__HAL_RCC_GET_FLAG(RCC_FLAG_SIRCRDY) == RESET)
            {
                if((HAL_GetTick() - tickstart ) > SIRC_TIMEOUT_VALUE)
                {
                    return HAL_TIMEOUT;
                }
            }
            /*  To have a fully stabilized clock in the specified range, a software delay of 1ms
                should be added.*/
            RCC_Delay(1);
        }
        else
        {
            /* Disable the Internal Low Speed oscillator (SIRC). */
            __HAL_RCC_SIRC_DISABLE();

            /* Get Start Tick */
            tickstart = HAL_GetTick();

            /* Wait till LSI is disabled */
            while(__HAL_RCC_GET_FLAG(RCC_FLAG_SIRCRDY) != RESET)
            {
                if((HAL_GetTick() - tickstart ) > SIRC_TIMEOUT_VALUE)
                {
                    return HAL_TIMEOUT;
                }
            }
        }
    }
    /*------------------------------- HXT Configuration ------------------------*/
    if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HXT) == RCC_OSCILLATORTYPE_HXT)
    {
        /* Check the parameters */
        assert_param(IS_RCC_HXT(RCC_OscInitStruct->HXTState));

        /* When the HXT is used as system clock */
        if(__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_HXT)
        {
            if((__HAL_RCC_GET_FLAG(RCC_FLAG_HXTRDY) != RESET) && (RCC_OscInitStruct->HXTState == RCC_HXT_OFF))
            {
                return HAL_ERROR;
            }
        }
        else
        {
            /* Set the new HXT configuration ---------------------------------------*/
            __HAL_RCC_HXT_CONFIG(RCC_OscInitStruct->HXTState);

            /* Check the HXT State */
            if(RCC_OscInitStruct->HXTState != RCC_HXT_OFF)
            {
                /* Get Start Tick */
                tickstart = HAL_GetTick();

                /* Wait till HXT is ready */
                while(__HAL_RCC_GET_FLAG(RCC_FLAG_HXTRDY) == RESET)
                {
                    if((HAL_GetTick() - tickstart ) > HXT_TIMEOUT_VALUE)
                    {
                        return HAL_TIMEOUT;
                    }
                }
            }
            else
            {
                /* Get Start Tick */
                tickstart = HAL_GetTick();

                /* Wait till HXT is disabled */
                while(__HAL_RCC_GET_FLAG(RCC_FLAG_HXTRDY) != RESET)
                {
                    if((HAL_GetTick() - tickstart ) > HXT_TIMEOUT_VALUE)
                    {
                        return HAL_TIMEOUT;
                    }
                }
            }
        }
    }

    /*------------------------------ LXT Configuration -------------------------*/
    if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LXT) == RCC_OSCILLATORTYPE_LXT)
    {
        /* Check the parameters */
        assert_param(IS_RCC_LXT(RCC_OscInitStruct->LXTState));

        /* Set the new LXT configuration -----------------------------------------*/
        __HAL_RCC_LXT_CONFIG(RCC_OscInitStruct->LXTState);
        /* Check the LSE State */
        if(RCC_OscInitStruct->LXTState != RCC_LXT_OFF)
        {
            /* Get Start Tick */
            tickstart = HAL_GetTick();

            /* Wait till LSE is ready */
            while(__HAL_RCC_GET_FLAG(RCC_FLAG_LXTRDY) == RESET)
            {
                if((HAL_GetTick() - tickstart ) > RCC_LXT_TIMEOUT_VALUE)
                {
                    return HAL_TIMEOUT;
                }
            }
        }
        else
        {
            /* Get Start Tick */
            tickstart = HAL_GetTick();

            /* Wait till LSE is disabled */
            while(__HAL_RCC_GET_FLAG(RCC_FLAG_LXTRDY) != RESET)
            {
                if((HAL_GetTick() - tickstart ) > RCC_LXT_TIMEOUT_VALUE)
                {
                    return HAL_TIMEOUT;
                }
            }
        }
    }

#if defined(CONFIG_USE_ZB32L032)
    /*------------------------------ PLL Configuration -------------------------*/
    if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_PLL) == RCC_OSCILLATORTYPE_PLL)
    {
        assert_param(IS_RCC_PLL(RCC_OscInitStruct->PLL.PLLState));

        {   /* check PLL parameters */
            uint8_t     pll_n = 0, pll_m = 0, pll_source = 0, pll_sys_div = 0;
            uint16_t    freq_mhz = 0;

            pll_n = (RCC_OscInitStruct->PLL.PLLSourceDiv == RCC_PLLSource_PreDiv2) ? 2u :
                    (RCC_OscInitStruct->PLL.PLLSourceDiv == RCC_PLLSource_PreDiv4) ? 4u :
                    (RCC_OscInitStruct->PLL.PLLSourceDiv == RCC_PLLSource_PreDiv6) ? 6u :
                    1u;

            pll_m = (uint8_t)RCC_OscInitStruct->PLL.PLLMul;

            pll_sys_div = (RCC_OscInitStruct->PLL.PLLSysClkDivider == RCC_PLLSys_Div4) ? 4u :
                          (RCC_OscInitStruct->PLL.PLLSysClkDivider == RCC_PLLSys_Div3) ? 3u :
                          2u;

            pll_source = RCC_OscInitStruct->PLL.PLLSourceMHz;

            /* 4MHz <= PLL_N_output <= 8MHz */
            freq_mhz = pll_source / pll_n;
            if( freq_mhz < 4 || freq_mhz > 8 )
                return HAL_RCC_OUT_RANGE;

            /* check PLL output: 128MHz <= PLL_output <= 192MHz */
            freq_mhz = freq_mhz * pll_m;
            if( freq_mhz < 128 || freq_mhz > 192 )
                return HAL_RCC_OUT_RANGE;

            /* check PLL_SYS clock: 2MHz <= PLL_SYS <= 64MHz */
            freq_mhz = freq_mhz / pll_sys_div;
            if( freq_mhz < 2 || freq_mhz > 64 )
                return HAL_RCC_OUT_RANGE;
        }

        /* Check if PLL is used as system clock */
        if(__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLL)
        {
            /**
             *  PLL parameters can NOT be modified at run-time,
             *  it MUST switch to the other clock firstly.
             */
            if( __HAL_RCC_IS_PLL_READY() == RESET &&
                RCC_OscInitStruct->PLL.PLLState != RCC_PLL_ON )
            {
                return HAL_ERROR;
            }
        }
        else
        {
            uint32_t    target_state = SET;

            if( RCC_OscInitStruct->PLL.PLLState == RCC_PLL_ON )
            {
                uint32_t    value = 0ul;

                value = (RCC->PLLCR2 | (RCC_KEY_UNLOCK << RCC_PLLCR2_KEY_Pos));

                __HAL_RCC_REGWR_UNLOCK();

                /* Set RCLK */
                MODIFY_REG(value, RCC_PLLCR2_SELRCLK_Msk,
                           (RCC_OscInitStruct->PLL.PLLSource == RCC_PLLSOURCE_XTAL) ? RCC_PLLCR2_SELRCLK_XTAL :
                           (RCC_OscInitStruct->PLL.PLLSource == RCC_PLLSOURCE_OSC)  ? RCC_PLLCR2_SELRCLK_OSC :
                           RCC_PLLCR2_SELRCLK_HIRC);

                /* set N */
                MODIFY_REG(value, RCC_PLLCR2_PLL_N_Msk,
                           (RCC_OscInitStruct->PLL.PLLSourceDiv == RCC_PLLSource_PreDiv2) ? RCC_PLLCR2_PLL_N_RCLK_DIV2 << RCC_PLLCR2_PLL_N_Pos :
                           (RCC_OscInitStruct->PLL.PLLSourceDiv == RCC_PLLSource_PreDiv4) ? RCC_PLLCR2_PLL_N_RCLK_DIV4 << RCC_PLLCR2_PLL_N_Pos :
                           (RCC_OscInitStruct->PLL.PLLSourceDiv == RCC_PLLSource_PreDiv6) ? RCC_PLLCR2_PLL_N_RCLK_DIV6 << RCC_PLLCR2_PLL_N_Pos :
                           RCC_PLLCR2_PLL_N_RCLK_DIV1 << RCC_PLLCR2_PLL_N_Pos);

                /* set M */
                MODIFY_REG(value, RCC_PLLCR2_PLL_M_Msk, ((uint32_t)RCC_OscInitStruct->PLL.PLLMul << RCC_PLLCR2_PLL_M_Pos));

                WRITE_REG(RCC->PLLCR2, value);

                /* Set PLL Sys division */
                value = (RCC->PLLCR1 | (RCC_KEY_UNLOCK << RCC_PLLCR1_KEY_Pos));
                MODIFY_REG(value, RCC_PLLCR1_PLLSYS_Msk,
                           (RCC_OscInitStruct->PLL.PLLSysClkDivider == RCC_PLLSys_Div4) ? RCC_PLLCR1_PLLSYS_DIV4 << RCC_PLLCR1_PLLSYS_Pos :
                           (RCC_OscInitStruct->PLL.PLLSysClkDivider == RCC_PLLSys_Div3) ? RCC_PLLCR1_PLLSYS_DIV3 << RCC_PLLCR1_PLLSYS_Pos :
                           RCC_PLLCR1_PLLSYS_DIV2 << RCC_PLLCR1_PLLSYS_Pos);

                /* Adjusts the PLL step value.*/
                MODIFY_REG(value, RCC_PLLCR1_PLLTRIM_Msk, (RCC_OscInitStruct->PLL.PLLCalibrationValue << RCC_PLLCR1_PLLTRIM_Pos));

                WRITE_REG(RCC->PLLCR1, value);

                __HAL_RCC_REGWR_LOCK();

                __HAL_RCC_PLL_ENABLE();
            }
            else
            {
                target_state = RESET;
                __HAL_RCC_PLL_DISABLE();
            }

            /* Wait H/w response */
            tickstart = HAL_GetTick();

            while( __HAL_RCC_IS_PLL_READY() != target_state )
            {
                if((HAL_GetTick() - tickstart ) > HIRC_TIMEOUT_VALUE)
                {
                    return HAL_TIMEOUT;
                }
            }
        }
    }
#endif  /* defined(CONFIG_USE_ZB32L032) */

    return HAL_OK;
}

/**
 * @brief  Initializes the CPU, AHB and APB buses clocks according to the specified
 *         parameters in the RCC_ClkInitStruct.
 * @param  RCC_ClkInitStruct pointer to an RCC_OscInitTypeDef structure that
 *         contains the configuration information for the RCC peripheral.
 * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency
 *         and updated by @ref HAL_RCC_GetHCLKFreq() function called within this function
 *
 * @note   A switch from one clock source to another occurs only if the target
 *         clock source is ready.
 *         If a clock source which is not yet ready is selected, the switch will
 *         occur when the clock source will be ready.
 *         You can use @ref HAL_RCC_GetClockConfig() function to know which clock is
 *         currently used as system clock source.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct)
{
    uint32_t tickstart = 0U;

    /* Check the parameters */
    assert_param(RCC_ClkInitStruct != NULL);
    assert_param(IS_RCC_CLOCKTYPE(RCC_ClkInitStruct->ClockType));

    /*-------------------------- HCLK Configuration --------------------------*/
    if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
    {
        /* Set the highest APBx dividers in order to ensure that we do not go through
        a non-spec phase whatever we decrease or increase HCLK. */
        if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK) == RCC_CLOCKTYPE_PCLK)
        {
            MODIFY_REG(RCC->PCLKDIV, RCC_PCLKDIV_APBCKDIV, RCC_ClkInitStruct->APBCLKDivider);
        }

        /* Set the new HCLK clock divider */
        assert_param(IS_RCC_HCLK(RCC_ClkInitStruct->AHBCLKDivider));
        MODIFY_REG(RCC->HCLKDIV, RCC_HCLKDIV_AHBCKDIV, RCC_ClkInitStruct->AHBCLKDivider);
    }

    /*------------------------- SYSCLK Configuration ---------------------------*/
    if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK)
    {
        assert_param(IS_RCC_SYSCLKSOURCE(RCC_ClkInitStruct->SYSCLKSource));

        /* HIRC is selected as System Clock Source */
        if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HIRC)
        {
            /* Check the HIRC ready flag */
            if(__HAL_RCC_GET_FLAG(RCC_FLAG_HIRCRDY) == RESET)
            {
                return HAL_ERROR;
            }
        }
        /* HXT is selected as System Clock Source */
        else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HXT)
        {
            /* Check the HXT ready flag */
            if(__HAL_RCC_GET_FLAG(RCC_FLAG_HXTRDY) == RESET)
            {
                return HAL_ERROR;
            }
        }
    #if defined(CONFIG_USE_ZB32L032)
        /* PLL is selected as System Clock Source */
        else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLL)
        {
            if( __HAL_RCC_IS_PLL_READY() == RESET )
                return HAL_ERROR;
        }
    #endif  /* defined(CONFIG_USE_ZB32L032) */
        /* SIRC is selected as System Clock Source */
        else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_SIRC)
        {
            /* Check the SIRC ready flag */
            if(__HAL_RCC_GET_FLAG(RCC_FLAG_SIRCRDY) == RESET)
            {
                return HAL_ERROR;
            }
        }
        else
        {
            /* Check the LXT ready flag */
            if(__HAL_RCC_GET_FLAG(RCC_FLAG_LXTRDY) == RESET)
            {
                return HAL_ERROR;
            }
        }
        __HAL_RCC_SYSCLK_CONFIG(RCC_ClkInitStruct->SYSCLKSource);

        /* Get Start Tick */
        tickstart = HAL_GetTick();

        if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HIRC)
        {
            while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HIRC)
            {
                if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
                {
                    return HAL_TIMEOUT;
                }
            }
        }
        else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HXT)
        {
            while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HXT)
            {
                if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
                {
                    return HAL_TIMEOUT;
                }
            }
        }
    #if defined(CONFIG_USE_ZB32L032)
        else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLL)
        {
            while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_PLL)
            {
                if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
                {
                    return HAL_TIMEOUT;
                }
            }
        }
    #endif  /* defined(CONFIG_USE_ZB32L032 */
        else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_SIRC)
        {
            while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_SIRC)
            {
                if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
                {
                    return HAL_TIMEOUT;
                }
            }
        }
        else if(RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_LXT)
        {
            while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_LXT)
            {
                if((HAL_GetTick() - tickstart ) > CLOCKSWITCH_TIMEOUT_VALUE)
                {
                    return HAL_TIMEOUT;
                }
            }
        }
    }

    /*-------------------------- PCLK Configuration ---------------------------*/
    if(((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK) == RCC_CLOCKTYPE_PCLK)
    {
        assert_param(IS_RCC_PCLK(RCC_ClkInitStruct->APBCLKDivider));
        MODIFY_REG(RCC->PCLKDIV, RCC_PCLKDIV_APBCKDIV, RCC_ClkInitStruct->APBCLKDivider);
    }

    /* Update the SystemCoreClock global variable */
    if((RCC->HCLKDIV & RCC_HCLKDIV_AHBCKDIV) != 0)
        SystemCoreClock = (HAL_RCC_GetSysClockFreq() >> 1) / (RCC->HCLKDIV & RCC_HCLKDIV_AHBCKDIV);
    else
        SystemCoreClock = HAL_RCC_GetSysClockFreq();

    /* Configure system tick overflow to 100Hz because of low frequency of LXT or SIRC*/
    if((RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_SIRC) || (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_LXT))
    {
        uwTickFreq = HAL_TICK_FREQ_100HZ;
    }
    /* Configure the source of time base considering new system clocks settings*/
    HAL_InitTick (TICK_INT_PRIORITY);

    return HAL_OK;
}

/**
 * @}
 */ /*End of group RCC_Exported_Functions_Group1*/


/** @defgroup RCC_Exported_Functions_Group2 Peripheral Control functions
 *  @brief   RCC clocks control functions
 *
 @verbatim
 ===============================================================================
                 ##### Peripheral Control functions #####
 ===============================================================================
   [..]
   This subsection provides a set of functions allowing to control the RCC Clocks
   frequencies.

 @endverbatim
 * @{
 */

/**
 * @brief  Selects the clock source to output on MCO pin.
 * @note   MCO pin should be configured in alternate function mode.
 * @param  RCC_MCOx specifies the output direction for the clock source.
 *          This parameter can be one of the following values:
 *            @arg @ref RCC_MCOx Clock source to output on MCO pin(PC4/PC6).
 * @param  RCC_MCOSource specifies the clock source to output.
 *          This parameter can be one of the following values:
 *            @arg @ref RCC_MCOSOURCE_HIRC     HIRC selected as MCO clock
 *            @arg @ref RCC_MCOSOURCE_HXT      HXT selected as MCO clock
 *            @arg @ref RCC_MCOSOURCE_SIRC     SIRC selected as MCO clock
 *            @arg @ref RCC_MCOSOURCE_LXT      LXT selected as MCO clock
 *            @arg @ref RCC_MCOSOURCE_SYSCLK   SYSCLK selected as MCO clock
 *            @arg @ref RCC_MCOSOURCE_HCLK     HCLK selected as MCO clock
 *            @arg @ref RCC_MCOSOURCE_PCLK     PCLK selected as MCO clock
 * @param  RCC_MCODiv specifies the MCO DIV.
 *          This parameter can be one of the following values:
 *            @arg @ref RCC_MCODIV_1 no division applied to MCO clock
 * @retval None
 */
void HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv)
{
    GPIO_InitTypeDef gpio = {0U};

    /* Check the parameters */
    assert_param(IS_RCC_MCO(RCC_MCOx));
    assert_param(IS_RCC_MCODIV(RCC_MCODiv));
    assert_param(IS_RCC_MCO1SOURCE(RCC_MCOSource));

    /* Prevent unused argument(s) compilation warning */
    UNUSED(RCC_MCOx);
    UNUSED(RCC_MCODiv);

    /* Configure the MCO pin in alternate function mode */
    gpio.Mode      = GPIO_MODE_AF;
    gpio.SlewRate  = GPIO_SLEW_RATE_HIGH;
    gpio.Pull      = GPIO_NOPULL;
    gpio.Pin       = MCO_PIN;
    gpio.Alternate = MCO_GPIO_AF;
    /* MCO Clock Enable */
    MCO_CLK_ENABLE();

    HAL_GPIO_Init(MCO_GPIO_PORT, &gpio);

    /* Configure the MCO clock source */
    __HAL_RCC_MCO_CONFIG(RCC_MCOSource, RCC_MCODiv);
}


/**
 * @brief  Returns the SYSCLK frequency
 * @note   The system frequency computed by this function is not the real
 *         frequency in the chip. It is calculated based on the predefined
 *         constant and the selected clock source:
 * @note     If SYSCLK source is HIRC, function returns values based on HIRC_VALUE_xxM
 * @note     If SYSCLK source is HXT, function returns a value based on HXT_VALUE
 * @note     If SYSCLK source is SIRC, function returns a value based on SIRC_VALUE
 * @note     If SYSCLK source is LXT, function returns a value based on LXT_VALUE
 * @note     HIRC_VALUE_xxM is a constant defined in zb32l03x_hal_conf.h file (default value
 *           4 MHz) but the real value may vary depending on the variations in voltage and temperature.
 * @note     HXT_VALUE is a constant defined in zb32l03x_hal_conf.h file (default value
 *           8 MHz), user has to ensure that HSE_VALUE is same as the real
 *           frequency of the crystal used. Otherwise, this function may
 *           have wrong result.
 * @note     SIRC_VALUE is a constant defined in zb32l03x_hal_conf.h file (default value
 *           38.4 KHz) but the real value may vary depending on the variations
 *           in voltage and temperature.
 * @note     LXT_VALUE is a constant defined in zb32l03x_hal_conf.h file (default value
 *           32.768 KHz), user has to ensure that LXT_VALUE is same as the real
 *           frequency of the crystal used. Otherwise, this function may
 *           have wrong result.
 *
 * @note   This function can be used by the user application to compute the
 *         baud-rate for the communication peripherals or configure other parameters.
 *
 * @note   Each time SYSCLK changes, this function must be called to update the
 *         right SYSCLK value. Otherwise, any configuration based on this function will be incorrect.
 *
 * @retval SYSCLK frequency
 */
uint32_t HAL_RCC_GetSysClockFreq(void)
{
    uint32_t tmpreg = 0U;
    uint32_t sysclockfreq = 0U;

    tmpreg = RCC->SYSCLKSEL;

    /* Get SYSCLK source -------------------------------------------------------*/
    switch (tmpreg & RCC_SYSCLKSEL_CLKSW)
    {
        case RCC_SYSCLKSOURCE_STATUS_HIRC:  /* HIRC used as system clock */
            {
                if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_24M)
                {
                    sysclockfreq = HIRC_VALUE_24M;
                }
                else if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_22M)
                {
                    sysclockfreq = HIRC_VALUE_22M;
                }
                else if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_16M)
                {
                    sysclockfreq = HIRC_VALUE_16M;
                }
                else if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_8M)
                {
                    sysclockfreq = HIRC_VALUE_8M;
                }
                else if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_4M)
                {
                    sysclockfreq = HIRC_VALUE_4M;
                }
                else
                {
                    sysclockfreq = HIRC_VALUE_4M;
                }
                break;
            }
        case RCC_SYSCLKSOURCE_STATUS_HXT:  /* HXT used as system clock */
            {
                sysclockfreq = HXT_VALUE;
                break;
            }
        case RCC_SYSCLKSOURCE_STATUS_SIRC:  /* SIRC used as system clock */
            {
                sysclockfreq = SIRC_VALUE;
                break;
            }
    #if defined(CONFIG_USE_ZB32L032)
        case RCC_SYSCLKSOURCE_STATUS_PLL:
            {
                uint16_t        pll_n = 0;
                uint16_t        pll_m = 0;
                uint32_t        rclk = 0;
                uint16_t        pll_sys_div = 0;

                if( (RCC->PLLCR2 & RCC_PLLCR2_SELRCLK_Msk) == RCC_PLLSOURCE_XTAL )
                    rclk = HXT_VALUE;
                else if( (RCC->PLLCR2 & RCC_PLLCR2_SELRCLK_Msk) == RCC_PLLSOURCE_OSC )
                    rclk = HXT_VALUE;
                else
                {
                    /* RCLK is HIRC */
                    if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_24M)
                        rclk = HIRC_VALUE_24M;
                    else if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_22M)
                        rclk = HIRC_VALUE_22M;
                    else if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_16M)
                        rclk = HIRC_VALUE_16M;
                    else if((uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos) == RCC_HIRCCALIBRATION_8M)
                        rclk = HIRC_VALUE_8M;
                    else
                        rclk = HIRC_VALUE_4M;
                }

                pll_n = (((RCC->PLLCR2 & RCC_PLLCR2_PLL_N_Msk) >> RCC_PLLCR2_PLL_N_Pos) == RCC_PLLCR2_PLL_N_RCLK_DIV6) ? 6 :
                        (((RCC->PLLCR2 & RCC_PLLCR2_PLL_N_Msk) >> RCC_PLLCR2_PLL_N_Pos) == RCC_PLLCR2_PLL_N_RCLK_DIV4) ? 4 :
                        (((RCC->PLLCR2 & RCC_PLLCR2_PLL_N_Msk) >> RCC_PLLCR2_PLL_N_Pos) == RCC_PLLCR2_PLL_N_RCLK_DIV2) ? 2 :
                        1;

                pll_m = (RCC->PLLCR2 & RCC_PLLCR2_PLL_M_Msk) >> RCC_PLLCR2_PLL_M_Pos;

                pll_sys_div = (((RCC->PLLCR1 & RCC_PLLCR1_PLLSYS_Msk) >> RCC_PLLCR1_PLLSYS_Pos) == RCC_PLLCR1_PLLSYS_DIV3) ? 3 :
                              (((RCC->PLLCR1 & RCC_PLLCR1_PLLSYS_Msk) >> RCC_PLLCR1_PLLSYS_Pos) == RCC_PLLCR1_PLLSYS_DIV4) ? 4 :
                              2;

                sysclockfreq = (rclk * pll_m) / (pll_n * pll_sys_div);
            }
            break;
    #endif
        default: /* LXT used as system clock */
            {
                sysclockfreq = LXT_VALUE;
                break;
            }
    }
    return sysclockfreq;
}

/**
 * @brief  Returns the HCLK frequency
 * @note   Each time HCLK changes, this function must be called to update the
 *         right HCLK value. Otherwise, any configuration based on this function will be incorrect.
 *
 * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency
 *         and updated within this function
 * @retval HCLK frequency
 */
uint32_t HAL_RCC_GetHCLKFreq(void)
{
    return SystemCoreClock;
}

/**
 * @brief  Returns the PCLK frequency
 * @note   Each time PCLK changes, this function must be called to update the
 *         right PCLK value. Otherwise, any configuration based on this function will be incorrect.
 * @retval PCLK frequency
 */
uint32_t HAL_RCC_GetPCLKFreq(void)
{
    /* Get HCLK source and Compute PCLK frequency ---------------------------*/
    if(RCC->PCLKDIV != 0)
        return ((HAL_RCC_GetHCLKFreq() >> 1) / RCC->PCLKDIV);
    else
        return (HAL_RCC_GetHCLKFreq());
}


/**
 * @brief  Configures the RCC_OscInitStruct according to the internal
 *          RCC configuration registers.
 * @param  RCC_OscInitStruct pointer to an RCC_OscInitTypeDef structure that will be configured.
 * @retval None
 */
void HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
    /* Check the parameters */
    assert_param(RCC_OscInitStruct != NULL);

    /* Set all possible values for the Oscillator type parameter ---------------*/
    RCC_OscInitStruct->OscillatorType = RCC_OSCILLATORTYPE_HIRC | RCC_OSCILLATORTYPE_HXT  \
                                        | RCC_OSCILLATORTYPE_LXT | RCC_OSCILLATORTYPE_SIRC;

    /* Get the HIRC configuration -----------------------------------------------*/
    if((RCC->SYSCLKSEL & RCC_SYSCLKCR_HIRCEN) == RCC_SYSCLKCR_HIRCEN)
    {
        RCC_OscInitStruct->HIRCState = RCC_HIRC_ON;
    }
    else
    {
        RCC_OscInitStruct->HIRCState = RCC_HIRC_OFF;
    }

    /* Get the HXT configuration -----------------------------------------------*/
    if((RCC->SYSCLKSEL & RCC_SYSCLKCR_HXTBYP) == RCC_SYSCLKCR_HXTBYP)
    {
        RCC_OscInitStruct->HXTState = RCC_HXT_BYPASS;
    }
    else if((RCC->SYSCLKSEL & RCC_SYSCLKCR_HXTEN) == RCC_SYSCLKCR_HXTEN)
    {
        RCC_OscInitStruct->HXTState = RCC_HXT_ON;
    }
    else
    {
        RCC_OscInitStruct->HXTState = RCC_HXT_OFF;
    }

    RCC_OscInitStruct->HIRCCalibrationValue = (uint32_t)((RCC->HIRCCR & RCC_HIRCCR_HIRCTRIM) >> RCC_HIRCCR_HIRCTRIM_Pos);

    /* Get the LSI configuration -----------------------------------------------*/
    if((RCC->SYSCLKSEL & RCC_SYSCLKCR_SIRCEN) == RCC_SYSCLKCR_SIRCEN)
    {
        RCC_OscInitStruct->SIRCState = RCC_SIRC_ON;
    }
    else
    {
        RCC_OscInitStruct->SIRCState = RCC_SIRC_OFF;
    }

    /* Get the LXT configuration -----------------------------------------------*/
    if((RCC->LXTCR & RCC_LXTCR_LXTBYP) == RCC_LXTCR_LXTBYP)
    {
        RCC_OscInitStruct->LXTState = RCC_LXT_BYPASS;
    }
    else if((RCC->LXTCR & RCC_LXTCR_LXTEN) == RCC_LXTCR_LXTEN)
    {
        RCC_OscInitStruct->LXTState = RCC_LXT_ON;
    }
    else
    {
        RCC_OscInitStruct->LXTState = RCC_LXT_OFF;
    }

#if defined(CONFIG_USE_ZB32L032)
    /* Get the PLLconfiguration -----------------------------------------------*/
    RCC_OscInitStruct->PLL.PLLState = ((RCC->SYSCLKSEL & RCC_SYSCLKCR_PLLEN) == RCC_SYSCLKCR_PLLEN)
                                    ? RCC_PLL_ON : RCC_PLL_OFF;
#endif

}

/**
 * @brief  Get the RCC_ClkInitStruct according to the internal
 *          RCC configuration registers.
 * @param  RCC_ClkInitStruct    pointer to an RCC_ClkInitTypeDef structure that
 *                                  contains the current clock configuration.
 * @retval None
 */
void HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct)
{
    /* Check the parameters */
    assert_param(RCC_ClkInitStruct != NULL);

    /* Set all possible values for the Clock type parameter --------------------*/
    RCC_ClkInitStruct->ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK;

    /* Get the SYSCLK configuration --------------------------------------------*/
    RCC_ClkInitStruct->SYSCLKSource = (uint32_t)(RCC->SYSCLKSEL & RCC_SYSCLKSEL_CLKSW);

    /* Get the HCLK configuration ----------------------------------------------*/
    RCC_ClkInitStruct->AHBCLKDivider = (uint32_t)(RCC->HCLKDIV & RCC_HCLKDIV_AHBCKDIV);

    /* Get the APB1 configuration ----------------------------------------------*/
    RCC_ClkInitStruct->APBCLKDivider = (uint32_t)(RCC->PCLKDIV & RCC_PCLKDIV_APBCKDIV);
    return;
}



/**
 * @}
 */ /* End of group RCC_Exported_Functions_Group2 */

/**
 * @}
 */ /* End of group RCC_Exported_Functions*/

#endif  /* HAL_RCC_MODULE_ENABLED */

/**
 * @}
 */ /* End of group RCC*/

/**
 * @}
 */ /* group ZB32L03x_HAL_Driver */

