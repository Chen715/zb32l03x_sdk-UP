/**
 ******************************************************************************
 * @file    zb32l03x_hal_tim.h
 * @author  MCU Software Team
 * @Version V1.2.0
 * @Date    2022/01/19
 * @brief   Header file of TIM HAL module.
 ******************************************************************************
 **/


#ifndef __ZB32L03x_HAL_TIM_H
#define __ZB32L03x_HAL_TIM_H

#ifdef __cplusplus
extern "C" {
#endif


#include "zb32l03x_hal_def.h"


/** @addtogroup TIM
 * @{
 */


/** @defgroup TIM_Exported_Types TIM Exported Types
 * @{
 */

/**
 * @brief  TIM Time base Configuration Structure definition
 */
typedef struct
{
    uint32_t Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                   This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

    uint32_t CounterMode;       /*!< Specifies the counter mode.
                                   This parameter can be a value of @ref TIM_Counter_Mode */

    uint32_t Period;            /*!< Specifies the period value to be loaded into the active
                                   Auto-Reload Register at the next update event.
                                   This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.  */

    uint32_t ClockDivision;     /*!< Specifies the clock division.
                                   This parameter can be a value of @ref TIM_ClockDivision */

    uint32_t RepetitionCounter; /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                    reaches zero, an update event is generated and counting restarts
                                    from the RCR value (N).
                                    This means in PWM mode that (N+1) corresponds to:
                                        - the number of PWM periods in edge-aligned mode
                                        - the number of half PWM period in center-aligned mode
                                     This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
                                     @note This parameter is valid only for TIM1 and TIM2. */

    uint32_t AutoReloadPreload; /*!< Specifies the auto-reload preload.
                                    This parameter can be a value of @ref TIM_AutoReloadPreload */
} TIM_Base_InitTypeDef;


/**
 * @brief  TIM Output Compare Configuration Structure definition
 */
typedef struct
{
    uint32_t OCMode;        /*!< Specifies the TIM mode.
                               This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

    uint32_t Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                               This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

    uint32_t OCPolarity;    /*!< Specifies the output polarity.
                               This parameter can be a value of @ref TIM_Output_Compare_Polarity */

    uint32_t OCNPolarity;   /*!< Specifies the complementary output polarity.
                               This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                               @note This parameter is valid only for TIM1 and TIM2. */

    uint32_t OCFastMode;    /*!< Specifies the Fast mode state.
                               This parameter can be a value of @ref TIM_Output_Fast_State
                               @note This parameter is valid only in PWM1 and PWM2 mode. */


    uint32_t OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                               This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                               @note This parameter is valid only for TIM1 and TIM2. */

    uint32_t OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                               This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                               @note This parameter is valid only for TIM1 and TIM2. */
} TIM_OC_InitTypeDef;

/**
 * @brief  TIM One Pulse Mode Configuration Structure definition
 */
typedef struct
{
    uint32_t OCMode;        /*!< Specifies the TIM mode.
                               This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

    uint32_t Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                               This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

    uint32_t OCPolarity;    /*!< Specifies the output polarity.
                               This parameter can be a value of @ref TIM_Output_Compare_Polarity */

    uint32_t OCNPolarity;   /*!< Specifies the complementary output polarity.
                               This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                               @note This parameter is valid only for TIM1 and TIM2. */

    uint32_t OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                               This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                               @note This parameter is valid only for TIM1 and TIM2. */

    uint32_t OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                               This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                               @note This parameter is valid only for TIM1 and TIM2. */

    uint32_t ICPolarity;    /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Input_Capture_Polarity */

    uint32_t ICSelection;   /*!< Specifies the input.
                              This parameter can be a value of @ref TIM_Input_Capture_Selection */

    uint32_t ICFilter;      /*!< Specifies the input capture filter.
                              This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_OnePulse_InitTypeDef;


/**
 * @brief  TIM Input Capture Configuration Structure definition
 */
typedef struct
{
    uint32_t  ICPolarity;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Input_Capture_Polarity */

    uint32_t ICSelection;   /*!< Specifies the input.
                              This parameter can be a value of @ref TIM_Input_Capture_Selection */

    uint32_t ICPrescaler;   /*!< Specifies the Input Capture Prescaler.
                              This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

    uint32_t ICFilter;      /*!< Specifies the input capture filter.
                              This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_IC_InitTypeDef;

/**
 * @brief  TIM Encoder Configuration Structure definition
 */
typedef struct
{
    uint32_t EncoderMode;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Encoder_Mode */

    uint32_t IC1Polarity;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Input_Capture_Polarity */

    uint32_t IC1Selection;  /*!< Specifies the input.
                               This parameter can be a value of @ref TIM_Input_Capture_Selection */

    uint32_t IC1Prescaler;  /*!< Specifies the Input Capture Prescaler.
                               This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

    uint32_t IC1Filter;     /*!< Specifies the input capture filter.
                               This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */

    uint32_t IC2Polarity;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Input_Capture_Polarity */

    uint32_t IC2Selection;  /*!< Specifies the input.
                              This parameter can be a value of @ref TIM_Input_Capture_Selection */

    uint32_t IC2Prescaler;  /*!< Specifies the Input Capture Prescaler.
                               This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

    uint32_t IC2Filter;     /*!< Specifies the input capture filter.
                               This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_Encoder_InitTypeDef;


/**
  * @brief  TIM Clock Configuration Handle Structure definition
  */
typedef struct
{
    uint32_t ClockSource;       /*!< TIM clock sources
                                    This parameter can be a value of @ref TIM_Clock_Source */
    uint32_t ClockPolarity;     /*!< TIM clock polarity
                                    This parameter can be a value of @ref TIM_Clock_Polarity */
    uint32_t ClockPrescaler;    /*!< TIM clock prescaler
                                    This parameter can be a value of @ref TIM_Clock_Prescaler */
    uint32_t ClockFilter;       /*!< TIM clock filter
                                    This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_ClockConfigTypeDef;

/**
 * @brief  TIM Clear Input Configuration Handle Structure definition
 */
typedef struct
{
    uint32_t ClearInputState;       /*!< TIM clear Input state
                                        This parameter can be ENABLE or DISABLE */
    uint32_t ClearInputSource;      /*!< TIM clear Input sources
                                        This parameter can be a value of @ref TIM_ClearInput_Source */
    uint32_t ClearInputPolarity;    /*!< TIM Clear Input polarity
                                        This parameter can be a value of @ref TIM_ClearInput_Polarity */
    uint32_t ClearInputPrescaler;   /*!< TIM Clear Input prescaler
                                        This parameter can be a value of @ref TIM_ClearInput_Prescaler */
    uint32_t ClearInputFilter;      /*!< TIM Clear Input filter
                                        This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_ClearInputConfigTypeDef;

/**
 * @brief  TIM Master configuration Structure definition
 */
typedef struct
{
    uint32_t    MasterOutputTrigger;    /*!< Trigger output (TRGO) selection
                                            This parameter can be a value of @ref TIM_Master_Mode_Selection */
    uint32_t    MasterSlaveMode;        /*!< Master/slave mode selection
                                            This parameter can be a value of @ref TIM_Master_Slave_Mode */
} TIM_MasterConfigTypeDef;


/**
 * @brief  TIM Slave configuration Structure definition
 */
typedef struct
{
    uint32_t  SlaveMode;            /*!< Slave mode selection
                                        This parameter can be a value of @ref TIM_Slave_Mode */
    uint32_t  InputTrigger;         /*!< Input Trigger source
                                        This parameter can be a value of @ref TIM_Trigger_Selection */
    uint32_t  TriggerPolarity;      /*!< Input Trigger polarity
                                        This parameter can be a value of @ref TIM_Trigger_Polarity */
    uint32_t  TriggerPrescaler;     /*!< Input trigger prescaler
                                        This parameter can be a value of @ref TIM_Trigger_Prescaler */
    uint32_t  TriggerFilter;        /*!< Input trigger filter
                                        This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */

} TIM_SlaveConfigTypeDef;


/**
 * @brief  TIM Break and Dead time configuration Structure definition
 */
typedef struct
{
    uint32_t OffStateRunMode;       /*!< TIM off state in run mode
                                        This parameter can be a value of @ref TIM_OSSR_Off_State_Selection_for_Run_mode_state */
    uint32_t OffStateIDLEMode;      /*!< TIM off state in IDLE mode
                                        This parameter can be a value of @ref TIM_OSSI_Off_State_Selection_for_Idle_mode_state */
    uint32_t LockLevel;             /*!< TIM Lock level
                                        This parameter can be a value of @ref TIM_Lock_level */
    uint32_t DeadTime;              /*!< TIM dead Time
                                        This parameter can be a number between Min_Data = 0x00 and Max_Data = 0xFF */
    uint32_t BreakState;            /*!< TIM Break State
                                        This parameter can be a value of @ref TIM_Break_Input_enable_disable */
    uint32_t BreakPolarity;         /*!< TIM Break input polarity
                                        This parameter can be a value of @ref TIM_Break_Polarity */
    uint32_t AutomaticOutput;       /*!< TIM Automatic Output Enable state
                                        This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */
} TIM_BreakDeadTimeConfigTypeDef;



/**
 * @brief  HAL State structures definition
 */
typedef enum
{
    HAL_TIM_STATE_RESET             = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
    HAL_TIM_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
    HAL_TIM_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
    HAL_TIM_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
    HAL_TIM_STATE_ERROR             = 0x04U     /*!< Reception process is ongoing                */
} HAL_TIM_StateTypeDef;

/**
 * @brief  HAL Active channel structures definition
 */
typedef enum
{
    HAL_TIM_ACTIVE_CHANNEL_1        = 0x01U,    /*!< The active channel is 1     */
    HAL_TIM_ACTIVE_CHANNEL_2        = 0x02U,    /*!< The active channel is 2     */
    HAL_TIM_ACTIVE_CHANNEL_3        = 0x04U,    /*!< The active channel is 3     */
    HAL_TIM_ACTIVE_CHANNEL_4        = 0x08U,    /*!< The active channel is 4     */
    HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00U     /*!< All active channels cleared */
} HAL_TIM_ActiveChannel;

/**
 * @brief  TIM Time Base Handle Structure definition
 */
typedef struct
{
    TIM_TypeDef                 *Instance;     /*!< Register base address             */
    TIM_Base_InitTypeDef        Init;          /*!< TIM Time Base required parameters */
    HAL_TIM_ActiveChannel       Channel;       /*!< Active channel                    */
    HAL_LockTypeDef             Lock;          /*!< Locking object                    */
    __IO HAL_TIM_StateTypeDef   State;         /*!< TIM operation state               */
} TIM_HandleTypeDef;

/**
 * @}
 */


/** @defgroup TIM_Exported_Constants TIM Exported Constants
 * @{
 */



/** @defgroup TIM_ETR_Polarity TIM ETR Polarity
 * @{
 */
#define TIM_ETRPOLARITY_INVERTED                (TIM_SMCR_ETP)                    /*!< Polarity for ETR source */
#define TIM_ETRPOLARITY_NONINVERTED             0x00000000U                       /*!< Polarity for ETR source */
/**
 * @}
 */


/** @defgroup TIM_Counter_Mode TIM Counter Mode
 * @{
 */
#define TIM_COUNTERMODE_UP                      0x00000000U
#define TIM_COUNTERMODE_DOWN                    TIM_CR1_DIR
#define TIM_COUNTERMODE_CENTERALIGNED1          (0x1ul << TIM_CR1_CMS_Pos)
#define TIM_COUNTERMODE_CENTERALIGNED2          (0x2ul << TIM_CR1_CMS_Pos)
#define TIM_COUNTERMODE_CENTERALIGNED3          (0x3ul << TIM_CR1_CMS_Pos)

/**
 * @}
 */

/** @defgroup TIM_ClockDivision TIM ClockDivision
 * @{
 */
#define TIM_CLOCKDIVISION_DIV1                  (0x0ul << TIM_CR1_CKD_Pos)
#define TIM_CLOCKDIVISION_DIV2                  (0x1ul << TIM_CR1_CKD_Pos)
#define TIM_CLOCKDIVISION_DIV4                  (0x2ul << TIM_CR1_CKD_Pos)


/**
 * @}
 */

/** @defgroup TIM_AutoReloadPreload TIM Auto-Reload Preload
 * @{
 */
#define TIM_AUTORELOAD_PRELOAD_DISABLE          0x0000U              /*!< TIMx_ARR register is not buffered */
#define TIM_AUTORELOAD_PRELOAD_ENABLE           (TIM_CR1_ARPE)       /*!< TIMx_ARR register is buffered */
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_and_PWM_modes TIM Output Compare and PWM modes
 * @{
 */
#define TIM_OCMODE_TIMING                       (TIM_CCMR1_OUT_OC1M_FROZEN         << TIM_CCMR1_OUT_OC1M_Pos)
#define TIM_OCMODE_ACTIVE                       (TIM_CCMR1_OUT_OC1M_CH1_ACTIVE     << TIM_CCMR1_OUT_OC1M_Pos)
#define TIM_OCMODE_INACTIVE                     (TIM_CCMR1_OUT_OC1M_CH1_INACTIVE   << TIM_CCMR1_OUT_OC1M_Pos)
#define TIM_OCMODE_TOGGLE                       (TIM_CCMR1_OUT_OC1M_TOGGLE         << TIM_CCMR1_OUT_OC1M_Pos)
#define TIM_OCMODE_FORCED_INACTIVE              (TIM_CCMR1_OUT_OC1M_FORCE_INACTIVE << TIM_CCMR1_OUT_OC1M_Pos)
#define TIM_OCMODE_FORCED_ACTIVE                (TIM_CCMR1_OUT_OC1M_FORCE_ACTIVE   << TIM_CCMR1_OUT_OC1M_Pos)
#define TIM_OCMODE_PWM1                         (TIM_CCMR1_OUT_OC1M_PWM_MODE1      << TIM_CCMR1_OUT_OC1M_Pos)
#define TIM_OCMODE_PWM2                         (TIM_CCMR1_OUT_OC1M_PWM_MODE2      << TIM_CCMR1_OUT_OC1M_Pos)

/**
 * @}
 */

/** @defgroup TIM_Output_Compare_State TIM Output Compare State
 * @{
 */
#define TIM_OUTPUTSTATE_DISABLE                 0x00000000U
#define TIM_OUTPUTSTATE_ENABLE                  (TIM_CCER_CC1E)
/**
 * @}
 */

/** @defgroup TIM_Output_Fast_State TIM Output Fast State
 * @{
 */
#define TIM_OCFAST_DISABLE                      0x00000000U
#define TIM_OCFAST_ENABLE                       (TIM_CCMR1_OUT_OC1FE)
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_N_State TIM Complementary Output Compare State
 * @{
 */
#define TIM_OUTPUTNSTATE_DISABLE                0x00000000U
#define TIM_OUTPUTNSTATE_ENABLE                 (TIM_CCER_CC1NE)
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_Polarity TIM Output Compare Polarity
 * @{
 */
#define TIM_OCPOLARITY_HIGH                     0x00000000U
#define TIM_OCPOLARITY_LOW                      (TIM_CCER_CC1P)
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_N_Polarity TIM Complementary Output Compare Polarity
 * @{
 */
#define TIM_OCNPOLARITY_HIGH                    0x00000000U
#define TIM_OCNPOLARITY_LOW                     (TIM_CCER_CC1NP)
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_Idle_State TIM Output Compare Idle State
 * @{
 */
#define TIM_OCIDLESTATE_SET                     (TIM_CR2_OIS1)
#define TIM_OCIDLESTATE_RESET                   0x00000000U
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_N_Idle_State TIM Complementary Output Compare Idle State
 * @{
 */
#define TIM_OCNIDLESTATE_SET                    (TIM_CR2_OIS1N)
#define TIM_OCNIDLESTATE_RESET                  0x00000000U
/**
 * @}
 */

/** @defgroup TIM_Channel TIM Channel
 * @{
 */
#define TIM_CHANNEL_1                           0x00000000U
#define TIM_CHANNEL_2                           0x00000004U
#define TIM_CHANNEL_3                           0x00000008U
#define TIM_CHANNEL_4                           0x0000000CU
#define TIM_CHANNEL_ALL                         0x00000018U

/**
 * @}
 */

/** @defgroup TIM_Input_Capture_Polarity TIM Input Capture Polarity
 * @{
 */
#define TIM_ICPOLARITY_RISING                   0x00000000U                         /*!< Capture triggered by rising edge on timer input */
#define TIM_ICPOLARITY_FALLING                  (TIM_CCER_CC1P)                     /*!< Capture triggered by falling edge on timer input */
#define TIM_ICPOLARITY_BOTHEDGE                 (TIM_CCER_CC1P | TIM_CCER_CC1NP)    /*!< Capture triggered by both rising and falling edges on timer input */
/**
 * @}
 */



/** @defgroup TIM_Input_Capture_Selection TIM Input Capture Selection
 * @{
 */
#define TIM_ICSELECTION_TI1                     (TIM_CCMR1_IN_CC1S_INPUT_TI1 << TIM_CCMR1_IN_CC1S_Pos)  /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                                                            connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSELECTION_TI2                     (TIM_CCMR1_IN_CC1S_INPUT_TI2 << TIM_CCMR1_IN_CC1S_Pos)  /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                                                            connected to IC2, IC1, IC4 or IC3, respectively */
#define TIM_ICSELECTION_TRC                     (TIM_CCMR1_IN_CC1S_INPUT_TRC << TIM_CCMR1_IN_CC1S_Pos)  /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC */
/**
 * @}
 */

/** @defgroup TIM_Input_Capture_Prescaler TIM Input Capture Prescaler
 * @{
 */
#define TIM_ICPSC_DIV1                          (0x0u)     /*!< Capture performed each time an edge is detected on the capture input */
#define TIM_ICPSC_DIV2                          (0x1u)     /*!< Capture performed once every 2 events */
#define TIM_ICPSC_DIV4                          (0x2u)     /*!< Capture performed once every 4 events */
#define TIM_ICPSC_DIV8                          (0x3u)     /*!< Capture performed once every 8 events */
/**
 * @}
 */

/** @defgroup TIM_One_Pulse_Mode TIM One Pulse Mode
 * @{
 */
#define TIM_OPMODE_SINGLE                       (TIM_CR1_OPM)
#define TIM_OPMODE_REPETITIVE                   0x00000000U
/**
 * @}
 */

/** @defgroup TIM_Encoder_Mode TIM Encoder Mode
 * @{
 */
#define TIM_ENCODERMODE_TI1                     (TIM_SMCR_SMS_ENCODER_MODE_1 << TIM_SMCR_SMS_Pos)
#define TIM_ENCODERMODE_TI2                     (TIM_SMCR_SMS_ENCODER_MODE_2 << TIM_SMCR_SMS_Pos)
#define TIM_ENCODERMODE_TI12                    (TIM_SMCR_SMS_ENCODER_MODE_3 << TIM_SMCR_SMS_Pos)

/**
 * @}
 */

/** @defgroup TIM_Interrupt_definition TIM Interrupt Definition
 * @{
 */
#define TIM_IT_UPDATE                           (TIM_DIER_UIE)
#define TIM_IT_CC1                              (TIM_DIER_CC1IE)
#define TIM_IT_CC2                              (TIM_DIER_CC2IE)
#define TIM_IT_CC3                              (TIM_DIER_CC3IE)
#define TIM_IT_CC4                              (TIM_DIER_CC4IE)
#define TIM_IT_COM                              (TIM_DIER_COMIE)
#define TIM_IT_TRIGGER                          (TIM_DIER_TIE)
#define TIM_IT_BREAK                            (TIM_DIER_BIE)
/**
 * @}
 */

/** @defgroup TIM_Commutation_Source  TIM Commutation Source
 * @{
 */
#define TIM_COMMUTATION_TRGI                    (TIM_CR2_CCUS)
#define TIM_COMMUTATION_SOFTWARE                0x00000000U

/**
 * @}
 */


/** @defgroup TIM_Event_Source TIM Event Source
 * @{
 */
#define TIM_EVENTSOURCE_UPDATE                  TIM_EGR_UG
#define TIM_EVENTSOURCE_CC1                     TIM_EGR_CC1G
#define TIM_EVENTSOURCE_CC2                     TIM_EGR_CC2G
#define TIM_EVENTSOURCE_CC3                     TIM_EGR_CC3G
#define TIM_EVENTSOURCE_CC4                     TIM_EGR_CC4G
#define TIM_EVENTSOURCE_COM                     TIM_EGR_COMG
#define TIM_EVENTSOURCE_TRIGGER                 TIM_EGR_TG
#define TIM_EVENTSOURCE_BREAK                   TIM_EGR_BG
/**
 * @}
 */

/** @defgroup TIM_Flag_definition TIM Flag Definition
  * @{
  */
#define TIM_FLAG_UPDATE                         (TIM_SR_UIF)
#define TIM_FLAG_CC1                            (TIM_SR_CC1IF)
#define TIM_FLAG_CC2                            (TIM_SR_CC2IF)
#define TIM_FLAG_CC3                            (TIM_SR_CC3IF)
#define TIM_FLAG_CC4                            (TIM_SR_CC4IF)
#define TIM_FLAG_COM                            (TIM_SR_COMIF)
#define TIM_FLAG_TRIGGER                        (TIM_SR_TIF)
#define TIM_FLAG_BREAK                          (TIM_SR_BIF)
#define TIM_FLAG_CC1OF                          (TIM_SR_CC1OF)
#define TIM_FLAG_CC2OF                          (TIM_SR_CC2OF)
#define TIM_FLAG_CC3OF                          (TIM_SR_CC3OF)
#define TIM_FLAG_CC4OF                          (TIM_SR_CC4OF)
/**
 * @}
 */

/** @defgroup TIM_Clock_Source TIM Clock Source
 * @{
 */
#define TIM_CLOCKSOURCE_ETRMODE2                (TIM_SMCR_ETPS_ETRP_DIV4 << TIM_SMCR_ETPS_Pos)
#define TIM_CLOCKSOURCE_INTERNAL                (TIM_SMCR_ETPS_ETRP_DIV2 << TIM_SMCR_ETPS_Pos)
#define TIM_CLOCKSOURCE_ITR0                    (TIM_SMCR_TS_ITR0        << TIM_SMCR_TS_Pos)
#define TIM_CLOCKSOURCE_ITR1                    (TIM_SMCR_TS_ITR1        << TIM_SMCR_TS_Pos)
#define TIM_CLOCKSOURCE_ITR2                    (TIM_SMCR_TS_ITR2        << TIM_SMCR_TS_Pos)
#define TIM_CLOCKSOURCE_ITR3                    (TIM_SMCR_TS_ITR3        << TIM_SMCR_TS_Pos)
#define TIM_CLOCKSOURCE_TI1ED                   (TIM_SMCR_TS_TI1F_ED     << TIM_SMCR_TS_Pos)
#define TIM_CLOCKSOURCE_TI1                     (TIM_SMCR_TS_TI1FP1      << TIM_SMCR_TS_Pos)
#define TIM_CLOCKSOURCE_TI2                     (TIM_SMCR_TS_TI1FP2      << TIM_SMCR_TS_Pos)
#define TIM_CLOCKSOURCE_ETRMODE1                (TIM_SMCR_TS_ETRF        << TIM_SMCR_TS_Pos)
/**
 * @}
 */

/** @defgroup TIM_Clock_Polarity TIM Clock Polarity
 * @{
 */
#define TIM_CLOCKPOLARITY_INVERTED              TIM_ETRPOLARITY_INVERTED           /*!< Polarity for ETRx clock sources */
#define TIM_CLOCKPOLARITY_NONINVERTED           TIM_ETRPOLARITY_NONINVERTED        /*!< Polarity for ETRx clock sources */
#define TIM_CLOCKPOLARITY_RISING                0x00000000U                        /*!< Polarity for TIx clock sources */
#define TIM_CLOCKPOLARITY_FALLING               (TIM_CCER_CC1P)                    /*!< Polarity for TIx clock sources */
#define TIM_CLOCKPOLARITY_BOTHEDGE              (TIM_CCER_CC1P | TIM_CCER_CC1NP)   /*!< Polarity for TIx clock sources */
/**
 * @}
 */

/** @defgroup TIM_Clock_Prescaler TIM Clock Prescaler
 * @{
 */
#define TIM_CLOCKPRESCALER_DIV1                 (TIM_SMCR_ETPS_ETRP_DIV1 << TIM_SMCR_ETPS_Pos)     /*!< No prescaler is used */
#define TIM_CLOCKPRESCALER_DIV2                 (TIM_SMCR_ETPS_ETRP_DIV2 << TIM_SMCR_ETPS_Pos)     /*!< Prescaler for External ETR Clock: Capture performed once every 2 events. */
#define TIM_CLOCKPRESCALER_DIV4                 (TIM_SMCR_ETPS_ETRP_DIV4 << TIM_SMCR_ETPS_Pos)     /*!< Prescaler for External ETR Clock: Capture performed once every 4 events. */
#define TIM_CLOCKPRESCALER_DIV8                 (TIM_SMCR_ETPS_ETRP_DIV8 << TIM_SMCR_ETPS_Pos)     /*!< Prescaler for External ETR Clock: Capture performed once every 8 events. */
/**
 * @}
 */

/** @defgroup TIM_ClearInput_Source TIM ClearInput Source
 * @{
 */
#define TIM_CLEARINPUTSOURCE_ETR                0x00000001U
#define TIM_CLEARINPUTSOURCE_NONE               0x00000000U
/**
 * @}
 */

/** @defgroup TIM_ClearInput_Polarity TIM Clear Input Polarity
 * @{
 */
#define TIM_CLEARINPUTPOLARITY_INVERTED         TIM_ETRPOLARITY_INVERTED        /*!< Polarity for ETRx pin */
#define TIM_CLEARINPUTPOLARITY_NONINVERTED      TIM_ETRPOLARITY_NONINVERTED     /*!< Polarity for ETRx pin */
/**
 * @}
 */

/** @defgroup TIM_ClearInput_Prescaler TIM Clear Input Prescaler
 * @{
 */
#define TIM_CLEARINPUTPRESCALER_DIV1            (TIM_SMCR_ETPS_ETRP_DIV1 << TIM_SMCR_ETPS_Pos)   /*!< No prescaler is used */
#define TIM_CLEARINPUTPRESCALER_DIV2            (TIM_SMCR_ETPS_ETRP_DIV2 << TIM_SMCR_ETPS_Pos)   /*!< Prescaler for External ETR pin: Capture performed once every 2 events. */
#define TIM_CLEARINPUTPRESCALER_DIV4            (TIM_SMCR_ETPS_ETRP_DIV4 << TIM_SMCR_ETPS_Pos)   /*!< Prescaler for External ETR pin: Capture performed once every 4 events. */
#define TIM_CLEARINPUTPRESCALER_DIV8            (TIM_SMCR_ETPS_ETRP_DIV8 << TIM_SMCR_ETPS_Pos)   /*!< Prescaler for External ETR pin: Capture performed once every 8 events. */
/**
 * @}
 */

/** @defgroup TIM_OSSR_Off_State_Selection_for_Run_mode_state TIM OSSR Off State Selection for Run mode state
 * @{
 */
#define TIM_OSSR_ENABLE                         (TIM_BDTR_OSSR)
#define TIM_OSSR_DISABLE                        0x00000000U
/**
 * @}
 */

/** @defgroup TIM_OSSI_Off_State_Selection_for_Idle_mode_state TIM OSSI Off State Selection for Idle mode state
 * @{
 */
#define TIM_OSSI_ENABLE                         (TIM_BDTR_OSSI)
#define TIM_OSSI_DISABLE                        0x00000000U
/**
 * @}
 */

/** @defgroup TIM_Lock_level TIM Lock level
 * @{
 */
#define TIM_LOCKLEVEL_OFF                       (TIM_BDTR_LOCK_OFF << TIM_BDTR_LOCK_Pos)
#define TIM_LOCKLEVEL_1                         (TIM_BDTR_LOCK_LV1 << TIM_BDTR_LOCK_Pos)
#define TIM_LOCKLEVEL_2                         (TIM_BDTR_LOCK_LV2 << TIM_BDTR_LOCK_Pos)
#define TIM_LOCKLEVEL_3                         (TIM_BDTR_LOCK_LV3 << TIM_BDTR_LOCK_Pos)

/**
 * @}
 */

/** @defgroup TIM_Break_Input_enable_disable TIM Break Input Enable Disable
 * @{
 */
#define TIM_BREAK_ENABLE                        (TIM_BDTR_BKE)
#define TIM_BREAK_DISABLE                       0x00000000U
/**
 * @}
  */

/** @defgroup TIM_Break_Polarity TIM Break Input Polarity
 * @{
 */
#define TIM_BREAKPOLARITY_LOW                   0x00000000U
#define TIM_BREAKPOLARITY_HIGH                  (TIM_BDTR_BKP)
/**
 * @}
  */
/** @defgroup TIM_AOE_Bit_Set_Reset TIM Automatic Output Enable
 * @{
 */
#define TIM_AUTOMATICOUTPUT_ENABLE              (TIM_BDTR_AOE)
#define TIM_AUTOMATICOUTPUT_DISABLE             0x00000000U
/**
 * @}
 */

/** @defgroup TIM_Master_Mode_Selection TIM Master Mode Selection
 * @{
 */
#define TIM_TRGO_RESET                          (TIM_CR2_MMS_RESET     << TIM_CR2_MMS_Pos)
#define TIM_TRGO_ENABLE                         (TIM_CR2_MMS_ENABLE    << TIM_CR2_MMS_Pos)
#define TIM_TRGO_UPDATE                         (TIM_CR2_MMS_UPDATE    << TIM_CR2_MMS_Pos)
#define TIM_TRGO_OC1                            (TIM_CR2_MMS_CMP_PLUSE << TIM_CR2_MMS_Pos)
#define TIM_TRGO_OC1REF                         (TIM_CR2_MMS_OC1REF    << TIM_CR2_MMS_Pos)
#define TIM_TRGO_OC2REF                         (TIM_CR2_MMS_OC2REF    << TIM_CR2_MMS_Pos)
#define TIM_TRGO_OC3REF                         (TIM_CR2_MMS_OC3REF    << TIM_CR2_MMS_Pos)
#define TIM_TRGO_OC4REF                         (TIM_CR2_MMS_OC4REF    << TIM_CR2_MMS_Pos)

/**
 * @}
 */

/** @defgroup TIM_Slave_Mode TIM Slave Mode
 * @{
 */
#define TIM_SLAVEMODE_DISABLE                   (TIM_SMCR_SMS_SLAVE_OFF       << TIM_SMCR_SMS_Pos)     /*!< SLAVE_OFF : Slave mode disabled           */
#define TIM_SLAVEMODE_ENCODER_1                 (TIM_SMCR_SMS_ENCODER_MODE_1  << TIM_SMCR_SMS_Pos)     /*!< ENCODER_MODE_1 : Encoder mode 1           */
#define TIM_SLAVEMODE_ENCODER_2                 (TIM_SMCR_SMS_ENCODER_MODE_2  << TIM_SMCR_SMS_Pos)     /*!< ENCODER_MODE_2 : Encoder mode 2           */
#define TIM_SLAVEMODE_ENCODER_3                 (TIM_SMCR_SMS_ENCODER_MODE_3  << TIM_SMCR_SMS_Pos)     /*!< ENCODER_MODE_3 : Encoder mode 3           */
#define TIM_SLAVEMODE_RESET                     (TIM_SMCR_SMS_RESET_MODE      << TIM_SMCR_SMS_Pos)     /*!< RESET_MODE : Reset mode                   */
#define TIM_SLAVEMODE_GATED                     (TIM_SMCR_SMS_GATED_MODE      << TIM_SMCR_SMS_Pos)     /*!< GATED_MODE : Gated mode                   */
#define TIM_SLAVEMODE_TRIGGER                   (TIM_SMCR_SMS_TRIGGER_MODE    << TIM_SMCR_SMS_Pos)     /*!< TRIGGER_MODE : Trigger mode               */
#define TIM_SLAVEMODE_EXTERNAL1                 (TIM_SMCR_SMS_EXT_CLK_MODE_1  << TIM_SMCR_SMS_Pos)     /*!< EXT_CLK_MODE_1 : External Clock mode 1    */

/**
 * @}
 */

/** @defgroup TIM_Master_Slave_Mode TIM Master Slave Mode
 * @{
 */
#define TIM_MASTERSLAVEMODE_ENABLE              0x00000080U
#define TIM_MASTERSLAVEMODE_DISABLE             0x00000000U
/**
 * @}
 */

/** @defgroup TIM_Trigger_Selection TIM Trigger Selection
 * @{
 */
#define TIM_TS_ITR0                             (TIM_SMCR_TS_ITR0    << TIM_SMCR_TS_Pos)     /*!< ITR0 : Internal Trigger 0           */
#define TIM_TS_ITR1                             (TIM_SMCR_TS_ITR1    << TIM_SMCR_TS_Pos)     /*!< ITR1 : Internal Trigger 1           */
#define TIM_TS_ITR2                             (TIM_SMCR_TS_ITR2    << TIM_SMCR_TS_Pos)     /*!< ITR2 : Internal Trigger 2           */
#define TIM_TS_ITR3                             (TIM_SMCR_TS_ITR3    << TIM_SMCR_TS_Pos)     /*!< ITR3 : Internal Trigger 3           */
#define TIM_TS_TI1F_ED                          (TIM_SMCR_TS_TI1F_ED << TIM_SMCR_TS_Pos)     /*!< TI1F_ED : TI1 Edge Detector         */
#define TIM_TS_TI1FP1                           (TIM_SMCR_TS_TI1FP1  << TIM_SMCR_TS_Pos)     /*!< TI1FP1 : Filtered Timer Input 1     */
#define TIM_TS_TI2FP2                           (TIM_SMCR_TS_TI1FP2  << TIM_SMCR_TS_Pos)     /*!< TI1FP2 : Filtered Timer Input 2     */
#define TIM_TS_ETRF                             (TIM_SMCR_TS_ETRF    << TIM_SMCR_TS_Pos)     /*!< ETRF : External Trigger input       */

/**
 * @}
 */

/** @defgroup TIM_Trigger_Polarity TIM Trigger Polarity
 * @{
 */
#define TIM_TRIGGERPOLARITY_INVERTED            TIM_ETRPOLARITY_INVERTED               /*!< Polarity for ETRx trigger sources */
#define TIM_TRIGGERPOLARITY_NONINVERTED         TIM_ETRPOLARITY_NONINVERTED            /*!< Polarity for ETRx trigger sources */
#define TIM_TRIGGERPOLARITY_RISING              0x00000000U                            /*!< Polarity for TIxFPx or TI1_ED trigger sources */
#define TIM_TRIGGERPOLARITY_FALLING             (TIM_CCER_CC1P)                        /*!< Polarity for TIxFPx or TI1_ED trigger sources */
#define TIM_TRIGGERPOLARITY_BOTHEDGE            (TIM_CCER_CC1P | TIM_CCER_CC1NP)       /*!< Polarity for TIxFPx or TI1_ED trigger sources */
/**
 * @}
 */

/** @defgroup TIM_Trigger_Prescaler TIM Trigger Prescaler
 * @{
 */
#define TIM_TRIGGERPRESCALER_DIV1               (TIM_SMCR_ETPS_ETRP_DIV1 << TIM_SMCR_ETPS_Pos)     /*!< No prescaler is used */
#define TIM_TRIGGERPRESCALER_DIV2               (TIM_SMCR_ETPS_ETRP_DIV2 << TIM_SMCR_ETPS_Pos)     /*!< Prescaler for External ETR Trigger: Capture performed once every 2 events. */
#define TIM_TRIGGERPRESCALER_DIV4               (TIM_SMCR_ETPS_ETRP_DIV4 << TIM_SMCR_ETPS_Pos)     /*!< Prescaler for External ETR Trigger: Capture performed once every 4 events. */
#define TIM_TRIGGERPRESCALER_DIV8               (TIM_SMCR_ETPS_ETRP_DIV8 << TIM_SMCR_ETPS_Pos)     /*!< Prescaler for External ETR Trigger: Capture performed once every 8 events. */
/**
 * @}
 */

/** @defgroup TIM_TI1_Selection TIM TI1 Input Selection
 * @{
 */
#define TIM_TI1SELECTION_CH1                    0x00000000U
#define TIM_TI1SELECTION_XORCOMBINATION         (TIM_CR2_TI1S)
/**
 * @}
 */

/** @defgroup TIM_Channel_CC_State TIM Capture/Compare Channel State
 * @{
 */
#define TIM_CCx_ENABLE                          0x00000001U
#define TIM_CCx_DISABLE                         0x00000000U
#define TIM_CCxN_ENABLE                         0x00000004U
#define TIM_CCxN_DISABLE                        0x00000000U
/**
 * @}
 */


/**
 * @}
 */


/** @defgroup TIM_Private_Constants TIM Private Constants
 * @{
 */

/* The counter of a timer instance is disabled only if all the CCx and CCxN channels have been disabled */
#define TIM_CCER_CCxE_MASK                      ((uint32_t)(TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E))
#define TIM_CCER_CCxNE_MASK                     ((uint32_t)(TIM_CCER_CC1NE | TIM_CCER_CC2NE | TIM_CCER_CC3NE))

/**
 * @}
 */


/** @defgroup TIM_Private_Macros TIM Private Macros
 * @{
 */

#define IS_TIM_COUNTER_MODE(MODE)           (((MODE) == TIM_COUNTERMODE_UP)              || \
                                             ((MODE) == TIM_COUNTERMODE_DOWN)            || \
                                             ((MODE) == TIM_COUNTERMODE_CENTERALIGNED1)  || \
                                             ((MODE) == TIM_COUNTERMODE_CENTERALIGNED2)  || \
                                             ((MODE) == TIM_COUNTERMODE_CENTERALIGNED3))

#define IS_TIM_CLOCKDIVISION_DIV(DIV)       (((DIV) == TIM_CLOCKDIVISION_DIV1) || \
                                             ((DIV) == TIM_CLOCKDIVISION_DIV2) || \
                                             ((DIV) == TIM_CLOCKDIVISION_DIV4))

#define IS_TIM_AUTORELOAD_PRELOAD(PRELOAD)  (((PRELOAD) == TIM_AUTORELOAD_PRELOAD_DISABLE) || \
                                             ((PRELOAD) == TIM_AUTORELOAD_PRELOAD_ENABLE))

#define IS_TIM_PWM_MODE(MODE)               (((MODE) == TIM_OCMODE_PWM1) || ((MODE) == TIM_OCMODE_PWM2))

#define IS_TIM_OC_MODE(MODE)                (((MODE) == TIM_OCMODE_TIMING)        || \
                                             ((MODE) == TIM_OCMODE_ACTIVE)        || \
                                             ((MODE) == TIM_OCMODE_INACTIVE)      || \
                                             ((MODE) == TIM_OCMODE_TOGGLE)        || \
                                             ((MODE) == TIM_OCMODE_FORCED_ACTIVE) || \
                                             ((MODE) == TIM_OCMODE_FORCED_INACTIVE))

#define IS_TIM_FAST_STATE(STATE)            (((STATE) == TIM_OCFAST_DISABLE) || ((STATE) == TIM_OCFAST_ENABLE))

#define IS_TIM_OC_POLARITY(POLARITY)        (((POLARITY) == TIM_OCPOLARITY_HIGH) || ((POLARITY) == TIM_OCPOLARITY_LOW))

#define IS_TIM_OCN_POLARITY(POLARITY)       (((POLARITY) == TIM_OCNPOLARITY_HIGH) || ((POLARITY) == TIM_OCNPOLARITY_LOW))

#define IS_TIM_OCIDLE_STATE(STATE)          (((STATE) == TIM_OCIDLESTATE_SET) || ((STATE) == TIM_OCIDLESTATE_RESET))

#define IS_TIM_OCNIDLE_STATE(STATE)         (((STATE) == TIM_OCNIDLESTATE_SET) || ((STATE) == TIM_OCNIDLESTATE_RESET))

#define IS_TIM_CHANNELS(CHANNEL)            (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2) || \
                                             ((CHANNEL) == TIM_CHANNEL_3) || ((CHANNEL) == TIM_CHANNEL_4) || \
                                             ((CHANNEL) == TIM_CHANNEL_ALL))

#define IS_TIM_OPM_CHANNELS(CHANNEL)        (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2))

#define IS_TIM_COMPLEMENTARY_CHANNELS(CHANNEL) (((CHANNEL) == TIM_CHANNEL_1) || ((CHANNEL) == TIM_CHANNEL_2) || ((CHANNEL) == TIM_CHANNEL_3))

#define IS_TIM_IC_POLARITY(__POLARITY__)    (((__POLARITY__) == TIM_ICPOLARITY_RISING)   || \
                                             ((__POLARITY__) == TIM_ICPOLARITY_FALLING)  || \
                                             ((__POLARITY__) == TIM_ICPOLARITY_BOTHEDGE))

#define IS_TIM_IC_SELECTION(SELECTION)      (((SELECTION) == TIM_ICSELECTION_TI1) || \
                                             ((SELECTION) == TIM_ICSELECTION_TI2) || \
                                             ((SELECTION) == TIM_ICSELECTION_TRC))

#define IS_TIM_IC_PRESCALER(PRESCALER)      (((PRESCALER) == TIM_ICPSC_DIV1) || \
                                             ((PRESCALER) == TIM_ICPSC_DIV2) || \
                                             ((PRESCALER) == TIM_ICPSC_DIV4) || \
                                             ((PRESCALER) == TIM_ICPSC_DIV8))

#define IS_TIM_OPM_MODE(MODE)               (((MODE) == TIM_OPMODE_SINGLE) || ((MODE) == TIM_OPMODE_REPETITIVE))

#define IS_TIM_ENCODER_MODE(MODE)           (((MODE) == TIM_ENCODERMODE_TI1) || \
                                             ((MODE) == TIM_ENCODERMODE_TI2) || \
                                             ((MODE) == TIM_ENCODERMODE_TI12))

#define IS_TIM_EVENT_SOURCE(SOURCE)         ((((SOURCE) & 0xFFFFFF00U) == 0x00000000U) && ((SOURCE) != 0x00000000U))

#define IS_TIM_CLOCKSOURCE(CLOCK)           (((CLOCK) == TIM_CLOCKSOURCE_INTERNAL) || \
                                             ((CLOCK) == TIM_CLOCKSOURCE_ETRMODE2) || \
                                             ((CLOCK) == TIM_CLOCKSOURCE_ITR0)     || \
                                             ((CLOCK) == TIM_CLOCKSOURCE_ITR1)     || \
                                             ((CLOCK) == TIM_CLOCKSOURCE_ITR2)     || \
                                             ((CLOCK) == TIM_CLOCKSOURCE_ITR3)     || \
                                             ((CLOCK) == TIM_CLOCKSOURCE_TI1ED)    || \
                                             ((CLOCK) == TIM_CLOCKSOURCE_TI1)      || \
                                             ((CLOCK) == TIM_CLOCKSOURCE_TI2)      || \
                                             ((CLOCK) == TIM_CLOCKSOURCE_ETRMODE1))

#define IS_TIM_CLOCKPOLARITY(POLARITY)      (((POLARITY) == TIM_CLOCKPOLARITY_INVERTED)    || \
                                             ((POLARITY) == TIM_CLOCKPOLARITY_NONINVERTED) || \
                                             ((POLARITY) == TIM_CLOCKPOLARITY_RISING)      || \
                                             ((POLARITY) == TIM_CLOCKPOLARITY_FALLING)     || \
                                             ((POLARITY) == TIM_CLOCKPOLARITY_BOTHEDGE))

#define IS_TIM_CLOCKPRESCALER(PRESCALER)    (((PRESCALER) == TIM_CLOCKPRESCALER_DIV1) || \
                                             ((PRESCALER) == TIM_CLOCKPRESCALER_DIV2) || \
                                             ((PRESCALER) == TIM_CLOCKPRESCALER_DIV4) || \
                                             ((PRESCALER) == TIM_CLOCKPRESCALER_DIV8))

