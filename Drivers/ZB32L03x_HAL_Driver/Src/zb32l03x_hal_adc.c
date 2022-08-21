/**
 * Copyright (c) 2022 Wei-Lun Hsu. All Rights Reserved.
 */
/** @file zb32l03x_hal_adc.c
 *
 * @author Wei-Lun Hsu
 * @version 0.1
 * @date 2022/03/29
 * @license
 * @description
 */


#include "zb32l03x_hal.h"

#if defined(HAL_ADC_MODULE_ENABLED)
//=============================================================================
//                  Constant Definition
//=============================================================================
/**
 *  Timeout values for ADC enable/disable settling time.
 *  Values defined to be higher than worst cases: low clocks freq, maximum pre-scaler.
 *
 *  Ex of profile low frequency : Clock source at 0.1 MHz, ADC clock
 *  pre-scaler 4, sampling time 12.5 ADC clock cycles, resolution 12 bits.
 *  Unit: ms
 */
#define ADC_ENABLE_TIMEOUT_MS              2U
#define ADC_DISABLE_TIMEOUT_MS             2U

/**
 *  Delay for ADC stabilization time.
 *      Maximum delay is 1us (refer to device datasheet, parameter tSTAB).
 *      Unit: us
 */
#define ADC_STAB_DELAY_US               1U


#if defined(CONFIG_USE_ZB32L003S)
#define HAL_ADC_ALL_CHANNEL_Msk                                    \
        (ADC_MSKINTSR_ADCMIS_0_Msk | ADC_MSKINTSR_ADCMIS_1_Msk |   \
         ADC_MSKINTSR_ADCMIS_2_Msk | ADC_MSKINTSR_ADCMIS_3_Msk |   \
         ADC_MSKINTSR_ADCMIS_4_Msk | ADC_MSKINTSR_ADCMIS_5_Msk |   \
         ADC_MSKINTSR_ADCMIS_6_Msk | ADC_MSKINTSR_ADCMIS_7_Msk)

#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
#define HAL_ADC_ALL_CHANNEL_Msk                                                                     \
            (ADC_MSKINTSR_ADCMIS_0_Msk | ADC_MSKINTSR_ADCMIS_8_Msk  | ADC_MSKINTSR_ADCMIS_16_Msk |  \
             ADC_MSKINTSR_ADCMIS_1_Msk | ADC_MSKINTSR_ADCMIS_9_Msk  | ADC_MSKINTSR_ADCMIS_17_Msk |  \
             ADC_MSKINTSR_ADCMIS_2_Msk | ADC_MSKINTSR_ADCMIS_10_Msk | ADC_MSKINTSR_ADCMIS_18_Msk |  \
             ADC_MSKINTSR_ADCMIS_3_Msk | ADC_MSKINTSR_ADCMIS_11_Msk | ADC_MSKINTSR_ADCMIS_19_Msk |  \
             ADC_MSKINTSR_ADCMIS_4_Msk | ADC_MSKINTSR_ADCMIS_12_Msk | ADC_MSKINTSR_ADCMIS_20_Msk |  \
             ADC_MSKINTSR_ADCMIS_5_Msk | ADC_MSKINTSR_ADCMIS_13_Msk | ADC_MSKINTSR_ADCMIS_21_Msk |  \
             ADC_MSKINTSR_ADCMIS_6_Msk | ADC_MSKINTSR_ADCMIS_14_Msk | ADC_MSKINTSR_ADCMIS_22_Msk |  \
             ADC_MSKINTSR_ADCMIS_7_Msk | ADC_MSKINTSR_ADCMIS_15_Msk | ADC_MSKINTSR_ADCMIS_23_Msk)
#endif
//=============================================================================
//                  Macro Definition
//=============================================================================

/**
 *  @brief  Verification of ADC state: enabled or disabled
 *
 *  @param [in] __HANDLE__      ADC handle
 *  @return
 *      SET (ADC enabled) or RESET (ADC disabled)
 */
#define __ADC_IS_ENABLE(__HANDLE__)         \
            (((__HANDLE__)->Instance->CR0 & ADC_CR0_ADCEN_Msk) ? SET : RESET)


/**
 *  @brief  Conversion trigger is software start or not.
 *
 *  @param [in] __HANDLE__      ADC handle
 *  @return
 *      SET (software start) or RESET (external trigger)
 */
#define __ADC_IS_SOFTWARE_START(__HANDLE__)                                                                             \
            ((((__HANDLE__)->Instance->CR1 & ADC_CR1_TRIGS0_Msk) == HAL_ADC_EXTTRIG_SW_START) &&                        \
             (((__HANDLE__)->Instance->CR1 & ADC_CR1_TRIGS1_Msk) == (HAL_ADC_EXTTRIG_SW_START << ADC_CR1_TRIGS1_Pos)))


/**
 *  \brief  Enable the ADC peripheral
 *
 *  \param [in] __HANDLE__      ADC handle
 *  \return
 *      None
 */
#define __HAL_ADC_ENABLE(__HANDLE__)    \
            SET_BIT((__HANDLE__)->Instance->CR0, ADC_CR0_ADCEN)

