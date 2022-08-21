/**
 ******************************************************************************
 * @file    zb32l03x_hal_vc.c
 * @author  MCU Software Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   VC HAL module driver.
 *          This file provides firmware functions to manage the following
 *          functionalities of the Voltage comparator (VC) peripheral:
 *           + Initialization and Start functions
 *           + IO operation functions
 *
 @verbatim
 ==============================================================================
                   ##### VC Generic features #####
 ==============================================================================
 [..]
   (+) The VC can be started by  software (configurable through option byte).

   (+) The VC Filter is clocked by Slow-Speed clock (SIRC)or PCLK .

                    ##### How to use this driver #####
 ==============================================================================
 [..]
   (#) Use VC using HAL_VC_Init() function to :
     (++) Enable VC 25DIV in VC_CR0 register.
     (++) Select input source for "+" and "-"
     (++) Configure the VC filter set.
     (++) set triger and interrupt.


    *** VC HAL driver macros list ***
    ====================================
  @endverbatim
 ******************************************************************************
 **/


#include "zb32l03x_hal.h"



#if defined(HAL_VC_MODULE_ENABLED)
/** @defgroup VC VC
 * @brief VC HAL module driver.
 * @{
 */


//=============================================================================
//                  Constant Definition
//=============================================================================

//=============================================================================
//                  Macro Definition
//=============================================================================

#if defined(CONFIG_USE_ZB32L003S)

/**
 *  @brief  Enable 2.5V reference voltage
 *
 *  @param [in] __HANDLE__      Pointer to a HAL_VC_HandleTypeDef structure
 *  @return     none
 */
#define __VC_V25DIV_ENABLE(__HANDLE__)              SET_BIT((__HANDLE__)->Instance->CR0, VC_CR0_V25DIV_EN)

/**
 *  @brief  Disable 2.5V reference voltage
 *
 *  @param [in] __HANDLE__      Pointer to a HAL_VC_HandleTypeDef structure
 *  @return     none
 */
#define __VC_V25DIV_DISABLE(__HANDLE__)             CLEAR_BIT((__HANDLE__)->Instance->CR0, VC_CR0_V25DIV_EN)

#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
/**
 *  @brief  Enable VC DAC
 *
 *  @param [in] __HANDLE__      Pointer to a HAL_VC_HandleTypeDef structure
 *  @return     none
 */
#define __VC_DAC_ENABLE(__HANDLE__)                 SET_BIT((__HANDLE__)->Instance->CR0, VC_CR0_DAC_CxEN)

/**
 *  @brief  Disable VC DAC
 *
 *  @param [in] __HANDLE__      Pointer to a HAL_VC_HandleTypeDef structure
 *  @return     none
 */
#define __VC_DAC_DISABLE(__HANDLE__)                CLEAR_BIT((__HANDLE__)->Instance->CR0, VC_CR0_DAC_CxEN)

#endif  /* CONFIG_USE_ZB32L030 || CONFIG_USE_ZB32L032 */

/**
 *  @brief  Check VC is enable or not
 *
 *  @param [in] __VC_BASE__     Instance of VC
 *  @return     true or false
 */
#define IS_VC_ENABLE(__VC_BASE__)                   READ_BIT(((VC_TypeDef*)(__VC_BASE__))->CR1, VC_CR1_VCEN)

/**
 * @brief  Check VC FILTER NUMBER.
 * @param  FILTER_NUM  VC Filter number
 * @retval None
 */
#define IS_VC_FILTER_NUM(FILTER_NUM)                ((((int)FILTER_NUM) >= (int)0U) && ((FILTER_NUM) <= 0xFFFFU))
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
 * @brief  Initializes the VC MSP.
 * @param  hVC: VC handle
 * @retval None
 */

__weak void HAL_VC_MspInit(HAL_VC_HandleTypeDef *hVC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hVC);
    /* NOTE : This function should not be modified. When the callback is needed,
              function HAL_VC_MspInit must be implemented in the user file.
     */
}
/**
 * @brief  DeInitializes the VC MSP.
 * @param  hVC: VC handle
 * @retval None
 */
