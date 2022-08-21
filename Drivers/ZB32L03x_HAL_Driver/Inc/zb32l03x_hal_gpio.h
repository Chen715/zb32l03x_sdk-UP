/**
 ******************************************************************************
 * @file    zb32l03x_hal_gpio.h
 * @author  MCU Software Team
 * @Version V0.0.0
 * @Date    2022/01/19
 * @brief   Header file of GPIO HAL module.
 ******************************************************************************
 **/


#ifndef __ZB32L03x_HAL_GPIO_H
#define __ZB32L03x_HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif


#include "zb32l03x_hal_def.h"

/** @addtogroup ZB32L03x_HAL_Driver
 * @{
 */

/** @addtogroup GPIO
 * @{
 */


/** @defgroup GPIO_Exported_Types GPIO Exported Types
 * @{
 */

/**
 * @brief GPIO Debounce Init structure definition
 *      These parameters can be values of @ref GPIO_debounce_define
 */
typedef struct
{
    uint32_t Enable;
    uint32_t TwoLevelSync;
    uint32_t DebounceClk;
} GPIO_Debounce_InitTypeDef;

/**
 * @brief GPIO Exti Init structure definition
 *      These parameters can be values of @ref GPIO_exti_define
 */
typedef struct
{
    uint32_t Enable;
    uint32_t EdgeLevelSel;
    uint32_t RiseFallSel;
} GPIO_Exti_InitTypeDef;

/**
 * @brief GPIO Init structure definition
 */
typedef struct
{
    uint32_t Pin;                           /*!< Specifies the GPIO pins to be configured.
                                                    This parameter can be any value of @ref GPIO_pins_define */

    uint32_t Mode;                          /*!< Specifies the operating mode for the selected pins.
                                                    This parameter can be a value of @ref GPIO_mode_define */

    uint32_t Pull;                          /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                                                    This parameter can be a value of @ref GPIO_pull_define */

    uint32_t OpenDrain;                     /*!< Specifies the PushPull or OpenDrain output for the selected pins.
                                                    This parameter can be a value of @ref GPIO_opendrain_define */

    GPIO_Debounce_InitTypeDef Debounce;     /*!< Specifies the debounce for the selected pins.
                                                    This parameter can be a value of @ref GPIO_debounce_define */

    uint32_t SlewRate;                      /*!< Specifies the slew rate for the selected pins.
                                                    This parameter can be a value of @ref GPIO_slewrate_define */

    uint32_t DrvStrength;                   /*!< Specifies the driver strength for the selected pins.
                                                    This parameter can be a value of @ref GPIO_driver_strength_define */

    GPIO_Exti_InitTypeDef Exti;             /*!< Specifies exti type for the selected pins.
                                                    This parameter can be a value of @ref GPIO_exti_define */

    uint32_t Alternate;                     /*!< Peripheral to be connected to the selected pins.
                                                    This parameter can be a value of @ref GPIO_alternate_function_selection */

} GPIO_InitTypeDef;

/**
 * @brief  GPIO Bit SET and Bit RESET enumeration
 */
typedef enum
{
    GPIO_PIN_RESET = 0U,
    GPIO_PIN_SET,
    GPIO_PIN_LOW  = GPIO_PIN_RESET,
    GPIO_PIN_HIGH = GPIO_PIN_SET,
} GPIO_PinState;
/**
 * @}
 */ /* End of group GPIO_Exported_Types */


/** @defgroup GPIO_Exported_Constants GPIO Exported Constants
 * @{
 */

/** @defgroup GPIO_pins_define GPIO pins define
 * @{
 */
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected    */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected    */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected    */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected    */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected    */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected    */

#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_PIN_MASK              0x0000FFFFU         /* PIN mask for assert  */
/**
 * @}
 */

/** @defgroup GPIO_mode_define GPIO mode define
 * @brief GPIO Configuration Mode
 *        Elements values convention: 0xX0yz00YZ
 *           - X  : GPIO mode or EXTI Mode
 *           - y  : External IT or Event trigger detection
 *           - z  : IO configuration on External IT or Event
 *           - Y  : Output type (Push Pull or Open Drain)
 *           - Z  : IO Direction mode (Input, Output, Alternate or Analog)
 * @{
 */