#define IS_TIM_CLOCKFILTER(ICFILTER)        ((ICFILTER) <= 0x0FU)

#define IS_TIM_CLEARINPUT_SOURCE(SOURCE)    (((SOURCE) == TIM_CLEARINPUTSOURCE_ETR) || ((SOURCE) == TIM_CLEARINPUTSOURCE_NONE))

#define IS_TIM_CLEARINPUT_POLARITY(POLARITY) (((POLARITY) == TIM_CLEARINPUTPOLARITY_INVERTED) || ((POLARITY) == TIM_CLEARINPUTPOLARITY_NONINVERTED))

#define IS_TIM_CLEARINPUT_PRESCALER(PRESCALER)  (((PRESCALER) == TIM_CLEARINPUTPRESCALER_DIV1) || \
                                                 ((PRESCALER) == TIM_CLEARINPUTPRESCALER_DIV2) || \
                                                 ((PRESCALER) == TIM_CLEARINPUTPRESCALER_DIV4) || \
                                                 ((PRESCALER) == TIM_CLEARINPUTPRESCALER_DIV8))

#define IS_TIM_CLEARINPUT_FILTER(ICFILTER)  ((ICFILTER) <= 0x0FU)

#define IS_TIM_OSSR_STATE(STATE)            (((STATE) == TIM_OSSR_ENABLE) || ((STATE) == TIM_OSSR_DISABLE))

