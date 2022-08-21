/**
 ******************************************************************************
 * @file    zb32l03x_starterkit.c
 * @author  MCU Software Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief  This file contains definitions for:
 *          - LED, push-button, EEPROM and External SPI flash available on ZB32L03x-StarterKit
 *            from ZBit
 *
 @verbatim
 */



#ifndef __ZB32L03x_STARTERKIT_H
#define __ZB32L03x_STARTERKIT_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup BSP
  * @{
  */

/** @addtogroup ZB32L03x_STARTERKIT
 * @{
 */


#include "zb32l03x_hal.h"


/** @defgroup ZB32L03x_STARTERKIT_Exported_Constants ZB32L03x STARTERKIT Exported Constants
 * @{
 */

/**
 * @brief  Define for ZB32L03x_STARTERKIT board
 */

#if defined(CONFIG_USE_ZB32L003S)
    #define USE_ZB32L003_STARTERKIT
#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    #define USE_ZB32L03x_STARTERKIT
#endif


/** @defgroup ZB32L03x_STARTERKIT_LED ZB32L03x STARTERKIT LED
 * @{
 */

#define LEDn                            1

typedef enum
{
    LED1 = 0
} Led_TypeDef;

#if defined(USE_ZB32L003_STARTERKIT)
    #define LED1_PIN                            GPIO_PIN_4
    #define LED1_GPIO_PORT                      GPIOD
    #define LED1_GPIO_CLK_ENABLE()              __HAL_RCC_GPIOD_CLK_ENABLE()
    #define LED1_GPIO_CLK_DISABLE()             __HAL_RCC_GPIOD_CLK_DISABLE()

#elif defined(USE_ZB32L03x_STARTERKIT)
    #define LED1_PIN                            GPIO_PIN_6
    #define LED1_GPIO_PORT                      GPIOC
    #define LED1_GPIO_CLK_ENABLE()              __HAL_RCC_GPIOC_CLK_ENABLE()
    #define LED1_GPIO_CLK_DISABLE()             __HAL_RCC_GPIOC_CLK_DISABLE()
#endif  /* USE_ZB32L03x_STARTERKIT */

#define LEDx_GPIO_CLK_ENABLE(__INDEX__)     do{                                 \
                                                if((__INDEX__) == 0)            \
                                                    LED1_GPIO_CLK_ENABLE();     \
                                            }while(0U)

#define LEDx_GPIO_CLK_DISABLE(__INDEX__)  (((__INDEX__) == 0) ? LED1_GPIO_CLK_DISABLE() : 0)

/**
  * @}
  */

/** @defgroup ZB32L03x_STARTERKIT_BUTTON ZB32L03x STARTERKIT BUTTON
  * @{
  */
#define BUTTONn                          1

typedef enum
{
    BUTTON_0_USER = 0,
} Button_TypeDef;

typedef enum
{
    BUTTON_MODE_GPIO = 0,
    BUTTON_MODE_EXTI
} ButtonMode_TypeDef;


/**
 * @brief User push-button
 */
#if defined(USE_ZB32L003_STARTERKIT)
    #define USER_BUTTON_0_PIN                           GPIO_PIN_6
    #define USER_BUTTON_0_GPIO_PORT                     GPIOC
    #define USER_BUTTON_0_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOC_CLK_ENABLE()
    #define USER_BUTTON_0_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOC_CLK_DISABLE()
    #define USER_BUTTON_0_EXTI_IRQn                     GPIOC_IRQn

#elif defined(USE_ZB32L03x_STARTERKIT)
    #define USER_BUTTON_0_PIN                           GPIO_PIN_5
    #define USER_BUTTON_0_GPIO_PORT                     GPIOC
    #define USER_BUTTON_0_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOC_CLK_ENABLE()
    #define USER_BUTTON_0_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOC_CLK_DISABLE()
    #define USER_BUTTON_0_EXTI_IRQn                     GPIOC_IRQn
#endif  /* USE_ZB32L03x_STARTERKIT */

#if (BUTTONn == 1)
#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)              \
            do{                                         \
                if((__INDEX__) == 0)                    \
                    USER_BUTTON_0_GPIO_CLK_ENABLE();    \
            }while(0U)

#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)                 \
            do{                                             \
                if( (__INDEX__) == BUTTON_0_USER )          \
                    USER_BUTTON_0_GPIO_CLK_DISABLE();       \
            }while(0U)

#endif  /* (BUTTONn == 1) */


/**
 * @}
 */


/**
 * @}
 */

/** @addtogroup ZB32L03x_STARTERKIT_Exported_Functions
 * @{
 */
uint32_t BSP_GetVersion(void);

/** @addtogroup ZB32L03x_STARTERKIT_LED_Functions ZB32L03x STARTERKIT LED Functions
 * @{
 */

void BSP_LED_Init(Led_TypeDef Led);
void BSP_LED_DeInit(Led_TypeDef Led);
void BSP_LED_On(Led_TypeDef Led);
void BSP_LED_Off(Led_TypeDef Led);
void BSP_LED_Toggle(Led_TypeDef Led);

/**
 * @}
 */

/** @addtogroup ZB32L03x_STARTERKIT_BUTTON_Functions ZB32L03x STARTERKIT BUTTON Functions
 * @{
 */
void     BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
void     BSP_PB_DeInit(Button_TypeDef Button);
uint32_t BSP_PB_GetState(Button_TypeDef Button);

/**
 * @}
 */

/**
 * @}
 */  /* End of group ZB32L03x_STARTERKIT_Exported_Functions */

/**
 * @}
 */  /* End of group ZB32L03x_STARTERKIT */

/**
 * @}
 */  /* End of group BSP */

#ifdef __cplusplus
}
#endif

#endif /* __ZB32L03x_STARTERKIT_H */


