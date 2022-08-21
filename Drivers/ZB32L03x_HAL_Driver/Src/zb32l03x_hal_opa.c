/**
 * Copyright (c) 2022 Wei-Lun Hsu. All Rights Reserved.
 */
/** @file zb32l03x_hal_opa.c
 *
 * @author Wei-Lun Hsu
 * @version 0.1
 * @date 2022/02/14
 * @license
 * @description
 */


#include "zb32l03x_hal.h"


/** @addtogroup ZB32L03x_HAL_Driver
 * @{
 */


/** @defgroup OPA OPA
 * @brief OPA HAL module driver.
 * @{
 */

#if defined(HAL_OPA_MODULE_ENABLED)
//=============================================================================
//                  Constant Definition
//=============================================================================
#define OPA_TIMEOUT_US              14   /* ideally stable duration (< 10us) */

//=============================================================================
//                  Macro Definition
//=============================================================================
#define __HAL_OPA_DAC_ENABLE(__HANDLE__)            SET_BIT((__HANDLE__)->Instance->OPDAC_CR, OPA_OPDAC_CR_OPDAC_EN_Msk)
#define __HAL_OPA_DAC_DISABLE(__HANDLE__)           CLEAR_BIT((__HANDLE__)->Instance->OPDAC_CR, OPA_OPDAC_CR_OPDAC_EN_Msk)

#define __HAL_OPA_DAC_BUF_ENABLE(__HANDLE__)        SET_BIT((__HANDLE__)->Instance->OPDAC_CR, OPA_OPDAC_CR_OPDAC_BUF_EN_Msk)
#define __HAL_OPA_DAC_BUF_DISABLE(__HANDLE__)       CLEAR_BIT((__HANDLE__)->Instance->OPDAC_CR, OPA_OPDAC_CR_OPDAC_BUF_EN_Msk)
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
  * @brief  Initialize the OPA MSP.
  * @param  hOPA        OPA handle
  * @retval None
  */
__weak void HAL_OPA_MspInit(HAL_OPA_HandleTypeDef *hOPA)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hOPA);

    /* NOTE : This function should not be modified, when the callback is needed,
            the function "HAL_OPA_MspInit()" must be implemented in the user file.
    */
}

/**
  * @brief  DeInitialize OPA MSP.
  * @param  hOPA        OPA handle
  * @retval None
  */
