/**
 ******************************************************************************
 * @file    zb32l03x_hal_tim.c
 * @author  MCU Software Team
 * @Version V1.2.0
 * @Date    14-Nov-2019
 * @brief   TIM HAL module driver
 *          This file provides firmware functions to manage the following
 *          functionalities of the Timer (TIM) peripheral:
 *           + Time Base Initialization
 *           + Time Base Start
 *           + Time Base Start Interruption
 *           + Time Output Compare/PWM Initialization
 *           + Time Output Compare/PWM Channel Configuration
 *           + Time Output Compare/PWM  Start
 *           + Time Output Compare/PWM  Start Interruption
 *           + Time Input Capture Initialization
 *           + Time Input Capture Channel Configuration
 *           + Time Input Capture Start
 *           + Time Input Capture Start Interruption
 *           + Time One Pulse Initialization
 *           + Time One Pulse Channel Configuration
 *           + Time One Pulse Start
 *           + Time Encoder Interface Initialization
 *           + Time Encoder Interface Start
 *           + Time Encoder Interface Start Interruption
 *           + Time OCRef clear configuration
 *           + Time External Clock configuration
 *           + Start the Complementary PWM.
 *           + Stop the Complementary PWM.
 *           + Start the Complementary PWM and enable interrupts.
 *           + Stop the Complementary PWM and disable interrupts.
 @verbatim
 ==============================================================================
                     ##### TIMER Generic features #####
 ==============================================================================
 [..] The Timer features include:
      (#) 16-bit up, down, up/down auto-reload counter.
      (#) 16-bit programmable prescaler allowing dividing (also on the fly) the
          counter clock frequency either by any factor between 1 and 65536.
      (#) Up to 4 independent channels for:
          (++) Input Capture
          (++) Output Compare
          (++) PWM generation (Edge and Center-aligned Mode)
          (++) One-pulse mode output

           ##### How to use this driver #####
 ==============================================================================
   [..]
    (#) Initialize the TIM low level resources by implementing the following functions
        depending from feature used :
          (++) Time Base : HAL_TIM_Base_MspInit()
          (++) Input Capture : HAL_TIM_IC_MspInit()
          (++) Output Compare : HAL_TIM_OC_MspInit()
          (++) PWM generation : HAL_TIM_PWM_MspInit()
          (++) One-pulse mode output : HAL_TIM_OnePulse_MspInit()
          (++) Encoder mode output : HAL_TIM_Encoder_MspInit()

    (#) Initialize the TIM low level resources :
       (##) Enable the TIM interface clock using __HAL_RCC_TIMx_CLK_ENABLE();
       (##) TIM pins configuration
           (+++) Enable the clock for the TIM GPIOs using the following function:
            __HAL_RCC_GPIOx_CLK_ENABLE();
           (+++) Configure these TIM pins in Alternate function mode using HAL_GPIO_Init();

    (#) The external Clock can be configured, if needed (the default clock is the
        internal clock from the APB), using the following function:
        HAL_TIM_ConfigClockSource, the clock configuration should be done before
        any start function.

    (#) Configure the TIM in the desired functioning mode using one of the
      Initialization function of this driver:
      (++) HAL_TIM_Base_Init: to use the Timer to generate a simple time base
      (++) HAL_TIM_OC_Init and HAL_TIM_OC_ConfigChannel: to use the Timer to generate an
           Output Compare signal.
      (++) HAL_TIM_PWM_Init and HAL_TIM_PWM_ConfigChannel: to use the Timer to generate a
           PWM signal.
      (++) HAL_TIM_IC_Init and HAL_TIM_IC_ConfigChannel: to use the Timer to measure an
           external signal.
        (++) HAL_TIM_OnePulse_Init and HAL_TIM_OnePulse_ConfigChannel: to use the Timer
             in One Pulse Mode.
      (++) HAL_TIM_Encoder_Init: to use the Timer Encoder Interface.

    (#) Activate the TIM peripheral using one of the start functions depending from the feature used:
          (++) Time Base : HAL_TIM_Base_Start(), HAL_TIM_Base_Start_IT()
          (++) Input Capture :  HAL_TIM_IC_Start(), HAL_TIM_IC_Start_IT()
          (++) Output Compare : HAL_TIM_OC_Start(), HAL_TIM_OC_Start_IT()
          (++) PWM generation : HAL_TIM_PWM_Start()
          (++) One-pulse mode output : HAL_TIM_OnePulse_Start(), HAL_TIM_OnePulse_Start_IT()
          (++) Encoder mode output : HAL_TIM_Encoder_Start(), HAL_TIM_Encoder_Start_IT().


 @endverbatim
 ******************************************************************************
 **/


#include "zb32l03x_hal.h"

/** @addtogroup ZB32L03x_HAL_Driver
 * @{
 */


/** @defgroup TIM TIM
 * @brief TIM HAL module driver
 * @{
 */

#if defined(HAL_TIM_MODULE_ENABLED)


/** @defgroup TIM_Private_Functions TIM Private Functions
 * @{
 */

/**
 * @brief  Time Output Compare 1 configuration
 * @param  TIMx to select the TIM peripheral
 * @param  OC_Config : The output configuration structure
 * @retval None
 */
static void TIM_OC1_SetConfig(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef *OC_Config)
{
    uint32_t    tmpccmrx = 0U;
    uint32_t    tmpccer = 0U;
    uint32_t    tmpcr2 = 0U;

    /* Disable the Channel 1: Reset the CC1E Bit */
    CLEAR_BIT(TIMx->CCER, TIM_CCER_CC1E);

    tmpccer  = READ_REG(TIMx->CCER);
    tmpcr2   = READ_REG(TIMx->CR2);
    tmpccmrx = READ_REG(TIMx->CCMR1_OUT);

    // set channel 1 to output
    CLEAR_BIT(tmpccmrx, TIM_CCMR1_OUT_CC1S);

    /* Select the Output Compare Mode */
    WRITE_REG_MASK(tmpccmrx, TIM_CCMR1_OUT_OC1M_Msk, OC_Config->OCMode);

    /* Set the Output Compare Polarity */
    WRITE_REG_MASK(tmpccer, TIM_CCER_CC1P_Msk, OC_Config->OCPolarity);

    if( IS_TIM_CCXN_INSTANCE(TIMx, TIM_CHANNEL_1) )
    {
        /* Check parameters */
        assert_param(IS_TIM_OCN_POLARITY(OC_Config->OCNPolarity));

        /* Set the Output N Polarity and N State */
        WRITE_REG_MASK(tmpccer,
                       TIM_CCER_CC1NP_Msk | TIM_CCER_CC1NE_Msk,
                       OC_Config->OCNPolarity);
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx))
    {
        /* Check parameters */
        assert_param(IS_TIM_OCNIDLE_STATE(OC_Config->OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(OC_Config->OCIdleState));

        /* Set the Output Idle state and N Idle state */
        WRITE_REG_MASK(tmpcr2,
                       TIM_CR2_OIS1_Msk | TIM_CR2_OIS1N_Msk,
                       OC_Config->OCIdleState | OC_Config->OCNIdleState);
    }
    /* Write to TIMx CR2/CCMR1/CCR1/CCER */
    WRITE_REG(TIMx->CR2, tmpcr2);
    WRITE_REG(TIMx->CCMR1_OUT, tmpccmrx);
    WRITE_REG_MASK(TIMx->CCR1, TIM_CCR1_CCR1_Msk, OC_Config->Pulse);
    WRITE_REG(TIMx->CCER, tmpccer);
    return;
}

/**
 * @brief  Time Output Compare 2 configuration
 * @param  TIMx  to select the TIM peripheral
 * @param  OC_Config : The output configuration structure
 * @retval None
 */
static void TIM_OC2_SetConfig(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef *OC_Config)
{
    uint32_t tmpccmrx = 0U;
    uint32_t tmpccer = 0U;
    uint32_t tmpcr2 = 0U;

    /* Disable the Channel 2: Reset the CC2E Bit */
    CLEAR_BIT(TIMx->CCER, TIM_CCER_CC2E);

    /* Get the TIMx CCER/CR2/CCMR1 register value */
    tmpccer  = READ_REG(TIMx->CCER);
    tmpcr2   = READ_REG(TIMx->CR2);
    tmpccmrx = READ_REG(TIMx->CCMR1_OUT);

    /* Select the Output Compare Mode */
    WRITE_REG_MASK(tmpccmrx,
                   TIM_CCMR1_OUT_OC2M_Msk | TIM_CCMR1_OUT_CC2S_Msk,
                   (OC_Config->OCMode << 8U));

    /* Set the Output Compare Polarity */
    WRITE_REG_MASK(tmpccer, TIM_CCER_CC2P_Msk, (OC_Config->OCPolarity << 4U));

    if(IS_TIM_CCXN_INSTANCE(TIMx, TIM_CHANNEL_2))
    {
        assert_param(IS_TIM_OCN_POLARITY(OC_Config->OCNPolarity));

        /* Set the Output N Polarity and N State */
        WRITE_REG_MASK(tmpccer,
                       TIM_CCER_CC2NP_Msk | TIM_CCER_CC2NE_Msk,
                       (OC_Config->OCNPolarity << 4U));
    }

    if( IS_TIM_BREAK_INSTANCE(TIMx) )
    {
        /* Check parameters */
        assert_param(IS_TIM_OCNIDLE_STATE(OC_Config->OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(OC_Config->OCIdleState));

        /* Set the Output Idle state and N Idle state */
        WRITE_REG_MASK(tmpcr2,
                       TIM_CR2_OIS2_Msk | TIM_CR2_OIS2N_Msk,
                       (OC_Config->OCIdleState << 2) | (OC_Config->OCNIdleState << 2));
    }

    /* Write to TIMx CR2/CCMR1/CCR2/CCER */
    WRITE_REG(TIMx->CR2, tmpcr2);
    WRITE_REG(TIMx->CCMR1_OUT, tmpccmrx);
    WRITE_REG_MASK(TIMx->CCR2, TIM_CCR2_CCR2_Msk, OC_Config->Pulse);
    WRITE_REG(TIMx->CCER, tmpccer);
    return;
}

/**
 * @brief  Time Output Compare 3 configuration
 * @param  TIMx  to select the TIM peripheral
 * @param  OC_Config : The output configuration structure
 * @retval None
 */
static void TIM_OC3_SetConfig(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef *OC_Config)
{
    uint32_t tmpccmrx = 0U;
    uint32_t tmpccer = 0U;
    uint32_t tmpcr2 = 0U;

    /* Disable the Channel 3: Reset the CC2E Bit */
    CLEAR_BIT(TIMx->CCER, TIM_CCER_CC3E);

    /* Get the TIMx CCER/CR2/CCMR2 register value */
    tmpccer  = READ_REG(TIMx->CCER);
    tmpcr2   = READ_REG(TIMx->CR2);
    tmpccmrx = READ_REG(TIMx->CCMR2_OUT);

    /* Select the Output Compare Mode */
    WRITE_REG_MASK(tmpccmrx,
                   TIM_CCMR2_OUT_OC3M_Msk | TIM_CCMR2_OUT_CC3S_Msk,
                   OC_Config->OCMode);

    /* Set the Output Compare Polarity */
    WRITE_REG_MASK(tmpccer, TIM_CCER_CC3P_Msk, (OC_Config->OCPolarity << 8U));

    if(IS_TIM_CCXN_INSTANCE(TIMx, TIM_CHANNEL_3))
    {
        assert_param(IS_TIM_OCN_POLARITY(OC_Config->OCNPolarity));

        /* Set the Output N Polarity and N State */
        WRITE_REG_MASK(tmpccer,
                       TIM_CCER_CC3NP_Msk | TIM_CCER_CC3NE_Msk,
                       (OC_Config->OCNPolarity << 8U));
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx))
    {
        /* Check parameters */
        assert_param(IS_TIM_OCNIDLE_STATE(OC_Config->OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(OC_Config->OCIdleState));

        /* Set the Output Idle state and N Idle state */
        WRITE_REG_MASK(tmpcr2,
                       TIM_CR2_OIS3_Msk | TIM_CR2_OIS3N_Msk,
                       (OC_Config->OCIdleState << 4U) | (OC_Config->OCNIdleState << 4U));
    }

    /* Write to TIMx CR2/CCMR2/CCR3/CCER */
    WRITE_REG(TIMx->CR2, tmpcr2);
    WRITE_REG(TIMx->CCMR2_OUT, tmpccmrx);
    WRITE_REG_MASK(TIMx->CCR3, TIM_CCR3_CCR3_Msk, OC_Config->Pulse);
    WRITE_REG(TIMx->CCER, tmpccer);
    return;
}

/**
 * @brief  Time Output Compare 4 configuration
 * @param  TIMx  to select the TIM peripheral
 * @param  OC_Config : The output configuration structure
 * @retval None
 */
static void TIM_OC4_SetConfig(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef *OC_Config)
{
    uint32_t tmpccmrx = 0U;
    uint32_t tmpccer = 0U;
    uint32_t tmpcr2 = 0U;

    /* Disable the Channel 4: Reset the CC4E Bit */
    CLEAR_BIT(TIMx->CCER, TIM_CCER_CC4E);

    /* Get the TIMx CCER/CR2/CCMR2 register value */
    tmpccer  = READ_REG(TIMx->CCER);
    tmpcr2   = READ_REG(TIMx->CR2);
    tmpccmrx = READ_REG(TIMx->CCMR2_OUT);

    /* Select the Output Compare Mode */
    WRITE_REG_MASK(tmpccmrx,
                   TIM_CCMR2_OUT_OC4M_Msk | TIM_CCMR2_OUT_CC4S_Msk,
                   (OC_Config->OCMode << 8U));

    /* Set the Output Compare Polarity */
    WRITE_REG_MASK(tmpccer, TIM_CCER_CC4P_Msk, (OC_Config->OCPolarity << 12U));

    if(IS_TIM_BREAK_INSTANCE(TIMx))
    {
        assert_param(IS_TIM_OCIDLE_STATE(OC_Config->OCIdleState));

        /* Set the Output Idle state */
        WRITE_REG_MASK(tmpcr2, TIM_CR2_OIS4_Msk, (OC_Config->OCIdleState << 6));
    }

    /* Write to TIMx CR2/CCMR2/CCR4/CCER/CCER */
    WRITE_REG(TIMx->CR2, tmpcr2);
    WRITE_REG(TIMx->CCMR2_OUT, tmpccmrx);
    WRITE_REG_MASK(TIMx->CCR4, TIM_CCR4_CCR4_Msk, OC_Config->Pulse);
    WRITE_REG(TIMx->CCER, tmpccer);
    return;
}

/**
 * @brief  Configure the TI1 as Input.
 * @param  TIMx  to select the TIM peripheral.
 * @param  TIM_ICPolarity : The Input Polarity.
 *          This parameter can be one of the following values:
 *            @arg TIM_ICPOLARITY_RISING
 *            @arg TIM_ICPOLARITY_FALLING
 *            @arg TIM_ICPOLARITY_BOTHEDGE
 * @param  TIM_ICSelection : specifies the input to be used.
 *          This parameter can be one of the following values:
 *            @arg TIM_ICSELECTION_DIRECTTI:    TIM Input 1 is selected to be connected to IC1.
 *            @arg TIM_ICSELECTION_INDIRECTTI:  TIM Input 1 is selected to be connected to IC2.
 *            @arg TIM_ICSELECTION_TRC:         TIM Input 1 is selected to be connected to TRC.
 * @param  TIM_ICFilter : Specifies the Input Capture Filter.
 *          This parameter must be a value between 0x00 and 0x0F.
 * @retval None
 * @note TIM_ICFilter and TIM_ICPolarity are not used in INDIRECT mode as TI2FP1
 *       (on channel2 path) is used as the input signal. Therefore CCMR1 must be
 *        protected against un-initialized filter and polarity values.
 */
static void TIM_TI1_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t TIM_ICFilter)
{
    uint32_t    tmpccmr1 = 0U;
    uint32_t    tmpccer = 0U;

    /* Disable the Channel 1: Reset the CC1E Bit */
    CLEAR_BIT(TIMx->CCER, TIM_CCER_CC1E);

    tmpccmr1 = READ_REG(TIMx->CCMR1_IN);
    tmpccer  = READ_REG(TIMx->CCER);

    /* Select the Input and filter */
    WRITE_REG_MASK(tmpccmr1,
                   (TIM_CCMR1_IN_CC1S_Msk | TIM_CCMR1_IN_IC1F_Msk),
                   ((TIM_ICSelection << TIM_CCMR1_IN_CC1S_Pos) | (TIM_ICFilter << TIM_CCMR1_IN_IC1F_Pos)));

    /* Select the Polarity */
    WRITE_REG_MASK(tmpccer, (TIM_CCER_CC1P_Msk | TIM_CCER_CC1NP_Msk), TIM_ICPolarity);

    /* Write to TIMx CCMR1 and CCER registers */
    WRITE_REG(TIMx->CCMR1_IN, tmpccmr1);
    WRITE_REG(TIMx->CCER, tmpccer);
    return;
}


