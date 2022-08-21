/**
 ******************************************************************************
 * @file    zb32l03x_hal_crc.c
 * @author  MCU Software Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   CRC HAL module driver.
 *          This file provides firmware functions to manage the following
 *          functionalities of the Cyclic Redundancy Check (CRC) peripheral:
 *           + Initialization and de-initialization functions
 *           + Peripheral Control functions
 *           + Peripheral State functions
 *
 @verbatim
 ==============================================================================
                    ##### How to use this driver #####
 ==============================================================================
   [..]
     The CRC HAL driver can be used as follows:

     (#) Enable CRC AHB clock using __HAL_RCC_CRC_CLK_ENABLE();

     (#) Use HAL_CRC_Accumulate() function to compute the CRC value of
         a 8-bit data buffer using combination of the previous CRC value
         and the new one.

     (#) Use HAL_CRC_Calculate() function to compute the CRC Value of
         a new 8-bit data buffer. This function resets the CRC computation
         unit before starting the computation to avoid getting wrong CRC values.

 @endverbatim
 ******************************************************************************
 */

#include "zb32l03x_hal.h"

/** @addtogroup ZB32L03x_HAL_Driver
  * @{
  */


/** @defgroup CRC CRC
  * @brief CRC HAL module driver.
  * @{
  */

#if defined(HAL_CRC_MODULE_ENABLED)

/** @defgroup CRC_Exported_Functions CRC Exported Functions
  * @{
  */

/** @defgroup CRC_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions.
 *
@verbatim
  ==============================================================================
            ##### Initialization and de-initialization functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the CRC according to the specified parameters
          in the CRC_InitTypeDef and create the associated handle
      (+) DeInitialize the CRC peripheral
      (+) Initialize the CRC MSP
      (+) DeInitialize CRC MSP

@endverbatim
 * @{
 */

/**
 * @brief  Initializes the CRC according to the specified
 *         parameters in the CRC_InitTypeDef and creates the associated handle.
 * @param  hcrc: pointer to a CRC_HandleTypeDef structure that contains
 *         the configuration information for CRC
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_CRC_Init(CRC_HandleTypeDef *hcrc)
{
    /* Check the CRC handle allocation */
    if(hcrc == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    assert_param(hcrc);
    assert_param(IS_CRC_ALL_INSTANCE(hcrc->Instance));

    if(hcrc->State == HAL_CRC_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        hcrc->Lock = HAL_UNLOCKED;

        /* Init the low level hardware */
        HAL_CRC_MspInit(hcrc);
    }

    hcrc->pvCrcData = (void*)&CRC->DATA0;

    /* Change CRC peripheral state */
    hcrc->State = HAL_CRC_STATE_READY;

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  DeInitializes the CRC peripheral.
 * @param  hcrc: pointer to a CRC_HandleTypeDef structure that contains
 *         the configuration information for CRC
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_CRC_DeInit(CRC_HandleTypeDef *hcrc)
{
    /* Check the CRC handle allocation */
    if(hcrc == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    assert_param(hcrc);
    assert_param(IS_CRC_ALL_INSTANCE(hcrc->Instance));

    /* Change CRC peripheral state */
    hcrc->State = HAL_CRC_STATE_BUSY;

    /* DeInit the low level hardware */
    HAL_CRC_MspDeInit(hcrc);

    /* Resets the CRC calculation unit */
    __HAL_RCC_CRC_FORCE_RESET();
    __HAL_RCC_CRC_RELEASE_RESET();

    /* Change CRC peripheral state */
    hcrc->State = HAL_CRC_STATE_RESET;

    /* Release Lock */
    __HAL_UNLOCK(hcrc);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Initializes the CRC MSP.
 * @param  hcrc: pointer to a CRC_HandleTypeDef structure that contains
 *         the configuration information for CRC
 * @retval None
 */
__weak void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hcrc);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_CRC_MspInit could be implemented in the user file
     */
}

/**
 * @brief  DeInitializes the CRC MSP.
 * @param  hcrc: pointer to a CRC_HandleTypeDef structure that contains
 *         the configuration information for CRC
 * @retval None
 */
__weak void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hcrc);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_CRC_MspDeInit could be implemented in the user file
     */
}

/**
 * @}
 */

/** @defgroup CRC_Exported_Functions_Group2 Peripheral Control functions
 *  @brief    management functions.
 *
@verbatim
 ==============================================================================
                     ##### Peripheral Control functions #####
 ==============================================================================
   [..]  This section provides functions allowing to:
     (+) Compute the 16-bit CRC value of 8-bit data buffer,
         using combination of the previous CRC value and the new one.
     (+) Compute the 16-bit CRC value of 8-bit data buffer,
         independently of the previous CRC value.

@endverbatim
 * @{
 */

/**
 * @brief  Computes the 16-bits/32-bites CRC of 8-bit data buffer using combination
 *         of the previous CRC value and the new one.
 *         ps. ZB32L030 ONLY support 16-bits CRC
 * @param  hcrc: pointer to a CRC_HandleTypeDef structure that contains
 *         the configuration information for CRC
 * @param  pBuffer: pointer to the buffer containing the data to be computed
 * @param  BufferLength: length of the buffer to be computed (defined in word, 4 bytes)
 * @retval 16-bits/32-bits CRC
 */
