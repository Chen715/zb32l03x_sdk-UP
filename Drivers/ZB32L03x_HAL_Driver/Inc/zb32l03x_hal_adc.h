/**
 * Copyright (c) 2022 Wei-Lun Hsu. All Rights Reserved.
 */
/** @file zb32l03x_hal_adc.h
 *
 * @author Wei-Lun Hsu
 * @version 0.1
 * @date 2022/03/29
 * @license
 * @description
 */

#ifndef __zb32l03x_hal_adc_org_H_wy0doRo7_lP1p_Hmal_s8yt_u8YtcLFWoqkS__
#define __zb32l03x_hal_adc_org_H_wy0doRo7_lP1p_Hmal_s8yt_u8YtcLFWoqkS__

#ifdef __cplusplus
extern "C" {
#endif

#include "zb32l03x_hal_def.h"

/** @addtogroup ZB32L03x_HAL_Driver
 * @{
 */

/** @addtogroup ADC
 * @{
 */


//=============================================================================
//                  Constant Definition
//=============================================================================
/** @defgroup HAL_ADC_SampleDuty ADC Sample duty cycle
 * @{
 */
typedef enum HAL_ADC_SampleDuty
{
    HAL_ADC_SAMPLE_4CYCLE   = 0x00U,        /*!< ADC Sample 4 cycles    */
    HAL_ADC_SAMPLE_8CYCLE   = ADC_CR0_SAM,  /*!< ADC Sample 8 cycles    */
} HAL_ADC_SampleDutyTypeDef;

/**
 * @}
 */

/** @defgroup HAL_ADC_ChannelSel ADC channel select
 * @{
 */
typedef enum HAL_ADC_ChannelSel
{
    HAL_ADC_CHANNEL_0        = (0x1 << 0),       /*!< Select ADC channel 0 in single mode            */
    HAL_ADC_CHANNEL_1        = (0x1 << 1),       /*!< Select ADC channel 1 in single mode            */
    HAL_ADC_CHANNEL_2        = (0x1 << 2),       /*!< Select ADC channel 2 in single mode            */
    HAL_ADC_CHANNEL_3        = (0x1 << 3),       /*!< Select ADC channel 3 in single mode            */
    HAL_ADC_CHANNEL_4        = (0x1 << 4),       /*!< Select ADC channel 4 in single mode            */
    HAL_ADC_CHANNEL_5        = (0x1 << 5),       /*!< Select ADC channel 5 in single mode            */
    HAL_ADC_CHANNEL_6        = (0x1 << 6),       /*!< Select ADC channel 6 in single mode            */
    HAL_ADC_CHANNEL_7        = (0x1 << 7),       /*!< Select ADC channel 7 in single mode            */

#if defined(CONFIG_USE_ZB32L003S)
    HAL_ADC_CHANNEL_VCAP    = HAL_ADC_CHANNEL_7,

#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    HAL_ADC_CHANNEL_8        = (0x1 << 8),       /*!< Select ADC channel 8 in single mode            */
    HAL_ADC_CHANNEL_9        = (0x1 << 9),       /*!< Select ADC channel 9 in single mode            */
    HAL_ADC_CHANNEL_10       = (0x1 << 10),      /*!< Select ADC channel 10 in single mode           */
    HAL_ADC_CHANNEL_11       = (0x1 << 11),      /*!< Select ADC channel 11 in single mode           */
    HAL_ADC_CHANNEL_12       = (0x1 << 12),      /*!< Select ADC channel 12 in single mode           */
    HAL_ADC_CHANNEL_13       = (0x1 << 13),      /*!< Select ADC channel 13 in single mode           */
    HAL_ADC_CHANNEL_14       = (0x1 << 14),      /*!< Select ADC channel 14 in single mode           */
    HAL_ADC_CHANNEL_15       = (0x1 << 15),      /*!< Select ADC channel 15 in single mode           */
    HAL_ADC_CHANNEL_16       = (0x1 << 16),      /*!< Select ADC channel 16 in single mode           */
    HAL_ADC_CHANNEL_17       = (0x1 << 17),      /*!< Select ADC channel 17 in single mode           */
    HAL_ADC_CHANNEL_18       = (0x1 << 18),      /*!< Select ADC channel 18 in single mode           */
    HAL_ADC_CHANNEL_19       = (0x1 << 19),      /*!< Select ADC channel 19 in single mode           */
    HAL_ADC_CHANNEL_20       = (0x1 << 20),      /*!< Select ADC channel 20 in single mode           */
    HAL_ADC_CHANNEL_21       = (0x1 << 21),      /*!< Select ADC channel 21 in single mode           */
    HAL_ADC_CHANNEL_22       = (0x1 << 22),      /*!< Select ADC channel 22 in single mode           */
    HAL_ADC_CHANNEL_23       = (0x1 << 23),      /*!< Select ADC channel 23 in single mode           */

    HAL_ADC_CHANNEL_OP1_O   = HAL_ADC_CHANNEL_10,
    HAL_ADC_CHANNEL_OP2_O   = HAL_ADC_CHANNEL_11,
    HAL_ADC_CHANNEL_DAC_OP  = HAL_ADC_CHANNEL_12,
    HAL_ADC_CHANNEL_V12     = HAL_ADC_CHANNEL_13,
    HAL_ADC_CHANNEL_VCAP    = HAL_ADC_CHANNEL_14,
#endif

} HAL_ADC_ChannelSelTypeDef;

/**
 * @}
 */



/** @defgroup HAL_ADC_ClkSel ADC clock selection
 * @{
 */
typedef enum HAL_ADC_ClkSel
{
    HAL_ADC_CLOCK_PCLK_DIV1     = (ADC_CR0_CLKSEL_PCLK_DIV1   << ADC_CR0_CLKSEL_Pos),     /*!< Select ADC clock PCLK          */
    HAL_ADC_CLOCK_PCLK_DIV2     = (ADC_CR0_CLKSEL_PCLK_DIV2   << ADC_CR0_CLKSEL_Pos),     /*!< Select ADC clock PCLK/2        */
    HAL_ADC_CLOCK_PCLK_DIV4     = (ADC_CR0_CLKSEL_PCLK_DIV4   << ADC_CR0_CLKSEL_Pos),     /*!< Select ADC clock PCLK/4        */
    HAL_ADC_CLOCK_PCLK_DIV8     = (ADC_CR0_CLKSEL_PCLK_DIV8   << ADC_CR0_CLKSEL_Pos),     /*!< Select ADC clock PCLK/8        */
    HAL_ADC_CLOCK_PCLK_DIV16    = (ADC_CR0_CLKSEL_PCLK_DIV16  << ADC_CR0_CLKSEL_Pos),     /*!< Select ADC clock PCLK/16       */
    HAL_ADC_CLOCK_PCLK_DIV32    = (ADC_CR0_CLKSEL_PCLK_DIV32  << ADC_CR0_CLKSEL_Pos),     /*!< Select ADC clock PCLK/32       */
    HAL_ADC_CLOCK_PCLK_DIV64    = (ADC_CR0_CLKSEL_PCLK_DIV64  << ADC_CR0_CLKSEL_Pos),     /*!< Select ADC clock PCLK/64       */
    HAL_ADC_CLOCK_PCLK_DIV128   = (ADC_CR0_CLKSEL_PCLK_DIV128 << ADC_CR0_CLKSEL_Pos),     /*!< Select ADC clock PCLK/128      */

} HAL_ADC_ClkSelTypeDef;

/**
 * @}
 */

/** @defgroup ADC_SingleContinueMode ADC single/continue mode selection
 * @{
 */
typedef enum HAL_ADC_ConvMode
{
    HAL_ADC_MODE_SINGLE     = 0,                /*!< Select ADC single mode          */
    HAL_ADC_MODE_CONTINUE   = ADC_CR1_CT,     /*!< Select ADC continue mode        */

} HAL_ADC_ConvModeTypeDef;

/**
 * @}
 */


/** @defgroup HAL_ADC_AutoAccumulation ADC conversion results are auto accmulated in ADC_RESULT_ACC register
 * @{
 */
typedef enum HAL_ADC_AutoAcc
{
    HAL_ADC_AUTOACC_DISABLE     = 0,
    HAL_ADC_AUTOACC_ENABLE      = ADC_CR1_RACC_EN,      /*!< Auto accumulation enable       */
} HAL_ADC_AutoAccTypeDef;

/**
 * @}
 */

/** @defgroup HAL_ADC_CircleMode ADC multichannel conversion mode selection: circle/non-circle
 * @{
 */
typedef enum HAL_ADC_CircleMode
{
    HAL_ADC_MULTICHANNEL_NONCIRCLE      = 0,
    HAL_ADC_MULTICHANNEL_CIRCLE         = (ADC_CR2_CIRCLE_MODE),    /*!< ADC multichannel conversion circle mode   */

} HAL_ADC_CircleModeTypeDef;

/**
 * @}
 */

/** @defgroup HAL_ADC_Vref ADC reference voltage
 * @{
 */
typedef enum HAL_ADC_Vref
{
    HAL_ADC_VREF_VDD        = (ADC_CR0_VRSEL_AVDD     << ADC_CR0_VRSEL_Pos),

#if defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    HAL_ADC_VREF_EXT_VREF   = (ADC_CR0_VRSEL_EXT_VREF << ADC_CR0_VRSEL_Pos),
#endif

    HAL_ADC_VREF_VCAP       = (ADC_CR0_VRSEL_VCAP     << ADC_CR0_VRSEL_Pos),

} HAL_ADC_VrefTypeDef;

/**
 * @}
 */


/** @defgroup ADC_External_Trigger_Source ADC external trigger source 1 select
 * @{
 */
typedef enum HAL_ADC_ExtTrigger_Src
{
    HAL_ADC_EXTTRIG_SW_START        = 0x00u,
    HAL_ADC_EXTTRIG_TIM10           = 0x01u,
    HAL_ADC_EXTTRIG_TIM11           = 0x02u,
    HAL_ADC_EXTTRIG_TIM1            = 0x03u,
    HAL_ADC_EXTTRIG_LPTIM           = 0x04u,
    HAL_ADC_EXTTRIG_TIM1_TRGO       = 0x05u,
    HAL_ADC_EXTTRIG_TIM2_TRGO       = 0x06u,
    HAL_ADC_EXTTRIG_TIM2_INT        = 0x07u,
    HAL_ADC_EXTTRIG_UART0_INT       = 0x08u,
    HAL_ADC_EXTTRIG_UART1_INT       = 0x09u,
    HAL_ADC_EXTTRIG_LPUART_INT      = 0x0Au,
    HAL_ADC_EXTTRIG_VC0_INT         = 0x0Bu,
    HAL_ADC_EXTTRIG_VC1_INT         = 0x0Cu,
    HAL_ADC_EXTTRIG_RTC_INT         = 0x0Du,
    HAL_ADC_EXTTRIG_PCA_INT         = 0x0Eu,
    HAL_ADC_EXTTRIG_SPI_INT         = 0x0Fu,
    HAL_ADC_EXTTRIG_PA1_INT         = 0x10u,
    HAL_ADC_EXTTRIG_PA2_INT         = 0x11u,
    HAL_ADC_EXTTRIG_PA3_INT         = 0x12u,
    HAL_ADC_EXTTRIG_PB4_INT         = 0x13u,
    HAL_ADC_EXTTRIG_PB5_INT         = 0x14u,
    HAL_ADC_EXTTRIG_PA5_INT         = 0x15u,
    HAL_ADC_EXTTRIG_PA6_INT         = 0x16u,
    HAL_ADC_EXTTRIG_PC5_INT         = 0x17u,
    HAL_ADC_EXTTRIG_PC6_INT         = 0x18u,
    HAL_ADC_EXTTRIG_PA7_INT         = 0x19u,
    HAL_ADC_EXTTRIG_PA8_INT         = 0x1Au,
    HAL_ADC_EXTTRIG_PA9_INT         = 0x1Bu,
    HAL_ADC_EXTTRIG_PA10_INT        = 0x1Cu,
    HAL_ADC_EXTTRIG_PB0_INT         = 0x1Du,
    HAL_ADC_EXTTRIG_PB1_INT         = 0x1Eu,
    HAL_ADC_EXTTRIG_PD0_INT         = 0x1Fu,
} HAL_ADC_ExtTrigger_SrcTypeDef;

/**
 * @}
 */

/** @defgroup ADC_Interrupt_Type ADC interrupt type definition
 * @{
 */

typedef enum HAL_ADC_IT
{
    HAL_ADC_IT_LOW_THRESHOLD        = (int)ADC_INTEN_LLT_IEN,        /*!< ADC conversion data below threshold interrupt flag */
    HAL_ADC_IT_HIGH_THRESHOLD       = (int)ADC_INTEN_HHT_IEN,        /*!< ADC conversion data above threshold interrupt flag */
    HAL_ADC_IT_RANGE_THRESHOLD      = (int)ADC_INTEN_REG_IEN,        /*!< ADC conversion data in defined range interrupt flag */
    HAL_ADC_IT_CONTINUE             = (int)ADC_INTEN_CONT_IEN,       /*!< ADC End of Continue Conversion interrupt flag */
    HAL_ADC_IT_CHANNEL_0            = (int)ADC_INTEN_ADCXIEN_0,      /*!< ADC End of channel 0  conversion interrupt source */
    HAL_ADC_IT_CHANNEL_1            = (int)ADC_INTEN_ADCXIEN_1,      /*!< ADC End of channel 1  conversion interrupt source */
    HAL_ADC_IT_CHANNEL_2            = (int)ADC_INTEN_ADCXIEN_2,      /*!< ADC End of channel 2  conversion interrupt source */
    HAL_ADC_IT_CHANNEL_3            = (int)ADC_INTEN_ADCXIEN_3,      /*!< ADC End of channel 3  conversion interrupt source */
    HAL_ADC_IT_CHANNEL_4            = (int)ADC_INTEN_ADCXIEN_4,      /*!< ADC End of channel 4  conversion interrupt source */
    HAL_ADC_IT_CHANNEL_5            = (int)ADC_INTEN_ADCXIEN_5,      /*!< ADC End of channel 5  conversion interrupt source */
    HAL_ADC_IT_CHANNEL_6            = (int)ADC_INTEN_ADCXIEN_6,      /*!< ADC End of channel 6  conversion interrupt source */
    HAL_ADC_IT_CHANNEL_7            = (int)ADC_INTEN_ADCXIEN_7,      /*!< ADC End of channel 7  conversion interrupt source */
#if defined(CONFIG_USE_ZB32L003S)
    HAL_ADC_IT_CHANNEL_ALL          = (int)0xFF,
#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    HAL_ADC_IT_CHANNEL_8            = (int)ADC_INTEN_ADCXIEN_8,      /*!< ADC End of channel 8  conversion interrupt source */
    HAL_ADC_IT_CHANNEL_9            = (int)ADC_INTEN_ADCXIEN_9,      /*!< ADC End of channel 9  conversion interrupt source */
    HAL_ADC_IT_CHANNEL_10           = (int)ADC_INTEN_ADCXIEN_10,     /*!< ADC End of channel 10 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_11           = (int)ADC_INTEN_ADCXIEN_11,     /*!< ADC End of channel 11 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_12           = (int)ADC_INTEN_ADCXIEN_12,     /*!< ADC End of channel 12 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_13           = (int)ADC_INTEN_ADCXIEN_13,     /*!< ADC End of channel 13 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_14           = (int)ADC_INTEN_ADCXIEN_14,     /*!< ADC End of channel 14 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_15           = (int)ADC_INTEN_ADCXIEN_15,     /*!< ADC End of channel 15 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_16           = (int)ADC_INTEN_ADCXIEN_16,     /*!< ADC End of channel 16 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_17           = (int)ADC_INTEN_ADCXIEN_17,     /*!< ADC End of channel 17 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_18           = (int)ADC_INTEN_ADCXIEN_18,     /*!< ADC End of channel 18 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_19           = (int)ADC_INTEN_ADCXIEN_19,     /*!< ADC End of channel 19 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_20           = (int)ADC_INTEN_ADCXIEN_20,     /*!< ADC End of channel 20 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_21           = (int)ADC_INTEN_ADCXIEN_21,     /*!< ADC End of channel 21 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_22           = (int)ADC_INTEN_ADCXIEN_22,     /*!< ADC End of channel 22 conversion interrupt source */
    HAL_ADC_IT_CHANNEL_23           = (int)ADC_INTEN_ADCXIEN_23,     /*!< ADC End of channel 23 conversion interrupt source */

    HAL_ADC_IT_CHANNEL_ALL          = (int)0xFFFFFFFF,
#endif

    HAL_ADC_IT_NONE                 = 0,
} HAL_ADC_ITTypeDef;


/**
 * @}
 */


/** @defgroup ADC_State ADC state
 * @{
 */
typedef enum HAL_ADC_State
{
    /* States of ADC global scope */
    HAL_ADC_STATE_RESET             = 0x00000000U,    /*!< ADC not yet initialized or disabled */
    HAL_ADC_STATE_READY             = 0x00000001U,    /*!< ADC peripheral ready for use */
    HAL_ADC_STATE_BUSY_INTERNAL     = 0x00000002U,    /*!< ADC is busy to internal process (initialization, calibration) */
    HAL_ADC_STATE_TIMEOUT           = 0x00000004U,    /*!< TimeOut occurrence */

    /* States of ADC errors */
    HAL_ADC_STATE_ERROR_INTERNAL    = 0x00000010U,    /*!< Internal error occurrence */
    HAL_ADC_STATE_ERROR_CONFIG      = 0x00000020U,    /*!< Configuration error occurrence */

    /* States of ADC conversion */
    HAL_ADC_STATE_BUSY              = 0x00000100U,    /*!< A conversion is ongoing (either by continuous mode, external trigger) */
    HAL_ADC_STATE_EOC               = 0x00000200U,    /*!< Conversion data available (End Of Conversion) */

    /* States of ADC value out of range */
    HAL_ADC_STATE_OUTRANGE          = 0x00010000U,    /*!< Out-of-range occurrence defined by user */

} HAL_ADC_StateTypeDef;
/**
 * @}
 */

/** @defgroup ADC_CompareMode ADC conversion value compared with threshold value ADC_HT/ADC_LT
 * @{
 */

typedef enum HAL_ADC_CompareMode
{
    HAL_ADC_COMP_THRESHOLD_NONE     = 0x00000000,           /*!< Disable Comparison with threshold  */
    HAL_ADC_COMP_THRESHOLD_HIGH     = ADC_CR1_HTCMP,        /*!< Compare with high threshold        */
    HAL_ADC_COMP_THRESHOLD_LOW      = ADC_CR1_LTCMP,        /*!< Compare with low threshold         */
    HAL_ADC_COMP_THRESHOLD_RANGE    = ADC_CR1_REGCMP,       /*!< Compare with range threshold       */
} HAL_ADC_CompareModeTypeDef;


/**
 * @}
 */


typedef enum HAL_ADC_SampleShift
{
    HAL_ADC_SAMPLE_SHIFT_0NS_PE     = (ADC_CR0_ADCK_SF_NO_SHIFT         << ADC_CR0_ADCK_SF_Pos),     /*!< No shift with SYSCLK positive edge    */
    HAL_ADC_SAMPLE_SHIFT_4NS_PE     = (ADC_CR0_ADCK_SF_4NS_SHIFT        << ADC_CR0_ADCK_SF_Pos),     /*!< Shift 4 ns with SYSCLK positive edge  */
    HAL_ADC_SAMPLE_SHIFT_8NS_PE     = (ADC_CR0_ADCK_SF_8NS_SHIFT        << ADC_CR0_ADCK_SF_Pos),     /*!< Shift 8 ns with SYSCLK positive edge  */
    HAL_ADC_SAMPLE_SHIFT_12NS_PE    = (ADC_CR0_ADCK_SF_12NS_SHIFT       << ADC_CR0_ADCK_SF_Pos),     /*!< Shift 12 ns with SYSCLK positive edge */
    HAL_ADC_SAMPLE_SHIFT_0NS_NE     = (ADC_CR0_ADCK_SF_NO_SHIFT_NEDGE   << ADC_CR0_ADCK_SF_Pos),     /*!< No shift with SYSCLK negative edge    */
    HAL_ADC_SAMPLE_SHIFT_4NS_NE     = (ADC_CR0_ADCK_SF_4NS_SHIFT_NEDGE  << ADC_CR0_ADCK_SF_Pos),     /*!< Shift 4 ns with SYSCLK negative edge  */
    HAL_ADC_SAMPLE_SHIFT_8NS_NE     = (ADC_CR0_ADCK_SF_8NS_SHIFT_NEDGE  << ADC_CR0_ADCK_SF_Pos),     /*!< Shift 8 ns with SYSCLK negative edge  */
    HAL_ADC_SAMPLE_SHIFT_16NS_NE    = (ADC_CR0_ADCK_SF_12NS_SHIFT_NEDGE << ADC_CR0_ADCK_SF_Pos),     /*!< Shift 12 ns with SYSCLK negative edge */
} HAL_ADC_SampleShiftTypeDef;

/** @defgroup ADC_Error_Code ADC Error Code
 * @{
 */
#define HAL_ADC_ERROR_NONE                  0x00U    /*!< No error              */
#define HAL_ADC_ERROR_INTERNAL              0x01U    /*!< ADC IP internal error */
#define HAL_ADC_ERROR_TIMEOUT               0x20U    /*!< Timeout Error         */
#define HAL_ADC_ERROR_UNKNOWN               0x30U    /*!< Unknown Error         */

/**
 * @}
 */

//=============================================================================
//                  Macro Definition
//=============================================================================
/**
 *  \brief  Enable and start the ADC peripheral
 *          ps. ADC module stop by hardware after conversion.
 *
 *  \param [in] __HANDLE__      ADC handle
 *  \return
 *      None
 */
#define __HAL_ADC_FORCE_ENABLE(__HANDLE__)                               \
            do {                                                         \
                SET_BIT((__HANDLE__)->Instance->CR0, ADC_CR0_ADCEN);     \
                SET_BIT((__HANDLE__)->Instance->CR0, ADC_CR0_START);     \
            } while(0)


/**
 *  \brief  Disable the ADC peripheral
 *
 *  \param [in] __HANDLE__      ADC handle
 *  \return
 *      None
 */
#define __HAL_ADC_DISABLE(__HANDLE__)   \
            CLEAR_BIT((__HANDLE__)->Instance->CR0, ADC_CR0_ADCEN | ADC_CR0_START)

/**
 *  \brief  Reset ADC handle state
 *
 *  \param [in] __HANDLE__      ADC handle
 *  \return
 *      None
 */
#define __HAL_ADC_RESET_STATE(__HANDLE__)   \
            ((__HANDLE__)->State = HAL_ADC_STATE_RESET)

/**
 *  \brief  Get ADC handle state
 *
 *  \param [in] __HANDLE__      ADC handle
 *  \return
 *      ADC handle state @ref ADC_State
 */
#define __HAL_ADC_GET_STATE(__HANDLE__)     ((__HANDLE__)->State)


/**
 *  \brief  Enable the ADC end of conversion interrupt.
 *
 *  \param [in] __HANDLE__          ADC handle
 *  \param [in] __INTERRUPT__       Interrupt type of ADC @ref HAL_ADC_ITTypeDef
 *  \return
 *      None
 */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__)      \
            SET_BIT((__HANDLE__)->Instance->INTEN, (__INTERRUPT__))