/**
 *  \brief  Start conversion of the ADC
 *          ps. ADC module stop by hardware after conversion.
 *
 *  \param [in] __HANDLE__      ADC handle
 *  \return
 *      None
 */
#define __HAL_ADC_START(__HANDLE__)     \
            SET_BIT((__HANDLE__)->Instance->CR0, ADC_CR0_START)


//=============================================================================
//                  Structure Definition
//=============================================================================

//=============================================================================
//                  Global Data Definition
//=============================================================================

//=============================================================================
//                  Private Function Definition
//=============================================================================
/**
 * @brief  Initializes the ADC MSP.
 * @param  hADC: ADC handle
 * @retval None
 */
__weak void HAL_ADC_MspInit(ADC_HandleTypeDef *hADC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hADC);
    /* NOTE : This function should not be modified. When the callback is needed,
              function HAL_ADC_MspInit must be implemented in the user file.
     */
}

/**
 * @brief  DeInitializes the ADC MSP.
 * @param  hADC: ADC handle
 * @retval None
 */
__weak void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hADC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hADC);
    /* NOTE : This function should not be modified. When the callback is needed,
              function HAL_ADC_MspDeInit must be implemented in the user file.
     */
}

/**
 * @brief  Continue conversion complete callback in non blocking mode
 * @param  hADC: ADC handle
 * @retval None
 */
__weak void HAL_ADC_ContConvCpltCallback(ADC_HandleTypeDef *hADC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hADC);
    /* NOTE : This function should not be modified. When the callback is needed,
              function HAL_ADC_ContConvCpltCallback must be implemented in the user file.
    */
}


/**
 *  @brief  Out of threshold callback in non blocking mode.
 *
 *  @param [in] hADC            ADC handle
 *  @param [in] IT_Type         Interrupt type @ref HAL_ADC_ITTypeDef
 *  @return
 *      None
 */
__weak void HAL_ADC_LevelOutOfRangeCallback(ADC_HandleTypeDef *hADC, HAL_ADC_ITTypeDef IT_Type)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hADC);
    UNUSED(IT_Type);
    /* NOTE : This function should not be modified. When the callback is needed,
              function HAL_ADC_LevelOutOfRangeCallback must be implemented in the user file.
    */
}

/**
 *  @brief  Channel Conversion complete callback
 *
 *  @param [in] hADC        ADC handle
 *  @param [in] channel     Channel ID, @ref HAL_ADC_ChannelSel
 *  @return                 None
 */
__weak void HAL_ADC_ChannelxCallback(ADC_HandleTypeDef *hADC, HAL_ADC_ChannelSelTypeDef channel)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hADC);
    UNUSED(channel);
    /* NOTE : This function should not be modified. When the callback is needed,
              function HAL_ADC_ChannelxCallback must be implemented in the user file.
    */
}

/**
 *  @brief  Reset ADC conversion status and disable the selected ADC
 *
 *  @param [in] hADC        ADC handle
 *  @return
 *      HAL status
 */
static HAL_StatusTypeDef _ADC_Reset(ADC_HandleTypeDef *hADC)
{
    do {
        uint32_t    tick_start = 0U;

        /* Verification if ADC is not already disabled */
        if( __ADC_IS_ENABLE(hADC) == RESET )
            break;

        __HAL_ADC_DISABLE(hADC);

        CLEAR_BIT(hADC->State, HAL_ADC_STATE_ERROR_INTERNAL);

        tick_start = HAL_GetTick();

        while( __ADC_IS_ENABLE(hADC) != RESET )
        {
            if( (HAL_GetTick() - tick_start) > ADC_DISABLE_TIMEOUT_MS )
            {
                /* Update ADC state machine to error */
                SET_BIT(hADC->State, HAL_ADC_STATE_ERROR_INTERNAL);
                return HAL_ERROR;
            }
        }

    } while(0);

    return HAL_OK;
}

/**
  * @brief  Enable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC must be disabled
  *         and clock must be enabled (done into HAL_ADC_Init()).
  * @param  hADC: ADC handle
  * @retval HAL status.
  */
static HAL_StatusTypeDef _ADC_Enable(ADC_HandleTypeDef *hADC)
{

    do {
        uint32_t        tick_start = 0U;
        __IO uint32_t   timeout_us = 0U;
        /* Verification if ADC is not already disabled */
        if( __ADC_IS_ENABLE(hADC) == SET )
            break;

        __HAL_ADC_ENABLE(hADC);

        /**
         *  Delay for ADC stabilization time
         *  Compute number of CPU cycles to wait for
         */
        timeout_us = (ADC_STAB_DELAY_US * (SystemCoreClock / 4000000U));
        while( timeout_us-- ) {}

        CLEAR_BIT(hADC->State, HAL_ADC_STATE_ERROR_INTERNAL);

        tick_start = HAL_GetTick();

        while( __ADC_IS_ENABLE(hADC) == RESET )
        {
            if( (HAL_GetTick() - tick_start) > ADC_DISABLE_TIMEOUT_MS )
            {
                /* Update ADC state machine to error */
                SET_BIT(hADC->State, HAL_ADC_STATE_ERROR_INTERNAL);
                return HAL_ERROR;
            }
        }

    } while(0);

    return HAL_OK;
}