/**
 * @brief  Configure the Polarity and Filter for TI1.
 * @param  TIMx  to select the TIM peripheral.
 * @param  TIM_ICPolarity : The Input Polarity.
 *          This parameter can be one of the following values:
 *            @arg TIM_ICPOLARITY_RISING
 *            @arg TIM_ICPOLARITY_FALLING
 *            @arg TIM_ICPOLARITY_BOTHEDGE
 * @param  TIM_ICFilter : Specifies the Input Capture Filter.
 *          This parameter must be a value between 0x00 and 0x0F.
 * @retval None
 */
static void TIM_TI1_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICFilter)
{
    uint32_t tmpccmr1 = 0U;
    uint32_t tmpccer = 0U;

    tmpccer = READ_REG(TIMx->CCER);
    tmpccmr1 = READ_REG(TIMx->CCMR1_IN);

    /* Disable the Channel 1: Reset the CC1E Bit */
    CLEAR_BIT(TIMx->CCER, TIM_CCER_CC1E);

    /* Set the filter */
    WRITE_REG_MASK(tmpccmr1, TIM_CCMR1_IN_IC1F_Msk, (TIM_ICFilter << TIM_CCMR1_IN_IC1F_Pos));

    /* Select the Polarity */
    WRITE_REG_MASK(tmpccer, (TIM_CCER_CC1P_Msk | TIM_CCER_CC1NP_Msk), TIM_ICPolarity);

    /* Write to TIMx CCMR1 and CCER registers */
    WRITE_REG(TIMx->CCMR1_IN, tmpccmr1);
    WRITE_REG(TIMx->CCER, tmpccer);
    return;
}

/**
 * @brief  Configure the TI2 as Input.
 * @param  TIMx  to select the TIM peripheral
 * @param  TIM_ICPolarity : The Input Polarity.
 *          This parameter can be one of the following values:
 *            @arg TIM_ICPOLARITY_RISING
 *            @arg TIM_ICPOLARITY_FALLING
 *            @arg TIM_ICPOLARITY_BOTHEDGE
 * @param  TIM_ICSelection : specifies the input to be used.
 *          This parameter can be one of the following values:
 *            @arg TIM_ICSELECTION_DIRECTTI:   TIM Input 2 is selected to be connected to IC2.
 *            @arg TIM_ICSELECTION_INDIRECTTI: TIM Input 2 is selected to be connected to IC1.
 *            @arg TIM_ICSELECTION_TRC:        TIM Input 2 is selected to be connected to TRC.
 * @param  TIM_ICFilter : Specifies the Input Capture Filter.
 *          This parameter must be a value between 0x00 and 0x0F.
 * @retval None
 * @note TIM_ICFilter and TIM_ICPolarity are not used in INDIRECT mode as TI1FP2
 *       (on channel1 path) is used as the input signal. Therefore CCMR1 must be
 *        protected against un-initialized filter and polarity values.
 */
static void TIM_TI2_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                              uint32_t TIM_ICFilter)
{
    uint32_t    tmpccmr1 = 0U;
    uint32_t    tmpccer = 0U;

    /* Disable the Channel 2: Reset the CC2E Bit */
    CLEAR_BIT(TIMx->CCER, TIM_CCER_CC2E);

    tmpccmr1 = READ_REG(TIMx->CCMR1_IN);
    tmpccer  = READ_REG(TIMx->CCER);

    /* Select the Input and filter*/
    WRITE_REG_MASK(tmpccmr1,
                   (TIM_CCMR1_IN_CC2S_Msk | TIM_CCMR1_IN_IC2F_Msk),
                   ((TIM_ICSelection << TIM_CCMR1_IN_CC2S_Pos) | ((TIM_ICFilter << TIM_CCMR1_IN_IC2F_Pos))));

    /* Select the Polarity */
    WRITE_REG_MASK(tmpccer, (TIM_CCER_CC2P_Msk | TIM_CCER_CC2NP_Msk), (TIM_ICPolarity << TIM_CCER_CC2E_Pos));

    /* Write to TIMx CCMR1 and CCER registers */
    WRITE_REG(TIMx->CCMR1_IN, tmpccmr1);
    WRITE_REG(TIMx->CCER, tmpccer);
    return;
}

/**
 * @brief  Configure the Polarity and Filter for TI2.
 * @param  TIMx  to select the TIM peripheral.
 * @param  TIM_ICPolarity : The Input Polarity.
 *          This parameter can be one of the following values:
 *            @arg TIM_ICPOLARITY_RISING
 *            @arg TIM_ICPOLARITY_FALLING
 *            @arg TIM_ICPOLARITY_BOTHEDGE
 * @param  TIM_ICFilter : Specifies the Input Capture Filter.
 *          This parameter must be a value between 0x00 and 0x0F.
 * @retval None
 */
static void TIM_TI2_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICFilter)
{
    uint32_t    tmpccmr1 = 0U;
    uint32_t    tmpccer = 0U;

    /* Disable the Channel 2: Reset the CC2E Bit */
    CLEAR_BIT(TIMx->CCER, TIM_CCER_CC2E);

    tmpccmr1 = READ_REG(TIMx->CCMR1_IN);
    tmpccer  = READ_REG(TIMx->CCER);

    /* Set the filter */
    WRITE_REG_MASK(tmpccmr1, TIM_CCMR1_IN_IC2F_Msk, (TIM_ICFilter << TIM_CCMR1_IN_IC2F_Pos));

    /* Select the Polarity */
    WRITE_REG_MASK(tmpccer, (TIM_CCER_CC2P_Msk | TIM_CCER_CC2NP_Msk), (TIM_ICPolarity << TIM_CCER_CC2E_Pos));

    /* Write to TIMx CCMR1 and CCER registers */
    WRITE_REG(TIMx->CCMR1_IN, tmpccmr1);
    WRITE_REG(TIMx->CCER, tmpccer);
    return;
}

/**
 * @brief  Configure the TI3 as Input.
 * @param  TIMx  to select the TIM peripheral
 * @param  TIM_ICPolarity : The Input Polarity.
 *          This parameter can be one of the following values:
 *            @arg TIM_ICPOLARITY_RISING
 *            @arg TIM_ICPOLARITY_FALLING
 * @param  TIM_ICSelection : specifies the input to be used.
 *          This parameter can be one of the following values:
 *            @arg TIM_ICSELECTION_DIRECTTI:   TIM Input 3 is selected to be connected to IC3.
 *            @arg TIM_ICSELECTION_INDIRECTTI: TIM Input 3 is selected to be connected to IC4.
 *            @arg TIM_ICSELECTION_TRC:        TIM Input 3 is selected to be connected to TRC.
 * @param  TIM_ICFilter : Specifies the Input Capture Filter.
 *          This parameter must be a value between 0x00 and 0x0F.
 * @retval None
 * @note TIM_ICFilter and TIM_ICPolarity are not used in INDIRECT mode as TI3FP4
 *       (on channel1 path) is used as the input signal. Therefore CCMR2 must be
 *        protected against un-initialized filter and polarity values.
 */
static void TIM_TI3_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                              uint32_t TIM_ICFilter)
{
    uint32_t    tmpccmr2 = 0U;
    uint32_t    tmpccer = 0U;

    /* Disable the Channel 3: Reset the CC3E Bit */
    CLEAR_BIT(TIMx->CCER, TIM_CCER_CC3E);

    tmpccmr2 = READ_REG(TIMx->CCMR2_IN);
    tmpccer  = READ_REG(TIMx->CCER);

    /* Select the Input and filter */
    WRITE_REG_MASK(tmpccmr2,
                   (TIM_CCMR2_IN_CC3S_Msk | TIM_CCMR2_IN_IC3F_Msk),
                    TIM_ICSelection | (TIM_ICFilter << TIM_CCMR2_IN_IC3F_Pos));

    /* Select the Polarity and set the CC3E Bit */
    WRITE_REG_MASK(tmpccer, (TIM_CCER_CC3P_Msk | TIM_CCER_CC3NP_Msk), (TIM_ICPolarity << TIM_CCER_CC3E_Pos));

    /* Write to TIMx CCMR2 and CCER registers */
    WRITE_REG(TIMx->CCMR2_IN, tmpccmr2);
    WRITE_REG(TIMx->CCER, tmpccer);
    return;
}

/**
 * @brief  Configure the TI4 as Input.
 * @param  TIMx to select the TIM peripheral
 * @param  TIM_ICPolarity : The Input Polarity.
 *          This parameter can be one of the following values:
 *            @arg TIM_ICPOLARITY_RISING
 *            @arg TIM_ICPOLARITY_FALLING
 * @param  TIM_ICSelection : specifies the input to be used.
 *          This parameter can be one of the following values:
 *            @arg TIM_ICSELECTION_DIRECTTI:   TIM Input 4 is selected to be connected to IC4.
 *            @arg TIM_ICSELECTION_INDIRECTTI: TIM Input 4 is selected to be connected to IC3.
 *            @arg TIM_ICSELECTION_TRC:        TIM Input 4 is selected to be connected to TRC.
 * @param  TIM_ICFilter : Specifies the Input Capture Filter.
 *          This parameter must be a value between 0x00 and 0x0F.
 * @note TIM_ICFilter and TIM_ICPolarity are not used in INDIRECT mode as TI4FP3
 *       (on channel1 path) is used as the input signal. Therefore CCMR2 must be
 *        protected against un-initialized filter and polarity values.
 * @retval None
 */
static void TIM_TI4_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                              uint32_t TIM_ICFilter)
{
    uint32_t    tmpccmr2 = 0U;
    uint32_t    tmpccer = 0U;

    /* Disable the Channel 4: Reset the CC4E Bit */
    CLEAR_BIT(TIMx->CCER, TIM_CCER_CC4E);

    tmpccmr2 = READ_REG(TIMx->CCMR2_IN);
    tmpccer  = READ_REG(TIMx->CCER);

    /* Select the Input and filter */
    WRITE_REG_MASK(tmpccmr2,
                   (TIM_CCMR2_IN_CC4S_Msk | TIM_CCMR2_IN_IC4F_Msk),
                   ((TIM_ICSelection << TIM_CCMR2_IN_CC4S_Pos) | (TIM_ICFilter << TIM_CCMR2_IN_IC4F_Pos)));

    /* Select the Polarity and set the CC4E Bit */
    WRITE_REG_MASK(tmpccer, TIM_CCER_CC4P_Msk, (TIM_ICPolarity << TIM_CCER_CC4E_Pos));

    /* Write to TIMx CCMR2 and CCER registers */
    WRITE_REG(TIMx->CCMR2_IN, tmpccmr2);
    WRITE_REG(TIMx->CCER, tmpccer);
    return;
}

/**
 * @brief  Selects the Input Trigger source
 * @param  TIMx  to select the TIM peripheral
 * @param  InputTriggerSource : The Input Trigger source.
 *          This parameter can be one of the following values:
 *            @arg TIM_TS_ITR0 : Internal Trigger 0
 *            @arg TIM_TS_ITR1 : Internal Trigger 1
 *            @arg TIM_TS_ITR2 : Internal Trigger 2
 *            @arg TIM_TS_ITR3 : Internal Trigger 3
 *            @arg TIM_TS_TI1F_ED : TI1 Edge Detector
 *            @arg TIM_TS_TI1FP1 : Filtered Timer Input 1
 *            @arg TIM_TS_TI2FP2 : Filtered Timer Input 2
 *            @arg TIM_TS_ETRF : External Trigger input
 * @retval None
 */