#define  GPIO_MODE_INPUT                        0x00000000U   /*!< Input Floating Mode                   */
#define  GPIO_MODE_OUTPUT                       0x00000001U   /*!< Output Mode                           */
#define  GPIO_MODE_AF                           0x00000002U   /*!< Alternate Function Mode               */
#define  GPIO_MODE_ANALOG                       0x00000003U   /*!< Analog Mode                           */
#define  GPIO_MODE_GPIO                         0x00000004U   /*!< Gpio Function Mode                    */
#define  EXTI_MODE                              0x10000000U   /*!< Exti Mode                             */
/**
 * @}
 */

/** @defgroup GPIO_slewrate_define  GPIO slewrate define
 * @brief GPIO Output Maximum frequency
 * @{
 */
#define  GPIO_SLEW_RATE_LOW                                 0x00000001U
#define  GPIO_SLEW_RATE_HIGH                                0x00000000U
/**
 * @}
 */

/** @defgroup GPIO_pull_define GPIO pull define
 * @brief GPIO Pull-Up or Pull-Down Activation
 * @{
 */
#define  GPIO_NOPULL                                        0x00000000U   /*!< No Pull-up or Pull-down activation  */
#define  GPIO_PULLUP                                        0x00000001U   /*!< Pull-up activation                  */
#define  GPIO_PULLDOWN                                      0x00000002U   /*!< Pull-down activation                */
/**
 * @}
 */

/** @defgroup GPIO_opendrain_define GPIO output mode define
 * @brief GPIO PushPull or Opendrain Activation
 * @{
 */
#define  GPIO_PUSHPULL                                      0x00000000U   /*!< Push pull activation              */
#define  GPIO_OPENDRAIN                                     0x00000001U   /*!< Open drain activation             */
/**
 * @}
 */


/** @defgroup GPIO_driver_strength_define GPIO driver strengh
 * @brief GPIO driver strengh setting
 * @{
 */
#define  GPIO_DRV_STRENGTH_HIGH                             0x00000000U   /*!< GPIO driver strengh high  */
#define  GPIO_DRV_STRENGTH_LOW                              0x00000001U   /*!< GPIO driver strengh low   */
/**
 * @}
 */


/** @defgroup GPIO_debounce_define GPIO debounce mode define
 * @brief GPIO debounce Activation
 * @{
 */
#define  GPIO_DEBOUNCE_DISABLE                              0x00000000U
#define  GPIO_DEBOUNCE_ENABLE                               0x00000001U

#define  GPIO_SYNC_DISABLE                                  0x00000000U
#define  GPIO_SYNC_ENABLE                                   0x00000001U

#define  GPIO_DBCLK_DIV_1                                   0x00000000U
#define  GPIO_DBCLK_DIV_2                                   0x00000001U
#define  GPIO_DBCLK_DIV_4                                   0x00000002U
#define  GPIO_DBCLK_DIV_8                                   0x00000003U
#define  GPIO_DBCLK_DIV_16                                  0x00000004U
#define  GPIO_DBCLK_DIV_32                                  0x00000005U
#define  GPIO_DBCLK_DIV_64                                  0x00000006U
#define  GPIO_DBCLK_DIV_128                                 0x00000007U
#define  GPIO_DBCLK_DIV_256                                 0x00000008U
#define  GPIO_DBCLK_DIV_512                                 0x00000009U
#define  GPIO_DBCLK_DIV_1024                                0x0000000AU
#define  GPIO_DBCLK_DIV_2048                                0x0000000BU
#define  GPIO_DBCLK_DIV_4096                                0x0000000CU
#define  GPIO_DBCLK_DIV_8192                                0x0000000DU
#define  GPIO_DBCLK_DIV_16384                               0x0000000EU
#define  GPIO_DBCLK_DIV_32768                               0x0000000FU

/**
 * @}
 */

/** @defgroup GPIO_exti_define GPIO exti mode define
 * @brief
 * @{
 */
#define  GPIO_EXTI_INT_DISABLE                              0x00000000U
#define  GPIO_EXTI_INT_ENABLE                               0x00000001U