//=============================================================================
//                  Public Function Definition
//=============================================================================

/**
 *  @brief  Initializes the ADC peripheral and regular group according to
 *              parameters specified in structure "ADC_InitTypeDef".
 *
 * @note   As prerequisite, ADC clock must be configured at RCC top level
 *         (clock source APB).
 *         See commented example code below that can be copied and uncommented
 *         into HAL_ADC_MspInit().
 * @note   Possibility to update parameters on the fly:
 *         This function initializes the ADC MSP (HAL_ADC_MspInit()) only when
 *         coming from ADC state reset. Following calls to this function can
 *         be used to reconfigure some parameters of ADC_InitTypeDef
 *         structure on the fly, without modifying MSP configuration. If ADC
 *         MSP has to be modified again, HAL_ADC_DeInit() must be called
 *         before HAL_ADC_Init().
 *         The setting of these parameters is conditioned to ADC state.
 *         For parameters constraints, see comments of structure
 *         "ADC_InitTypeDef".
 *
 *  @param [in] hADC        ADC handle
 *  @return
 *      HAL status
 */
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hADC)
{
    HAL_StatusTypeDef       status = HAL_ERROR;

    assert_param(hADC);
    assert_param(hADC->Instance);

    if( !hADC )
        return status;

    do {
        uint32_t    cr0_value = 0ul;
        uint32_t    cr1_value = 0ul;
        uint32_t    cr2_value = 0ul;

        /**
         *  As prerequisite, into HAL_ADC_MspInit(), ADC clock must be configured at RCC top level.
         *  Refer to header of this file for more details on clock enabling procedure.
         *
         *  Actions performed only if ADC is coming from state reset:
         *  - Initialization of ADC MSP
         */
        if( hADC->State == HAL_ADC_STATE_RESET )
        {
            __HAL_UNLOCK(hADC);

            /* Init the low level hardware */
            HAL_ADC_MspInit(hADC);
        }

        status = _ADC_Reset(hADC);
        if( status != HAL_OK )  break;

        /**
         *  disable HAL_ADC_STATE_BUSY and enable HAL_ADC_STATE_BUSY_INTERNAL
         */
        MODIFY_REG(hADC->State, HAL_ADC_STATE_BUSY, HAL_ADC_STATE_BUSY_INTERNAL);

        /**
         *  Set configuration of ADC:
         */
        WRITE_REG_MASK(cr0_value,
                       ADC_CR0_SAM_Msk | ADC_CR0_CLKSEL_Msk | ADC_CR0_VRSEL_Msk | ADC_CR0_ADCK_SF_Msk,
                       hADC->Init.SamplingTime | hADC->Init.ClkSel | hADC->Init.Vref | hADC->Init.ClkShift);

        WRITE_REG_MASK(cr1_value, ADC_CR1_CT_Msk, hADC->Init.ConvMode);

        if( hADC->Init.CircleMode == HAL_ADC_MULTICHANNEL_CIRCLE ||
            (hADC->Init.CircleMode != HAL_ADC_MULTICHANNEL_CIRCLE &&
             hADC->Init.ConvMode == HAL_ADC_MODE_CONTINUE) )
        {
            /* Set circle mode */
            if( hADC->Init.CircleMode == HAL_ADC_MULTICHANNEL_CIRCLE )
            {
                SET_BIT(cr2_value, ADC_CR2_CIRCLE_MODE);
                CLEAR_BIT(cr1_value, ADC_CR1_CT);
            }
            else
                CLEAR_BIT(cr2_value, ADC_CR2_CIRCLE_MODE);

            if( hADC->Init.ConvMode == HAL_ADC_MODE_CONTINUE )
            {
                /* Set continue times */
                WRITE_REG_MASK(cr2_value, ADC_CR2_ADCCNT_Msk, hADC->Init.NbrOfConversion << ADC_CR2_ADCCNT_Pos);
            }

        #if defined(CONFIG_USE_ZB32L003S)
            /* Select multi-channels */
            if( hADC->Init.ContinueChannelSel & ADC_CR2_CHEN_Msk )
            {
                WRITE_REG_MASK(cr2_value, ADC_CR2_CHEN_Msk, hADC->Init.ContinueChannelSel & ADC_CR2_CHEN_Msk);
            }
        #elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
            /* Select multi-channels in the same group */
            if( hADC->Init.ContinueChannelSel & ADC_CR2_CHEN_Msk )
            {
                /* AIN 0 ~ AIN7 */
                WRITE_REG_MASK(cr2_value, ADC_CR2_CHSEL_Msk, ADC_CR2_CHSEL_AIN7_0 << ADC_CR2_CHSEL_Pos);
                WRITE_REG_MASK(cr2_value, ADC_CR2_CHEN_Msk, hADC->Init.ContinueChannelSel & ADC_CR2_CHEN_Msk);
            }
            else if( (hADC->Init.ContinueChannelSel >> 8) & ADC_CR2_CHEN_Msk )
            {
                /* AIN 8 ~ AIN15 */
                WRITE_REG_MASK(cr2_value, ADC_CR2_CHSEL_Msk, ADC_CR2_CHSEL_AIN15_8 << ADC_CR2_CHSEL_Pos);
                WRITE_REG_MASK(cr2_value, ADC_CR2_CHEN_Msk, (hADC->Init.ContinueChannelSel >> 8) & ADC_CR2_CHEN_Msk);
            }
            else if( (hADC->Init.ContinueChannelSel >> 16) & ADC_CR2_CHEN_Msk )
            {
                /* AIN 16 ~ AIN23 */
                WRITE_REG_MASK(cr2_value, ADC_CR2_CHSEL_Msk, ADC_CR2_CHSEL_AIN23_16 << ADC_CR2_CHSEL_Pos);
                WRITE_REG_MASK(cr2_value, ADC_CR2_CHEN_Msk, (hADC->Init.ContinueChannelSel >> 16) & ADC_CR2_CHEN_Msk);
            }
        #endif
        }
        else
        {
            int     channel_id = 31 - __CLZ(hADC->Init.AChannelSel);

            CLEAR_BIT(cr2_value, ADC_CR2_CIRCLE_MODE);

            /* default use single channel */
            WRITE_REG_MASK(cr0_value, ADC_CR0_SEL_Msk, channel_id << ADC_CR0_SEL_Pos);
        }

        /**
         *  Set Auto-Accumulation and external interrupt trigger
         */
        WRITE_REG_MASK(cr1_value,
                       (ADC_CR1_RACC_EN_Msk | ADC_CR1_TRIGS0_Msk | ADC_CR1_TRIGS1_Msk),
                       (hADC->Init.AutoAccumulation |
                        hADC->Init.ExtTrigConv0 << ADC_CR1_TRIGS0_Pos |
                        hADC->Init.ExtTrigConv1 << ADC_CR1_TRIGS1_Pos));

        /* write to registers */
        WRITE_REG(hADC->Instance->CR1, cr1_value);
        WRITE_REG(hADC->Instance->CR2, cr2_value);
        WRITE_REG(hADC->Instance->CR0, cr0_value);

        /**
         *  Check back that ADC registers have effectively been configured to
         *  ensure of no potential problem of ADC core IP clocking.
         *
         *  Check through register CR0 (excluding bits set in other functions)
         */
        if( READ_REG(hADC->Instance->CR0) != cr0_value )
        {
            MODIFY_REG(hADC->State, HAL_ADC_STATE_BUSY_INTERNAL, HAL_ADC_STATE_ERROR_INTERNAL);
            break;
        }

        MODIFY_REG(hADC->State, HAL_ADC_STATE_BUSY_INTERNAL, HAL_ADC_STATE_READY);
        status = HAL_OK;

    } while(0);

    return status;
}


