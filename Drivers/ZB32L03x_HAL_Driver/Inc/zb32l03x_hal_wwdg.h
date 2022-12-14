/**
 ******************************************************************************
 * @file    zb32l03x_hal_wwdg.h
 * @author  MCU Software Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   Header file of WWDG HAL module.
 ******************************************************************************
 **/



#ifndef __ZB32L03x_HAL_WWDG_H
#define __ZB32L03x_HAL_WWDG_H

#ifdef __cplusplus
extern "C" {
#endif


#include "zb32l03x_hal_def.h"


/** @addtogroup WWDG
 * @{
 */


/** @defgroup WWDG_Exported_Types WWDG Exported Types
 * @{
 */

/**
 * @brief  WWDG Init structure definition
 */
typedef struct
{
    uint32_t    Prescaler;      /*!< Specifies the prescaler value of the WWDG.
                                    This parameter can be a value of @ref WWDG_Prescaler */

    uint8_t     Window;         /*!< Specifies the WWDG window value to be compared to the down-counter.
                                    This parameter must be a number Min_Data > 0x10 and Max_Data = 0xFF */

    uint8_t     INTSet ;        /*!< Specifies if WWDG Interrupt is enable or not.
                                    This parameter can be a value of @ref WWDG_INT_SET */

    uint8_t     Reload;         /*!< Specifies the WWDG free-running reload  value.
                                    This parameter must be a number between Min_Data > 0x20 and Max_Data = 0xFF */
} WWDG_InitTypeDef;

/**
 * @brief  IWDG Handle Structure definition
 */
typedef struct
{
    WWDG_TypeDef                 *Instance;  /*!< Register base address    */

    WWDG_InitTypeDef             Init;       /*!< WWDG required parameters */

} WWDG_HandleTypeDef;
/**
 * @}
 */



/** @defgroup WWDG_Exported_Constants WWDG Exported Constants
 * @{
 */

/** @defgroup WWDG_Prescaler WWDG Prescaler
 * @{
 */
#define WWDG_PRESCALER_MIN                 0x00000000U  /*!< WWDG  clock Prescaler MIN */
#define WWDG_PRESCALER_MAX                 0x000FFFFFU  /*!< WWDG  clock Prescaler MAX*/

/**
 * @}
 */

/** @defgroup WWDG_INT_SET WWDG  Interrupt SET
 * @{
 */
#define WWDG_INT_DISABLE                    0x0U      /*!< Interrupt Disable */
#define WWDG_INT_ENABLE                     0x1U      /*!< Interrupt Enable */
/**
 * @}
 */

/** @defgroup WWDG_WINDOW AND RELOAD  WWDG  WINDOW AND RELOAD VALUE RANGE
 * @{
 */
#define  WWDG_WINDOW_MIN                    (0x10U)
#define  WWDG_WINDOW_MAX                    (0xFFU)
#define  WWDG_RELOAD_MIN                    (0x20U)
#define  WWDG_RELOAD_MAX                    (0xFFU)
/**
 * @}
 */

/**
 * @}
 */



/** @defgroup WWDG_Private_Macros WWDG Private Macros
 * @{
 */
#define IS_WWDG_PRESCALER(__PRESCALER__)    (((int)(__PRESCALER__) >= (int)WWDG_PRESCALER_MIN) &&((__PRESCALER__) <= WWDG_PRESCALER_MAX))

#define IS_WWDG_WINDOW(__WINDOW__)          (((__WINDOW__) >= WWDG_WINDOW_MIN) && ((__WINDOW__) <= WWDG_WINDOW_MAX))

#define IS_WWDG_RELOAD(__RELOAD__)          (((__RELOAD__) >= WWDG_RELOAD_MIN) && ((__RELOAD__) <= WWDG_RELOAD_MAX))

#define IS_WWDG_INT_SET(__SET__)            (((__SET__) == WWDG_INT_ENABLE) || ((__SET__) == WWDG_INT_DISABLE))

/**
 * @}
 */




/** @defgroup WWDG_Exported_Macros WWDG Exported Macros
 * @{
 */

/**
 * @brief  Enables the WWDG peripheral.
 * @param  __HANDLE__  WWDG Handle.
 * @retval None
 */
#define __HAL_WWDG_ENABLE(__HANDLE__)           SET_BIT((__HANDLE__)->Instance->CR, WWDG_CR_WWDGEN)

/**
 * @brief  Enables the WWDG  interrupt.
 * @param  __HANDLE__  WWDG Handle.
 * @note   Once enabled this interrupt cannot be disabled except by a system reset.
 * @retval None
 */
#define __HAL_WWDG_ENABLE_INT(__HANDLE__)       SET_BIT((__HANDLE__)->Instance->INTEN, WWDG_INTEN_WWDGIEN)


/** @brief  Check whether the WWDG interrupt  is enabled or not.
 * @param  None.
 * @retval state of __INTERRUPT__ (RESET or SET).
 */
#define __HAL_WWDG_GET_INT_STATE()              READ_BIT(WWDG->INTEN, WWDG_INTEN_WWDGIEN)

/**
 * @brief  Checks whether the selected WWDG interrupt has occurred or not.
 * @param  None
 * @retval The new state of WWDG_FLAG (SET or RESET).
 */
#define __HAL_WWDG_GET_INT()                    READ_BIT(WWDG->SR, WWDG_SR_WWDGIF)

/** @brief  Clear the WWDG's interrupt pending bits
 * @param  None.
 * @retval  None
 */
#define __HAL_WWDG_CLEAR_INT()                  SET_BIT(WWDG->INTCLR, WWDG_INTCLR_INTCLR)



/**
 * @}
 */


/** @addtogroup WWDG_Exported_Functions
 * @{
 */

/** @addtogroup WWDG_Exported_Functions_Group1
 * @{
 */

/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_WWDG_Init(WWDG_HandleTypeDef *hwwdg);

/**
 * @}
 */

/** @addtogroup WWDG_Exported_Functions_Group2
 * @{
 */

/* I/O operation functions ******************************************************/
HAL_StatusTypeDef HAL_WWDG_Refresh(WWDG_HandleTypeDef *hwwdg);
HAL_StatusTypeDef HAL_WWDG_Get_Counter(WWDG_HandleTypeDef *hwwdg, uint32_t *pCounter);

void HAL_WWDG_IRQHandler(void);
void HAL_WWDG_Timeout_Callback(void);
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

#endif /* __ZB32L03x_HAL_WWDG_H */