__weak void HAL_VC_MspDeInit(HAL_VC_HandleTypeDef *hVC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hVC);
    /* NOTE : This function should not be modified. When the callback is needed,
              function HAL_VC_MspDeInit must be implemented in the user file.
     */
}


/**
 * @brief  Period elapsed callback in non blocking mode
 * @param  htim : VC handle
 * @retval None
 */
__weak void HAL_VC_FilterCmpltCallback(HAL_VC_HandleTypeDef *hVC)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hVC);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_VC_PeriodElapsedCallback could be implemented in the user file
     */

}

//=============================================================================
//                  Public Function Definition
//=============================================================================

/** @addtogroup VC_Exported_Functions
 * @{
 */

/** @addtogroup VC_Exported_Functions_Group1
 *  @brief    Initialization and Start functions.
 *
@verbatim
 ===============================================================================
          ##### Initialization and Start functions #####
 ===============================================================================
 [..]  This section provides functions allowing to:
      (+) Initialize the VC according to the specified parameters in the
          VC_InitTypeDef of associated handle.
      (+) Once initialization is performed in HAL_VC_Init function,
          the Voltage comparator will work.
@endverbatim
 * @{
 */


/**
 * @brief  Initialize the VC according to the specified parameters in the
 *         HAL_VC_HandleTypeDef and start VC.
 * @param  hVC  pointer to a HAL_VC_HandleTypeDef structure that contains
 *                the configuration information for the specified VC module.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_VC_Init(HAL_VC_HandleTypeDef *hVC)
{
    /* Check the VC handle allocation */
    if( hVC == NULL )
        return HAL_ERROR;


    /* Check the parameters */
    assert_param(hVC);
    assert_param(hVC->Instance);
    assert_param(IS_VC_FILTER_NUM(hVC->Init.Fliter_Num));

    if( hVC->State == HAL_VC_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        hVC->Lock = HAL_UNLOCKED;

        /* Init the low level hardware */
        HAL_VC_MspInit(hVC);
    }

    WRITE_REG_MASK(hVC->Instance->CR0,
                   VC_CR0_VPxINSEL_Msk | VC_CR0_VNxINSEL_Msk,
                   (hVC->Init.NInChannelSel << VC_CR0_VNxINSEL_Pos) | (hVC->Init.PInChannelSel << VC_CR0_VPxINSEL_Pos));

#if defined(CONFIG_USE_ZB32L003S)
    // Set 2.5V prescale
    WRITE_REG_MASK(hVC->Instance->CR0, VC_CR0_V25DIV_Msk, (hVC->Init.V25div << VC_CR0_V25DIV_Pos));

#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)

    // Set DAC Vref
    if( hVC->Init.Vref == HAL_VC_DAC_VREF_VDD )
        SET_BIT(hVC->Instance->CR0, VC_CR0_DACVREF);
    else
        CLEAR_BIT(hVC->Instance->CR0, VC_CR0_DACVREF);

    // Set DAC level
    WRITE_REG_MASK(hVC->Instance->CR0, VC_CR0_DAC_CxO_Msk, (hVC->Init.DACLevel << VC_CR0_DAC_CxO_Pos));

#endif

    // Set Interrupt
    if( hVC->Init.InterruptMode == HAL_VC_INTERRUPT_DISABLE )
    {
        CLEAR_BIT(hVC->Instance->CR1, VC_CR1_FALLINTEN_Msk | VC_CR1_RISEINTEN_Msk | VC_CR1_HIGHINTEN_Msk | VC_CR1_INT_EN_Msk);
    }
    else
    {
        WRITE_REG_MASK(hVC->Instance->CR1,
                       VC_CR1_FALLINTEN_Msk | VC_CR1_RISEINTEN_Msk | VC_CR1_HIGHINTEN_Msk | VC_CR1_INT_EN_Msk,
                       hVC->Init.InterruptMode | VC_CR1_INT_EN);
    }

    // Set filter
    WRITE_REG_MASK(hVC->Instance->CR1,
                   VC_CR1_FLT_NUM_Msk | VC_CR1_FLTCLK_SEL_Msk,
                   (hVC->Init.Fliter_Num << VC_CR1_FLT_NUM_Pos) | hVC->Init.Filter_Clk);

    if( hVC->Init.FilterEnable )
        SET_BIT(hVC->Instance->CR1, VC_CR1_FLTEN);
    else
        CLEAR_BIT(hVC->Instance->CR1, VC_CR1_FLTEN);

    /* Change VC peripheral state */
    hVC->State = HAL_VC_STATE_READY;

    return HAL_OK;
}