/**
 *  @brief  De-initialize the ADC peripheral registers to their default reset values,
 *              with de-initialization of the ADC MSP.
 *
 *  @param [in] hADC        ADC handle
 *  @return
 *      HAL status
 */
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef *hADC)
{
    HAL_StatusTypeDef       status = HAL_ERROR;

    assert_param(hADC);
    assert_param(hADC->Instance);

    if( !hADC )
        return status;

    __HAL_LOCK(hADC);

    SET_BIT(hADC->State, HAL_ADC_STATE_BUSY_INTERNAL);

    status = _ADC_Reset(hADC);
    if( status == HAL_OK )
    {
        /* Hard reset ADC */
        __HAL_RCC_ADC_FORCE_RESET();
        __HAL_RCC_ADC_RELEASE_RESET();

        /* DeInit the low level hardware: GPIO, NVIC */
        HAL_ADC_MspDeInit(hADC);

        hADC->State = HAL_ADC_STATE_RESET;
        status = HAL_OK;
    }

    __HAL_UNLOCK(hADC);
    return status;
}

/**
  * @brief  Enables ADC, starts conversion.
  *         Interruptions enabled in this function: None.
  * @param  hADC: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hADC)
{
    HAL_StatusTypeDef   status = HAL_ERROR;

    assert_param(hADC);
    assert_param(hADC->Instance);

    if( !hADC )
        return status;

    __HAL_LOCK(hADC);

    do {
        /* Enable the ADC peripheral */
        status = _ADC_Enable(hADC);
        if( status != HAL_OK )  break;

        /**
         *  + Disable HAL_ADC_STATE_READY and  HAL_ADC_STATE_EOC
         *  + Enable HAL_ADC_STATE_BUSY
         */
        MODIFY_REG(hADC->State, HAL_ADC_STATE_READY | HAL_ADC_STATE_EOC, HAL_ADC_STATE_BUSY);

        if( hADC->Init.AutoAccumulation == HAL_ADC_AUTOACC_ENABLE )
        {
            SET_BIT(hADC->Instance->CR1, ADC_CR1_RACC_CLR);
        }

        /**
         *  Clear continue conversion flag
         *  (To ensure of no unknown state from potential previous ADC operations)
         */
        __HAL_ADC_CLR_IT_FLAG(hADC, HAL_ADC_IT_CONTINUE);

        /**
         *  Enable conversion.
         *  If software start has been selected, conversion starts immediately.
         *  If external trigger has been selected, conversion will start at next trigger event.
         */
        if( __ADC_IS_SOFTWARE_START(hADC) )
        {
            __HAL_ADC_START(hADC);
        }

        status = HAL_OK;
    } while(0);

    __HAL_UNLOCK(hADC);
    return status;
}