/**
 *  \brief  Disable the ADC end of conversion interrupt.
 *
 *  \param [in] __HANDLE__          ADC handle
 *  \param [in] __INTERRUPT__       Interrupt type of ADC @ref HAL_ADC_ITTypeDef
 *  \return
 *      None
 */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__)     \
            CLEAR_BIT((__HANDLE__)->Instance->INTEN, (__INTERRUPT__))


/**
 *  \brief  Clear the ADC's pending IT flags
 *
 *  \param [in] __HANDLE__          ADC handle
 *  \param [in] __INTERRUPT__       Interrupt type of ADC @ref HAL_ADC_ITTypeDef
 *  \return
 *      None
 */
#define __HAL_ADC_CLR_IT_FLAG(__HANDLE__, __INTERRUPT__)    \
            SET_BIT((__HANDLE__)->Instance->INTCLR, (__INTERRUPT__))


/**
 *  \brief  Get the ADC divider value
 *
 *  \param [in] __HANDLE__          ADC handle
 *  \return
 *      ADC divider value
 */
#define __HAL_ADC_GET_DIV(__HANDLE__)       (0x1ul << ((__HANDLE__)->Init.ClkSel >> ADC_CR0_CLKSEL_Pos))

/**
 *  \brief  Check ADC is bysy or not
 *
 *  \param [in] __HANDLE__          ADC handle
 *  \return
 *      RESET: idle
 *      SET  : busy
 */