__weak void HAL_OPA_MspDeInit(HAL_OPA_HandleTypeDef *hOPA)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hOPA);

    /* NOTE : This function should not be modified, when the callback is needed,
            the function "HAL_OPA_MspDeInit()" must be implemented in the user file.
    */
}
//=============================================================================
//                  Public Function Definition
//=============================================================================
HAL_StatusTypeDef
HAL_OPA_Init(HAL_OPA_HandleTypeDef *hOPA)
{
    assert_param(hOPA);
    assert_param(hOPA->Instance);

    if( hOPA->State == HAL_OPA_STATE_RESET )
    {
        __HAL_UNLOCK(hOPA);
        HAL_OPA_MspInit(hOPA);
    }

    WRITE_REG(hOPA->Instance->OP1_CR0, 0x0);
    WRITE_REG(hOPA->Instance->OP2_CR0, 0x0);
    WRITE_REG(hOPA->Instance->OPDAC_CR, 0x0);

    WRITE_REG_MASK(hOPA->Instance->OPDAC_CR,
                   OPA_OPDAC_CR_OPDAC_Msk | OPA_OPDAC_CR_OPDAC_VREF_Msk,
                   ((hOPA->Init.DC_Level_Step << OPA_OPDAC_CR_OPDAC_Pos) & OPA_OPDAC_CR_OPDAC_Msk) |
                   ((hOPA->Init.Vref << OPA_OPDAC_CR_OPDAC_VREF_Pos) & OPA_OPDAC_CR_OPDAC_VREF_Msk));

    if( hOPA->Init.OP1_Mode == OPA_MODE_FOLLOWER_INP )
    {
        // follow VIP
        WRITE_REG_MASK(hOPA->Instance->OP1_CR0,
                       OPA_OP1_CR0_SW1PVSS_Msk | OPA_OP1_CR0_SW1NVSS_Msk | \
                       OPA_OP1_CR0_SW1_0_Msk | OPA_OP1_CR0_SW1_1_Msk | OPA_OP1_CR0_SW1_2_Msk,
                       OPA_OP1_CR0_SW1_2);

        __HAL_OPA_DAC_BUF_DISABLE(hOPA);
    }
    else if( hOPA->Init.OP1_Mode == OPA_MODE_FOLLOWER_DAC )
    {
        // Follow DAC output
        WRITE_REG(hOPA->Instance->OP1_CR0, 0x0);
        __HAL_OPA_DAC_BUF_ENABLE(hOPA);
    }
    else if( (hOPA->Init.OP1_Mode & OPA_MODE_PGA_MSK) == OPA_MODE_PGA_TYPE )
    {
        if( hOPA->Init.OP1_Mode == OPA_MODE_PGA_INVERTING )
        {
            /**
             *  Inverting Amplifier:
             *  Vout = -(R2/R1) * Vi + ((R1+R2)/R1) * Vdac_op
             *       = -16 * Vi + 17 * Vdac_op
             */
            WRITE_REG_MASK(hOPA->Instance->OP1_CR0,
                           OPA_OP1_CR0_SW1PVSS_Msk | OPA_OP1_CR0_SW1NVSS_Msk | \
                           OPA_OP1_CR0_SW1_0_Msk | OPA_OP1_CR0_SW1_1_Msk | OPA_OP1_CR0_SW1_2_Msk,
                           OPA_OP1_CR0_SW1_0 | OPA_OP1_CR0_SW1PVSS);

            __HAL_OPA_DAC_BUF_DISABLE(hOPA);
        }
        else if( hOPA->Init.OP1_Mode == OPA_MODE_PGA_NONINVERTING )
        {
            // VIP input
            WRITE_REG_MASK(hOPA->Instance->OP1_CR0,
                           OPA_OP1_CR0_SW1PVSS_Msk | OPA_OP1_CR0_SW1NVSS_Msk | \
                           OPA_OP1_CR0_SW1_0_Msk | OPA_OP1_CR0_SW1_1_Msk | OPA_OP1_CR0_SW1_2_Msk,
                           OPA_OP1_CR0_SW1NVSS | OPA_OP1_CR0_SW1_2);

            __HAL_OPA_DAC_BUF_DISABLE(hOPA);
        }
        else if( hOPA->Init.OP1_Mode == OPA_MODE_PGA_DIFF )
        {
            // difference of VIP and VIN
            WRITE_REG_MASK(hOPA->Instance->OP1_CR0,
                           OPA_OP1_CR0_SW1PVSS_Msk | OPA_OP1_CR0_SW1NVSS_Msk | \
                           OPA_OP1_CR0_SW1_0_Msk | OPA_OP1_CR0_SW1_1_Msk | OPA_OP1_CR0_SW1_2_Msk,
                           OPA_OP1_CR0_SW1_0 | OPA_OP1_CR0_SW1_2);

            __HAL_OPA_DAC_BUF_ENABLE(hOPA);
        }
    }
    else if( hOPA->Init.OP1_Mode == OPA_MODE_CALIBRATION )
    {
        // Externally short VIP and VIN
        WRITE_REG_MASK(hOPA->Instance->OP1_CR0,
                       OPA_OP1_CR0_SW1PVSS_Msk | OPA_OP1_CR0_SW1NVSS_Msk | \
                       OPA_OP1_CR0_SW1_0_Msk | OPA_OP1_CR0_SW1_1_Msk | OPA_OP1_CR0_SW1_2_Msk,
                       OPA_OP1_CR0_SW1_1 | OPA_OP1_CR0_SW1_2);

        __HAL_OPA_DAC_BUF_ENABLE(hOPA);
    }
    else if( hOPA->Init.OP1_Mode == OPA_MODE_NONE )
    {
        // Do nothing
    }
    else
    {
        return HAL_ERROR;
    }

    if( hOPA->Init.OP1_Mode != OPA_MODE_NONE &&
        hOPA->Init.OP1_Out == OPA_Out_IO_PIN )
    {
        SET_BIT(hOPA->Instance->OP1_CR0, OPA_OP1_CR0_SW1_7);
    }

#if defined(CONFIG_USE_ZB32L032)
    /* Configure OP2 */
#endif  /* CONFIG_USE_ZB32L032 */

    hOPA->State = HAL_OPA_STATE_READY;

    return HAL_OK;
}


HAL_StatusTypeDef
HAL_OPA_DeInit(HAL_OPA_HandleTypeDef *hOPA)
{
    assert_param(hOPA);
    assert_param(hOPA->Instance);

    __HAL_LOCK(hOPA);

    WRITE_REG(hOPA->Instance->OP1_CR0, 0x0);
    WRITE_REG(hOPA->Instance->OP2_CR0, 0x0);
    WRITE_REG(hOPA->Instance->OPDAC_CR, 0x0);

    HAL_OPA_MspDeInit(hOPA);

    hOPA->State = HAL_OPA_STATE_RESET;

    __HAL_UNLOCK(hOPA);

    return HAL_OK;
}