static void TIM_ITRx_SetConfig(TIM_TypeDef *TIMx, uint16_t InputTriggerSource)
{
    uint32_t tmpsmcr = 0U;

    /* Get the TIMx SMCR register value */
    tmpsmcr = READ_REG(TIMx->SMCR);

    /* Set the Input Trigger source and the slave mode*/
    WRITE_REG_MASK(tmpsmcr,
                   TIM_SMCR_TS_Msk | TIM_SMCR_SMS_Msk,
                   InputTriggerSource | TIM_SLAVEMODE_EXTERNAL1);

    WRITE_REG(TIMx->SMCR, tmpsmcr);
    return;
}

/**
 * @brief  Configures the TIMx External Trigger (ETR).
 * @param  TIMx  to select the TIM peripheral
 * @param  TIM_ExtTRGPrescaler : The external Trigger Prescaler.
 *          This parameter can be one of the following values:
 *            @arg TIM_ETRPRESCALER_DIV1: ETRP Prescaler OFF.
 *            @arg TIM_ETRPRESCALER_DIV2: ETRP frequency divided by 2.
 *            @arg TIM_ETRPRESCALER_DIV4: ETRP frequency divided by 4.
 *            @arg TIM_ETRPRESCALER_DIV8: ETRP frequency divided by 8.
 * @param  TIM_ExtTRGPolarity : The external Trigger Polarity.
 *          This parameter can be one of the following values:
 *            @arg TIM_ETRPOLARITY_INVERTED: active low or falling edge active.
 *            @arg TIM_ETRPOLARITY_NONINVERTED: active high or rising edge active.
 * @param  ExtTRGFilter : External Trigger Filter.
 *          This parameter must be a value between 0x00 and 0x0F
 * @retval None
 */
static void TIM_ETR_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ExtTRGPrescaler,
                              uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter)
{
    uint32_t tmpsmcr = 0U;

    tmpsmcr = READ_REG(TIMx->SMCR);

    /* Set the Prescaler, the Filter value and the Polarity */
    WRITE_REG_MASK(tmpsmcr,
                   (TIM_SMCR_ETF_Msk | TIM_SMCR_ETPS_Msk | TIM_SMCR_ECE_Msk | TIM_SMCR_ETP_Msk),
                   ((ExtTRGFilter << TIM_SMCR_ETF_Pos) | TIM_ExtTRGPrescaler | TIM_ExtTRGPolarity));

    /* Write to TIMx SMCR */
    WRITE_REG(TIMx->SMCR, tmpsmcr);
    return;
}


/**
 * @brief  Time Base configuration
 * @param  TIMx : TIM periheral
 * @param  pInit : TIM Base configuration structure
 * @retval None
 */
static void TIM_Base_SetConfig(TIM_TypeDef *TIMx, TIM_Base_InitTypeDef *pInit)
{
    uint32_t    tmpcr1 = 0U;

    tmpcr1 = READ_REG(TIMx->CR1);

    /* Set TIM Time Base Unit parameters  */
    if( IS_TIM_COUNTER_MODE_SELECT_INSTANCE(TIMx) )
    {
        /* Select the Counter Mode */
        WRITE_REG_MASK(tmpcr1, TIM_CR1_DIR_Msk | TIM_CR1_CMS_Msk, pInit->CounterMode);
    }

    if( IS_TIM_CLOCK_DIVISION_INSTANCE(TIMx) )
    {
        /* Set the clock division */
        WRITE_REG_MASK(tmpcr1, TIM_CR1_CKD_Msk, (uint32_t)pInit->ClockDivision);
    }

    /* Set the auto-reload preload */
    WRITE_REG_MASK(tmpcr1, TIM_CR1_ARPE_Msk, (uint32_t)pInit->AutoReloadPreload);

    WRITE_REG(TIMx->CR1, tmpcr1);

    /* Set the Autoreload value */
    WRITE_REG_MASK(TIMx->ARR, TIM_ARR_ARR_Msk, (uint32_t)pInit->Period);

    /* Set the Prescaler value */
    WRITE_REG_MASK(TIMx->PSC, TIM_PSC_PSC_Msk, (uint32_t)pInit->Prescaler);

    if( IS_TIM_REPETITION_COUNTER_INSTANCE(TIMx) )
    {
        /* Set the Repetition Counter value */
        WRITE_REG_MASK(TIMx->RCR, TIM_RCR_REP_Msk, pInit->RepetitionCounter);
    }

    /* Generate an update event to reload the Prescaler
       and the repetition counter(only for TIM1) value immediatly */
    SET_BIT(TIMx->EGR, TIM_EGR_UG);
    return;
}


/**
 * @brief  Enables or disables the TIM Capture Compare Channel x.
 * @param  TIMx  to select the TIM peripheral
 * @param  Channel : specifies the TIM Channel
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1
 *            @arg TIM_CHANNEL_2: TIM Channel 2
 *            @arg TIM_CHANNEL_3: TIM Channel 3
 *            @arg TIM_CHANNEL_4: TIM Channel 4
 * @param  ChannelState : specifies the TIM Channel CCxE bit new state.
 *          This parameter can be: TIM_CCx_ENABLE or TIM_CCx_Disable.
 * @retval None
 */
static void TIM_CCxChannelCmd(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ChannelState)
{
    uint32_t    mask = 0U;

    /* Check the parameters */
    assert_param(IS_TIM_CC1_INSTANCE(TIMx));
    assert_param(IS_TIM_CHANNELS(Channel));

    mask = (TIM_CCER_CC1E_Msk << Channel);

    /* Set or reset the CCxE Bit */
    WRITE_REG_MASK(TIMx->CCER, mask, (ChannelState << Channel));

    return;
}

/**
 * @brief  Enables or disables the TIM Capture Compare Channel xN.
 * @param  TIMx  to select the TIM peripheral
 * @param  Channel : specifies the TIM Channel
 *          This parameter can be one of the following values:
 *            @arg TIM_Channel_1: TIM Channel 1
 *            @arg TIM_Channel_2: TIM Channel 2
 *            @arg TIM_Channel_3: TIM Channel 3
 * @param  ChannelNState : specifies the TIM Channel CCxNE bit new state.
 *          This parameter can be: TIM_CCxN_ENABLE or TIM_CCxN_Disable.
 * @retval None
 */
static void TIM_CCxNChannelCmd(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ChannelNState)
{
    uint32_t    mask = 0U;

    mask = (TIM_CCER_CC1NE_Msk << Channel);

    /* Set or reset the CCxNE Bit */
    WRITE_REG_MASK(TIMx->CCER, mask, ChannelNState << Channel);

    return;
}
/**
 * @}
 */


/**
 * @brief  Time Slave configuration
 * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
 *                the configuration information for TIM module.
 * @param  pSlaveConfig: The slave configuration structure
 * @retval None
 */
static void TIM_SlaveTimer_SetConfig(TIM_HandleTypeDef *htim,
                                     TIM_SlaveConfigTypeDef *pSlaveConfig)
{
    uint32_t tmpsmcr = 0U;
    uint32_t tmpccmr1 = 0U;
    uint32_t tmpccer = 0U;

    /* Get the TIMx SMCR register value */
    tmpsmcr = READ_REG(htim->Instance->SMCR);

    /*  Set the Input Trigger source */
    WRITE_REG_MASK(tmpsmcr, TIM_SMCR_TS_Msk, pSlaveConfig->InputTrigger);

    /* Set the slave mode */
    WRITE_REG_MASK(tmpsmcr, TIM_SMCR_SMS_Msk, pSlaveConfig->SlaveMode);

    /* Write to TIMx SMCR */
    WRITE_REG(htim->Instance->SMCR, tmpsmcr);

    /* Configure the trigger prescaler, filter, and polarity */
    switch (pSlaveConfig->InputTrigger)
    {
        case TIM_TS_ETRF:
            {
                /* Check the parameters */
                assert_param(IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(htim->Instance));
                assert_param(IS_TIM_TRIGGERPRESCALER(pSlaveConfig->TriggerPrescaler));
                assert_param(IS_TIM_TRIGGERPOLARITY(pSlaveConfig->TriggerPolarity));
                assert_param(IS_TIM_TRIGGERFILTER(pSlaveConfig->TriggerFilter));
                /* Configure the ETR Trigger source */
                TIM_ETR_SetConfig(htim->Instance,
                                  pSlaveConfig->TriggerPrescaler,
                                  pSlaveConfig->TriggerPolarity,
                                  pSlaveConfig->TriggerFilter);
            }
            break;

        case TIM_TS_TI1F_ED:
            {
                /* Check the parameters */
                assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));
                assert_param(IS_TIM_TRIGGERFILTER(pSlaveConfig->TriggerFilter));

                /* Disable the Channel 1: Reset the CC1E Bit */
                tmpccer  = READ_REG(htim->Instance->CCER);
                tmpccmr1 = READ_REG(htim->Instance->CCMR1_IN);
                CLEAR_BIT(htim->Instance->CCER, TIM_CCER_CC1E);

                /* Set the filter */
                WRITE_REG_MASK(tmpccmr1, TIM_CCMR1_IN_IC1F, (pSlaveConfig->TriggerFilter << TIM_CCMR1_IN_IC1F_Pos));

                /* Write to TIMx CCMR1 and CCER registers */
                WRITE_REG(htim->Instance->CCMR1_IN, tmpccmr1);
                WRITE_REG(htim->Instance->CCER, tmpccer);
            }
            break;

        case TIM_TS_TI1FP1:
            {
                /* Check the parameters */
                assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));
                assert_param(IS_TIM_TRIGGERPOLARITY(pSlaveConfig->TriggerPolarity));
                assert_param(IS_TIM_TRIGGERFILTER(pSlaveConfig->TriggerFilter));

                /* Configure TI1 Filter and Polarity */
                TIM_TI1_ConfigInputStage(htim->Instance,
                                         pSlaveConfig->TriggerPolarity,
                                         pSlaveConfig->TriggerFilter);
            }
            break;

        case TIM_TS_TI2FP2:
            {
                /* Check the parameters */
                assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));
                assert_param(IS_TIM_TRIGGERPOLARITY(pSlaveConfig->TriggerPolarity));
                assert_param(IS_TIM_TRIGGERFILTER(pSlaveConfig->TriggerFilter));

                /* Configure TI2 Filter and Polarity */
                TIM_TI2_ConfigInputStage(htim->Instance,
                                         pSlaveConfig->TriggerPolarity,
                                         pSlaveConfig->TriggerFilter);
            }
            break;

        case TIM_TS_ITR0:
        case TIM_TS_ITR1:
        case TIM_TS_ITR2:
        case TIM_TS_ITR3:
            {
                /* Check the parameter */
                assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));
            }
            break;

        default:
            break;
    }
}


/** @defgroup TIM_Exported_Functions TIM Exported Functions
 * @{
 */

/** @defgroup TIM_Exported_Functions_Group1 Time Base functions
 *  @brief    Time Base functions
 *
 @verbatim
  ==============================================================================
              ##### Time Base functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the TIM base.
    (+) De-initialize the TIM base.
    (+) Start the Time Base.
    (+) Stop the Time Base.
    (+) Start the Time Base and enable interrupt.
    (+) Stop the Time Base and disable interrupt.

 @endverbatim
 * @{
 */

/**
 * @brief  Initializes the TIM Time base Unit according to the specified
 *         parameters in the TIM_HandleTypeDef and create the associated handle.
 * @note Switching from Center Aligned counter mode to Edge counter mode (or reverse)
 *       requires a timer reset to avoid unexpected direction
 *       due to DIR bit readonly in center aligned mode.
 *       Ex: call @ref HAL_TIM_Base_DeInit() before HAL_TIM_Base_Init()
 * @param  htim : TIM Base handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)
{
    /* Check the TIM handle allocation */
    if(htim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_INSTANCE(htim->Instance));
    assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
    assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
    assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));

    if(htim->State == HAL_TIM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        htim->Lock = HAL_UNLOCKED;

        /* Init the low level hardware : GPIO, CLOCK, NVIC */
        HAL_TIM_Base_MspInit(htim);
    }

    /* Set the TIM state */
    htim->State = HAL_TIM_STATE_BUSY;

    /* Set the Time Base configuration */
    TIM_Base_SetConfig(htim->Instance, &htim->Init);

    /* Initialize the TIM state*/
    htim->State = HAL_TIM_STATE_READY;

    return HAL_OK;
}

/**
 * @brief  DeInitializes the TIM Base peripheral
 * @param  htim : TIM Base handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Base_DeInit(TIM_HandleTypeDef *htim)
{
    /* Check the parameters */
    assert_param(IS_TIM_INSTANCE(htim->Instance));

    htim->State = HAL_TIM_STATE_BUSY;

    /* Disable the TIM Peripheral Clock */
    __HAL_TIM_DISABLE(htim);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    HAL_TIM_Base_MspDeInit(htim);

    /* Change TIM state */
    htim->State = HAL_TIM_STATE_RESET;

    /* Release Lock */
    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief  Initializes the TIM Base MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_Base_MspInit could be implemented in the user file
    */
}

/**
 * @brief  DeInitializes TIM Base MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_Base_MspDeInit could be implemented in the user file
    */
}


/**
 * @brief  Starts the TIM Base generation.
 * @param  htim : TIM handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim)
{
    /* Check the parameters */
    assert_param(IS_TIM_INSTANCE(htim->Instance));

    /* Set the TIM state */
    htim->State = HAL_TIM_STATE_BUSY;

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Change the TIM state*/
    htim->State = HAL_TIM_STATE_READY;

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the TIM Base generation.
 * @param  htim : TIM handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim)
{
    /* Check the parameters */
    assert_param(IS_TIM_INSTANCE(htim->Instance));

    /* Set the TIM state */
    htim->State = HAL_TIM_STATE_BUSY;

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Change the TIM state*/
    htim->State = HAL_TIM_STATE_READY;

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Starts the TIM Base generation in interrupt mode.
 * @param  htim : TIM handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim)
{
    /* Check the parameters */
    assert_param(IS_TIM_INSTANCE(htim->Instance));

    /* Enable the TIM Update interrupt */
    __HAL_TIM_ENABLE_IT(htim, TIM_IT_UPDATE);

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the TIM Base generation in interrupt mode.
 * @param  htim : TIM handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim)
{
    /* Check the parameters */
    assert_param(IS_TIM_INSTANCE(htim->Instance));
    /* Disable the TIM Update interrupt */
    __HAL_TIM_DISABLE_IT(htim, TIM_IT_UPDATE);

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}