#define __HAL_ADC_IS_BUSY(__HANDLE__)       ((__HANDLE__)->Instance->CR0 & ADC_CR0_START_Msk)

/**
 *  \brief  Check ADC conversion value is over then high threshold
 *
 *  \param [in] __HANDLE__          ADC handle
 *  \return
 *      0: no, others: yes
 */
#define __HAL_ADC_IS_OVER_HIGH(__HANDLE__)  ((__HANDLE__)->Instance->RAWINTSR & ADC_RAWINTSR_HHT_INTF_Msk)

/**
 *  \brief  Check ADC conversion value is less than low threshold
 *
 *  \param [in] __HANDLE__          ADC handle
 *  \return
 *      0: no, others: yes
 */
#define __HAL_ADC_IS_LESS_LOW(__HANDLE__)   ((__HANDLE__)->Instance->RAWINTSR & ADC_RAWINTSR_LLT_INTF_Msk)

/**
 *  \brief  Check ADC conversion value is between high/low threshold
 *
 *  \param [in] __HANDLE__          ADC handle
 *  \return
 *      0: no, others: yes
 */
#define __HAL_ADC_IS_IN_RANGE(__HANDLE__)   ((__HANDLE__)->Instance->RAWINTSR & ADC_RAWINTSR_REG_INTF_Msk)