#define IS_TIM_OSSI_STATE(STATE)            (((STATE) == TIM_OSSI_ENABLE) || ((STATE) == TIM_OSSI_DISABLE))

#define IS_TIM_LOCK_LEVEL(LEVEL)            (((LEVEL) == TIM_LOCKLEVEL_OFF) || \
                                             ((LEVEL) == TIM_LOCKLEVEL_1)   || \
                                             ((LEVEL) == TIM_LOCKLEVEL_2)   || \
                                             ((LEVEL) == TIM_LOCKLEVEL_3))

#define IS_TIM_DEADTIME(DEADTIME)           ((int)(DEADTIME) >= (int)0x0 && (DEADTIME) <= (int)0xFF)
#define IS_TIM_BREAK_STATE(STATE)           (((STATE) == TIM_BREAK_ENABLE) || ((STATE) == TIM_BREAK_DISABLE))

#define IS_TIM_BREAK_POLARITY(POLARITY)     (((POLARITY) == TIM_BREAKPOLARITY_LOW) || ((POLARITY) == TIM_BREAKPOLARITY_HIGH))

#define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AUTOMATICOUTPUT_ENABLE) || ((STATE) == TIM_AUTOMATICOUTPUT_DISABLE))

#define IS_TIM_TRGO_SOURCE(SOURCE)          (((SOURCE) == TIM_TRGO_RESET)  || \
                                             ((SOURCE) == TIM_TRGO_ENABLE) || \
                                             ((SOURCE) == TIM_TRGO_UPDATE) || \
                                             ((SOURCE) == TIM_TRGO_OC1)    || \
                                             ((SOURCE) == TIM_TRGO_OC1REF) || \
                                             ((SOURCE) == TIM_TRGO_OC2REF) || \
                                             ((SOURCE) == TIM_TRGO_OC3REF) || \
                                             ((SOURCE) == TIM_TRGO_OC4REF))

