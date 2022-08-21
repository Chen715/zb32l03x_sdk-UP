/**
 * Copyright (c) 2022 Wei-Lun Hsu. All Rights Reserved.
 */
/** @file zb32l03x_hal_opa.h
 *
 * @author Wei-Lun Hsu
 * @version 0.1
 * @date 2022/02/14
 * @license
 * @description
 */

#ifndef __zb32l03x_hal_opa_H_wUgwzSUs_lvf8_HCAQ_sRZV_upnDSQZ5NplX__
#define __zb32l03x_hal_opa_H_wUgwzSUs_lvf8_HCAQ_sRZV_upnDSQZ5NplX__

#ifdef __cplusplus
extern "C" {
#endif

#include "zb32l03x_hal_def.h"

/** @addtogroup ZB32L03x_HAL_Driver
 * @{
 */

/** @addtogroup OPA
 * @{
 */
//=============================================================================
//                  Constant Definition
//=============================================================================
/** @defgroup OPA_Exported_Constants OPA Exported Constants
 * @{
 */

typedef enum OPA_Id
{
    OPA_ID_1 = 0,
    OPA_ID_2,
    OPA_ID_ALL,

} OPA_IdTypeDef;

typedef enum OPA_Mode
{
#define OPA_MODE_PGA_MSK        0xF0u
#define OPA_MODE_PGA_TYPE       0x20u

    OPA_MODE_NONE              = 0x0,

#if defined(CONFIG_USE_ZB32L030)
    OPA_MODE_STANDALONE        = 0x01,                         /*!< L030 OP2 with external gain setting (ONLY OP2 support)         */
#endif  /* CONFIG_USE_ZB32L030 */

    OPA_MODE_CALIBRATION       = 0x02,                         /*!< OP1 calibration mode. User SHOULD measure trim offset manually */
    OPA_MODE_FOLLOWER_INP      = 0x03,                         /*!< OP1 Voltage-Follower (or Unit Gain) mode and OPA1_INP input    */
    OPA_MODE_FOLLOWER_DAC      = 0x04,                         /*!< OP1 Voltage-Follower (or Unit Gain) mode and Vdac input        */
    OPA_MODE_PGA_INVERTING     = (OPA_MODE_PGA_TYPE | 0x00),   /*!< OP1 Inverting Amplifier mode                                   */
    OPA_MODE_PGA_NONINVERTING  = (OPA_MODE_PGA_TYPE | 0x01),   /*!< OP1 Non-Inverting Amplifier mode                               */
    OPA_MODE_PGA_DIFF          = (OPA_MODE_PGA_TYPE | 0x02),   /*!< OP1 Difference Amplifier mode                                  */

} OPA_ModeTypeDef;

typedef enum OPA_DAC_Vref
{
    OPA_DAC_VREF_VCAP = 0x0,
    OPA_DAC_VREF_VDD  = 0x1,

} OPA_DAC_VrefTypeDef;

typedef enum OPA_Out
{
    OPA_Out_ADC    = 0x0,
    OPA_Out_IO_PIN = 0x1,

} OPA_OutTypeDef;

/**
 * @brief  HAL State structures definition
 */
typedef enum HAL_OPA_State
{
    HAL_OPA_STATE_RESET           = 0x00,       /*!< OPA is not yet Initialized          */
    HAL_OPA_STATE_READY           = 0x01,       /*!< OPA is initialized and ready for use */
    HAL_OPA_STATE_BUSY            = 0x02,       /*!< OPA is enabled and running in normal mode */

} HAL_OPA_StateTypeDef;

/**
 * @}
 */  /* End of group OPA_Exported_Constants */

//=============================================================================
//                  Macro Definition
//=============================================================================
/** @defgroup OPA_Exported_Macros OPA Exported Macros
 * @{
 */

/**
 *  \brief Brief Enable OP1/OP2 cascading
 *
 *  \param [in] __HANDLE__      The pointer of a HAL_OPA_HandleTypeDef structure
 */
#define __HAL_OPA_ENABLE_CASCADING(__HANDLE__)  \
            ((__HANDLE__)->Instance->OP1_CR0 |= OPA_OP1_CR0_SW12EN)

/**
 *  \brief Brief Disable OP1/OP2 cascading
 *
 *  \param [in] __HANDLE__      The pointer of a HAL_OPA_HandleTypeDef structure
 */
#define __HAL_OPA_DISABLE_CASCADING(__HANDLE__)  \
            ((__HANDLE__)->Instance->OP1_CR0 &= ~OPA_OP1_CR0_SW12EN)

/**
 *  \brief  Get OPA state
 *
 *  \param [in] __HANDLE__      The pointer of a HAL_OPA_HandleTypeDef structure
 *  \return
 *      @ref HAL_OPA_StateTypeDef
 */
#define __HAL_OPA_GET_STATE(__HANDLE__)         ((__HANDLE__)->State)

/**
 * @}
 */  /* End of group OPA_Exported_Macros */

//=============================================================================
//                  Structure Definition
//=============================================================================

/** @defgroup OPA_Exported_Types OPA Exported Types
 * @{
 */


/**
 * @brief  OPAMP Init structure definition
 */
typedef struct OPA_Init
{
    OPA_ModeTypeDef         OP1_Mode;   /*!< Specifies the OP1 mode
                                            This parameter must be a value of @ref OPA_ModeTypeDef */
    OPA_OutTypeDef          OP1_Out;    /*!< Specifies the OP1 output type
                                            This parameter must be a value of @ref OPA_OutTypeDef */

    OPA_ModeTypeDef         OP2_Mode;   /*!< Specifies the OP2 mode (L030 ONLY supports OPA_MODE_STANDALONE)
                                            This parameter must be a value of @ref OPA_ModeTypeDef */

    OPA_OutTypeDef          OP2_Out;    /*!< Specifies the OP2 output type
                                            This parameter must be a value of @ref OPA_OutTypeDef */

    OPA_DAC_VrefTypeDef     Vref;       /*!< Specifies the OP2 mode
                                            This parameter must be a value of @ref OPA_DAC_VrefTypeDef */

    uint8_t                 DC_Level_Step;  /* range: 0 ~ 63 */

} OPA_InitTypeDef;



/**
 * @brief OPAMP Handle Structure definition
 */
typedef struct
{
    OPA_TypeDef                 *Instance;      /*!< OPA instance's registers base address   */
    OPA_InitTypeDef             Init;           /*!< OPA required parameters */
    HAL_StatusTypeDef           Status;         /*!< OPA peripheral status   */
    HAL_LockTypeDef             Lock;           /*!< Locking object          */
    __IO HAL_OPA_StateTypeDef   State;          /*!< OPA communication state */

} HAL_OPA_HandleTypeDef;

typedef struct OPA_Config
{
    OPA_IdTypeDef       OP_Id;          /*!< OPA target ID @ref OPA_IdTypeDef     */
    OPA_ModeTypeDef     Mode;           /*!< OPA targer mode @ref OPA_ModeTypeDef */
    OPA_OutTypeDef      OutType;        /*!< OPA target output typt @ref OPA_OutTypeDef */

#define OPA_CONFIG_IGNORE_TAG    -1
    int8_t              DC_Level_Step;  /* range: 0 ~ 63, OPA_CONFIG_SKIP_DC_LEVEL will ignore this parament */
} OPA_ConfigTypeDef;

/**
 * @}
 */  /* End of group OPA_Exported_Types */

//=============================================================================
//                  Global Data Definition
//=============================================================================

//=============================================================================
//                  Private Function Definition
//=============================================================================

//=============================================================================
//                  Public Function Definition
//=============================================================================
/** @addtogroup OPA_Exported_Functions
 * @{
 */

/**
 *  \brief  OP-Amplifier initialize
 *
 *  \param [in] hOPA        The pointer of OPA handle
 *  \return
 *      HAL status
 */
HAL_StatusTypeDef
HAL_OPA_Init(HAL_OPA_HandleTypeDef *hOPA);

/**
 *  \brief  OP-Amplifier de-initialize
 *
 *  \param [in] hOPA        The pointer of OPA handle
 *  \return
 *      HAL status
 */
HAL_StatusTypeDef
HAL_OPA_DeInit(HAL_OPA_HandleTypeDef *hOPA);

/**
 *  \brief  Start the OP-Amplifier.
 *
 *  \param [in] hOPA        The pointer of OPA handle
 *  \param [in] OP_Id       The target OPA id, @ref OPA_IdTypeDef
 *  \return
 *      HAL status
 */
HAL_StatusTypeDef
HAL_OPA_Start(HAL_OPA_HandleTypeDef *hOPA, OPA_IdTypeDef OP_Id);

/**
 *  \brief  Stop the OP-Amplifier.
 *
 *  \param [in] hOPA        The pointer of OPA handle
 *  \param [in] OP_Id       The target OPA id, @ref OPA_IdTypeDef
 *  \return
 *      HAL status
 */
HAL_StatusTypeDef
HAL_OPA_Stop(HAL_OPA_HandleTypeDef *hOPA, OPA_IdTypeDef OP_Id);

/**
 *  \brief  Re-Configure OPA
 *
 *  \param [in] hOPA        The pointer of OPA handle
 *  \param [in] pCfg        The pointer of @ref OPA_ConfigTypeDef
 *  \return
 *      HAL status
 */
HAL_StatusTypeDef
HAL_OPA_Config(HAL_OPA_HandleTypeDef *hOPA, OPA_ConfigTypeDef *pCfg);


/**
 * @}
 */  /* End of group OPA_Exported_Functions */

/**
 * @}
 */  /* End of group OPA */

/**
 * @}
 */  /* End of group ZB32L03x_HAL_Driver */


#ifdef __cplusplus
}
#endif

#endif