uint32_t HAL_CRC_Accumulate(CRC_HandleTypeDef *hcrc, uint8_t pBuffer[], uint32_t BufferLength)
{
    uint32_t index = 0U;

    /* Process Locked */
    __HAL_LOCK(hcrc);

    /* Change CRC peripheral state */
    hcrc->State = HAL_CRC_STATE_BUSY;

    /* Enter Data to the CRC calculator */
    for(index = 0U; index < BufferLength; index++)
    {
        *(uint8_t *)(hcrc->pvCrcData) = pBuffer[index];
    }

    /* Change CRC peripheral state */
    hcrc->State = HAL_CRC_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hcrc);

    /* Return the CRC computed value */
    return (hcrc->Instance->RESULT & CRC_RESULT_RESULT_Msk);
}

/**
 * @brief  Computes the 16-bit CRC of 8-bit data buffer independently
 *         of the previous CRC value.
 * @param  hcrc: pointer to a CRC_HandleTypeDef structure that contains
 *         the configuration information for CRC
 * @param  pBuffer: Pointer to the buffer containing the data to be computed
 * @param  BufferLength: Length of the buffer to be computed (defined in word, 4 bytes)
 * @retval 16-bit CRC
 */
uint16_t HAL_CRC_Calculate(CRC_HandleTypeDef *hcrc, uint8_t pBuffer[], uint32_t BufferLength)
{
    uint32_t index = 0U;

    /* Process Locked */
    __HAL_LOCK(hcrc);

    /* Change CRC peripheral state */
    hcrc->State = HAL_CRC_STATE_BUSY;

    /* Reset CRC Calculation Unit */
    __HAL_RCC_CRC_FORCE_RESET();
    __HAL_RCC_CRC_RELEASE_RESET();

#if defined(CONFIG_USE_ZB32L032)
    SET_BIT(hcrc->Instance->CR, CRC_CR_SEL);
#endif

    __HAL_CRC_INITIAL(hcrc);

    /* Enter Data to the CRC calculator */
    for(index = 0U; index < BufferLength; index++)
    {
        *(uint8_t *)(hcrc->pvCrcData) = pBuffer[index];
    }

    /* Change CRC peripheral state */
    hcrc->State = HAL_CRC_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hcrc);

    /* Return the CRC computed value */
    return (hcrc->Instance->RESULT & CRC_RESULT_RESULT_Msk);
}

ErrorStatus HAL_Get_CRC_RESULT_FLAG(CRC_HandleTypeDef *hcrc)
{
#if defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L003S)
    return (hcrc->Instance->RESULT & CRC_RESULT_FLAG_Msk) ? SUCCESS : ERROR;
#elif defined(CONFIG_USE_ZB32L032)
    return (hcrc->Instance->CR & CRC_CR_FLAG_Msk) ? SUCCESS : ERROR;
#endif
}


#if defined(CONFIG_USE_ZB32L032)
/**
 * @brief  Computes the 32-bit CRC of 8-bit data buffer independently
 *         of the previous CRC value.
 * @param  hcrc: pointer to a CRC_HandleTypeDef structure that contains
 *         the configuration information for CRC
 * @param  pBuffer: Pointer to the buffer containing the data to be computed
 * @param  BufferLength: Length of the buffer to be computed (defined in word, 4 bytes)
 * @retval 32-bit CRC
 */
uint32_t HAL_CRC32_Calculate(CRC_HandleTypeDef *hcrc, uint8_t pBuffer[], uint32_t BufferLength)
{
    uint32_t index = 0U;

    /* Process Locked */
    __HAL_LOCK(hcrc);

    /* Change CRC peripheral state */
    hcrc->State = HAL_CRC_STATE_BUSY;

    /* Reset CRC Calculation Unit */
    __HAL_RCC_CRC_FORCE_RESET();
    __HAL_RCC_CRC_RELEASE_RESET();

    CLEAR_BIT(hcrc->Instance->CR, CRC_CR_SEL);

    __HAL_CRC_INITIAL(hcrc);

    /* Enter Data to the CRC calculator */
    for(index = 0U; index < BufferLength; index++)
    {
        *(uint8_t *)(hcrc->pvCrcData) = pBuffer[index];
    }

    /* Change CRC peripheral state */
    hcrc->State = HAL_CRC_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hcrc);

    /* Return the CRC computed value */
    return (hcrc->Instance->RESULT & CRC_RESULT_RESULT_Msk);
}
#endif  /* defined(CONFIG_USE_ZB32L032) */


/**
 * @}
 */

/** @defgroup CRC_Exported_Functions_Group3 Peripheral State functions
 *  @brief    Peripheral State functions.
 *
@verbatim
 ==============================================================================
                     ##### Peripheral State functions #####
 ==============================================================================
   [..]
   This subsection permits to get in run-time the status of the peripheral.

@endverbatim
 * @{
 */

/**
 * @brief  Returns the CRC state.
 * @param  hcrc: pointer to a CRC_HandleTypeDef structure that contains
 *         the configuration information for CRC
 * @retval HAL state
 */
HAL_CRC_StateTypeDef HAL_CRC_GetState(CRC_HandleTypeDef *hcrc)
{
    return hcrc->State;
}

/**
 * @}
 */

/**
 * @}
 */

#endif /* HAL_CRC_MODULE_ENABLED */

/**
 * @}
 */

/**
 * @}
 */ /* group ZB32L03x_HAL_Driver */