/**
 * @}
 */

/** @defgroup TIM_Exported_Functions_Group2 Time Output Compare functions
 *  @brief    Time Output Compare functions
 *
 @verbatim
  ==============================================================================
                  ##### Time Output Compare functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the TIM Output Compare.
    (+) De-initialize the TIM Output Compare.
    (+) Start the Time Output Compare.
    (+) Stop the Time Output Compare.
    (+) Start the Time Output Compare and enable interrupt.
    (+) Stop the Time Output Compare and disable interrupt.

 @endverbatim
 * @{
 */

/**
 * @brief  Initializes the TIM Output Compare according to the specified
 *         parameters in the TIM_HandleTypeDef and create the associated handle.
 * @note Switching from Center Aligned counter mode to Edge counter mode (or reverse)
 *       requires a timer reset to avoid unexpected direction
 *       due to DIR bit readonly in center aligned mode.
 *       Ex: call @ref HAL_TIM_OC_DeInit() before HAL_TIM_OC_Init()
 * @param  htim : TIM Output Compare handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_Init(TIM_HandleTypeDef *htim)
{
    /* Check the TIM handle allocation */
    if(htim == NULL)
        return HAL_ERROR;


    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_INSTANCE(htim->Instance));
    assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
    assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
    assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));

    if(htim->State == HAL_TIM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        htim->Lock = HAL_UNLOCKED;

        /* Init the low level hardware : GPIO, CLOCK, NVIC */
        HAL_TIM_OC_MspInit(htim);
    }

    /* Set the TIM state */
    htim->State = HAL_TIM_STATE_BUSY;

    /* Init the base time for the Output Compare */
    TIM_Base_SetConfig(htim->Instance, &htim->Init);

    /* Initialize the TIM state*/
    htim->State = HAL_TIM_STATE_READY;

    return HAL_OK;
}

/**
 * @brief  DeInitializes the TIM peripheral
 * @param  htim : TIM Output Compare handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_DeInit(TIM_HandleTypeDef *htim)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_INSTANCE(htim->Instance));

    htim->State = HAL_TIM_STATE_BUSY;

    /* Disable the TIM Peripheral Clock */
    __HAL_TIM_DISABLE(htim);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC*/
    HAL_TIM_OC_MspDeInit(htim);

    /* Change TIM state */
    htim->State = HAL_TIM_STATE_RESET;

    /* Release Lock */
    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief  Initializes the TIM Output Compare MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_OC_MspInit could be implemented in the user file
    */
}

/**
 * @brief  DeInitializes TIM Output Compare MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_OC_MspDeInit could be implemented in the user file
    */
}

/**
 * @brief  Starts the TIM Output Compare signal generation.
 * @param  htim : TIM Output Compare handle
 * @param  Channel : TIM Channel to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_Start(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Enable the Output compare channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    if(IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Enable the main output */
        __HAL_TIM_MOE_ENABLE(htim);
    }

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the TIM Output Compare signal generation.
 * @param  htim : TIM handle
 * @param  Channel : TIM Channel to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Disable the Output compare channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    if(IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Disable the Main Output */
        __HAL_TIM_MOE_DISABLE(htim);
    }

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Starts the TIM Output Compare signal generation in interrupt mode.
 * @param  htim : TIM OC handle
 * @param  Channel : TIM Channel to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Enable the TIM Capture/Compare channels interrupt */
    switch (Channel)
    {
        case TIM_CHANNEL_1: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1); break;
        case TIM_CHANNEL_2: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2); break;
        case TIM_CHANNEL_3: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC3); break;
        case TIM_CHANNEL_4: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC4); break;
        default:
            return HAL_ERROR;
    }

    /* Enable the Output compare channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    if(IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Enable the main output */
        __HAL_TIM_MOE_ENABLE(htim);
    }

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the TIM Output Compare signal generation in interrupt mode.
 * @param  htim : TIM Output Compare handle
 * @param  Channel : TIM Channel to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Disable the TIM Capture/Compare channels interrupt */
    switch (Channel)
    {
        case TIM_CHANNEL_1: __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1); break;
        case TIM_CHANNEL_2: __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2); break;
        case TIM_CHANNEL_3: __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC3); break;
        case TIM_CHANNEL_4: __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC4); break;
        default:
            return HAL_ERROR;
    }

    /* Disable the Output compare channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    if(IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Disable the Main Output */
        __HAL_TIM_MOE_DISABLE(htim);
    }

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}


/**
 * @}
 */

/** @defgroup TIM_Exported_Functions_Group3 Time PWM functions
 *  @brief    Time PWM functions
 *
 @verbatim
  ==============================================================================
                          ##### Time PWM functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the TIM PWM.
    (+) De-initialize the TIM PWM.
    (+) Start the Time PWM.
    (+) Stop the Time PWM.
    (+) Start the Time PWM and enable interrupt.
    (+) Stop the Time PWM and disable interrupt.
    (+) Start the Complementary PWM.
    (+) Stop the Complementary PWM.
    (+) Start the Complementary PWM and enable interrupts.
    (+) Stop the Complementary PWM and disable interrupts.

 @endverbatim
 * @{
 */

/**
 * @brief  Initializes the TIM PWM Time Base according to the specified
 *         parameters in the TIM_HandleTypeDef and create the associated handle.
 * @note Switching from Center Aligned counter mode to Edge counter mode (or reverse)
 *       requires a timer reset to avoid unexpected direction
 *       due to DIR bit readonly in center aligned mode.
 *       Ex: call @ref HAL_TIM_PWM_DeInit() before HAL_TIM_PWM_Init()
 * @param  htim : TIM handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim)
{
    /* Check the TIM handle allocation */
    if(htim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_INSTANCE(htim->Instance));
    assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
    assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
    assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));

    if(htim->State == HAL_TIM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        htim->Lock = HAL_UNLOCKED;

        /* Init the low level hardware : GPIO, CLOCK, NVIC */
        HAL_TIM_PWM_MspInit(htim);
    }

    /* Set the TIM state */
    htim->State = HAL_TIM_STATE_BUSY;

    /* Init the base time for the PWM */
    TIM_Base_SetConfig(htim->Instance, &htim->Init);

    /* Initialize the TIM state*/
    htim->State = HAL_TIM_STATE_READY;

    return HAL_OK;
}

/**
 * @brief  DeInitializes the TIM peripheral
 * @param  htim : TIM handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_DeInit(TIM_HandleTypeDef *htim)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_INSTANCE(htim->Instance));

    htim->State = HAL_TIM_STATE_BUSY;

    /* Disable the TIM Peripheral Clock */
    __HAL_TIM_DISABLE(htim);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    HAL_TIM_PWM_MspDeInit(htim);

    /* Change TIM state */
    htim->State = HAL_TIM_STATE_RESET;

    /* Release Lock */
    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief  Initializes the TIM PWM MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_PWM_MspInit could be implemented in the user file
    */
}

/**
 * @brief  DeInitializes TIM PWM MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_PWM_MspDeInit could be implemented in the user file
    */
}

/**
 * @brief  Starts the PWM signal generation.
 * @param  htim : TIM handle
 * @param  Channel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Enable the Capture compare channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    if(IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Enable the main output */
        __HAL_TIM_MOE_ENABLE(htim);
    }

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the PWM signal generation.
 * @param  htim : TIM handle
 * @param  Channel : TIM Channels to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Disable the Capture compare channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    if(IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Disable the Main Output */
        __HAL_TIM_MOE_DISABLE(htim);
    }

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Change the htim state */
    htim->State = HAL_TIM_STATE_READY;

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Starts the PWM signal generation in interrupt mode.
 * @param  htim : TIM handle
 * @param  Channel : TIM Channel to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Enable the TIM Capture/Compare 1 interrupt */
    switch( Channel )
    {
        case TIM_CHANNEL_1: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1); break;
        case TIM_CHANNEL_2: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2); break;
        case TIM_CHANNEL_3: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC3); break;
        case TIM_CHANNEL_4: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC4); break;
        default:
            return HAL_ERROR;
    }

    /* Enable the Capture compare channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    if(IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Enable the main output */
        __HAL_TIM_MOE_ENABLE(htim);
    }

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the PWM signal generation in interrupt mode.
 * @param  htim : TIM handle
 * @param  Channel : TIM Channels to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Disable the TIM Capture/Compare channels interrupt */
    switch( Channel )
    {
        case TIM_CHANNEL_1: __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1); break;
        case TIM_CHANNEL_2: __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2); break;
        case TIM_CHANNEL_3: __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC3); break;
        case TIM_CHANNEL_4: __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC4); break;
        default:
            return HAL_ERROR;
    }

    /* Disable the Capture compare channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    if( IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET )
    {
        /* Disable the Main Output */
        __HAL_TIM_MOE_DISABLE(htim);
    }

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}




/**
 * @brief  Starts the PWM signal generation on the complementary output.
 * @param  htim : TIM handle
 * @param  Channel : TIM Channel to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWMN_Start(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CCXN_INSTANCE(htim->Instance, Channel));

    /* Enable the complementary PWM output  */
    TIM_CCxNChannelCmd(htim->Instance, Channel, TIM_CCxN_ENABLE);

    /* Enable the Main Output */
    __HAL_TIM_MOE_ENABLE(htim);

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the PWM signal generation on the complementary output.
 * @param  htim : TIM handle
 * @param  Channel : TIM Channel to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWMN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_TIM_CCXN_INSTANCE(htim->Instance, Channel));

    /* Disable the complementary PWM output  */
    TIM_CCxNChannelCmd(htim->Instance, Channel, TIM_CCxN_DISABLE);

    /* Disable the Main Output */
    __HAL_TIM_MOE_DISABLE(htim);

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Starts the PWM signal generation in interrupt mode on the
 *         complementary output.
 * @param  htim : TIM handle
 * @param  Channel : TIM Channel to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWMN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CCXN_INSTANCE(htim->Instance, Channel));

    /* Enable the TIM Capture/Compare channels interrupt */
    switch( Channel )
    {
        case TIM_CHANNEL_1: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);  break;
        case TIM_CHANNEL_2: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2);  break;
        case TIM_CHANNEL_3: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC3);  break;
        default:
            return HAL_ERROR;
    }

    /* Enable the TIM Break interrupt */
    __HAL_TIM_ENABLE_IT(htim, TIM_IT_BREAK);

    /* Enable the complementary PWM output  */
    TIM_CCxNChannelCmd(htim->Instance, Channel, TIM_CCxN_ENABLE);

    /* Enable the Main Output */
    __HAL_TIM_MOE_ENABLE(htim);

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the PWM signal generation in interrupt mode on the
 *         complementary output.
 * @param  htim : TIM handle
 * @param  Channel : TIM Channel to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWMN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    uint32_t tmpccer = 0U;

    /* Check the parameters */
    assert_param(IS_TIM_CCXN_INSTANCE(htim->Instance, Channel));

    /* Disable the TIM Capture/Compare channels interrupt */
    switch( Channel )
    {
        case TIM_CHANNEL_1: __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1); break;
        case TIM_CHANNEL_2: __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2); break;
        case TIM_CHANNEL_3: __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC3); break;
        default:
            return HAL_ERROR;
    }

    /* Disable the complementary PWM output  */
    TIM_CCxNChannelCmd(htim->Instance, Channel, TIM_CCxN_DISABLE);

    /* Disable the TIM Break interrupt (only if no more channel is active) */
    tmpccer = READ_REG(htim->Instance->CCER);
    if( READ_BIT(tmpccer, (TIM_CCER_CC1NE | TIM_CCER_CC2NE | TIM_CCER_CC3NE)) == RESET)
    {
        __HAL_TIM_DISABLE_IT(htim, TIM_IT_BREAK);
    }

    /* Disable the Main Output */
    __HAL_TIM_MOE_DISABLE(htim);

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}


/**
 * @}
 */

/** @defgroup TIM_Exported_Functions_Group4 Time Input Capture functions
 *  @brief    Time Input Capture functions
 *
 @verbatim
  ==============================================================================
              ##### Time Input Capture functions #####
  ==============================================================================
 [..]
   This section provides functions allowing to:
   (+) Initialize and configure the TIM Input Capture.
   (+) De-initialize the TIM Input Capture.
   (+) Start the Time Input Capture.
   (+) Stop the Time Input Capture.
   (+) Start the Time Input Capture and enable interrupt.
   (+) Stop the Time Input Capture and disable interrupt.


 @endverbatim
 * @{
 */

/**
 * @brief  Initializes the TIM Input Capture Time base according to the specified
 *         parameters in the TIM_HandleTypeDef and create the associated handle.
 * @note Switching from Center Aligned counter mode to Edge counter mode (or reverse)
 *       requires a timer reset to avoid unexpected direction
 *       due to DIR bit readonly in center aligned mode.
 *       Ex: call @ref HAL_TIM_IC_DeInit() before HAL_TIM_IC_Init()
 * @param  htim : TIM Input Capture handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_Init(TIM_HandleTypeDef *htim)
{
    /* Check the TIM handle allocation */
    if(htim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_INSTANCE(htim->Instance));
    assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
    assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
    assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));

    if(htim->State == HAL_TIM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        htim->Lock = HAL_UNLOCKED;

        /* Init the low level hardware : GPIO, CLOCK, NVIC */
        HAL_TIM_IC_MspInit(htim);
    }

    /* Set the TIM state */
    htim->State = HAL_TIM_STATE_BUSY;

    /* Init the base time for the input capture */
    TIM_Base_SetConfig(htim->Instance, &htim->Init);

    /* Initialize the TIM state*/
    htim->State = HAL_TIM_STATE_READY;

    return HAL_OK;
}

/**
 * @brief  DeInitializes the TIM peripheral
 * @param  htim : TIM Input Capture handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_DeInit(TIM_HandleTypeDef *htim)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_INSTANCE(htim->Instance));

    htim->State = HAL_TIM_STATE_BUSY;

    /* Disable the TIM Peripheral Clock */
    __HAL_TIM_DISABLE(htim);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    HAL_TIM_IC_MspDeInit(htim);

    /* Change TIM state */
    htim->State = HAL_TIM_STATE_RESET;

    /* Release Lock */
    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief  Initializes the TIM Input Capture MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_IC_MspInit could be implemented in the user file
    */
}