//=============================================================================
//                  Structure Definition
//=============================================================================
typedef struct ADC_Init
{
    HAL_ADC_SampleDutyTypeDef   SamplingTime;       /*!< Specifies ADC sample time.
                                                        This parameter can be a value of @ref HAL_ADC_SampleDuty */

    HAL_ADC_ChannelSelTypeDef   AChannelSel;        /*!< Specifies ADC a channel select in single conversion mode.
                                                        This parameter can be a value of @ref HAL_ADC_ChannelSelTypeDef */

    HAL_ADC_ClkSelTypeDef       ClkSel;             /*!< Specifies ADC clock select.
                                                        This parameter can be a value of @ref HAL_ADC_ClkSel */

    HAL_ADC_ConvModeTypeDef     ConvMode;           /*!< Specifies ADC single/continue conversion mode select.
                                                        This parameter can be a value of @ref ADC_SingleContinueMode */

    HAL_ADC_AutoAccTypeDef      AutoAccumulation;   /*!< Specifies ADC conversion result auto accumulation.
                                                        This parameter can be a value of @ref HAL_ADC_AutoAccumulation */

    HAL_ADC_CircleModeTypeDef   CircleMode;         /*!< Specifies whether the conversion is performed in circle mode or normal mode for multichannel
                                                        This parameter can be a value of @ref HAL_ADC_CircleMode */

    HAL_ADC_VrefTypeDef         Vref;               /*!< Specifies ADC reference voltage.
                                                        This parameter can be a value of @ref HAL_ADC_Vref */

    uint32_t                    NbrOfConversion;    /*!< Specifies the times of conversions in continue mode.
                                                        This parameter can be a value between 0x00 to 0xff */

    uint32_t                    ContinueChannelSel; /*!< Specifies channels to be converted in multchannel conversion mode.
                                                        Multi-channels selection MUST be the same group.
                                                        - Group 0: AIN0 ~ AIN7
                                                        - Group 1: AIN8 ~ AIN15 (L030 or L032)
                                                        - Group 2: AIN16 ~ AIN23 (L030 or L032)
                                                        This parameter can be a value of @ref HAL_ADC_ChannelSel */

    HAL_ADC_ExtTrigger_SrcTypeDef   ExtTrigConv0;   /*!< Selects the external interrupt 0 used to trigger the conversion.
                                                        If set to ADC_SOFTWARE_START, external triggers are disabled.
                                                        If set to external trigger source, triggering is on interrupt flag rising edge.
                                                        This parameter can be a value of @ref ADC_External_Trigger_Source */

    HAL_ADC_ExtTrigger_SrcTypeDef   ExtTrigConv1;   /*!< Selects the external interrupt 1 used to trigger the conversion.
                                                        If set to ADC_SOFTWARE_START, external triggers are disabled.
                                                        If set to external trigger source, triggering is on interrupt flag rising edge.
                                                        This parameter can be a value of @ref ADC_External_Trigger_Source */

    HAL_ADC_SampleShiftTypeDef  ClkShift;           /*!< Specifies ADC shift clock (with SYSCLK) to sample.
                                                        This parameter can be a value of @ref HAL_ADC_SampleShiftTypeDef*/

} ADC_InitTypeDef;