#define  GPIO_EXTI_INT_EDGE                                 0x00000000U
#define  GPIO_EXTI_INT_LEVEL                                0x00000001U

#define  GPIO_EXTI_INT_LOWFALL                              0x00000000U
#define  GPIO_EXTI_INT_HIGHRISE                             0x00000001U
#define  GPIO_EXTI_INT_FALLRISE                             0x00000002U

/**
 * @}
 */

/** @defgroup GPIO_alternate_function_selection  GPIO alternate function selection
 * @brief
 * @{
 */

#define GPIO_AF_MODE_0                  0x00u   /* GPIO Alternate mode 0 */
#define GPIO_AF_MODE_1                  0x01u   /* GPIO Alternate mode 1 */
#define GPIO_AF_MODE_2                  0x02u   /* GPIO Alternate mode 2 */
#define GPIO_AF_MODE_3                  0x03u   /* GPIO Alternate mode 3 */
#define GPIO_AF_MODE_4                  0x04u   /* GPIO Alternate mode 4 */
#define GPIO_AF_MODE_5                  0x05u   /* GPIO Alternate mode 5 */
#define GPIO_AF_MODE_6                  0x06u   /* GPIO Alternate mode 6 */
#define GPIO_AF_MODE_7                  0x07u   /* GPIO Alternate mode 7 */
#define GPIO_AF_MODE_8                  0x08u   /* GPIO Alternate mode 8 */
#define GPIO_AF_MODE_9                  0x09u   /* GPIO Alternate mode 9 */
#define GPIO_AF_MODE_F                  0x0Fu   /* GPIO Alternate mode F */

/**
 * @}
 */

/**
 * @}
 */ /* End of group GPIO_Exported_Constants */


/** @defgroup GPIO_Exported_Macros GPIO Exported Macros
 * @{
 */

/**
 * @brief  Set GPIO_PIN_x as input
 * @param  __GPIOx__: specifies the GPIO.
 *                      This parameter can be GPIOx where x can be(A..D)
 * @param  __GPIO_PIN__: specifies the pin.
 *          This parameter can be GPIO_PIN_x where x can be(0..15)
 * @retval None.
 */
#define __HAL_GPIO_SET_INPUT(__GPIOx__, __GPIO_PIN__)           (__GPIOx__->DIRCR &= (~(__GPIO_PIN__)))

/**
 * @brief  Set GPIO_PIN_x as output
 * @param  __GPIOx__: specifies the GPIO.
 *                      This parameter can be GPIOx where x can be(A..D)
 * @param  __GPIO_PIN__: specifies the pin.
 *          This parameter can be GPIO_PIN_x where x can be(0..15)
 * @retval None.
 */
#define __HAL_GPIO_SET_OUTPUT(__GPIOx__, __GPIO_PIN__)          (__GPIOx__->DIRCR |= (__GPIO_PIN__))

/**
 * @brief  Checks whether the specified EXTI line flag is set or not.
 * @param  __GPIOx__: specifies the GPIO to check.
 *                      This parameter can be GPIOx where x can be(A..D)
 * @param  __EXTI_LINE__: specifies the EXTI line to check.
 *          This parameter can be GPIO_PIN_x where x can be(0..15)
 * @retval The new state of __EXTI_LINE__ (SET or RESET).
 */
#define __HAL_GPIO_EXTI_GET_FLAG(__GPIOx__, __EXTI_LINE__)      (__GPIOx__->MSKINTSR & (__EXTI_LINE__))

/**
 * @brief  Clears the EXTI's line pending flags.
 * @param  __GPIOx__: specifies the GPIO to check.
 *                      This parameter can be GPIOx where x can be(A..D)
 * @param  __EXTI_LINE__: specifies the EXTI line to check.
 *          This parameter can be GPIO_PIN_x where x can be(0..15)
 * @retval None
 */
#define __HAL_GPIO_EXTI_CLEAR_FLAG(__GPIOx__, __EXTI_LINE__)    (__GPIOx__->INTCLR = (__EXTI_LINE__))