#define IS_TIM_SLAVE_MODE(MODE)             (((MODE) == TIM_SLAVEMODE_DISABLE) || \
                                             ((MODE) == TIM_SLAVEMODE_GATED)   || \
                                             ((MODE) == TIM_SLAVEMODE_RESET)   || \
                                             ((MODE) == TIM_SLAVEMODE_TRIGGER) || \
                                             ((MODE) == TIM_SLAVEMODE_EXTERNAL1))

#define IS_TIM_MSM_STATE(STATE)             (((STATE) == TIM_MASTERSLAVEMODE_ENABLE) || ((STATE) == TIM_MASTERSLAVEMODE_DISABLE))

#define IS_TIM_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0)    || \
                                             ((SELECTION) == TIM_TS_ITR1)    || \
                                             ((SELECTION) == TIM_TS_ITR2)    || \
                                             ((SELECTION) == TIM_TS_ITR3)    || \
                                             ((SELECTION) == TIM_TS_TI1F_ED) || \
                                             ((SELECTION) == TIM_TS_TI1FP1)  || \
                                             ((SELECTION) == TIM_TS_TI2FP2)  || \
                                             ((SELECTION) == TIM_TS_ETRF))

#define IS_TIM_INTERNAL_TRIGGEREVENT_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                                           ((SELECTION) == TIM_TS_ITR1) || \
                                                           ((SELECTION) == TIM_TS_ITR2) || \
                                                           ((SELECTION) == TIM_TS_ITR3))