/**
  * @brief  Stop ADC conversion, disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing stop of potential
  *         conversion.
  * @param  hADC: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *hADC)
{
    HAL_StatusTypeDef   status = HAL_ERROR;

    /* Check the parameters */
    assert_param(hADC);
    assert_param(hADC->Instance);

    if( !hADC )
        return status;

    __HAL_LOCK(hADC);

    /* Disable ADC peripheral */
    status = _ADC_Reset(hADC);

    __HAL_ADC_DISABLE(hADC);

    /* Check if ADC is effectively disabled */
    if( status == HAL_OK )
    {
        /**
         *  disable HAL_ADC_STATE_BUSY and enable HAL_ADC_STATE_READY
         */
        MODIFY_REG(hADC->State, HAL_ADC_STATE_BUSY, HAL_ADC_STATE_READY);
    }

    __HAL_UNLOCK(hADC);
    return status;
}

/**
 *  @brief  Enables ADC, starts conversion with interruption.
 *
 *  @param [in] hADC        ADC handle
 *  @return
 *      HAL status
 */
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef *hADC)
{
    HAL_StatusTypeDef       status = HAL_ERROR;

    /* Check the parameters */
    assert_param(hADC);
    assert_param(hADC->Instance);

    if( !hADC )
        return status;

    __HAL_LOCK(hADC);

    do {
        /* Enable the ADC peripheral */
        status = _ADC_Enable(hADC);
        if( status != HAL_OK )
        {
            __HAL_UNLOCK(hADC);
            break;
        }

        /**
         *  + disable HAL_ADC_STATE_READY and HAL_ADC_STATE_EOC
         *  + enable HAL_ADC_STATE_BUSY
         */
        MODIFY_REG(hADC->State, HAL_ADC_STATE_READY | HAL_ADC_STATE_EOC, HAL_ADC_STATE_BUSY);

        /**
         *  Process unlocked.
         *  Unlock before starting ADC conversions:
         *  In case of potential interruption, to let the process to ADC IRQ Handler.
         */
        __HAL_UNLOCK(hADC);

        if( hADC->Init.AutoAccumulation == HAL_ADC_AUTOACC_ENABLE )
        {
            SET_BIT(hADC->Instance->CR1, ADC_CR1_RACC_CLR);
        }

        if( hADC->Init.ConvMode == HAL_ADC_MODE_CONTINUE )
        {
            uint32_t    channels = hADC->Init.ContinueChannelSel;

            __HAL_ADC_CLR_IT_FLAG(hADC, HAL_ADC_ALL_CHANNEL_Msk);

        #if defined(CONFIG_USE_ZB32L003S)
            if( channels & ADC_CR2_CHEN_Msk )
            {
                __HAL_ADC_ENABLE_IT(hADC, HAL_ADC_IT_CONTINUE | ((channels & 0xFF) << ADC_INTEN_ADCXIEN_0_Pos));
            }
        #elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
            if( channels & ADC_CR2_CHEN_Msk )
            {
                /* AIN 0 ~ AIN7 */
                __HAL_ADC_ENABLE_IT(hADC, HAL_ADC_IT_CONTINUE | ((channels & 0xFF) << ADC_INTEN_ADCXIEN_0_Pos));
            }
            else if( (channels >> 8) & ADC_CR2_CHEN_Msk )
            {
                /* AIN 8 ~ AIN15 */
                __HAL_ADC_ENABLE_IT(hADC, HAL_ADC_IT_CONTINUE | (((channels >> 8) & 0xFF) << ADC_INTEN_ADCXIEN_8_Pos));
            }
            else if( (channels >> 16) & ADC_CR2_CHEN_Msk )
            {
                /* AIN 16 ~ AIN23 */
                __HAL_ADC_ENABLE_IT(hADC, HAL_ADC_IT_CONTINUE | (((channels >> 16) & 0xFF) << ADC_INTEN_ADCXIEN_16_Pos));
            }
        #endif  /* CONFIG_USE_ZB32L030 || CONFIG_USE_ZB32L032 */
        }
        else
        {
            HAL_ADC_ITTypeDef       adc_it_type = HAL_ADC_IT_NONE;

        #if defined(CONFIG_USE_ZB32L030)
            if( hADC->Init.AChannelSel == HAL_ADC_CHANNEL_15 ||
                hADC->Init.AChannelSel == HAL_ADC_CHANNEL_23 )
            {
                status = HAL_ERROR;
                __HAL_UNLOCK(hADC);
                break;
            }
        #endif  /* CONFIG_USE_ZB32L030 */

            if( hADC->Init.AChannelSel & HAL_ADC_ALL_CHANNEL_Msk )
            {
        #if defined(CONFIG_USE_ZB32L003S)
                adc_it_type  = (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_0)  ? HAL_ADC_IT_CHANNEL_0 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_1)  ? HAL_ADC_IT_CHANNEL_1 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_2)  ? HAL_ADC_IT_CHANNEL_2 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_3)  ? HAL_ADC_IT_CHANNEL_3 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_4)  ? HAL_ADC_IT_CHANNEL_4 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_5)  ? HAL_ADC_IT_CHANNEL_5 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_6)  ? HAL_ADC_IT_CHANNEL_6 :
                               HAL_ADC_IT_CHANNEL_7;

        #elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
                adc_it_type  = (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_0)  ? HAL_ADC_IT_CHANNEL_0 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_1)  ? HAL_ADC_IT_CHANNEL_1 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_2)  ? HAL_ADC_IT_CHANNEL_2 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_3)  ? HAL_ADC_IT_CHANNEL_3 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_4)  ? HAL_ADC_IT_CHANNEL_4 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_5)  ? HAL_ADC_IT_CHANNEL_5 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_6)  ? HAL_ADC_IT_CHANNEL_6 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_7)  ? HAL_ADC_IT_CHANNEL_7 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_8)  ? HAL_ADC_IT_CHANNEL_8 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_9)  ? HAL_ADC_IT_CHANNEL_9 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_10) ? HAL_ADC_IT_CHANNEL_10 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_11) ? HAL_ADC_IT_CHANNEL_11 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_12) ? HAL_ADC_IT_CHANNEL_12 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_13) ? HAL_ADC_IT_CHANNEL_13 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_14) ? HAL_ADC_IT_CHANNEL_14 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_15) ? HAL_ADC_IT_CHANNEL_15 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_16) ? HAL_ADC_IT_CHANNEL_16 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_17) ? HAL_ADC_IT_CHANNEL_17 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_18) ? HAL_ADC_IT_CHANNEL_18 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_19) ? HAL_ADC_IT_CHANNEL_19 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_20) ? HAL_ADC_IT_CHANNEL_20 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_21) ? HAL_ADC_IT_CHANNEL_21 :
                               (hADC->Init.AChannelSel == HAL_ADC_CHANNEL_22) ? HAL_ADC_IT_CHANNEL_22 :
                               HAL_ADC_IT_CHANNEL_23;
        #endif  /* CONFIG_USE_ZB32L030 || CONFIG_USE_ZB32L032 */
            }
            else
            {
                __HAL_ADC_DISABLE_IT(hADC, HAL_ADC_IT_CHANNEL_ALL);
                status = HAL_ERROR;
                __HAL_UNLOCK(hADC);
                break;
            }

            /**
             *  Clear conversion end flag
             *  (To ensure of no unknown state from potential previous ADC operations)
             */
            __HAL_ADC_CLR_IT_FLAG(hADC, adc_it_type);

            /* Enable end of conversion interrupt */
            __HAL_ADC_ENABLE_IT(hADC, adc_it_type);
        }

        /**
         *  Enable conversion.
         *  If software start has been selected, conversion starts immediately.
         *  If external trigger has been selected, conversion will start at next trigger event.
         */
        if( __ADC_IS_SOFTWARE_START(hADC) )
        {
            __HAL_ADC_START(hADC);
        }

    } while(0);

    return status;
}