/**
 * @brief  DE Initialize the VC according to the specified parameters in the
 *         HAL_VC_HandleTypeDef .
 * @param  hVC  pointer to a HAL_VC_HandleTypeDef structure that contains
 *                the configuration information for the specified VC module.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_VC_DeInit(HAL_VC_HandleTypeDef *hVC)
{
    assert_param(hVC);
    assert_param(hVC->Instance);

    __HAL_LOCK(hVC);

    __HAL_VC_DISABLE(hVC);

#if defined(CONFIG_USE_ZB32L003S)
    CLEAR_REG(hVC->Instance->CR0);
#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)

    if( IS_VC_ENABLE(VC0) == 0 && IS_VC_ENABLE(VC1) == 0 )
    {
        __VC_DAC_DISABLE(hVC);
    }
#endif

    CLEAR_REG(hVC->Instance->CR1);
    CLEAR_REG(hVC->Instance->OUTCFG);
    CLEAR_REG(hVC->Instance->SR);

    __HAL_UNLOCK(hVC);
    return HAL_OK;
}

/**
 * @}
 */

/**
 *  @brief  Start VC
 *
 *  @param [in] hVC     Pointer to a HAL_VC_HandleTypeDef structure that contains
 *                          the configuration information for the specified VC module.
 *  @return             HAL status
 */
HAL_StatusTypeDef HAL_VC_Start(HAL_VC_HandleTypeDef *hVC)
{
    assert_param(hVC);
    assert_param(hVC->Instance);

    __HAL_LOCK(hVC);

#if defined(CONFIG_USE_ZB32L003S)
    if( hVC->Init.NInChannelSel == HAL_VC_IN_CHANNEL_V25DIV )
    {
        // Enable 2.5V
        __VC_V25DIV_ENABLE(hVC);
    }
#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    if( hVC->Init.NInChannelSel == HAL_VC_IN_CHANNEL_DACO )
    {
        // Enable DAC
        __VC_DAC_ENABLE(hVC);
    }
#endif

    // Enable VC
    __HAL_VC_ENABLE(hVC);

    __HAL_UNLOCK(hVC);
    return HAL_OK;
}

/**
 *  @brief  Stop VC
 *
 *  @param [in] hVC     Pointer to a HAL_VC_HandleTypeDef structure that contains
 *                          the configuration information for the specified VC module.
 *  @return             HAL status
 */
HAL_StatusTypeDef HAL_VC_Stop(HAL_VC_HandleTypeDef *hVC)
{
    assert_param(hVC);
    assert_param(hVC->Instance);

    __HAL_LOCK(hVC);

#if defined(CONFIG_USE_ZB32L003S)
    if( hVC->Init.NInChannelSel == HAL_VC_IN_CHANNEL_V25DIV )
    {
        // Disable 2.5V
        __VC_V25DIV_DISABLE(hVC);
    }
#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    if( hVC->Init.NInChannelSel == HAL_VC_IN_CHANNEL_DACO )
    {
        // Disable DAC
        __VC_DAC_DISABLE(hVC);
    }
#endif

    // Disable VC
    __HAL_VC_DISABLE(hVC);

    __HAL_UNLOCK(hVC);
    return HAL_OK;
}