/**
 * @brief  DeInitializes TIM Input Capture MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_IC_MspDeInit could be implemented in the user file
    */
}

/**
 * @brief  Starts the TIM Input Capture measurement.
 * @param  htim : TIM Input Capture handle
 * @param  Channel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Enable the Input Capture channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the TIM Input Capture measurement.
 * @param  htim : TIM handle
 * @param  Channel : TIM Channels to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Disable the Input Capture channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Starts the TIM Input Capture measurement in interrupt mode.
 * @param  htim : TIM Input Capture handle
 * @param  Channel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Enable the TIM Capture/Compare channels interrupt */
    switch( Channel )
    {
        case TIM_CHANNEL_1: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);  break;
        case TIM_CHANNEL_2: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2);  break;
        case TIM_CHANNEL_3: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC3);  break;
        case TIM_CHANNEL_4: __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC4);  break;
        default:
            return HAL_ERROR;
    }

    /* Enable the Input Capture channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the TIM Input Capture measurement in interrupt mode.
 * @param  htim : TIM handle
 * @param  Channel : TIM Channels to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

    /* Disable the TIM Capture/Compare channels interrupt */
    switch( Channel )
    {
        case TIM_CHANNEL_1:     __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1); break;
        case TIM_CHANNEL_2:     __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2); break;
        case TIM_CHANNEL_3:     __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC3); break;
        case TIM_CHANNEL_4:     __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC4); break;
        default:
            return HAL_ERROR;
    }

    /* Disable the Input Capture channel */
    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}


/**
 * @}
 */

/** @defgroup TIM_Exported_Functions_Group5 Time One Pulse functions
 *  @brief    Time One Pulse functions
 *
 @verbatim
  ==============================================================================
                        ##### Time One Pulse functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the TIM One Pulse.
    (+) De-initialize the TIM One Pulse.
    (+) Start the Time One Pulse.
    (+) Stop the Time One Pulse.
    (+) Start the Time One Pulse and enable interrupt.
    (+) Stop the Time One Pulse and disable interrupt.

 @endverbatim
 * @{
 */

/**
 * @brief  Initializes the TIM One Pulse Time Base according to the specified
 *         parameters in the TIM_HandleTypeDef and create the associated handle.
 * @note Switching from Center Aligned counter mode to Edge counter mode (or reverse)
 *       requires a timer reset to avoid unexpected direction
 *       due to DIR bit readonly in center aligned mode.
 *       Ex: call @ref HAL_TIM_OnePulse_DeInit() before HAL_TIM_OnePulse_Init()
 * @param  htim : TIM OnePulse handle
 * @param  OnePulseMode : Select the One pulse mode.
 *         This parameter can be one of the following values:
 *            @arg TIM_OPMODE_SINGLE: Only one pulse will be generated.
 *            @arg TIM_OPMODE_REPETITIVE: Repetitive pulses wil be generated.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t OnePulseMode)
{
    /* Check the TIM handle allocation */
    if(htim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_INSTANCE(htim->Instance));
    assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
    assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
    assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));
    assert_param(IS_TIM_OPM_MODE(OnePulseMode));

    if(htim->State == HAL_TIM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        htim->Lock = HAL_UNLOCKED;

        /* Init the low level hardware : GPIO, CLOCK, NVIC */
        HAL_TIM_OnePulse_MspInit(htim);
    }

    /* Set the TIM state */
    htim->State = HAL_TIM_STATE_BUSY;

    /* Configure the Time base in the One Pulse Mode */
    TIM_Base_SetConfig(htim->Instance, &htim->Init);

    /* Configure the OPM Mode */
    WRITE_REG_MASK(htim->Instance->CR1, TIM_CR1_OPM_Msk, OnePulseMode);

    /* Initialize the TIM state*/
    htim->State = HAL_TIM_STATE_READY;

    return HAL_OK;
}

/**
 * @brief  DeInitializes the TIM One Pulse
 * @param  htim : TIM One Pulse handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OnePulse_DeInit(TIM_HandleTypeDef *htim)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_INSTANCE(htim->Instance));

    htim->State = HAL_TIM_STATE_BUSY;

    /* Disable the TIM Peripheral Clock */
    __HAL_TIM_DISABLE(htim);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    HAL_TIM_OnePulse_MspDeInit(htim);

    /* Change TIM state */
    htim->State = HAL_TIM_STATE_RESET;

    /* Release Lock */
    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief  Initializes the TIM One Pulse MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_OnePulse_MspInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_OnePulse_MspInit could be implemented in the user file
    */
}

/**
 * @brief  DeInitializes TIM One Pulse MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_OnePulse_MspDeInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_OnePulse_MspDeInit could be implemented in the user file
    */
}

/**
 * @brief  Starts the TIM One Pulse signal generation.
 * @param  htim : TIM One Pulse handle
 * @param  OutputChannel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OnePulse_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel)
{
    /**
     *  Enable the Capture compare and the Input Capture channels
     *  (in the OPM Mode the two possible channels that can be used are TIM_CHANNEL_1 and TIM_CHANNEL_2)
     *  if TIM_CHANNEL_1 is used as output, the TIM_CHANNEL_2 will be used as input and
     *  if TIM_CHANNEL_1 is used as input, the TIM_CHANNEL_2 will be used as output
     *  in all combinations, the TIM_CHANNEL_1 and TIM_CHANNEL_2 should be enabled together
     *
     *  No need to enable the counter, it's enabled automatically by hardware
     *  (the counter starts in response to a stimulus and generate a pulse
     */
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);

    if(IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Enable the main output */
        __HAL_TIM_MOE_ENABLE(htim);
    }

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the TIM One Pulse signal generation.
 * @param  htim : TIM One Pulse handle
 * @param  OutputChannel : TIM Channels to be disable
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel)
{
    /**
     * Disable the Capture compare and the Input Capture channels
     * (in the OPM Mode the two possible channels that can be used are TIM_CHANNEL_1 and TIM_CHANNEL_2)
     * if TIM_CHANNEL_1 is used as output, the TIM_CHANNEL_2 will be used as input and
     * if TIM_CHANNEL_1 is used as input, the TIM_CHANNEL_2 will be used as output
     * in all combinations, the TIM_CHANNEL_1 and TIM_CHANNEL_2 should be disabled together
     */

    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);

    if(IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Disable the Main Output */
        __HAL_TIM_MOE_DISABLE(htim);
    }

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Starts the TIM One Pulse signal generation in interrupt mode.
 * @param  htim : TIM One Pulse handle
 * @param  OutputChannel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OnePulse_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel)
{
    /**
     *  Enable the Capture compare and the Input Capture channels
     *  (in the OPM Mode the two possible channels that can be used are TIM_CHANNEL_1 and TIM_CHANNEL_2)
     *  if TIM_CHANNEL_1 is used as output, the TIM_CHANNEL_2 will be used as input and
     *  if TIM_CHANNEL_1 is used as input, the TIM_CHANNEL_2 will be used as output
     *  in all combinations, the TIM_CHANNEL_1 and TIM_CHANNEL_2 should be enabled together
     *
     *  No need to enable the counter, it's enabled automatically by hardware
     *  (the counter starts in response to a stimulus and generate a pulse
     */

    /* Enable the TIM Capture/Compare 1 interrupt */
    __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);

    /* Enable the TIM Capture/Compare 2 interrupt */
    __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2);

    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);

    if(IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Enable the main output */
        __HAL_TIM_MOE_ENABLE(htim);
    }

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the TIM One Pulse signal generation in interrupt mode.
 * @param  htim : TIM One Pulse handle
 * @param  OutputChannel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel)
{
    /* Disable the TIM Capture/Compare 1 interrupt */
    __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);

    /* Disable the TIM Capture/Compare 2 interrupt */
    __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);

    /**
     *  Disable the Capture compare and the Input Capture channels
     *  (in the OPM Mode the two possible channels that can be used are TIM_CHANNEL_1 and TIM_CHANNEL_2)
     *  if TIM_CHANNEL_1 is used as output, the TIM_CHANNEL_2 will be used as input and
     *  if TIM_CHANNEL_1 is used as input, the TIM_CHANNEL_2 will be used as output
     *  in all combinations, the TIM_CHANNEL_1 and TIM_CHANNEL_2 should be disabled together
     */
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);

    if(IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {
        /* Disable the Main Output */
        __HAL_TIM_MOE_DISABLE(htim);
    }

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @}
 */

/** @defgroup TIM_Exported_Functions_Group6 Time Encoder functions
 *  @brief    Time Encoder functions
 *
 @verbatim
  ==============================================================================
                          ##### Time Encoder functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the TIM Encoder.
    (+) De-initialize the TIM Encoder.
    (+) Start the Time Encoder.
    (+) Stop the Time Encoder.
    (+) Start the Time Encoder and enable interrupt.
    (+) Stop the Time Encoder and disable interrupt.

 @endverbatim
 * @{
 */

/**
 * @brief  Initializes the TIM Encoder Interface and create the associated handle.
 * @note Switching from Center Aligned counter mode to Edge counter mode (or reverse)
 *       requires a timer reset to avoid unexpected direction
 *       due to DIR bit readonly in center aligned mode.
 *       Ex: call @ref HAL_TIM_Encoder_DeInit() before HAL_TIM_Encoder_Init()
 * @param  htim : TIM Encoder Interface handle
 * @param  pConfig : TIM Encoder Interface configuration structure
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Encoder_Init(TIM_HandleTypeDef *htim, TIM_Encoder_InitTypeDef *pConfig)
{
    uint32_t tmpsmcr = 0U;
    uint32_t tmpccmr1 = 0U;
    uint32_t tmpccer = 0U;

    /* Check the TIM handle allocation */
    if(htim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));
    assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
    assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
    assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));
    assert_param(IS_TIM_ENCODER_MODE(pConfig->EncoderMode));
    assert_param(IS_TIM_IC_SELECTION(pConfig->IC1Selection));
    assert_param(IS_TIM_IC_SELECTION(pConfig->IC2Selection));
    assert_param(IS_TIM_IC_POLARITY(pConfig->IC1Polarity));
    assert_param(IS_TIM_IC_POLARITY(pConfig->IC2Polarity));
    assert_param(IS_TIM_IC_PRESCALER(pConfig->IC1Prescaler));
    assert_param(IS_TIM_IC_PRESCALER(pConfig->IC2Prescaler));
    assert_param(IS_TIM_IC_FILTER(pConfig->IC1Filter));
    assert_param(IS_TIM_IC_FILTER(pConfig->IC2Filter));

    if(htim->State == HAL_TIM_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        htim->Lock = HAL_UNLOCKED;

        /* Init the low level hardware : GPIO, CLOCK, NVIC */
        HAL_TIM_Encoder_MspInit(htim);
    }

    /* Set the TIM state */
    htim->State = HAL_TIM_STATE_BUSY;

    /* Reset the SMS bits */
    CLEAR_BIT(htim->Instance->SMCR, TIM_SMCR_SMS);

    /* Configure the Time base in the Encoder Mode */
    TIM_Base_SetConfig(htim->Instance, &htim->Init);

    /* Get the TIMx SMCR/CCMR1/CCER register value */
    tmpsmcr  = READ_REG(htim->Instance->SMCR);
    tmpccmr1 = READ_REG(htim->Instance->CCMR1_IN);
    tmpccer  = READ_REG(htim->Instance->CCER);

    /* Set the encoder Mode */
    WRITE_REG_MASK(tmpsmcr, TIM_SMCR_SMS_Msk, pConfig->EncoderMode);

    /* Select the Capture Compare 1 and the Capture Compare 2 as input */
    WRITE_REG_MASK(tmpccmr1,
                   TIM_CCMR1_IN_CC1S_Msk | TIM_CCMR1_IN_CC2S_Msk,
                   pConfig->IC1Selection | (pConfig->IC2Selection << 8U));

    /* Set the the Capture Compare 1 and the Capture Compare 2 prescalers and filters */
    WRITE_REG_MASK(tmpccmr1,
                   TIM_CCMR1_IN_IC1PSC | TIM_CCMR1_IN_IC2PSC | TIM_CCMR1_IN_IC1F | TIM_CCMR1_IN_IC2F,
                   pConfig->IC1Prescaler | (pConfig->IC2Prescaler << 8U) |
                   (pConfig->IC1Filter << 4U) | (pConfig->IC2Filter << 12U));

    /* Set the TI1 and the TI2 Polarities */
    WRITE_REG_MASK(tmpccer,
                   TIM_CCER_CC1P | TIM_CCER_CC2P | TIM_CCER_CC1NP | TIM_CCER_CC2NP,
                   pConfig->IC1Polarity | (pConfig->IC2Polarity << 4U));

    /* Write to TIMx SMCR/CCMR1/CCER */
    WRITE_REG(htim->Instance->SMCR, tmpsmcr);
    WRITE_REG(htim->Instance->CCMR1_IN, tmpccmr1);
    WRITE_REG(htim->Instance->CCER, tmpccer);

    /* Initialize the TIM state*/
    htim->State = HAL_TIM_STATE_READY;

    return HAL_OK;
}


/**
 * @brief  DeInitializes the TIM Encoder interface
 * @param  htim : TIM Encoder handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Encoder_DeInit(TIM_HandleTypeDef *htim)
{
    /* Check the parameters */
    assert_param(IS_TIM_INSTANCE(htim->Instance));

    htim->State = HAL_TIM_STATE_BUSY;

    /* Disable the TIM Peripheral Clock */
    __HAL_TIM_DISABLE(htim);

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    HAL_TIM_Encoder_MspDeInit(htim);

    /* Change TIM state */
    htim->State = HAL_TIM_STATE_RESET;

    /* Release Lock */
    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief  Initializes the TIM Encoder Interface MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_Encoder_MspInit could be implemented in the user file
    */
}

/**
 * @brief  DeInitializes TIM Encoder Interface MSP.
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_Encoder_MspDeInit could be implemented in the user file
    */
}