HAL_StatusTypeDef
HAL_OPA_Start(HAL_OPA_HandleTypeDef *hOPA, OPA_IdTypeDef OP_Id)
{
    assert_param(hOPA);
    assert_param(hOPA->Instance);

    if( hOPA->State != HAL_OPA_STATE_READY )
        return HAL_ERROR;

    __HAL_LOCK(hOPA);

    if( OP_Id == OPA_ID_1 || OP_Id == OPA_ID_ALL)
    {
        if( hOPA->Init.OP1_Mode == OPA_MODE_FOLLOWER_INP )
        {
            __HAL_OPA_DAC_DISABLE(hOPA);
        }
        else if( (hOPA->Init.OP1_Mode & OPA_MODE_PGA_MSK) == OPA_MODE_PGA_TYPE )
        {
            if( hOPA->Init.OP1_Mode == OPA_MODE_PGA_DIFF )
            {
                /* DC Level from DAC output */
                __HAL_OPA_DAC_ENABLE(hOPA);
            }
            else if( hOPA->Init.OP1_Mode == OPA_MODE_PGA_NONINVERTING ||
                     hOPA->Init.OP1_Mode == OPA_MODE_PGA_INVERTING )
            {
                __HAL_OPA_DAC_DISABLE(hOPA);
            }
        }
        else if( hOPA->Init.OP1_Mode == OPA_MODE_FOLLOWER_DAC ||
                 hOPA->Init.OP1_Mode == OPA_MODE_CALIBRATION )
        {
            /* DC Level from DAC output */
            __HAL_OPA_DAC_ENABLE(hOPA);
        }

        /* Enable OP1 */
        SET_BIT(hOPA->Instance->OP1_CR0, OPA_OP1_CR0_OP1EN);
    }

    if( OP_Id == OPA_ID_2 || OP_Id == OPA_ID_ALL )
    {
#if defined(CONFIG_USE_ZB32L030)
        if( hOPA->Init.OP2_Mode == OPA_MODE_STANDALONE )
        {
            /* Enable OP2 */
            SET_BIT(hOPA->Instance->OP2_CR0, OPA_OP2_CR0_OP2EN);
        }
#elif defined(CONFIG_USE_ZB32L032)
        /* TODO: implement */
#endif  /* CONFIG_USE_ZB32L032 */
    }

    {   /* wait OPA stable */
        int     timeout = (OPA_TIMEOUT_US * 64) >> 2;
        while( timeout-- ) {}
    }

    __HAL_UNLOCK(hOPA);

    return HAL_OK;
}

HAL_StatusTypeDef
HAL_OPA_Stop(HAL_OPA_HandleTypeDef *hOPA, OPA_IdTypeDef OP_Id)
{
    assert_param(hOPA);
    assert_param(hOPA->Instance);

    if( hOPA->State != HAL_OPA_STATE_READY )
        return HAL_ERROR;

    __HAL_LOCK(hOPA);

    if( OP_Id == OPA_ID_2 || OP_Id == OPA_ID_ALL)
        CLEAR_BIT(hOPA->Instance->OP2_CR0, OPA_OP2_CR0_OP2EN);

    if( OP_Id == OPA_ID_1 || OP_Id == OPA_ID_ALL)
        CLEAR_BIT(hOPA->Instance->OP1_CR0, OPA_OP1_CR0_OP1EN);

    if( OP_Id == OPA_ID_ALL )
        __HAL_OPA_DAC_DISABLE(hOPA);

    __HAL_UNLOCK(hOPA);
    return HAL_OK;
}

