/**
 ******************************************************************************
 * @file    zb32l03x_hal_wwdg.c
 * @author  MCU Software Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   WWDG HAL module driver.
 *          This file provides firmware functions to manage the following
 *          functionalities of the Window Watchdog (WWDG) peripheral:
 *           + Initialization and de-initialization functions
 *           + IO operation functions
 *           + Peripheral State functions
 @verbatim
 ==============================================================================
                     ##### WWDG specific features #####
 ==============================================================================
 [..]
   Once enabled the WWDG generates a system reset on expiry of a programmed
   time period, unless the program refreshes the counter (downcounter)
   before reaching 0x00 value (i.e. a reset is generated when the counter
   value rolls over from 0x01 to 0x00).

   (+) An MCU reset is also generated if the counter value is refreshed
       before the counter has reached the refresh window value. This
       implies that the counter must be refreshed in a limited window.
   (+) Once enabled the WWDG cannot be disabled except by a system reset.
   (+) WWDGRST flag in RCC_RSTSR register can be used to inform when a WWDG
       reset occurs.
   (+) The WWDG counter input clock is derived from the APB clock divided
       by a programmable prescaler.


                    ##### How to use this driver #####
 ==============================================================================
 [..]


 @endverbatim
 ******************************************************************************
 **/


#include "zb32l03x_hal.h"

/** @addtogroup ZB32L03x_HAL_Driver
 * @{
 */


/** @defgroup WWDG WWDG
 * @brief WWDG HAL module driver.
 * @{
 */
#if defined(HAL_WWDG_MODULE_ENABLED)

/** @defgroup WWDG_Exported_Functions WWDG Exported Functions
 * @{
 */

/**
 * @brief  WWDG Interrupt callback.
 * @param  None
 * @retval None
 */
__weak void HAL_WWDG_Timeout_Callback()
{
    /* Prevent unused argument(s) compilation warning */
    /* NOTE: This function should not be modified, when the callback is needed,
             the HAL_WWDG_Timeout_Callback could be implemented in the user file
     */
}

/** @defgroup WWDG_Exported_Functions_Group1 Initialization and Configuration functions
 *  @brief    Initialization and Configuration functions.
 *
@verbatim
  ==============================================================================
          ##### Initialization and Configuration functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
      (+) Initialize and start the WWDG according to the specified parameters
          in the WWDG_HandleTypeDef of associated handle.

@endverbatim
 * @{
 */

/**
 * @brief  Initialize the WWDG according to the specified.
 *         parameters in the WWDG_HandleTypeDef .
 * @param  hwwdg  pointer to a WWDG_HandleTypeDef structure that contains
 *                the configuration information for the specified WWDG module.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_WWDG_Init(WWDG_HandleTypeDef *hwwdg)
{
    /* Check the parameters */
    assert_param(hwwdg);
    assert_param(IS_WWDG_PRESCALER(hwwdg->Init.Prescaler));
    assert_param(IS_WWDG_WINDOW(hwwdg->Init.Window));
    assert_param(IS_WWDG_RELOAD(hwwdg->Init.Reload));
    assert_param(IS_WWDG_INT_SET(hwwdg->Init.INTSet));

    /* Check the WWDG handle allocation */
    if (hwwdg == NULL)
        return HAL_ERROR;

    /* Set WWDG Counter */
    WRITE_REG(hwwdg->Instance->RLOAD, (WWDG_RLOAD_RLOAD_Msk & (hwwdg->Init.Reload << WWDG_RLOAD_RLOAD_Pos)));

    /* Set WWDG INTEN */
    if( hwwdg->Init.INTSet )
        SET_BIT(hwwdg->Instance->INTEN, WWDG_INTEN_WWDGIEN);
    else
        CLEAR_BIT(hwwdg->Instance->INTEN, WWDG_INTEN_WWDGIEN);

    /* Set WWDG Prescaler and Window, Enable WWDG */
    WRITE_REG(hwwdg->Instance->CR,
              ((hwwdg->Init.Prescaler << WWDG_CR_PRSC_Pos) & WWDG_CR_PRSC_Msk) |
              ((hwwdg->Init.Window << WWDG_CR_WINCMP_Pos) & WWDG_CR_WINCMP_Msk) |
              WWDG_CR_WWDGEN);

    /* Return function status */
    return HAL_OK;
}

/**
 * @}
 */

/** @defgroup WWDG_Exported_Functions_Group2 IO operation functions
 *  @brief    IO operation functions
 *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Refresh the WWDG.
    (+) Handle WWDG interrupt request and associated function callback.

@endverbatim
 * @{
 */

/**
 * @brief  Refresh the WWDG.
 * @param  hwwdg  pointer to a WWDG_HandleTypeDef structure that contains
 *                the configuration information for the specified WWDG module.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_WWDG_Refresh(WWDG_HandleTypeDef *hwwdg)
{
    /* Write to WWDG CR the WWDG Counter value to refresh with */
    WRITE_REG(hwwdg->Instance->RLOAD, (WWDG_RLOAD_RLOAD_Msk & (hwwdg->Init.Reload << WWDG_RLOAD_RLOAD_Pos)));

    /* Return function status */
    return HAL_OK;
}

/**
 *  @brief  Get counter of WWDG
 *
 *  @param [in] hwwdg       pointer to a WWDG_HandleTypeDef structure that contains
 *                          the configuration information for the specified WWDG module.
 *  @param [in] pCounter    The pointer of counter value
 *  @return
 *      HAL status
 */
HAL_StatusTypeDef HAL_WWDG_Get_Counter(WWDG_HandleTypeDef *hwwdg, uint32_t *pCounter)
{
    *pCounter = READ_REG(hwwdg->Instance->CNTVAL) & WWDG_CNTVAL_WWDGCNT_Msk;
    return HAL_OK;
}

/**
 * @brief  Handle WWDG interrupt request.
 * @note   The Interrupt can be used if specific safety operations
 *         or data logging must be performed before the actual reset is generated.
 *         The interrupt is enabled by calling HAL_WWDG_Init function with
 *         IRQMode set to ENABLE.
 *         When the downcounter reaches the value WWDG_CR.WINCMP, and interrupt is
 *         generated and the corresponding Interrupt Service Routine (ISR) can
 *         be used to trigger specific actions (such as communications or data
 *         logging), before resetting the device.
 * @param  None
 * @retval None
 */
void HAL_WWDG_IRQHandler(void)
{
    /* Check if  Interrupt is enable */
    if (__HAL_WWDG_GET_INT_STATE() != RESET)
    {
        /* Check if WWDG  Interrupt occurred */
        if (__HAL_WWDG_GET_INT() != RESET)
        {
            /* Clear the Interrupt flag */
            __HAL_WWDG_CLEAR_INT();

            /* Interrupt callback */
            HAL_WWDG_Timeout_Callback();
        }
    }
}



/**
 * @}
 */

/**
 * @}
 */

#endif /* HAL_WWDG_MODULE_ENABLED */
/**
 * @}
 */


/**
 * @}
 */ /* group ZB32L03x_HAL_Driver */