/**
 * @brief  Starts the TIM Encoder Interface.
 * @param  htim : TIM Encoder Interface handle
 * @param  Channel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_ALL: TIM Channel 1 and TIM Channel 2 are selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Encoder_Start(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

    /* Enable the encoder interface channels */
    switch (Channel)
    {
        case TIM_CHANNEL_1:
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
            break;
        case TIM_CHANNEL_2:
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
            break;

        case TIM_CHANNEL_ALL:
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
            break;
        default :
            return HAL_ERROR;
    }

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the TIM Encoder Interface.
 * @param  htim : TIM Encoder Interface handle
 * @param  Channel : TIM Channels to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_ALL: TIM Channel 1 and TIM Channel 2 are selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Encoder_Stop(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

    /* Disable the Input Capture channels 1 and 2
     (in the EncoderInterface the two possible channels that can be used are TIM_CHANNEL_1 and TIM_CHANNEL_2) */
    switch (Channel)
    {
        case TIM_CHANNEL_1:
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
            break;
        case TIM_CHANNEL_2:
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);
            break;

        case TIM_CHANNEL_ALL:
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);
            break;
        default :
            return HAL_ERROR;
    }

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Starts the TIM Encoder Interface in interrupt mode.
 * @param  htim : TIM Encoder Interface handle
 * @param  Channel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_ALL: TIM Channel 1 and TIM Channel 2 are selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Encoder_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

    /**
     *  Enable the encoder interface channels
     *  Enable the capture compare Interrupts 1 and/or 2
     */
    switch (Channel)
    {
        case TIM_CHANNEL_1:
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
            __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);
            break;

        case TIM_CHANNEL_2:
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
            __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2);
            break;

        case TIM_CHANNEL_ALL:
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
            TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
            __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);
            __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2);
            break;

        default:
            return HAL_ERROR;
    }

    /* Enable the Peripheral */
    __HAL_TIM_ENABLE(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Stops the TIM Encoder Interface in interrupt mode.
 * @param  htim : TIM Encoder Interface handle
 * @param  Channel : TIM Channels to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_ALL: TIM Channel 1 and TIM Channel 2 are selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

    /**
     * Disable the Input Capture channels 1 and 2
     * (in the EncoderInterface the two possible channels that can be used are TIM_CHANNEL_1 and TIM_CHANNEL_2)
     */
    if( Channel == TIM_CHANNEL_1 )
    {
        TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);

        /* Disable the capture compare Interrupts 1 */
        __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);
    }
    else if( Channel == TIM_CHANNEL_2 )
    {
        TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);

        /* Disable the capture compare Interrupts 2 */
        __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);
    }
    else if( Channel == TIM_CHANNEL_ALL )
    {
        TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
        TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);

        /* Disable the capture compare Interrupts 1 and 2 */
        __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);
        __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);
    }
    else
    {
        return HAL_ERROR;
    }

    /* Disable the Peripheral */
    __HAL_TIM_DISABLE(htim);

    /* Return function status */
    return HAL_OK;
}


/**
 * @}
 */

/** @defgroup TIM_Exported_Functions_Group7 TIM IRQ handler management
 *  @brief    IRQ handler management
 *
 @verbatim
  ==============================================================================
                        ##### IRQ handler management #####
  ==============================================================================
  [..]
    This section provides Timer IRQ handler function.

 @endverbatim
 * @{
 */

/**
 * @brief  This function handles TIM interrupts requests.
 * @param  htim : TIM  handle
 * @retval None
 */
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)
{
    /* Capture compare 1 event */
    if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
        {
            __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
            htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;

            if( READ_BIT(htim->Instance->CCMR1_IN, TIM_CCMR1_IN_CC1S) != 0x00U )
            {
                /* Input capture event */
                HAL_TIM_IC_CaptureCallback(htim);
            }
            else
            {
                /* Output compare event */
                HAL_TIM_OC_DelayElapsedCallback(htim);
                HAL_TIM_PWM_PulseFinishedCallback(htim);
            }

            htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
        }
    }

    /* Capture compare 2 event */
    if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
        {
            __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
            htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;

            if( READ_BIT(htim->Instance->CCMR1_IN, TIM_CCMR1_IN_CC2S) != 0x00U )
            {
                /* Input capture event */
                HAL_TIM_IC_CaptureCallback(htim);
            }
            else
            {
                /* Output compare event */
                HAL_TIM_OC_DelayElapsedCallback(htim);
                HAL_TIM_PWM_PulseFinishedCallback(htim);
            }

            htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
        }
    }

    /* Capture compare 3 event */
    if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
        {
            __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
            htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;

            if( READ_BIT(htim->Instance->CCMR2_IN, TIM_CCMR2_IN_CC3S) != 0x00U )
            {
                /* Input capture event */
                HAL_TIM_IC_CaptureCallback(htim);
            }
            else
            {
                /* Output compare event */
                HAL_TIM_OC_DelayElapsedCallback(htim);
                HAL_TIM_PWM_PulseFinishedCallback(htim);
            }

            htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
        }
    }

    /* Capture compare 4 event */
    if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
        {
            __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
            htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;

            if( READ_BIT(htim->Instance->CCMR2_IN, TIM_CCMR2_IN_CC4S) != 0x00U )
            {
                /* Input capture event */
                HAL_TIM_IC_CaptureCallback(htim);
            }
            else
            {
                /* Output compare event */
                HAL_TIM_OC_DelayElapsedCallback(htim);
                HAL_TIM_PWM_PulseFinishedCallback(htim);
            }

            htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
        }
    }

    /* TIM Update event */
    if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_UPDATE) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_UPDATE) != RESET)
        {
            __HAL_TIM_CLEAR_IT(htim, TIM_IT_UPDATE);
            HAL_TIM_PeriodElapsedCallback(htim);
        }
    }

    /* TIM Break input event */
    if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_BREAK) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_BREAK) != RESET)
        {
            __HAL_TIM_CLEAR_IT(htim, TIM_IT_BREAK);
            HAL_TIM_BreakCallback(htim);
        }
    }

    /* TIM Trigger detection event */
    if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_TRIGGER) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_TRIGGER) != RESET)
        {
            __HAL_TIM_CLEAR_IT(htim, TIM_IT_TRIGGER);
            HAL_TIM_TriggerCallback(htim);
        }
    }

    /* TIM commutation event */
    if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_COM) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_COM) != RESET)
        {
            __HAL_TIM_CLEAR_IT(htim, TIM_FLAG_COM);
            HAL_TIM_CommutationCallback(htim);
        }
    }

    return;
}

/**
 * @}
 */

/** @defgroup TIM_Exported_Functions_Group8 Peripheral Control functions
 *  @brief      Peripheral Control functions
 *
 @verbatim
  ==============================================================================
                   ##### Peripheral Control functions #####
  ==============================================================================
 [..]
   This section provides functions allowing to:
      (+) Configure The Input Output channels for OC, PWM, IC or One Pulse mode.
      (+) Configure External Clock source.
      (+) Configure Complementary channels, break features and dead time.
      (+) Configure Master and the Slave synchronization.

 @endverbatim
 * @{
 */

/**
 * @brief  Initializes the TIM Output Compare Channels according to the specified
 *         parameters in the TIM_OC_InitTypeDef.
 * @param  htim : TIM Output Compare handle
 * @param  pConfig : TIM Output Compare configuration structure
 * @param  Channel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *pConfig, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CHANNELS(Channel));
    assert_param(IS_TIM_OC_MODE(pConfig->OCMode));
    assert_param(IS_TIM_OC_POLARITY(pConfig->OCPolarity));

    /* Check input state */
    __HAL_LOCK(htim);

    htim->State = HAL_TIM_STATE_BUSY;

    switch (Channel)
    {
        case TIM_CHANNEL_1:
            {
                assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));
                /* Configure the TIM Channel 1 in Output Compare */
                TIM_OC1_SetConfig(htim->Instance, pConfig);
            }
            break;

        case TIM_CHANNEL_2:
            {
                assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));
                /* Configure the TIM Channel 2 in Output Compare */
                TIM_OC2_SetConfig(htim->Instance, pConfig);
            }
            break;

        case TIM_CHANNEL_3:
            {
                assert_param(IS_TIM_CC3_INSTANCE(htim->Instance));
                /* Configure the TIM Channel 3 in Output Compare */
                TIM_OC3_SetConfig(htim->Instance, pConfig);
            }
            break;

        case TIM_CHANNEL_4:
            {
                assert_param(IS_TIM_CC4_INSTANCE(htim->Instance));
                /* Configure the TIM Channel 4 in Output Compare */
                TIM_OC4_SetConfig(htim->Instance, pConfig);
            }
            break;

        default:
            return HAL_ERROR;
    }
    htim->State = HAL_TIM_STATE_READY;

    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief  Initializes the TIM Input Capture Channels according to the specified
 *         parameters in the TIM_IC_InitTypeDef.
 * @param  htim : TIM IC handle
 * @param  pConfig : TIM Input Capture configuration structure
 * @param  Channel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_IC_InitTypeDef *pConfig, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));
    assert_param(IS_TIM_IC_POLARITY(pConfig->ICPolarity));
    assert_param(IS_TIM_IC_SELECTION(pConfig->ICSelection));
    assert_param(IS_TIM_IC_PRESCALER(pConfig->ICPrescaler));
    assert_param(IS_TIM_IC_FILTER(pConfig->ICFilter));

    __HAL_LOCK(htim);

    htim->State = HAL_TIM_STATE_BUSY;

    if (Channel == TIM_CHANNEL_1)
    {
        /* TI1 Configuration */
        TIM_TI1_SetConfig(htim->Instance,
                          pConfig->ICPolarity,
                          pConfig->ICSelection,
                          pConfig->ICFilter);

        /* Set the IC1PSC value */
        WRITE_REG_MASK(htim->Instance->CCMR1_IN,
                       TIM_CCMR1_IN_IC1PSC_Msk,
                       (pConfig->ICPrescaler << TIM_CCMR1_IN_IC1PSC_Pos));
    }
    else if (Channel == TIM_CHANNEL_2)
    {
        /* TI2 Configuration */
        assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

        TIM_TI2_SetConfig(htim->Instance,
                          pConfig->ICPolarity,
                          pConfig->ICSelection,
                          pConfig->ICFilter);

        /* Set the IC2PSC value */
        WRITE_REG_MASK(htim->Instance->CCMR1_IN,
                       TIM_CCMR1_IN_IC2PSC_Msk,
                       (pConfig->ICPrescaler << TIM_CCMR1_IN_IC2PSC_Pos));
    }
    else if (Channel == TIM_CHANNEL_3)
    {
        /* TI3 Configuration */
        assert_param(IS_TIM_CC3_INSTANCE(htim->Instance));

        TIM_TI3_SetConfig(htim->Instance,
                          pConfig->ICPolarity,
                          pConfig->ICSelection,
                          pConfig->ICFilter);

        /* Set the IC3PSC value */
        WRITE_REG_MASK(htim->Instance->CCMR2_IN,
                       TIM_CCMR2_IN_IC3PSC_Msk,
                       pConfig->ICPrescaler << TIM_CCMR2_IN_IC3PSC_Pos);
    }
    else if( Channel == TIM_CHANNEL_4 )
    {
        /* TI4 Configuration */
        assert_param(IS_TIM_CC4_INSTANCE(htim->Instance));

        TIM_TI4_SetConfig(htim->Instance,
                          pConfig->ICPolarity,
                          pConfig->ICSelection,
                          pConfig->ICFilter);

        /* Set the IC4PSC value */
        WRITE_REG_MASK(htim->Instance->CCMR2_IN,
                       TIM_CCMR2_IN_IC4PSC_Msk,
                       pConfig->ICPrescaler << TIM_CCMR2_IN_IC4PSC_Pos);
    }
    else
        return HAL_ERROR;

    htim->State = HAL_TIM_STATE_READY;

    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief  Initializes the TIM PWM  channels according to the specified
 *         parameters in the TIM_OC_InitTypeDef.
 * @param  htim : TIM handle
 * @param  pConfig : TIM PWM configuration structure
 * @param  Channel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *pConfig, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_CHANNELS(Channel));
    assert_param(IS_TIM_PWM_MODE(pConfig->OCMode));
    assert_param(IS_TIM_OC_POLARITY(pConfig->OCPolarity));
    assert_param(IS_TIM_FAST_STATE(pConfig->OCFastMode));

    __HAL_LOCK(htim);

    htim->State = HAL_TIM_STATE_BUSY;

    switch (Channel)
    {
        case TIM_CHANNEL_1:
            {
                assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));
                /* Configure the Channel 1 in PWM mode */
                TIM_OC1_SetConfig(htim->Instance, pConfig);

                /**
                 *  Set the Preload enable bit
                 *  and Configure the Output Fast mode for channel 1
                 */
                WRITE_REG_MASK(htim->Instance->CCMR1_OUT,
                               TIM_CCMR1_OUT_OC1PE_Msk | TIM_CCMR1_OUT_OC1FE_Msk,
                               TIM_CCMR1_OUT_OC1PE | pConfig->OCFastMode);
            }
            break;

        case TIM_CHANNEL_2:
            {
                assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));
                /* Configure the Channel 2 in PWM mode */
                TIM_OC2_SetConfig(htim->Instance, pConfig);

                /**
                 *  Set the Preload enable bit
                 *  and Configure the Output Fast mode for channel 2
                 */
                WRITE_REG_MASK(htim->Instance->CCMR1_OUT,
                               TIM_CCMR1_OUT_OC2PE_Msk | TIM_CCMR1_OUT_OC2FE_Msk,
                               TIM_CCMR1_OUT_OC2PE | (pConfig->OCFastMode << 8));
            }
            break;

        case TIM_CHANNEL_3:
            {
                assert_param(IS_TIM_CC3_INSTANCE(htim->Instance));
                /* Configure the Channel 3 in PWM mode */
                TIM_OC3_SetConfig(htim->Instance, pConfig);

                /**
                 *  Set the Preload enable bit
                 *  and Configure the Output Fast mode for channel 3
                 */
                WRITE_REG_MASK(htim->Instance->CCMR2_OUT,
                               TIM_CCMR2_OUT_OC3PE_Msk | TIM_CCMR2_OUT_OC3FE_Msk,
                               TIM_CCMR2_OUT_OC3PE | (pConfig->OCFastMode));
            }
            break;

        case TIM_CHANNEL_4:
            {
                assert_param(IS_TIM_CC4_INSTANCE(htim->Instance));
                /* Configure the Channel 4 in PWM mode */
                TIM_OC4_SetConfig(htim->Instance, pConfig);

                /**
                 *  Set the Preload enable bit
                 *  and Configure the Output Fast mode for channel 4
                 */
                WRITE_REG_MASK(htim->Instance->CCMR2_OUT,
                               TIM_CCMR2_OUT_OC4PE_Msk | TIM_CCMR2_OUT_OC4FE_Msk,
                               TIM_CCMR2_OUT_OC4PE | (pConfig->OCFastMode << 8));
            }
            break;

        default:
            return HAL_ERROR;
    }

    htim->State = HAL_TIM_STATE_READY;

    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief  Initializes the TIM One Pulse Channels according to the specified
 *         parameters in the TIM_OnePulse_InitTypeDef.
 * @param  htim : TIM One Pulse handle
 * @param  pConfig : TIM One Pulse configuration structure
 * @param  OutputChannel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 * @param  InputChannel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OnePulse_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OnePulse_InitTypeDef *pConfig,
                                                 uint32_t OutputChannel, uint32_t InputChannel)
{
    TIM_OC_InitTypeDef temp1;

    /* Check the parameters */
    assert_param(IS_TIM_OPM_CHANNELS(OutputChannel));
    assert_param(IS_TIM_OPM_CHANNELS(InputChannel));

    if( OutputChannel == InputChannel )
        return HAL_ERROR;

    __HAL_LOCK(htim);

    htim->State = HAL_TIM_STATE_BUSY;

    /* Extract the Ouput compare configuration from pConfig structure */
    temp1.OCMode       = pConfig->OCMode;
    temp1.Pulse        = pConfig->Pulse;
    temp1.OCPolarity   = pConfig->OCPolarity;
    temp1.OCNPolarity  = pConfig->OCNPolarity;
    temp1.OCIdleState  = pConfig->OCIdleState;
    temp1.OCNIdleState = pConfig->OCNIdleState;

    switch (OutputChannel)
    {
        case TIM_CHANNEL_1:
            {
                assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));

                TIM_OC1_SetConfig(htim->Instance, &temp1);
            }
            break;
        case TIM_CHANNEL_2:
            {
                assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

                TIM_OC2_SetConfig(htim->Instance, &temp1);
            }
            break;
        default:
            return HAL_ERROR;
    }

    switch (InputChannel)
    {
        case TIM_CHANNEL_1:
            {
                assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));

                TIM_TI1_SetConfig(htim->Instance, pConfig->ICPolarity,
                                  pConfig->ICSelection, pConfig->ICFilter);

                /* Reset the IC1PSC Bits */
                CLEAR_BIT(htim->Instance->CCMR1_IN, TIM_CCMR1_IN_IC1PSC);

                /* Select the Trigger source and the Slave Mode */
                WRITE_REG_MASK(htim->Instance->SMCR,
                               TIM_SMCR_TS_Msk | TIM_SMCR_SMS_Msk,
                               TIM_TS_TI1FP1 | TIM_SLAVEMODE_TRIGGER);
            }
            break;
        case TIM_CHANNEL_2:
            {
                assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

                TIM_TI2_SetConfig(htim->Instance, pConfig->ICPolarity,
                                  pConfig->ICSelection, pConfig->ICFilter);

                /* Reset the IC2PSC Bits */
                CLEAR_BIT(htim->Instance->CCMR1_IN, TIM_CCMR1_IN_IC2PSC);

                /* Select the Trigger source and the Slave Mode */
                WRITE_REG_MASK(htim->Instance->SMCR,
                               TIM_SMCR_TS_Msk | TIM_SMCR_SMS_Msk,
                               TIM_TS_TI2FP2 | TIM_SLAVEMODE_TRIGGER);
            }
            break;

        default:
            return HAL_ERROR;
    }

    htim->State = HAL_TIM_STATE_READY;

    __HAL_UNLOCK(htim);

    return HAL_OK;
}