typedef struct HAL_ADC_ChannelConf
{
    HAL_ADC_ChannelSelTypeDef   AChannelSel;    /*!< Specifies ADC channel select in single conversion mode.
                                                    This parameter can be a value of @ref HAL_ADC_ChannelSelTypeDef */

    HAL_ADC_SampleDutyTypeDef   SamplingTime;   /*!< Specifies ADC sample time.
                                                    This parameter can be a value of @ref HAL_ADC_SampleDuty */

    HAL_ADC_ClkSelTypeDef       ClkSel;         /*!< Specifies ADC clock select.
                                                    This parameter can be a value of @ref HAL_ADC_ClkSel */

    HAL_ADC_VrefTypeDef         Vref;           /*!< Specifies ADC reference voltage.
                                                    This parameter can be a value of @ref HAL_ADC_Vref */

} HAL_ADC_ChannelConfTypeDef;

/**
 * @brief  ADC Configuration threshold definition
 * @note   The setting of these parameters with function is conditioned to ADC state.
 */
typedef struct HAL_ADC_ThresholdConf
{
    HAL_ADC_CompareModeTypeDef  CompareMode;    /*!< Specifies ADC threshold compare mode.
                                                    This parameter can be a value of @ref HAL_ADC_CompareModeTypeDef */

    uint32_t    HasUseIT;                       /*!< Specifies whether out of threshold is configured in interrupt or polling mode.
                                                    This parameter can be set to ENABLE or DISABLE */

    uint16_t    HighThreshold;                  /*!< Specifies ADC high level threshold.
                                                    This parameter can be a value between 0x0000 to 0x0fff */

    uint16_t    LowThreshold;                   /*!< Specifies ADC low level threshold.
                                                    This parameter can be a value between 0x0000 to 0x0fff */
} HAL_ADC_ThresholdConfTypeDef;