#define IS_TIM_TRIGGERPOLARITY(POLARITY)    (((POLARITY) == TIM_TRIGGERPOLARITY_INVERTED   ) || \
                                             ((POLARITY) == TIM_TRIGGERPOLARITY_NONINVERTED) || \
                                             ((POLARITY) == TIM_TRIGGERPOLARITY_RISING     ) || \
                                             ((POLARITY) == TIM_TRIGGERPOLARITY_FALLING    ) || \
                                             ((POLARITY) == TIM_TRIGGERPOLARITY_BOTHEDGE   ))

#define IS_TIM_TRIGGERPRESCALER(PRESCALER)  (((PRESCALER) == TIM_TRIGGERPRESCALER_DIV1) || \
                                             ((PRESCALER) == TIM_TRIGGERPRESCALER_DIV2) || \
                                             ((PRESCALER) == TIM_TRIGGERPRESCALER_DIV4) || \
                                             ((PRESCALER) == TIM_TRIGGERPRESCALER_DIV8))

#define IS_TIM_TRIGGERFILTER(ICFILTER)      ((ICFILTER) <= 0x0FU)

#define IS_TIM_TI1SELECTION(TI1SELECTION)   (((TI1SELECTION) == TIM_TI1SELECTION_CH1) || ((TI1SELECTION) == TIM_TI1SELECTION_XORCOMBINATION))