/**
 *  @brief  Stop ADC conversion, disable interruption of end-of-conversion,
 *              and disable ADC peripheral.
 *
 *  @param [in] hADC        ADC handle
 *  @return
 *      HAL status
 */
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef *hADC)
{
    HAL_StatusTypeDef       status = HAL_ERROR;

    /* Check the parameters */
    assert_param(hADC);
    assert_param(hADC->Instance);

    if( !hADC )
        return status;

    __HAL_LOCK(hADC);

    status = _ADC_Reset(hADC);

    /* Check if ADC is effectively disabled */
    if( status == HAL_OK )
    {
        /* Disable ADC end of conversion interrupt */
        __HAL_ADC_DISABLE_IT(hADC, HAL_ADC_IT_CHANNEL_ALL);
        __HAL_ADC_CLR_IT_FLAG(hADC, (uint32_t)HAL_ADC_IT_CHANNEL_ALL);

        /* Disable ADC */
        __HAL_ADC_DISABLE(hADC);

        /**
         *  disable HAL_ADC_STATE_BUSY and enable HAL_ADC_STATE_READY
         */
        MODIFY_REG(hADC->State, HAL_ADC_STATE_BUSY, HAL_ADC_STATE_READY);
    }

    __HAL_UNLOCK(hADC);
    return status;
}