/**
 * @brief  Checks whether the specified EXTI line is asserted or not.
 * @param  __GPIOx__: specifies the GPIO to check.
 *                      This parameter can be GPIOx where x can be(A..D)
 * @param  __EXTI_LINE__: specifies the EXTI line to check.
 *          This parameter can be GPIO_PIN_x where x can be(0..15)
 * @retval The new state of __EXTI_LINE__ (SET or RESET).
 */
#define __HAL_GPIO_EXTI_GET_IT(__GPIOx__, __EXTI_LINE__)        (__GPIOx__->INTEN & (__EXTI_LINE__))

/**
 * @brief  Clears the EXTI's line pending bits.
 * @param  __GPIOx__: specifies the GPIO to check.
 *                      This parameter can be GPIOx where x can be(A..D)
 * @param  __EXTI_LINE__: specifies the EXTI line to check.
 *          This parameter can be GPIO_PIN_x where x can be(0..15)
 * @retval None
 */
#define __HAL_GPIO_EXTI_CLEAR_IT(__GPIOx__, __EXTI_LINE__)      (__GPIOx__->INTEN &= (~(__EXTI_LINE__)))

/**
 * @}
 */ /* End of group GPIO_Exported_Macros */



/** @addtogroup GPIO_Exported_Functions
 * @{
 */

/** @addtogroup GPIO_Exported_Functions_Group1
 * @{
 */

/* Initialization and de-initialization functions *****************************/
void  HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void  HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
/**
 * @}
 */

/** @addtogroup GPIO_Exported_Functions_Group2
 * @{
 */
/* IO operation functions *****************************************************/
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_IRQHandler(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @}
 */

/**
 * @}
 */ /* End of group GPIO_Exported_Functions */


/** @defgroup GPIO_Private_Constants GPIO Private Constants
 * @{
 */

/**
 * @}
 */


/** @defgroup GPIO_Private_Macros GPIO Private Macros
 * @{
 */
#define IS_GPIO_PIN_ACTION(ACTION)      (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))

#define IS_GPIO_PIN(PIN)                ((((PIN) & GPIO_PIN_MASK ) != 0x00U) && (((PIN) & ~GPIO_PIN_MASK) == 0x00U))

#define IS_GPIO_MODE(MODE)              (((MODE) == GPIO_MODE_INPUT)  ||\
                                         ((MODE) == GPIO_MODE_OUTPUT) ||\
                                         ((MODE) == GPIO_MODE_AF)     ||\
                                         ((MODE) == GPIO_MODE_ANALOG) ||\
                                         ((MODE) == EXTI_MODE))

#define IS_GPIO_PULL(PULL)              (((PULL) == GPIO_NOPULL) || \
                                         ((PULL) == GPIO_PULLUP) || \
                                         ((PULL) == GPIO_PULLDOWN))

/** @defgroup GPIO_Get_Port_Index GPIO Get Port Index
 * @{
 */
#define GPIO_GET_INDEX(__GPIOx__)       (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                                  ((__GPIOx__) == (GPIOB))? 1U :\
                                                  ((__GPIOx__) == (GPIOC))? 2U :\
                                                  ((__GPIOx__) == (GPIOD))? 3U : 4U)
/**
 * @}
 */

/**
 * @}
 */


/** @defgroup GPIO_Private_Functions GPIO Private Functions
 * @{
 */
#define IS_GPIO_ALL_INSTANCE(INSTANCE)      ((INSTANCE) == GPIOA || (INSTANCE) == GPIOB || \
                                             (INSTANCE) == GPIOC || (INSTANCE) == GPIOD)

#if defined(CONFIG_USE_ZB32L003S) || defined(CONFIG_USE_ZB32L030)
    #define IS_GPIO_AF(AF)                      ((AF) == 0xF || ((int)(AF) >= (int)GPIO_AF_MODE_0 && (AF) <= GPIO_AF_MODE_8))
#elif defined(CONFIG_USE_ZB32L032)
    #define IS_GPIO_AF(AF)                      ((AF) == 0xF || ((int)(AF) >= (int)GPIO_AF_MODE_0 && (AF) <= GPIO_AF_MODE_9))
#endif

/**
 * @}
 */

/**
 * @}
 */ /* End of group GPIO */

/**
 * @}
 */ /* End of group ZB32L03x_HAL_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __ZL031_HAL_GPIO_H */
