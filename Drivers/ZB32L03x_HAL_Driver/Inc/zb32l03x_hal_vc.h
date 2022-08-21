/**
 ******************************************************************************
 * @file    zb32l03x_hal_vc.h
 * @author  MCU Software Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   Header file of VC HAL module.
 ******************************************************************************
 **/


#ifndef __ZB32L03x_HAL_VC_H
#define __ZB32L03x_HAL_VC_H

#ifdef __cplusplus
extern "C" {
#endif


#include "zb32l03x_hal_def.h"

/** @addtogroup ZB32L03x_HAL_Driver
 * @{
 */

/** @addtogroup VC
 * @{
 */
//=============================================================================
//                  Constant Definition
//=============================================================================
/** @defgroup VC_Exported_Constants VC Exported Constants
 * @{
 */

/** @defgroup VC_Input VC Input Channel
 * @{
 */
typedef enum HAL_VC_In_Channel
{
    HAL_VC_IN_CHANNEL_0 = 0x00U,
    HAL_VC_IN_CHANNEL_1,
    HAL_VC_IN_CHANNEL_2,
    HAL_VC_IN_CHANNEL_3,

#if defined(CONFIG_USE_ZB32L003S)
    HAL_VC_IN_CHANNEL_V25DIV = HAL_VC_IN_CHANNEL_3,

#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)

    HAL_VC_IN_CHANNEL_4,
    HAL_VC_IN_CHANNEL_5,
    HAL_VC_IN_CHANNEL_6,
    HAL_VC_IN_CHANNEL_7,
    HAL_VC_IN_CHANNEL_8,
    HAL_VC_IN_CHANNEL_9,
    HAL_VC_IN_CHANNEL_10,
    HAL_VC_IN_CHANNEL_11,
    HAL_VC_IN_CHANNEL_12,
    HAL_VC_IN_CHANNEL_13,
    HAL_VC_IN_CHANNEL_14,
    HAL_VC_IN_CHANNEL_15,

    HAL_VC_IN_CHANNEL_DACO  = HAL_VC_IN_CHANNEL_11,
    HAL_VC_IN_CHANNEL_V1_2V = HAL_VC_IN_CHANNEL_13,
    HAL_VC_IN_CHANNEL_VCAP  = HAL_VC_IN_CHANNEL_15,
#endif

} HAL_VC_In_ChannelTypeDef;

/**
 * @}
 */

/** @defgroup VC_DAC_Vref VC DAC Vref
 * @{
 */
typedef enum HAL_VC_DAC_Vref
{
    HAL_VC_DAC_VREF_VCAP = 0x0,
    HAL_VC_DAC_VREF_VDD  = 0x1,

} HAL_VC_DAC_VrefTypeDef;
/**
 * @}
 */

/** @defgroup VC_Output VC DAC Output Channel
 * @{
 */
typedef enum HAL_VC_Out_Channel
{
    HAL_VC_OUT_CHANNEL_00       = (0x1 << 0),
    HAL_VC_OUT_CHANNEL_01       = (0x1 << 1),
    HAL_VC_OUT_CHANNEL_02       = (0x1 << 2),
    HAL_VC_OUT_CHANNEL_04       = (0x1 << 4),
    HAL_VC_OUT_CHANNEL_05       = (0x1 << 5),
    HAL_VC_OUT_CHANNEL_06       = (0x1 << 6),
    HAL_VC_OUT_CHANNEL_07       = (0x1 << 7),
    HAL_VC_OUT_CHANNEL_08       = (0x1 << 8),
    HAL_VC_OUT_CHANNEL_09       = (0x1 << 9),
    HAL_VC_OUT_CHANNEL_10       = (0x1 << 10),
    HAL_VC_OUT_CHANNEL_11       = (0x1 << 11),
    HAL_VC_OUT_CHANNEL_12       = (0x1 << 12),
    HAL_VC_OUT_CHANNEL_13       = (0x1 << 13),
    HAL_VC_OUT_CHANNEL_14       = (0x1 << 14),
    HAL_VC_OUT_CHANNEL_15       = (0x1 << 15),
    HAL_VC_OUT_CHANNEL_16       = (0x1 << 16),
    HAL_VC_OUT_CHANNEL_17       = (0x1 << 17),
    HAL_VC_OUT_CHANNEL_18       = (0x1 << 18),

    /* VC */
    HAL_VC_OUT_CHANNEL_INV_TIMX   = HAL_VC_OUT_CHANNEL_00,
    HAL_VC_OUT_CHANNEL_TIM10      = HAL_VC_OUT_CHANNEL_01,
    HAL_VC_OUT_CHANNEL_TIM11      = HAL_VC_OUT_CHANNEL_02,
    HAL_VC_OUT_CHANNEL_LPTIM      = HAL_VC_OUT_CHANNEL_04,
    HAL_VC_OUT_CHANNEL_LPTIMEXT   = HAL_VC_OUT_CHANNEL_05,
    HAL_VC_OUT_CHANNEL_INV_PCA    = HAL_VC_OUT_CHANNEL_06,
    HAL_VC_OUT_CHANNEL_PCACAP0    = HAL_VC_OUT_CHANNEL_07,
    HAL_VC_OUT_CHANNEL_PCAECI     = HAL_VC_OUT_CHANNEL_08,
    HAL_VC_OUT_CHANNEL_INV_TM1CH1 = HAL_VC_OUT_CHANNEL_09,
    HAL_VC_OUT_CHANNEL_TM1CH1     = HAL_VC_OUT_CHANNEL_10,
    HAL_VC_OUT_CHANNEL_INV_TM1CH2 = HAL_VC_OUT_CHANNEL_11,
    HAL_VC_OUT_CHANNEL_TM1CH2     = HAL_VC_OUT_CHANNEL_12,
    HAL_VC_OUT_CHANNEL_INV_TM1CH3 = HAL_VC_OUT_CHANNEL_13,
    HAL_VC_OUT_CHANNEL_TIM1CH3    = HAL_VC_OUT_CHANNEL_14,
    HAL_VC_OUT_CHANNEL_INV_TM1CH4 = HAL_VC_OUT_CHANNEL_15,
    HAL_VC_OUT_CHANNEL_TM1CH4     = HAL_VC_OUT_CHANNEL_16,
    HAL_VC_OUT_CHANNEL_TM1BKE     = HAL_VC_OUT_CHANNEL_17,

#if defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    /* VC1 */
    HAL_VC_OUT_CHANNEL_INV_TM1ACH1     = HAL_VC_OUT_CHANNEL_09,
    HAL_VC_OUT_CHANNEL_TM1ACH1         = HAL_VC_OUT_CHANNEL_10,
    HAL_VC_OUT_CHANNEL_INV_TM1ACH2     = HAL_VC_OUT_CHANNEL_11,
    HAL_VC_OUT_CHANNEL_TM1ACH2         = HAL_VC_OUT_CHANNEL_12,
    HAL_VC_OUT_CHANNEL_INV_TM1ACH3     = HAL_VC_OUT_CHANNEL_13,
    HAL_VC_OUT_CHANNEL_TM1ACH3         = HAL_VC_OUT_CHANNEL_14,
    HAL_VC_OUT_CHANNEL_INV_TM1ACH4     = HAL_VC_OUT_CHANNEL_15,
    HAL_VC_OUT_CHANNEL_TM1ACH4         = HAL_VC_OUT_CHANNEL_16,
    HAL_VC_OUT_CHANNEL_TM1ABKE         = HAL_VC_OUT_CHANNEL_17,
    HAL_VC_1_OUT_CHANNEL_ALL           = 0x0003FE00,
#endif

    HAL_VC_OUT_CHANNEL_INV_PAD    = HAL_VC_OUT_CHANNEL_18,
    HAL_VC_OUT_CHANNEL_ALL        = 0x0007FFFF,

} HAL_VC_Out_ChannelTypeDef;

/** @defgroup VC_Interrupt_Trigger_Mode  VC Interrupt trigger mode
 * @{
 */
typedef enum HAL_VC_Interrupt_Mode
{
    HAL_VC_INTERRUPT_DISABLE       = 0u,
    HAL_VC_INTERRUPT_TRIGGER_HIGH  = VC_CR1_HIGHINTEN,   /* VC Interrupt hight level triger  */
    HAL_VC_INTERRUPT_TRIGGER_RISE  = VC_CR1_RISEINTEN,   /* VC Interrupt rising triger       */
    HAL_VC_INTERRUPT_TRIGGER_FALL  = VC_CR1_FALLINTEN,   /* VC Interrupt falling triger      */

} HAL_VC_Interrupt_ModeTypeDef;
/**
 * @}
 */

/** @defgroup VC_FILTER_CLK_SELECT  VC Filter clock select
 * @{
 */
typedef enum HAL_VC_Filter_Clk
{
    HAL_VC_FILTER_CLK_NONE  = 0x00U,                               /*!< VC Filter clock select NONE */
    HAL_VC_FILTER_CLK_PCLK  = (0x01U << VC_CR1_FLTCLK_SEL_Pos),    /*!< VC Filter clock select PCLK */
    HAL_VC_FILTER_CLK_SIRC  = (0x02U << VC_CR1_FLTCLK_SEL_Pos),    /*!< VC Filter clock select SIRC */
} HAL_VC_Filter_ClkTypeDef;
/**
 * @}
 */


/** @defgroup ADC_State VC state
 * @{
 */
typedef enum HAL_VC_State
{
    HAL_VC_STATE_RESET     = 0x00U,  /*!< CRC not yet initialized or disabled */
    HAL_VC_STATE_READY     = 0x01U,  /*!< CRC initialized and ready for use   */
    HAL_VC_STATE_BUSY      = 0x02U,  /*!< CRC internal process is ongoing     */
    HAL_VC_STATE_TIMEOUT   = 0x03U,  /*!< CRC timeout state                   */
    HAL_VC_STATE_ERROR     = 0x04U   /*!< CRC error state                     */

} HAL_VC_StateTypeDef;
/**
 * @}
 */

#if defined(CONFIG_USE_ZB32L003S)
typedef enum HAL_VC_V25DIV
{
    HAL_VC_V25DIV_1P4 = 0x00U,      /*!< Specifies the VC 1/4 V25D */
    HAL_VC_V25DIV_2P4,              /*!< Specifies the VC 2/4 V25D  */
    HAL_VC_V25DIV_3P4,              /*!< Specifies the VC 3/4 V25D  */
    HAL_VC_V25DIV_4P4,              /*!< Specifies the VC V25D not divided */
    HAL_VC_V25DIV_DISABLE,
} HAL_VC_V25DIVTypeDef;

#endif


/**
 * @}
 */

//=============================================================================
//                  Macro Definition
//=============================================================================
/** @defgroup VC_Exported_Macros VC Exported Macros
 * @{
 */

/**
 *  \brief  Enable VC
 *
 *  \param [in] __HANDLE__          Pointer to a HAL_VC_HandleTypeDef structure
 *  \return     none
 */
#define __HAL_VC_ENABLE(__HANDLE__)                 SET_BIT((__HANDLE__)->Instance->CR1, VC_CR1_VCEN)

/**
 *  \brief  Disable VC
 *
 *  \param [in] __HANDLE__          Pointer to a HAL_VC_HandleTypeDef structure
 *  \return     none
 */
#define __HAL_VC_DISABLE(__HANDLE__)                CLEAR_BIT((__HANDLE__)->Instance->CR1, VC_CR1_VCEN)


/**
 *  \brief  Enable VC interrupt
 *
 *  \param [in] __HANDLE__          Pointer to a HAL_VC_HandleTypeDef structure
 *  \return     none
 */
#define __HAL_VC_ENABLE_IT(__HANDLE__)              SET_BIT((__HANDLE__)->Instance->CR1, VC_CR1_INT_EN)

/**
 *  \brief  Disable VC interrupt
 *
 *  \param [in] __HANDLE__          Pointer to a HAL_VC_HandleTypeDef structure
 *  \return     none
 */
#define __HAL_VC_DISABLE_IT(__HANDLE__)             CLEAR_BIT((__HANDLE__)->Instance->CR1, VC_CR1_INT_EN)

/**
 *  \brief  Get interrupt flag status of VC
 *
 *  \param [in] __HANDLE__          Pointer to a HAL_VC_HandleTypeDef structure
 *  \return     true or false
 */
#define __HAL_VC_GET_IT_FLAG(__HANDLE__)            READ_BIT((__HANDLE__)->Instance->SR, VC_SR_INTF)

/**
 *  \brief  Clear interrupt flag of VC
 *
 *  \param [in] __HANDLE__          Pointer to a HAL_VC_HandleTypeDef structure
 *  \return     none
 */
#define __HAL_VC_CLEAR_IT_FLAG(__HANDLE__)          CLEAR_BIT((__HANDLE__)->Instance->SR, VC_SR_INTF)

/**
 *  \brief  Get output status of VC filtering
 *
 *  \param [in] __HANDLE__
 *  \return     status of VC filtering
 */
 #define __HAL_VC_GET_FILTER_OUT(__HANDLE__)         (READ_BIT((__HANDLE__)->Instance->SR, VC_SR_VC_FLOUT) ? 1 : 0)

/**
 * @}
 */
//=============================================================================
//                  Structure Definition
//=============================================================================
/** @defgroup VC_Exported_Types VC Exported Types
 * @{
 */
/**
 * @brief  VC Init structure definition
 */
typedef struct
{
    HAL_VC_In_ChannelTypeDef    NInChannelSel;  /*!< Negative input select, @ref VC_InputTypeDef               */
    HAL_VC_In_ChannelTypeDef    PInChannelSel;  /*!< Positive input select, @ref VC_InputTypeDef               */
    uint32_t                    InterruptMode;  /*!< Interrupt trigger mode, @ref VC_Interrupt_Trigger_Mode    */

    uint8_t                     FilterEnable;   /*!< Filter counter Enable or Disable                          */
    uint16_t                    Fliter_Num;     /*!< Filter counter number. Range: 0x0 ~ 0xFFFF                */
    HAL_VC_Filter_ClkTypeDef    Filter_Clk;     /*!< Filter clk select @ref HAL_VC_Filter_ClkTypeDef           */
    uint32_t                    OutCnannels;    /*!< Output channel selection, @ref HAL_VC_Out_ChannelTypeDef  */

#if defined(CONFIG_USE_ZB32L003S)
    HAL_VC_V25DIVTypeDef        V25div;         /*!< Specifies the VC V25DIV divider, @ref HAL_VC_V25DIVTypeDef */

#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    uint8_t                 DACLevel;       /*!< DAC level, Range: 0 ~ 63 */
    HAL_VC_DAC_VrefTypeDef  Vref;           /*!< DAC Vref, @ref HAL_VC_DAC_VrefTypeDef */
#endif
} VC_InitTypeDef;


/**
 * @brief  VC Handle Structure definition
 */
typedef struct
{
    VC_TypeDef              *Instance;  /*!< Register base address    */

    VC_InitTypeDef          Init;       /*!< VC required parameters */

    HAL_LockTypeDef         Lock;       /*!< ADC locking object */

    HAL_VC_StateTypeDef     State;      /*!< VC state */

} HAL_VC_HandleTypeDef;

/**
 * @}
 */

/**
 * @}
 */
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
HAL_StatusTypeDef HAL_VC_Init(HAL_VC_HandleTypeDef *hVC);
HAL_StatusTypeDef HAL_VC_DeInit(HAL_VC_HandleTypeDef *hVC);


void HAL_VC_MspInit(HAL_VC_HandleTypeDef *hVC);
void HAL_VC_MspDeInit(HAL_VC_HandleTypeDef *hVC);

HAL_StatusTypeDef HAL_VC_Start(HAL_VC_HandleTypeDef *hVC);
HAL_StatusTypeDef HAL_VC_Stop(HAL_VC_HandleTypeDef *hVC);

HAL_StatusTypeDef HAL_VC_Start_IT(HAL_VC_HandleTypeDef *hVC);
HAL_StatusTypeDef HAL_VC_Stop_IT(HAL_VC_HandleTypeDef *hVC);

HAL_StatusTypeDef HAL_VC_ConfigOutChannels(HAL_VC_HandleTypeDef *hVC, uint32_t channels);

void HAL_VC_IRQHandler(HAL_VC_HandleTypeDef *hVC);

void HAL_VC_FilterCmpltCallback(HAL_VC_HandleTypeDef *hVC);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZB32L03x_HAL_VC_H */