/**
 *  @brief  Get ADC conversion result.
 *              It will wait ADC IP ready by Timeout
 *
 *  @param [in] hADC            ADC handle
 *  @param [in] channel         ADC channel number used for continuous mode @ref HAL_ADC_ChannelSel
 *                                  For single channel mode, param channel will have no effect.
 *  @return
 *      ADC conversion data (12-bits), if 0xFFFFFFFF, it mean ADC not ready
 */
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hADC, HAL_ADC_ChannelSelTypeDef channel)
{
    uint32_t            adc_code = ~0ul;

    /* Check the parameters */
    assert_param(hADC);
    assert_param(hADC->Instance);

    if( !hADC )
        return adc_code;

    /**
     * This API may be called in ISR
     */
    if( hADC->Init.ConvMode == HAL_ADC_MODE_SINGLE )
    {
        adc_code = READ_REG(hADC->Instance->RESULT);
    }
    else
    {
        int     index = 31 - __CLZ(channel);

        if( channel & ADC_CR2_CHEN_Msk )
        {
            /* AIN 0 ~ AIN7 */
        }
    #if defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
        else if( (channel >> 16) & ADC_CR2_CHEN_Msk )
        {
            /* AIN 16 ~ AIN23 */
            index -= 16;
        }
        else if( (channel >> 8) & ADC_CR2_CHEN_Msk )
        {
            /* AIN 8 ~ AIN15 */
            index -= 8;
        }
    #endif  /* CONFIG_USE_ZB32L030 || CONFIG_USE_ZB32L032 */

        switch( index )
        {
            default:
            case 0:     adc_code = READ_REG(hADC->Instance->RESULT0);   break;
            case 1:     adc_code = READ_REG(hADC->Instance->RESULT1);   break;
            case 2:     adc_code = READ_REG(hADC->Instance->RESULT2);   break;
            case 3:     adc_code = READ_REG(hADC->Instance->RESULT3);   break;
            case 4:     adc_code = READ_REG(hADC->Instance->RESULT4);   break;
            case 5:     adc_code = READ_REG(hADC->Instance->RESULT5);   break;
            case 6:     adc_code = READ_REG(hADC->Instance->RESULT6);   break;
            case 7:     adc_code = READ_REG(hADC->Instance->RESULT7);   break;
        }
    }

    return adc_code;
}


/**
 *  @brief  Get ADC accumulating result
 *
 *  @param [in] hADC        ADC handle
 *  @return
 *      ADC conversion data
 */
uint32_t HAL_ADC_GetAccValue(ADC_HandleTypeDef *hADC)
{
    uint32_t    adc_code = ~0u;

    /* Check the parameters */
    assert_param(hADC);
    assert_param(hADC->Instance);

    if( !hADC )
        return adc_code;

    /**
     * This API may be called in ISR
     */
    adc_code = READ_REG(hADC->Instance->RESULT_ACC);

    return adc_code;
}


/**
 *  @brief  Configures the the selected channel.
 *  @note    Possibility to update parameters on the fly:
 *           This function initializes channel to be converted, following calls to this function can be used
 *           to reconfigure some parameters of structure "HAL_ADC_ChannelConfTypeDef" on the fly, without reseting the ADC.
 *           The setting of these parameters is conditioned to ADC state.
 *           For parameters constraints, see comments of structure "HAL_ADC_ChannelConfTypeDef".*
 *
 *  @param [in] hADC            ADC handle
 *  @param [in] pChConfig       Structure pointer of ADC channel configuration.
 *  @return
 *      HAL status
 */
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hADC, HAL_ADC_ChannelConfTypeDef *pChConfig)
{
    HAL_StatusTypeDef       status = HAL_ERROR;
    int                     aChannel_id = 31 - __CLZ(pChConfig->AChannelSel);

    /* Check the parameters */
    assert_param(hADC);
    assert_param(hADC->Instance);
    assert_param(pChConfig);

    if( !hADC )
        return status;

    __HAL_LOCK(hADC);

    WRITE_REG_MASK(hADC->Instance->CR0,
                   ADC_CR0_SAM_Msk | ADC_CR0_CLKSEL_Msk | ADC_CR0_VRSEL_Msk | ADC_CR0_SEL_Msk,
                   pChConfig->SamplingTime | pChConfig->ClkSel | pChConfig->Vref | (aChannel_id << ADC_CR0_SEL_Pos));

    __HAL_UNLOCK(hADC);
    return status;
}


/**
 *  @brief  Configures the threshold.
 *  @note   Thresholds can be modified while ADC conversion is on going.
 *          In this case, some constraints must be taken into account:
 *          the programmed threshold values are effective from the next ADC EOC (end of unitary conversion).
 *          Considering that registers write delay may happen due to bus activity,
 *          this might cause an uncertainty on the effective timing of the new programmed threshold values.
 *
 *  @param [in] hADC
 *  @param [in] pThConfig
 *  @return
 *      HAL status
 */