/**
 *  @brief  Start VC with interrupt mode
 *
 *  @param [in] hVC     Pointer to a HAL_VC_HandleTypeDef structure that contains
 *                          the configuration information for the specified VC module.
 *  @return             HAL status
 */
HAL_StatusTypeDef HAL_VC_Start_IT(HAL_VC_HandleTypeDef *hVC)
{
    assert_param(hVC);
    assert_param(hVC->Instance);

    __HAL_LOCK(hVC);

    __HAL_VC_ENABLE_IT(hVC);

#if defined(CONFIG_USE_ZB32L003S)
    if( hVC->Init.NInChannelSel == HAL_VC_IN_CHANNEL_V25DIV )
    {
        // Enable 2.5V
        __VC_V25DIV_ENABLE(hVC);
    }
#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    if( hVC->Init.NInChannelSel == HAL_VC_IN_CHANNEL_DACO )
    {
        // Enable DAC
        __VC_DAC_ENABLE(hVC);
    }
#endif

    __HAL_VC_ENABLE(hVC);

    __HAL_UNLOCK(hVC);
    return HAL_OK;
}

/**
 *  @brief  Stop VC with interrupt mode
 *
 *  @param [in] hVC     Pointer to a HAL_VC_HandleTypeDef structure that contains
 *                          the configuration information for the specified VC module.
 *  @return             HAL status
 */
HAL_StatusTypeDef HAL_VC_Stop_IT(HAL_VC_HandleTypeDef *hVC)
{
    assert_param(hVC);
    assert_param(hVC->Instance);

    __HAL_LOCK(hVC);

    __HAL_VC_DISABLE_IT(hVC);
    __HAL_VC_CLEAR_IT_FLAG(hVC);

#if defined(CONFIG_USE_ZB32L003S)
    if( hVC->Init.NInChannelSel == HAL_VC_IN_CHANNEL_V25DIV )
    {
        // Disable 2.5V
        __VC_V25DIV_DISABLE(hVC);
    }
#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    if( hVC->Init.NInChannelSel == HAL_VC_IN_CHANNEL_DACO )
    {
        // Disable DAC
        __VC_DAC_DISABLE(hVC);
    }
#endif

    __HAL_VC_DISABLE(hVC);

    __HAL_UNLOCK(hVC);
    return HAL_OK;
}


/**
 *  @brief  Configure VC outupt channels
 *
 *  @param [in] hVC             Pointer to a HAL_VC_HandleTypeDef structure that contains
 *                              the configuration information for the specified VC module.
 *  @param [in] channels        The target channels, @ref HAL_VC_Out_ChannelTypeDef
 *  @return
 *      HAL status
 */
HAL_StatusTypeDef HAL_VC_ConfigOutChannels(HAL_VC_HandleTypeDef *hVC, uint32_t channels)
{
    assert_param(hVC);
    assert_param(hVC->Instance);

    __HAL_LOCK(hVC);

#if defined(CONFIG_USE_ZB32L003S)
    SET_BIT(hVC->Instance->OUTCFG, (channels & HAL_VC_OUT_CHANNEL_ALL));

#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    if( hVC->Instance == VC0 )
        SET_BIT(hVC->Instance->OUTCFG, (channels & HAL_VC_OUT_CHANNEL_ALL));
    else if( hVC->Instance == (VC_TypeDef*)VC1 )
        SET_BIT(hVC->Instance->OUTCFG, (channels & HAL_VC_1_OUT_CHANNEL_ALL));
#endif

    __HAL_UNLOCK(hVC);

    return HAL_OK;
}


/**
 * @brief  This function handles VC interrupts requests.
 * @param  htim : VC  handle
 * @retval None
 */
void HAL_VC_IRQHandler(HAL_VC_HandleTypeDef *hVC)
{
    if( __HAL_VC_GET_IT_FLAG(hVC) == SET )
    {
        __HAL_VC_CLEAR_IT_FLAG(hVC);

        HAL_VC_FilterCmpltCallback(hVC);
    }
}


/**
 * @}
 */

/**
 * @}
 */

#endif  /* HAL_VC_MODULE_ENABLED */