#define IS_TIM_IC_FILTER(ICFILTER)          ((ICFILTER) <= 0x0FU)

#if defined(CONFIG_USE_ZB32L003S)
    /* L003S timer */
    #define IS_TIM_ADVANCED_INSTANCE(INSTANCE)          ((INSTANCE) == TIM1)
    #define IS_TIM_GENERAL_PURPOSE_INSTANCE(INSTANCE)   ((INSTANCE) == TIM2)

#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    /* L030 and L032 timer */
    #define IS_TIM_ADVANCED_INSTANCE(INSTANCE)                    \
              (((INSTANCE) == TIM1) || ((INSTANCE) == TIM1A) || ((INSTANCE) == TIM1B))

    #define IS_TIM_GENERAL_PURPOSE_INSTANCE(INSTANCE)                    \
              (((INSTANCE) == TIM2) || ((INSTANCE) == TIM2A) || ((INSTANCE) == TIM2B) || ((INSTANCE) == TIM2C))
#endif  /* CONFIG_USE_ZB32L030) || (CONFIG_USE_ZB32L032 */

#define IS_TIM_INSTANCE(INSTANCE)                             \
          (IS_TIM_ADVANCED_INSTANCE(INSTANCE) || IS_TIM_GENERAL_PURPOSE_INSTANCE(INSTANCE))

#define IS_TIM_CC1_INSTANCE(INSTANCE)                      IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_CC2_INSTANCE(INSTANCE)                      IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_CC3_INSTANCE(INSTANCE)                      IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_CC4_INSTANCE(INSTANCE)                      IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(INSTANCE)     IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(INSTANCE)     IS_TIM_INSTANCE(INSTANCE)
#define IS_TIM_CLOCKSOURCE_TIX_INSTANCE(INSTANCE)          IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_CLOCKSOURCE_ITRX_INSTANCE(INSTANCE)         IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_OCXREF_CLEAR_INSTANCE(INSTANCE)             IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_ENCODER_INTERFACE_INSTANCE(INSTANCE)        IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_XOR_INSTANCE(INSTANCE)                      IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_MASTER_INSTANCE(INSTANCE)                   IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_SLAVE_INSTANCE(INSTANCE)                    IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_SYNCHRO_INSTANCE(INSTANCE)                  IS_TIM_MASTER_INSTANCE(INSTANCE)

#define IS_TIM_DMABURST_INSTANCE(INSTANCE)                 IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_BREAK_INSTANCE(INSTANCE)                    IS_TIM_ADVANCED_INSTANCE(INSTANCE)

#define IS_TIM_CCX_INSTANCE(INSTANCE, CHANNEL)              (IS_TIM_INSTANCE(INSTANCE) &&  \
                                                             ((CHANNEL) == TIM_CHANNEL_1 || (CHANNEL) == TIM_CHANNEL_2 || \
                                                              (CHANNEL) == TIM_CHANNEL_3 || (CHANNEL) == TIM_CHANNEL_4))

#define IS_TIM_CCXN_INSTANCE(INSTANCE, CHANNEL)             (IS_TIM_ADVANCED_INSTANCE(INSTANCE) && \
                                                             (((CHANNEL) == TIM_CHANNEL_1) ||      \
                                                              ((CHANNEL) == TIM_CHANNEL_2) ||      \
                                                              ((CHANNEL) == TIM_CHANNEL_3)))

#define IS_TIM_COUNTER_MODE_SELECT_INSTANCE(INSTANCE)       IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_REPETITION_COUNTER_INSTANCE(INSTANCE)        IS_TIM_ADVANCED_INSTANCE(INSTANCE)

#define IS_TIM_CLOCK_DIVISION_INSTANCE(INSTANCE)            IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_COMMUTATION_EVENT_INSTANCE(INSTANCE)         IS_TIM_ADVANCED_INSTANCE(INSTANCE)

#define IS_TIM_ETR_INSTANCE(INSTANCE)                       IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE(INSTANCE)     IS_TIM_INSTANCE(INSTANCE)

#define IS_TIM_32B_COUNTER_INSTANCE(INSTANCE)               0U


/** @brief Set TIM IC prescaler
  * @param  __HANDLE__: TIM handle
  * @param  __CHANNEL__: specifies TIM Channel
  * @param  __ICPSC__: specifies the prescaler value.
  * @retval None
  */
#define TIM_SET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__, __ICPSC__)                                        \
            (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= (__ICPSC__)) :            \
             ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= ((__ICPSC__) << 8U)) :    \
             ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 |= (__ICPSC__)) :            \
             ((__HANDLE__)->Instance->CCMR2 |= ((__ICPSC__) << 8U)))

/** @brief Reset TIM IC prescaler
  * @param  __HANDLE__: TIM handle
  * @param  __CHANNEL__: specifies TIM Channel
  * @retval None
  */
#define TIM_RESET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__)                                                 \
            (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIM_CCMR1_IC1PSC) :      \
             ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIM_CCMR1_IC2PSC) :      \
             ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 &= ~TIM_CCMR2_IC3PSC) :      \
             ((__HANDLE__)->Instance->CCMR2 &= ~TIM_CCMR2_IC4PSC))


/** @brief Set TIM IC polarity
  * @param  __HANDLE__: TIM handle
  * @param  __CHANNEL__: specifies TIM Channel
  * @param  __POLARITY__: specifies TIM Channel Polarity
  * @retval None
  */
#define TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__)                                      \
            (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER |= (__POLARITY__)) :          \
             ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 4U)) :  \
             ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 8U)) :  \
             ((__HANDLE__)->Instance->CCER |= (((__POLARITY__) << 12U) & TIM_CCER_CC4P)))

/** @brief Reset TIM IC polarity
  * @param  __HANDLE__: TIM handle
  * @param  __CHANNEL__: specifies TIM Channel
  * @retval None
  */
#define TIM_RESET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__)                                                                     \
            (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER &= (uint16_t)~(TIM_CCER_CC1P | TIM_CCER_CC1NP)) :\
             ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER &= (uint16_t)~(TIM_CCER_CC2P | TIM_CCER_CC2NP)) :\
             ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER &= (uint16_t)~(TIM_CCER_CC3P | TIM_CCER_CC3NP)) :\
             ((__HANDLE__)->Instance->CCER &= (uint16_t)~TIM_CCER_CC4P))

/**
 * @}
 */


/** @defgroup TIM_Exported_Macros TIM Exported Macros
 * @{
 */

/** @brief  Reset TIM handle state
 * @param  __HANDLE__: TIM handle.
 * @retval None
 */
#define __HAL_TIM_RESET_HANDLE_STATE(__HANDLE__)        ((__HANDLE__)->State = HAL_TIM_STATE_RESET)

/**
 * @brief  Enable the TIM peripheral.
 * @param  __HANDLE__: TIM handle
 * @retval None
 */
#define __HAL_TIM_ENABLE(__HANDLE__)                    ((__HANDLE__)->Instance->CR1 |= (TIM_CR1_CEN))

/**
 * @brief  Enable the TIM main Output.
 * @param  __HANDLE__: TIM handle
 * @retval None
 */
#define __HAL_TIM_MOE_ENABLE(__HANDLE__)                ((__HANDLE__)->Instance->BDTR |= (TIM_BDTR_MOE))

/**
 * @brief  Disable the TIM peripheral.
 * @param  __HANDLE__: TIM handle
 * @retval None
 */
#define __HAL_TIM_DISABLE(__HANDLE__)                                              \
            do {                                                                   \
                if( ((__HANDLE__)->Instance->CCER & TIM_CCER_CCxE_MASK) == 0U &&   \
                    ((__HANDLE__)->Instance->CCER & TIM_CCER_CCxNE_MASK) == 0U )   \
                {                                                                  \
                    (__HANDLE__)->Instance->CR1 &= ~(TIM_CR1_CEN);                 \
                }                                                                  \
            } while(0U)

/* The Main Output Enable of a timer instance is disabled only if all the CCx and CCxN
   channels have been disabled */
/**
 * @brief  Disable the TIM main Output.
 * @param  __HANDLE__: TIM handle
 * @retval None
 * @note The Main Output Enable of a timer instance is disabled only if all the CCx and CCxN channels have been disabled
 */