/**
 * @brief  Generate a software event
 * @param  htim : TIM handle
 * @param  EventSource : specifies the event source.
 *          This parameter can be one of the following values:
 *            @arg TIM_EVENTSOURCE_UPDATE: Timer update Event source
 *            @arg TIM_EVENTSOURCE_CC1: Timer Capture Compare 1 Event source
 *            @arg TIM_EVENTSOURCE_CC2: Timer Capture Compare 2 Event source
 *            @arg TIM_EVENTSOURCE_CC3: Timer Capture Compare 3 Event source
 *            @arg TIM_EVENTSOURCE_CC4: Timer Capture Compare 4 Event source
 *            @arg TIM_EVENTSOURCE_COM: Timer COM event source
 *            @arg TIM_EVENTSOURCE_TRIGGER: Timer Trigger Event source
 *            @arg TIM_EVENTSOURCE_BREAK: Timer Break event source
 * @note TIM6 and TIM7 can only generate an update event.
 * @note TIM_EVENTSOURCE_COM and TIM_EVENTSOURCE_BREAK are used only with TIM1, TIM15, TIM16 and TIM17.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_INSTANCE(htim->Instance));
    assert_param(IS_TIM_EVENT_SOURCE(EventSource));

    /* Process Locked */
    __HAL_LOCK(htim);

    /* Change the TIM state */
    htim->State = HAL_TIM_STATE_BUSY;

    /* Set the event sources */
    SET_BIT(htim->Instance->EGR, EventSource);

    /* Change the TIM state */
    htim->State = HAL_TIM_STATE_READY;

    __HAL_UNLOCK(htim);

    /* Return function status */
    return HAL_OK;
}

/**
 * @brief  Configures the OCRef clear feature
 * @param  htim : TIM handle
 * @param  pClearInputConfig : pointer to a TIM_ClearInputConfigTypeDef structure that
 *         contains the OCREF clear feature and parameters for the TIM peripheral.
 * @param  Channel : specifies the TIM Channel
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1
 *            @arg TIM_CHANNEL_2: TIM Channel 2
 *            @arg TIM_CHANNEL_3: TIM Channel 3
 *            @arg TIM_CHANNEL_4: TIM Channel 4
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_ConfigOCrefClear(TIM_HandleTypeDef *htim,
                                           TIM_ClearInputConfigTypeDef *pClearInputConfig, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_OCXREF_CLEAR_INSTANCE(htim->Instance));
    assert_param(IS_TIM_CLEARINPUT_SOURCE(pClearInputConfig->ClearInputSource));
    assert_param(IS_TIM_CLEARINPUT_POLARITY(pClearInputConfig->ClearInputPolarity));
    assert_param(IS_TIM_CLEARINPUT_PRESCALER(pClearInputConfig->ClearInputPrescaler));
    assert_param(IS_TIM_CLEARINPUT_FILTER(pClearInputConfig->ClearInputFilter));

    /* Process Locked */
    __HAL_LOCK(htim);

    htim->State = HAL_TIM_STATE_BUSY;

    switch( pClearInputConfig->ClearInputSource )
    {
        case TIM_CLEARINPUTSOURCE_NONE:
            {
                /* Clear the ETR Bits */
                CLEAR_BIT(htim->Instance->SMCR, (TIM_SMCR_ETF | TIM_SMCR_ETPS | TIM_SMCR_ECE | TIM_SMCR_ETP));
            }
            break;

        case TIM_CLEARINPUTSOURCE_ETR:
            {
                TIM_ETR_SetConfig(htim->Instance,
                                  pClearInputConfig->ClearInputPrescaler,
                                  pClearInputConfig->ClearInputPolarity,
                                  pClearInputConfig->ClearInputFilter);

            }
            break;
        default:
            return HAL_ERROR;
    }

    switch (Channel)
    {
        case TIM_CHANNEL_1:
            {
                /* Enable/Disable the OC ref clear feature for Channel 1 */
                if(pClearInputConfig->ClearInputState != DISABLE)
                    SET_BIT(htim->Instance->CCMR1_OUT, TIM_CCMR1_OUT_OC1CE);
                else
                    CLEAR_BIT(htim->Instance->CCMR1_OUT, TIM_CCMR1_OUT_OC1CE);
            }
            break;
        case TIM_CHANNEL_2:
            {
                assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

                /* Enable/Disable the OC ref clear feature for Channel 2 */
                if(pClearInputConfig->ClearInputState != DISABLE)
                    SET_BIT(htim->Instance->CCMR1_OUT, TIM_CCMR1_OUT_OC2CE);
                else
                    CLEAR_BIT(htim->Instance->CCMR1_OUT, TIM_CCMR1_OUT_OC2CE);
            }
            break;
        case TIM_CHANNEL_3:
            {
                assert_param(IS_TIM_CC3_INSTANCE(htim->Instance));

                /* Enable/Disable the OC ref clear feature for Channel 3 */
                if(pClearInputConfig->ClearInputState != DISABLE)
                    SET_BIT(htim->Instance->CCMR2_OUT, TIM_CCMR2_OUT_OC3CE);
                else
                    CLEAR_BIT(htim->Instance->CCMR2_OUT, TIM_CCMR2_OUT_OC3CE);
            }
            break;
        case TIM_CHANNEL_4:
            {
                assert_param(IS_TIM_CC4_INSTANCE(htim->Instance));

                /* Enable/Disable the OC ref clear feature for Channel 3 */
                if(pClearInputConfig->ClearInputState != DISABLE)
                    SET_BIT(htim->Instance->CCMR2_OUT, TIM_CCMR2_OUT_OC4CE);
                else
                    CLEAR_BIT(htim->Instance->CCMR2_OUT, TIM_CCMR2_OUT_OC4CE);
            }
            break;

        default:
            return HAL_ERROR;
    }

    htim->State = HAL_TIM_STATE_READY;

    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief   Configures the clock source to be used
 * @param  htim : TIM handle
 * @param  pClockSourceConfig : pointer to a TIM_ClockConfigTypeDef structure that
 *         contains the clock source information for the TIM peripheral.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef *pClockSourceConfig)
{
    /* Process Locked */
    __HAL_LOCK(htim);

    htim->State = HAL_TIM_STATE_BUSY;

    /* Check the parameters */
    assert_param(IS_TIM_CLOCKSOURCE(pClockSourceConfig->ClockSource));

    /* Reset the SMS, TS, ECE, ETPS and ETRF bits */
    CLEAR_BIT(htim->Instance->SMCR,
              TIM_SMCR_SMS_Msk | TIM_SMCR_TS_Msk |
              TIM_SMCR_ETF_Msk | TIM_SMCR_ETPS_Msk | TIM_SMCR_ECE_Msk | TIM_SMCR_ETP_Msk);

    switch( pClockSourceConfig->ClockSource )
    {
        case TIM_CLOCKSOURCE_INTERNAL:
            {
                assert_param(IS_TIM_INSTANCE(htim->Instance));
                /* Disable slave mode to clock the prescaler directly with the internal clock */
                CLEAR_BIT(htim->Instance->SMCR, TIM_SMCR_SMS);
            }
            break;

        case TIM_CLOCKSOURCE_ETRMODE1:
            {
                /* Check whether or not the timer instance supports external trigger input mode 1 (ETRF)*/
                assert_param(IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(htim->Instance));

                /* Check ETR input conditioning related parameters */
                assert_param(IS_TIM_CLOCKPRESCALER(pClockSourceConfig->ClockPrescaler));
                assert_param(IS_TIM_CLOCKPOLARITY(pClockSourceConfig->ClockPolarity));
                assert_param(IS_TIM_CLOCKFILTER(pClockSourceConfig->ClockFilter));

                /* Configure the ETR Clock source */
                TIM_ETR_SetConfig(htim->Instance,
                                  pClockSourceConfig->ClockPrescaler,
                                  pClockSourceConfig->ClockPolarity,
                                  pClockSourceConfig->ClockFilter);

                WRITE_REG_MASK(htim->Instance->SMCR,
                               TIM_SMCR_SMS_Msk | TIM_SMCR_TS_Msk,
                               TIM_SLAVEMODE_EXTERNAL1 | TIM_CLOCKSOURCE_ETRMODE1);
            }
            break;

        case TIM_CLOCKSOURCE_ETRMODE2:
            {
                /* Check whether or not the timer instance supports external trigger input mode 2 (ETRF)*/
                assert_param(IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(htim->Instance));

                /* Check ETR input conditioning related parameters */
                assert_param(IS_TIM_CLOCKPRESCALER(pClockSourceConfig->ClockPrescaler));
                assert_param(IS_TIM_CLOCKPOLARITY(pClockSourceConfig->ClockPolarity));
                assert_param(IS_TIM_CLOCKFILTER(pClockSourceConfig->ClockFilter));

                /* Configure the ETR Clock source */
                TIM_ETR_SetConfig(htim->Instance,
                                  pClockSourceConfig->ClockPrescaler,
                                  pClockSourceConfig->ClockPolarity,
                                  pClockSourceConfig->ClockFilter);

                /* Enable the External clock mode2 */
                SET_BIT(htim->Instance->SMCR, TIM_SMCR_ECE);
            }
            break;

        case TIM_CLOCKSOURCE_TI1:
            {
                /* Check whether or not the timer instance supports external clock mode 1 */
                assert_param(IS_TIM_CLOCKSOURCE_TIX_INSTANCE(htim->Instance));

                /* Check TI1 input conditioning related parameters */
                assert_param(IS_TIM_CLOCKPOLARITY(pClockSourceConfig->ClockPolarity));
                assert_param(IS_TIM_CLOCKFILTER(pClockSourceConfig->ClockFilter));

                TIM_TI1_ConfigInputStage(htim->Instance,
                                         pClockSourceConfig->ClockPolarity,
                                         pClockSourceConfig->ClockFilter);

                TIM_ITRx_SetConfig(htim->Instance, TIM_CLOCKSOURCE_TI1);
            }
            break;
        case TIM_CLOCKSOURCE_TI2:
            {
                /* Check whether or not the timer instance supports external clock mode 1 (ETRF)*/
                assert_param(IS_TIM_CLOCKSOURCE_TIX_INSTANCE(htim->Instance));

                /* Check TI2 input conditioning related parameters */
                assert_param(IS_TIM_CLOCKPOLARITY(pClockSourceConfig->ClockPolarity));
                assert_param(IS_TIM_CLOCKFILTER(pClockSourceConfig->ClockFilter));

                TIM_TI2_ConfigInputStage(htim->Instance,
                                         pClockSourceConfig->ClockPolarity,
                                         pClockSourceConfig->ClockFilter);

                TIM_ITRx_SetConfig(htim->Instance, TIM_CLOCKSOURCE_TI2);
            }
            break;
        case TIM_CLOCKSOURCE_TI1ED:
            {
                /* Check whether or not the timer instance supports external clock mode 1 */
                assert_param(IS_TIM_CLOCKSOURCE_TIX_INSTANCE(htim->Instance));

                /* Check TI1 input conditioning related parameters */
                assert_param(IS_TIM_CLOCKPOLARITY(pClockSourceConfig->ClockPolarity));
                assert_param(IS_TIM_CLOCKFILTER(pClockSourceConfig->ClockFilter));

                TIM_TI1_ConfigInputStage(htim->Instance,
                                         pClockSourceConfig->ClockPolarity,
                                         pClockSourceConfig->ClockFilter);

                TIM_ITRx_SetConfig(htim->Instance, TIM_CLOCKSOURCE_TI1ED);
            }
            break;
        case TIM_CLOCKSOURCE_ITR0:
        case TIM_CLOCKSOURCE_ITR1:
        case TIM_CLOCKSOURCE_ITR2:
        case TIM_CLOCKSOURCE_ITR3:
            {
                /* Check whether or not the timer instance supports external clock mode 1 */
                assert_param(IS_TIM_CLOCKSOURCE_ITRX_INSTANCE(htim->Instance));

                TIM_ITRx_SetConfig(htim->Instance, pClockSourceConfig->ClockSource);
            }
            break;

        default:
            return HAL_ERROR;
    }

    htim->State = HAL_TIM_STATE_READY;

    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief  Selects the signal connected to the TI1 input: direct from CH1_input
 *         or a XOR combination between CH1_input, CH2_input & CH3_input
 * @param  htim : TIM handle.
 * @param  TI1_Selection : Indicate whether or not channel 1 is connected to the
 *         output of a XOR gate.
 *          This parameter can be one of the following values:
 *            @arg TIM_TI1SELECTION_CH1: The TIMx_CH1 pin is connected to TI1 input
 *            @arg TIM_TI1SELECTION_XORCOMBINATION: The TIMx_CH1, CH2 and CH3
 *            pins are connected to the TI1 input (XOR combination)
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_ConfigTI1Input(TIM_HandleTypeDef *htim, uint32_t TI1_Selection)
{
    uint32_t tmpcr2 = 0U;

    /* Check the parameters */
    assert_param(IS_TIM_XOR_INSTANCE(htim->Instance));
    assert_param(IS_TIM_TI1SELECTION(TI1_Selection));

    /* Get the TIMx CR2 register value */
    tmpcr2 = READ_REG(htim->Instance->CR2);

    /* Set the the TI1 selection */
    WRITE_REG_MASK(tmpcr2, TIM_CR2_TI1S_Msk, TI1_Selection);

    /* Write to TIMxCR2 */
    WRITE_REG(htim->Instance->CR2, tmpcr2);

    return HAL_OK;
}

/**
 *  @brief  Configures the TIM in Master mode
 *
 *  @param [in] htim                TIM handle.
 *  @param [in] pMasterConfig       Pointer to a TIM_MasterConfigTypeDef structure
 *  @return                         HAL status
 */
HAL_StatusTypeDef HAL_TIME_MasterConfigSynchronization(TIM_HandleTypeDef *htim, TIM_MasterConfigTypeDef *pMasterConfig)
{
    __HAL_LOCK(htim);

    htim->State = HAL_TIM_STATE_BUSY;

    WRITE_REG_MASK(htim->Instance->CR2, TIM_CR2_MMS_Msk, pMasterConfig->MasterOutputTrigger);

    if( pMasterConfig->MasterSlaveMode == TIM_MASTERSLAVEMODE_ENABLE )
        SET_BIT(htim->Instance->SMCR, TIM_SMCR_MSM);
    else
        CLEAR_BIT(htim->Instance->SMCR, TIM_SMCR_MSM);

    htim->State = HAL_TIM_STATE_READY;

    __HAL_UNLOCK(htim);

    return HAL_OK;
}
/**
  * @brief  Configures the TIM in Slave mode
  * @param  htim : TIM handle.
  * @param  pSlaveConfig : pointer to a TIM_SlaveConfigTypeDef structure that
  *         contains the selected trigger (internal trigger input, filtered
  *         timer input or external trigger input) and the ) and the Slave
  *         mode (Disable, Reset, Gated, Trigger, External clock mode 1).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchronization(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *pSlaveConfig)
{
    /* Check the parameters */
    assert_param(IS_TIM_SLAVE_INSTANCE(htim->Instance));
    assert_param(IS_TIM_SLAVE_MODE(pSlaveConfig->SlaveMode));
    assert_param(IS_TIM_TRIGGER_SELECTION(pSlaveConfig->InputTrigger));

    __HAL_LOCK(htim);

    htim->State = HAL_TIM_STATE_BUSY;

    TIM_SlaveTimer_SetConfig(htim, pSlaveConfig);

    /* Disable Trigger Interrupt */
    __HAL_TIM_DISABLE_IT(htim, TIM_IT_TRIGGER);

    htim->State = HAL_TIM_STATE_READY;

    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
  * @brief  Configures the TIM in Slave mode in interrupt mode
  * @param  htim: TIM handle.
  * @param  pSlaveConfig: pointer to a TIM_SlaveConfigTypeDef structure that
  *         contains the selected trigger (internal trigger input, filtered
  *         timer input or external trigger input) and the ) and the Slave
  *         mode (Disable, Reset, Gated, Trigger, External clock mode 1).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchronization_IT(TIM_HandleTypeDef *htim,
                                                        TIM_SlaveConfigTypeDef *pSlaveConfig)
{
    /* Check the parameters */
    assert_param(IS_TIM_SLAVE_INSTANCE(htim->Instance));
    assert_param(IS_TIM_SLAVE_MODE(pSlaveConfig->SlaveMode));
    assert_param(IS_TIM_TRIGGER_SELECTION(pSlaveConfig->InputTrigger));

    __HAL_LOCK(htim);

    htim->State = HAL_TIM_STATE_BUSY;

    TIM_SlaveTimer_SetConfig(htim, pSlaveConfig);

    /* Enable Trigger Interrupt */
    __HAL_TIM_ENABLE_IT(htim, TIM_IT_TRIGGER);

    htim->State = HAL_TIM_STATE_READY;

    __HAL_UNLOCK(htim);

    return HAL_OK;
}