HAL_StatusTypeDef HAL_ADC_ConfigThreshold(ADC_HandleTypeDef *hADC, HAL_ADC_ThresholdConfTypeDef *pThConfig)
{
    HAL_StatusTypeDef       status = HAL_ERROR;

    /* Check the parameters */
    assert_param(hADC);
    assert_param(hADC->Instance);
    assert_param(pThConfig);

    if( !hADC )
        return status;

    __HAL_LOCK(hADC);

    do {
        /* Configure ADC out of threshold interrupt */
        if( pThConfig->HasUseIT )
        {
            /* Enable the ADC out of threshold interrupt */
            if( pThConfig->CompareMode == HAL_ADC_COMP_THRESHOLD_RANGE )
                __HAL_ADC_ENABLE_IT(hADC, HAL_ADC_IT_RANGE_THRESHOLD);
            else if( pThConfig->CompareMode == HAL_ADC_COMP_THRESHOLD_HIGH )
                __HAL_ADC_ENABLE_IT(hADC, HAL_ADC_IT_HIGH_THRESHOLD);
            else if( pThConfig->CompareMode == HAL_ADC_COMP_THRESHOLD_LOW )
                __HAL_ADC_ENABLE_IT(hADC, HAL_ADC_IT_LOW_THRESHOLD);
            else        break;
        }
        else
        {
            /* Disable the ADC out of threshold interrupt */
            if( pThConfig->CompareMode == HAL_ADC_COMP_THRESHOLD_RANGE)
                __HAL_ADC_DISABLE_IT(hADC, HAL_ADC_IT_RANGE_THRESHOLD);
            else if( pThConfig->CompareMode == HAL_ADC_COMP_THRESHOLD_HIGH)
                __HAL_ADC_DISABLE_IT(hADC, HAL_ADC_IT_HIGH_THRESHOLD);
            else if( pThConfig->CompareMode == HAL_ADC_COMP_THRESHOLD_LOW)
                __HAL_ADC_DISABLE_IT(hADC, HAL_ADC_IT_LOW_THRESHOLD);
            else        break;
        }

        /* Set the high threshold */
        WRITE_REG(hADC->Instance->HT, pThConfig->HighThreshold);

        /* Set the low threshold */
        WRITE_REG(hADC->Instance->LT, pThConfig->LowThreshold);

        /* Comparison mode enable */
        WRITE_REG_MASK(hADC->Instance->CR1,
                       ADC_CR1_LTCMP_Msk | ADC_CR1_HTCMP_Msk | ADC_CR1_REGCMP_Msk,
                       pThConfig->CompareMode);

        status = HAL_OK;
    } while(0);

    __HAL_UNLOCK(hADC);

    return status;
}


/**
 *  @brief  Handles ADC interrupt request
 *
 *  @param [in] hADC        ADC handle
 *  @return
 *      None
 */
void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hADC)
{
    uint32_t        trigger_source = 0;

    assert_param(hADC);
    assert_param(hADC->Instance);

    trigger_source = READ_REG(hADC->Instance->MSKINTSR);

    /* Clear IT Flag */
    WRITE_REG(hADC->Instance->INTCLR, trigger_source);

    /* ADC end of Continue Conversion IRQ */
    if( trigger_source & ADC_MSKINTSR_CONT_MIF_Msk )
    {
        /* Disable ADC end of conversion interrupt */
//        __HAL_ADC_DISABLE_IT(hADC, HAL_ADC_IT_CONTINUE);

        /* Set ADC state */
        if( !READ_BIT(hADC->State, HAL_ADC_STATE_ERROR_INTERNAL) )
        {
            /* Update state machine on conversion status if not in error state */
            SET_BIT(hADC->State, HAL_ADC_STATE_EOC);
        }

        MODIFY_REG(hADC->State, HAL_ADC_STATE_BUSY, HAL_ADC_STATE_READY);

        /* Callback */
        HAL_ADC_ContConvCpltCallback(hADC);
    }

    /* ADC conversion data in defined range IRQ */
    if( trigger_source & ADC_MSKINTSR_REG_MIF_Msk )
    {
        /* Disable ADC interrupt */
//        __HAL_ADC_DISABLE_IT(hADC, HAL_ADC_IT_RANGE_THRESHOLD);

        /* Set ADC state */
        SET_BIT(hADC->State, HAL_ADC_STATE_OUTRANGE);

        HAL_ADC_LevelOutOfRangeCallback(hADC, HAL_ADC_IT_RANGE_THRESHOLD);
    }

    /* ADC conversion data above threshold IRQ */
    if( trigger_source & ADC_MSKINTSR_HHT_MIF_Msk )
    {
        /* Disable ADC interrupt */
//        __HAL_ADC_DISABLE_IT(hADC, HAL_ADC_IT_HIGH_THRESHOLD);

        /* Set ADC state */
        SET_BIT(hADC->State, HAL_ADC_STATE_OUTRANGE);

        HAL_ADC_LevelOutOfRangeCallback(hADC, HAL_ADC_IT_HIGH_THRESHOLD);
    }

    /* ADC conversion data below threshold IRQ */
    if( trigger_source & ADC_MSKINTSR_LLT_MIF_Msk )
    {
        /* Disable ADC interrupt */
//        __HAL_ADC_DISABLE_IT(hADC, HAL_ADC_IT_LOW_THRESHOLD);

        /* Set ADC state */
        SET_BIT(hADC->State, HAL_ADC_STATE_OUTRANGE);

        HAL_ADC_LevelOutOfRangeCallback(hADC, HAL_ADC_IT_LOW_THRESHOLD);
    }

    /* ADC End of channels conversion IRQ */
    if( trigger_source & HAL_ADC_ALL_CHANNEL_Msk )
    {
        trigger_source &= HAL_ADC_ALL_CHANNEL_Msk;

        while( trigger_source )
        {
            int     index = 31 - __CLZ(trigger_source);

            trigger_source &= ~(0x1 << index);

            if( hADC->Init.ConvMode == HAL_ADC_MODE_SINGLE )
            {
                __HAL_ADC_DISABLE_IT(hADC, (0x1u << index));
            }

        #if defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
            index = (index >= ADC_MSKINTSR_ADCMIS_8_Pos) ? index - 8 : index;
        #endif

            HAL_ADC_ChannelxCallback(hADC, (HAL_ADC_ChannelSelTypeDef)(0x1u << index));
        }
    }

    return;
}

#endif  /* defined(HAL_ADC_MODULE_ENABLED) */