#define __HAL_TIM_MOE_DISABLE(__HANDLE__)                                          \
            do {                                                                   \
                if( ((__HANDLE__)->Instance->CCER & TIM_CCER_CCxE_MASK) == 0U &&   \
                    ((__HANDLE__)->Instance->CCER & TIM_CCER_CCxNE_MASK) == 0U )   \
                {                                                                  \
                    (__HANDLE__)->Instance->BDTR &= ~(TIM_BDTR_MOE);               \
                }                                                                  \
            } while(0U)

/**
 * @brief  Disable the TIM main Output.
 * @param  __HANDLE__: TIM handle
 * @retval None
 * @note The Main Output Enable of a timer instance is disabled unconditionally
 */
#define __HAL_TIM_MOE_DISABLE_UNCONDITIONALLY(__HANDLE__)           (__HANDLE__)->Instance->BDTR &= ~(TIM_BDTR_MOE)

/**
 * @brief  Enables the specified TIM interrupt.
 * @param  __HANDLE__: specifies the TIM Handle.
 * @param  __INTERRUPT__: specifies the TIM interrupt source to enable.
 *          This parameter can be one of the following values:
 *            @arg TIM_IT_UPDATE: Update interrupt
 *            @arg TIM_IT_CC1:  Capture/Compare 1 interrupt
 *            @arg TIM_IT_CC2:  Capture/Compare 2 interrupt
 *            @arg TIM_IT_CC3:  Capture/Compare 3 interrupt
 *            @arg TIM_IT_CC4:  Capture/Compare 4 interrupt
 *            @arg TIM_IT_COM:  Commutation interrupt
 *            @arg TIM_IT_TRIGGER: Trigger interrupt
 *            @arg TIM_IT_BREAK: Break interrupt
 * @retval None
 */
#define __HAL_TIM_ENABLE_IT(__HANDLE__, __INTERRUPT__)              ((__HANDLE__)->Instance->DIER |= (__INTERRUPT__))

/**
 * @brief  Disables the specified TIM interrupt.
 * @param  __HANDLE__: specifies the TIM Handle.
 * @param  __INTERRUPT__: specifies the TIM interrupt source to disable.
 *          This parameter can be one of the following values:
 *            @arg TIM_IT_UPDATE: Update interrupt
 *            @arg TIM_IT_CC1:  Capture/Compare 1 interrupt
 *            @arg TIM_IT_CC2:  Capture/Compare 2 interrupt
 *            @arg TIM_IT_CC3:  Capture/Compare 3 interrupt
 *            @arg TIM_IT_CC4:  Capture/Compare 4 interrupt
 *            @arg TIM_IT_COM:  Commutation interrupt
 *            @arg TIM_IT_TRIGGER: Trigger interrupt
 *            @arg TIM_IT_BREAK: Break interrupt
 * @retval None
 */
#define __HAL_TIM_DISABLE_IT(__HANDLE__, __INTERRUPT__)             ((__HANDLE__)->Instance->DIER &= ~(__INTERRUPT__))


/**
 * @brief  Checks whether the specified TIM interrupt flag is set or not.
 * @param  __HANDLE__: specifies the TIM Handle.
 * @param  __FLAG__: specifies the TIM interrupt flag to check.
 *        This parameter can be one of the following values:
 *            @arg TIM_FLAG_UPDATE: Update interrupt flag
 *            @arg TIM_FLAG_CC1: Capture/Compare 1 interrupt flag
 *            @arg TIM_FLAG_CC2: Capture/Compare 2 interrupt flag
 *            @arg TIM_FLAG_CC3: Capture/Compare 3 interrupt flag
 *            @arg TIM_FLAG_CC4: Capture/Compare 4 interrupt flag
 *            @arg TIM_FLAG_COM:  Commutation interrupt flag
 *            @arg TIM_FLAG_TRIGGER: Trigger interrupt flag
 *            @arg TIM_FLAG_BREAK: Break interrupt flag
 *            @arg TIM_FLAG_CC1OF: Capture/Compare 1 overcapture flag
 *            @arg TIM_FLAG_CC2OF: Capture/Compare 2 overcapture flag
 *            @arg TIM_FLAG_CC3OF: Capture/Compare 3 overcapture flag
 *            @arg TIM_FLAG_CC4OF: Capture/Compare 4 overcapture flag
 * @retval The new state of __FLAG__ (TRUE or FALSE).
 */
#define __HAL_TIM_GET_FLAG(__HANDLE__, __FLAG__)                    (((__HANDLE__)->Instance->SR &(__FLAG__)) == (__FLAG__))

/**
 * @brief  Clears the specified TIM interrupt flag.
 * @param  __HANDLE__: specifies the TIM Handle.
 * @param  __FLAG__: specifies the TIM interrupt flag to clear.
 *        This parameter can be one of the following values:
 *            @arg TIM_FLAG_UPDATE: Update interrupt flag
 *            @arg TIM_FLAG_CC1: Capture/Compare 1 interrupt flag
 *            @arg TIM_FLAG_CC2: Capture/Compare 2 interrupt flag
 *            @arg TIM_FLAG_CC3: Capture/Compare 3 interrupt flag
 *            @arg TIM_FLAG_CC4: Capture/Compare 4 interrupt flag
 *            @arg TIM_FLAG_COM:  Commutation interrupt flag
 *            @arg TIM_FLAG_TRIGGER: Trigger interrupt flag
 *            @arg TIM_FLAG_BREAK: Break interrupt flag
 *            @arg TIM_FLAG_CC1OF: Capture/Compare 1 overcapture flag
 *            @arg TIM_FLAG_CC2OF: Capture/Compare 2 overcapture flag
 *            @arg TIM_FLAG_CC3OF: Capture/Compare 3 overcapture flag
 *            @arg TIM_FLAG_CC4OF: Capture/Compare 4 overcapture flag
 * @retval The new state of __FLAG__ (TRUE or FALSE).
 */
#define __HAL_TIM_CLEAR_FLAG(__HANDLE__, __FLAG__)                  ((__HANDLE__)->Instance->SR = ~(__FLAG__))

/**
 * @brief  Checks whether the specified TIM interrupt is enabled or not.
 * @param  __HANDLE__: TIM handle
 * @param  __INTERRUPT__: specifies the TIM interrupt source to check.
 * @retval The state of TIM_IT (SET or RESET).
 */
#define __HAL_TIM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)          ((((__HANDLE__)->Instance->DIER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/**
 * @brief Clear the TIM interrupt pending bits
 * @param  __HANDLE__: TIM handle
 * @param  __INTERRUPT__: specifies the interrupt pending bit to clear.
 * @retval None
 */
#define __HAL_TIM_CLEAR_IT(__HANDLE__, __INTERRUPT__)               ((__HANDLE__)->Instance->SR = ~(__INTERRUPT__))

/**
 * @brief  Indicates whether or not the TIM Counter is used as downcounter
 * @param  __HANDLE__: TIM handle.
 * @retval False (Counter used as upcounter) or True (Counter used as downcounter)
 * @note This macro is particularly usefull to get the counting mode when the timer operates in Center-aligned mode or Encoder mode.
 */
#define __HAL_TIM_IS_TIM_COUNTING_DOWN(__HANDLE__)                  (((__HANDLE__)->Instance->CR1 & (TIM_CR1_DIR)) == (TIM_CR1_DIR))

/**
 * @brief  Sets the TIM active prescaler register value on update event.
 * @param  __HANDLE__: TIM handle.
 * @param  __PRESC__: specifies the active prescaler register new value.
 * @retval None
 */
#define __HAL_TIM_SET_PRESCALER(__HANDLE__, __PRESC__)              ((__HANDLE__)->Instance->PSC = (__PRESC__))

/**
 * @brief  Sets the TIM Capture Compare Register value on runtime without
 *         calling another time ConfigChannel function.
 * @param  __HANDLE__: TIM handle.
 * @param  __CHANNEL__ : TIM Channels to be configured.
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @param  __COMPARE__: specifies the Capture Compare register new value.
 * @retval None
 */
#define __HAL_TIM_SET_COMPARE(__HANDLE__, __CHANNEL__, __COMPARE__) \
            (*(__IO uint32_t *)(&((__HANDLE__)->Instance->CCR1) + ((__CHANNEL__) >> 2U)) = (__COMPARE__))

/**
 * @brief  Gets the TIM Capture Compare Register value on runtime
 * @param  __HANDLE__: TIM handle.
 * @param  __CHANNEL__ : TIM Channel associated with the capture compare register
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: get capture/compare 1 register value
 *            @arg TIM_CHANNEL_2: get capture/compare 2 register value
 *            @arg TIM_CHANNEL_3: get capture/compare 3 register value
 *            @arg TIM_CHANNEL_4: get capture/compare 4 register value
 * @retval 16-bit or 32-bit value of the capture/compare register (TIMx_CCRy)
 */
#define __HAL_TIM_GET_COMPARE(__HANDLE__, __CHANNEL__) \
            (*(__IO uint32_t *)(&((__HANDLE__)->Instance->CCR1) + ((__CHANNEL__) >> 2U)))

/**
 * @brief  Sets the TIM Counter Register value on runtime.
 * @param  __HANDLE__: TIM handle.
 * @param  __COUNTER__: specifies the Counter register new value.
 * @retval None
 */
#define __HAL_TIM_SET_COUNTER(__HANDLE__, __COUNTER__)              ((__HANDLE__)->Instance->CNT = (__COUNTER__))

/**
 * @brief  Gets the TIM Counter Register value on runtime.
 * @param  __HANDLE__: TIM handle.
 * @retval 16-bit or 32-bit value of the timer counter register (TIMx_CNT)
 */
#define __HAL_TIM_GET_COUNTER(__HANDLE__)                           ((__HANDLE__)->Instance->CNT)

/**
 * @brief  Sets the TIM Autoreload Register value on runtime without calling
 *         another time any Init function.
 * @param  __HANDLE__: TIM handle.
 * @param  __AUTORELOAD__: specifies the Counter register new value.
 * @retval None
 */