/**
 * @brief  Read the captured value from Capture Compare unit
 * @param  htim : TIM handle.
 * @param  Channel : TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1 : TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2 : TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3 : TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4 : TIM Channel 4 selected
 * @retval Captured value
 */
uint32_t HAL_TIM_ReadCapturedValue(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    uint32_t tmpreg = 0U;

    __HAL_LOCK(htim);

    /* Return the capture value */
    switch (Channel)
    {
        case TIM_CHANNEL_1: tmpreg = READ_REG(htim->Instance->CCR1);    break;
        case TIM_CHANNEL_2: tmpreg = READ_REG(htim->Instance->CCR2);    break;
        case TIM_CHANNEL_3: tmpreg = READ_REG(htim->Instance->CCR3);    break;
        case TIM_CHANNEL_4: tmpreg = READ_REG(htim->Instance->CCR4);    break;
        default:
            break;
    }

    __HAL_UNLOCK(htim);
    return tmpreg;
}


/**
 * @brief   Configures the Break feature, dead time, Lock level, OSSI/OSSR State
 *          and the AOE(automatic output enable).
 * @param  htim : TIM handle
 * @param  pBreakDeadTimeConfig : pointer to a TIM_ConfigBreakDeadConfigTypeDef structure that
 *         contains the BDTR Register configuration  information for the TIM peripheral.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_ConfigBreakDeadTime(TIM_HandleTypeDef *htim,
                                              TIM_BreakDeadTimeConfigTypeDef *pBreakDeadTimeConfig)
{
    uint32_t tmpbdtr = 0U;

    /* Check the parameters */
    assert_param(htim);
    assert_param(IS_TIM_BREAK_INSTANCE(htim->Instance));
    assert_param(IS_TIM_OSSR_STATE(pBreakDeadTimeConfig->OffStateRunMode));
    assert_param(IS_TIM_OSSI_STATE(pBreakDeadTimeConfig->OffStateIDLEMode));
    assert_param(IS_TIM_LOCK_LEVEL(pBreakDeadTimeConfig->LockLevel));
    assert_param(IS_TIM_DEADTIME(pBreakDeadTimeConfig->DeadTime));
    assert_param(IS_TIM_BREAK_STATE(pBreakDeadTimeConfig->BreakState));
    assert_param(IS_TIM_BREAK_POLARITY(pBreakDeadTimeConfig->BreakPolarity));
    assert_param(IS_TIM_AUTOMATIC_OUTPUT_STATE(pBreakDeadTimeConfig->AutomaticOutput));

    /* Process Locked */
    __HAL_LOCK(htim);

    /**
     * Set the Lock level, the Break enable Bit and the Polarity, the OSSR State,
     * the OSSI State, the dead time value and the Automatic Output Enable Bit
     */

    /* Set the BDTR bits */
    MODIFY_REG(tmpbdtr, TIM_BDTR_DTG, pBreakDeadTimeConfig->DeadTime);
    MODIFY_REG(tmpbdtr, TIM_BDTR_LOCK, pBreakDeadTimeConfig->LockLevel);
    MODIFY_REG(tmpbdtr, TIM_BDTR_OSSI, pBreakDeadTimeConfig->OffStateIDLEMode);
    MODIFY_REG(tmpbdtr, TIM_BDTR_OSSR, pBreakDeadTimeConfig->OffStateRunMode);
    MODIFY_REG(tmpbdtr, TIM_BDTR_BKE, pBreakDeadTimeConfig->BreakState);
    MODIFY_REG(tmpbdtr, TIM_BDTR_BKP, pBreakDeadTimeConfig->BreakPolarity);
    MODIFY_REG(tmpbdtr, TIM_BDTR_AOE, pBreakDeadTimeConfig->AutomaticOutput);
    MODIFY_REG(tmpbdtr, TIM_BDTR_MOE, pBreakDeadTimeConfig->AutomaticOutput);

    /* Set TIMx_BDTR */
    htim->Instance->BDTR = tmpbdtr;

    __HAL_UNLOCK(htim);

    return HAL_OK;
}



/**
 * @}
 */

/** @defgroup TIM_Exported_Functions_Group9 TIM Callbacks functions
 *  @brief    TIM Callbacks functions
 *
 @verbatim
  ==============================================================================
                        ##### TIM Callbacks functions #####
  ==============================================================================
 [..]
   This section provides TIM callback functions:
   (+) Timer Period elapsed callback
   (+) Timer Output Compare callback
   (+) Timer Input capture callback
   (+) Timer Trigger callback
   (+) Timer Error callback

 @endverbatim
 * @{
 */


/**
 * @brief  Period elapsed callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the __HAL_TIM_PeriodElapsedCallback could be implemented in the user file
    */

}
/**
 * @brief  Output Compare callback in non blocking mode
 * @param  htim : TIM OC handle
 * @retval None
 */
__weak void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the __HAL_TIM_OC_DelayElapsedCallback could be implemented in the user file
    */
}
/**
 * @brief  Input Capture callback in non blocking mode
 * @param  htim : TIM IC handle
 * @retval None
 */
__weak void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the __HAL_TIM_IC_CaptureCallback could be implemented in the user file
    */
}

/**
 * @brief  PWM Pulse finished callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the __HAL_TIM_PWM_PulseFinishedCallback could be implemented in the user file
    */
}


/**
 * @brief  Break detection callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_BreakCallback(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_BreakCallback could be implemented in the user file
    */
}


/**
 * @brief  Hall Trigger detection callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_TriggerCallback could be implemented in the user file
    */
}


/**
 * @brief  Communication callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_CommutationCallback(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_CommutationCallback could be implemented in the user file
    */
}


/**
 * @brief  Timer error callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
__weak void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htim);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_TIM_ErrorCallback could be implemented in the user file
    */
}

/**
 * @}
 */

/** @defgroup TIM_Exported_Functions_Group10 Peripheral State functions
 *  @brief   Peripheral State functions
 *
 @verbatim
  ==============================================================================
                        ##### Peripheral State functions #####
  ==============================================================================
    [..]
    This subsection permit to get in run-time the status of the peripheral
    and the data flow.

 @endverbatim
 * @{
 */

/**
 * @brief  Return the TIM Base state
 * @param  htim : TIM Base handle
 * @retval HAL state
 */
HAL_TIM_StateTypeDef HAL_TIM_Base_GetState(TIM_HandleTypeDef *htim)
{
    return htim->State;
}

/**
 * @brief  Return the TIM OC state
 * @param  htim : TIM Ouput Compare handle
 * @retval HAL state
 */
HAL_TIM_StateTypeDef HAL_TIM_OC_GetState(TIM_HandleTypeDef *htim)
{
    return htim->State;
}

/**
 * @brief  Return the TIM PWM state
 * @param  htim : TIM handle
 * @retval HAL state
 */
HAL_TIM_StateTypeDef HAL_TIM_PWM_GetState(TIM_HandleTypeDef *htim)
{
    return htim->State;
}

/**
 * @brief  Return the TIM Input Capture state
 * @param  htim : TIM IC handle
 * @retval HAL state
 */
HAL_TIM_StateTypeDef HAL_TIM_IC_GetState(TIM_HandleTypeDef *htim)
{
    return htim->State;
}

/**
 * @brief  Return the TIM One Pulse Mode state
 * @param  htim : TIM OPM handle
 * @retval HAL state
 */
HAL_TIM_StateTypeDef HAL_TIM_OnePulse_GetState(TIM_HandleTypeDef *htim)
{
    return htim->State;
}

/**
 * @brief  Return the TIM Encoder Mode state
 * @param  htim : TIM Encoder handle
 * @retval HAL state
 */
HAL_TIM_StateTypeDef HAL_TIM_Encoder_GetState(TIM_HandleTypeDef *htim)
{
    return htim->State;
}

/**
 * @}
 */

/**
 * @}
 */


#endif /* HAL_TIM_MODULE_ENABLED */

/**
 * @}
 */

/**
 * @}
 */