HAL_StatusTypeDef
HAL_OPA_Config(HAL_OPA_HandleTypeDef *hOPA, OPA_ConfigTypeDef *pCfg)
{
    assert_param(hOPA);
    assert_param(hOPA->Instance);
    assert_param(pCfg);

    if( hOPA->State != HAL_OPA_STATE_READY )
        return HAL_ERROR;

    __HAL_LOCK(hOPA);

    /* Configure OP1 */
    if( pCfg->OP_Id == OPA_ID_1 )
    {
        if( pCfg->DC_Level_Step != OPA_CONFIG_IGNORE_TAG )
        {
            WRITE_REG_MASK(hOPA->Instance->OPDAC_CR,
                           OPA_OPDAC_CR_OPDAC_Msk,
                           (pCfg->DC_Level_Step << OPA_OPDAC_CR_OPDAC_Pos) & OPA_OPDAC_CR_OPDAC_Msk);
        }

        if( pCfg->Mode == OPA_MODE_FOLLOWER_INP )
        {
            // follow VIP
            WRITE_REG_MASK(hOPA->Instance->OP1_CR0,
                           OPA_OP1_CR0_SW1PVSS_Msk | OPA_OP1_CR0_SW1NVSS_Msk | \
                           OPA_OP1_CR0_SW1_0_Msk | OPA_OP1_CR0_SW1_1_Msk | OPA_OP1_CR0_SW1_2_Msk,
                           OPA_OP1_CR0_SW1_2);

            __HAL_OPA_DAC_BUF_DISABLE(hOPA);
        }
        else if( pCfg->Mode == OPA_MODE_FOLLOWER_DAC )
        {
            // Follow DAC output
            WRITE_REG_MASK(hOPA->Instance->OP1_CR0,
                           OPA_OP1_CR0_SW1PVSS_Msk | OPA_OP1_CR0_SW1NVSS_Msk | \
                           OPA_OP1_CR0_SW1_0_Msk | OPA_OP1_CR0_SW1_1_Msk | OPA_OP1_CR0_SW1_2_Msk,
                           0);
            __HAL_OPA_DAC_BUF_ENABLE(hOPA);
        }
        else if( (pCfg->Mode & OPA_MODE_PGA_MSK) == OPA_MODE_PGA_TYPE )
        {
            if( pCfg->Mode == OPA_MODE_PGA_INVERTING )
            {
                /**
                 *  Inverting Amplifier:
                 *  Vout = -(R2/R1) * Vi + ((R1+R2)/R1) * Vdac_op
                 *       = -16 * Vi + 17 * Vdac_op
                 */
                WRITE_REG_MASK(hOPA->Instance->OP1_CR0,
                               OPA_OP1_CR0_SW1PVSS_Msk | OPA_OP1_CR0_SW1NVSS_Msk | \
                               OPA_OP1_CR0_SW1_0_Msk | OPA_OP1_CR0_SW1_1_Msk | OPA_OP1_CR0_SW1_2_Msk,
                               OPA_OP1_CR0_SW1_0 | OPA_OP1_CR0_SW1PVSS);

                __HAL_OPA_DAC_BUF_DISABLE(hOPA);
            }
            else if( pCfg->Mode == OPA_MODE_PGA_NONINVERTING )
            {
                // VIP input
                WRITE_REG_MASK(hOPA->Instance->OP1_CR0,
                               OPA_OP1_CR0_SW1PVSS_Msk | OPA_OP1_CR0_SW1NVSS_Msk | \
                               OPA_OP1_CR0_SW1_0_Msk | OPA_OP1_CR0_SW1_1_Msk | OPA_OP1_CR0_SW1_2_Msk,
                               OPA_OP1_CR0_SW1NVSS | OPA_OP1_CR0_SW1_2);

                __HAL_OPA_DAC_BUF_DISABLE(hOPA);
            }
            else if( pCfg->Mode == OPA_MODE_PGA_DIFF )
            {
                // difference of VIP and VIN
                WRITE_REG_MASK(hOPA->Instance->OP1_CR0,
                               OPA_OP1_CR0_SW1PVSS_Msk | OPA_OP1_CR0_SW1NVSS_Msk | \
                               OPA_OP1_CR0_SW1_0_Msk | OPA_OP1_CR0_SW1_1_Msk | OPA_OP1_CR0_SW1_2_Msk,
                               OPA_OP1_CR0_SW1_0 | OPA_OP1_CR0_SW1_2);

                __HAL_OPA_DAC_BUF_ENABLE(hOPA);
            }
        }
        else if( pCfg->Mode == OPA_MODE_CALIBRATION )
        {
            // Externally short VIP and VIN
            WRITE_REG_MASK(hOPA->Instance->OP1_CR0,
                           OPA_OP1_CR0_SW1PVSS_Msk | OPA_OP1_CR0_SW1NVSS_Msk | \
                           OPA_OP1_CR0_SW1_0_Msk | OPA_OP1_CR0_SW1_1_Msk | OPA_OP1_CR0_SW1_2_Msk,
                           OPA_OP1_CR0_SW1_1 | OPA_OP1_CR0_SW1_2);

            __HAL_OPA_DAC_BUF_ENABLE(hOPA);
        }
        else if( pCfg->Mode == OPA_MODE_NONE )
        {
            // DO nothing
        }
        else
        {
            __HAL_UNLOCK(hOPA);
            return HAL_ERROR;
        }

        hOPA->Init.OP1_Mode = pCfg->Mode;

        if( pCfg->Mode != OPA_MODE_NONE &&
            pCfg->OutType == OPA_Out_IO_PIN )
        {
            SET_BIT(hOPA->Instance->OP1_CR0, OPA_OP1_CR0_SW1_7);
        }
        else
        {
            CLEAR_BIT(hOPA->Instance->OP1_CR0, OPA_OP1_CR0_SW1_7);
        }
    }

#if defined(CONFIG_USE_ZB32L032)
    /* Configure OP2 */
    if( pCfg->OP_Id == OPA_ID_2 )
    {
    }
#endif  /* CONFIG_USE_ZB32L032 */

    __HAL_UNLOCK(hOPA);
    return HAL_OK;
}

#endif  /* HAL_OPA_MODULE_ENABLED */

/**
 * @}
 */ /* group OPA OPA */

/**
 * @}
 */ /* group ZB32L03x_HAL_Driver */