#define __HAL_TIM_SET_AUTORELOAD(__HANDLE__, __AUTORELOAD__)        \
            do {                                                    \
                (__HANDLE__)->Instance->ARR = (__AUTORELOAD__);     \
                (__HANDLE__)->Init.Period = (__AUTORELOAD__);       \
            } while(0U)

/**
 * @brief  Gets the TIM Autoreload Register value on runtime
 * @param  __HANDLE__: TIM handle.
 * @retval @retval 16-bit or 32-bit value of the timer auto-reload register(TIMx_ARR)
 */
#define __HAL_TIM_GET_AUTORELOAD(__HANDLE__)                        ((__HANDLE__)->Instance->ARR)

/**
 * @brief  Sets the TIM Clock Division value on runtime without calling
 *         another time any Init function.
 * @param  __HANDLE__: TIM handle.
 * @param  __CKD__: specifies the clock division value.
 *          This parameter can be one of the following value:
 *            @arg TIM_CLOCKDIVISION_DIV1: tDTS=tCK_INT
 *            @arg TIM_CLOCKDIVISION_DIV2: tDTS=2*tCK_INT
 *            @arg TIM_CLOCKDIVISION_DIV4: tDTS=4*tCK_INT
 * @retval None
 */
#define __HAL_TIM_SET_CLOCKDIVISION(__HANDLE__, __CKD__)                  \
            do{                                                           \
                (__HANDLE__)->Instance->CR1 &= (uint16_t)(~TIM_CR1_CKD);  \
                (__HANDLE__)->Instance->CR1 |= (__CKD__);                 \
                (__HANDLE__)->Init.ClockDivision = (__CKD__);             \
            } while(0U)

/**
 * @brief  Gets the TIM Clock Division value on runtime
 * @param  __HANDLE__: TIM handle.
 * @retval The clock division can be one of the following values:
 *            @arg TIM_CLOCKDIVISION_DIV1: tDTS=tCK_INT
 *            @arg TIM_CLOCKDIVISION_DIV2: tDTS=2*tCK_INT
 *            @arg TIM_CLOCKDIVISION_DIV4: tDTS=4*tCK_INT
 */
#define __HAL_TIM_GET_CLOCKDIVISION(__HANDLE__)                     ((__HANDLE__)->Instance->CR1 & TIM_CR1_CKD)

/**
 * @brief  Sets the TIM Input Capture prescaler on runtime without calling
 *         another time HAL_TIM_IC_ConfigChannel() function.
 * @param  __HANDLE__: TIM handle.
 * @param  __CHANNEL__ : TIM Channels to be configured.
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @param  __ICPSC__: specifies the Input Capture4 prescaler new value.
 *          This parameter can be one of the following values:
 *            @arg TIM_ICPSC_DIV1: no prescaler
 *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
 *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
 *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
 * @retval None
 */
#define __HAL_TIM_SET_ICPRESCALER(__HANDLE__, __CHANNEL__, __ICPSC__)               \
            do{                                                                     \
                TIM_RESET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__));            \
                TIM_SET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__), (__ICPSC__)); \
            } while(0U)

/**
 * @brief  Gets the TIM Input Capture prescaler on runtime
 * @param  __HANDLE__: TIM handle.
 * @param  __CHANNEL__: TIM Channels to be configured.
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: get input capture 1 prescaler value
 *            @arg TIM_CHANNEL_2: get input capture 2 prescaler value
 *            @arg TIM_CHANNEL_3: get input capture 3 prescaler value
 *            @arg TIM_CHANNEL_4: get input capture 4 prescaler value
 * @retval The input capture prescaler can be one of the following values:
 *            @arg TIM_ICPSC_DIV1: no prescaler
 *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
 *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
 *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
 */
#define __HAL_TIM_GET_ICPRESCALER(__HANDLE__, __CHANNEL__)                                                  \
            (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 & TIM_CCMR1_IC1PSC) :        \
             ((__CHANNEL__) == TIM_CHANNEL_2) ? (((__HANDLE__)->Instance->CCMR1 & TIM_CCMR1_IC2PSC) >> 8U) :\
             ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 & TIM_CCMR2_IC3PSC) :        \
             (((__HANDLE__)->Instance->CCMR2 & TIM_CCMR2_IC4PSC)) >> 8U)

/**
 * @brief  Set the Update Request Source (URS) bit of the TIMx_CR1 register
 * @param  __HANDLE__: TIM handle.
 * @note  When the USR bit of the TIMx_CR1 register is set, only counter
 *        overflow/underflow generates an update interrupt.
 * @retval None
 */
#define __HAL_TIM_URS_ENABLE(__HANDLE__)                            ((__HANDLE__)->Instance->CR1 |= (TIM_CR1_URS))

/**
 * @brief  Reset the Update Request Source (URS) bit of the TIMx_CR1 register
 * @param  __HANDLE__: TIM handle.
 * @note  When the USR bit of the TIMx_CR1 register is reset, any of the
 *        following events generate an update interrupt:
 *          (+) Counter overflow/underflow
 *          (+) Setting the UG bit
 *          (+) Update generation through the slave mode controller
 * @retval None
 */
#define __HAL_TIM_URS_DISABLE(__HANDLE__)                           ((__HANDLE__)->Instance->CR1 &= ~(TIM_CR1_URS))

/**
 * @brief  Sets the TIM Capture x input polarity on runtime.
 * @param  __HANDLE__: TIM handle.
 * @param  __CHANNEL__: TIM Channels to be configured.
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @param  __POLARITY__: Polarity for TIx source
 *            @arg TIM_ICPOLARITY_RISING: Rising Edge
 *            @arg TIM_ICPOLARITY_FALLING: Falling Edge
 *            @arg TIM_ICPOLARITY_BOTHEDGE: Rising and Falling Edge
 * @note  The polarity TIM_INPUTCHANNELPOLARITY_BOTHEDGE is not authorized  for TIM Channel 4.
 * @retval None
 */
#define __HAL_TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__)          \
            do{                                                                       \
                TIM_RESET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__));               \
                TIM_SET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__), (__POLARITY__)); \
            }while(0U)


/**
 * @}
 */



/** @addtogroup TIM_Exported_Functions
  * @{
  */

/** @addtogroup TIM_Exported_Functions_Group1
 * @{
 */
/* Time Base functions ********************************************************/
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim);

/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim);

/**
 * @}
 */

/** @addtogroup TIM_Exported_Functions_Group2
 * @{
 */
/* Timer Output Compare functions **********************************************/
HAL_StatusTypeDef HAL_TIM_OC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_OC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim);

/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_OC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_OC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @}
 */

/** @addtogroup TIM_Exported_Functions_Group3
 * @{
 */
/* Timer PWM functions *********************************************************/
HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_PWM_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim);

/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Timer Complementary PWM functions  ****************************************/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_PWMN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWMN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_PWMN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWMN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_ConfigBreakDeadTime(TIM_HandleTypeDef *htim, TIM_BreakDeadTimeConfigTypeDef *pBreakDeadTimeConfig);
/**
 * @}
 */

/** @addtogroup TIM_Exported_Functions_Group4
 * @{
 */
/* Timer Input Capture functions ***********************************************/
HAL_StatusTypeDef HAL_TIM_IC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_IC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *htim);

/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @}
 */

/** @addtogroup TIM_Exported_Functions_Group5
 * @{
 */
/* Timer One Pulse functions ***************************************************/
HAL_StatusTypeDef HAL_TIM_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t OnePulseMode);
HAL_StatusTypeDef HAL_TIM_OnePulse_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspDeInit(TIM_HandleTypeDef *htim);

/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_OnePulse_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_OnePulse_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
/**
 * @}
 */

/** @addtogroup TIM_Exported_Functions_Group6
 * @{
 */
/* Timer Encoder functions *****************************************************/
HAL_StatusTypeDef HAL_TIM_Encoder_Init(TIM_HandleTypeDef *htim,  TIM_Encoder_InitTypeDef *pConfig);
HAL_StatusTypeDef HAL_TIM_Encoder_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *htim);

/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_Encoder_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_Encoder_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @}
 */

/** @addtogroup TIM_Exported_Functions_Group7
 * @{
 */
/* Interrupt Handler functions  **********************************************/
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);
/**
 * @}
 */

/** @addtogroup TIM_Exported_Functions_Group8
 * @{
 */
/* Control functions  *********************************************************/
HAL_StatusTypeDef HAL_TIM_OC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *pConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *pConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_IC_InitTypeDef *pConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OnePulse_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OnePulse_InitTypeDef *pConfig, uint32_t OutputChannel, uint32_t InputChannel);
HAL_StatusTypeDef HAL_TIM_ConfigOCrefClear(TIM_HandleTypeDef *htim, TIM_ClearInputConfigTypeDef *pClearInputConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef *pClockSourceConfig);
HAL_StatusTypeDef HAL_TIM_ConfigTI1Input(TIM_HandleTypeDef *htim, uint32_t TI1_Selection);
HAL_StatusTypeDef HAL_TIME_MasterConfigSynchronization(TIM_HandleTypeDef *htim, TIM_MasterConfigTypeDef *pMasterConfig);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchronization(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *pSlaveConfig);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchronization_IT(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *pSlaveConfig);
HAL_StatusTypeDef HAL_TIM_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource);
uint32_t HAL_TIM_ReadCapturedValue(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @}
 */

/** @addtogroup TIM_Exported_Functions_Group9
 * @{
 */
/* Callback in non blocking modes (Interrupt) *************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_BreakCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_CommutationCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim);

/**
 * @}
 */

/** @addtogroup TIM_Exported_Functions_Group10
 * @{
 */
/* Peripheral State functions  **************************************************/
HAL_TIM_StateTypeDef HAL_TIM_Base_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OC_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_PWM_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_IC_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OnePulse_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_Encoder_GetState(TIM_HandleTypeDef *htim);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* __ZB32L03x_HAL_TIM_H */