/**
 * @brief  ADC handle Structure definition
 */
typedef struct
{
    ADC_TypeDef         *Instance;          /*!< Register base address */

    ADC_InitTypeDef     Init;               /*!< ADC required parameters */

    HAL_LockTypeDef     Lock;               /*!< ADC locking object */

    __IO uint32_t       State;              /*!< ADC communication state (bitmap of ADC states) */

} ADC_HandleTypeDef;
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
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hADC);
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef *hADC);

void HAL_ADC_MspInit(ADC_HandleTypeDef *hADC);
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hADC);

HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hADC);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *hADC);

HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef *hADC);
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef *hADC);

void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hADC);

/* Configurate */
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hADC, HAL_ADC_ChannelConfTypeDef *pChConfig);
HAL_StatusTypeDef HAL_ADC_ConfigThreshold(ADC_HandleTypeDef *hADC, HAL_ADC_ThresholdConfTypeDef *pThConfig);

/* Get Value */
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hADC, HAL_ADC_ChannelSelTypeDef channel);
uint32_t HAL_ADC_GetAccValue(ADC_HandleTypeDef *hADC);

/* CallBack */
void HAL_ADC_ContConvCpltCallback(ADC_HandleTypeDef *hADC);
void HAL_ADC_LevelOutOfRangeCallback(ADC_HandleTypeDef *hADC, HAL_ADC_ITTypeDef IT_Type);
void HAL_ADC_ChannelxCallback(ADC_HandleTypeDef *hADC, HAL_ADC_ChannelSelTypeDef channel);

/**
 * @}
 */

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif
