/**
 ******************************************************************************
 * @file    zb32l03x_hal_pwr.h
 * @author  MCU Software Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   Header file of PWR HAL module.
 ******************************************************************************
 **/


#ifndef __ZB32L03x_HAL_PWR_H
#define __ZB32L03x_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif


#include "zb32l03x_hal_def.h"

/** @addtogroup ZB32L03x_HAL_Driver
 * @{
 */

/** @addtogroup PWR
 * @{
 */



/** @defgroup PWR_Exported_Constants PWR Exported Constants
 * @{
 */

/** @defgroup PWR_SLEEP_mode_entry PWR SLEEP mode entry
 * @{
 */
#define PWR_SLEEPENTRY_WFI              ((uint8_t)0x01)
#define PWR_SLEEPENTRY_WFE              ((uint8_t)0x02)

/**
 * @}
 */

/**
 * @}
 */



/** @defgroup PWR_Private_Macros PWR Private Macros
 * @{
 */
#define IS_PWR_SLEEP_ENTRY(ENTRY)       (((ENTRY) == PWR_SLEEPENTRY_WFI) || ((ENTRY) == PWR_SLEEPENTRY_WFE))

/**
 * @}
 */


/** @addtogroup PWR_Exported_Functions PWR Exported Functions
 * @{
 */

/** @addtogroup PWR_Exported_Functions_Group1 Peripheral Control functions
 * @{
 */

/* Low Power modes configuration functions ************************************/
void HAL_PWR_EnterSleepMode(uint8_t SLEEPEntry);
void HAL_PWR_EnterDeepSleepMode(void);

void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */ /* End of group PWR */

/**
 * @}
 */ /* End of group ZB32L03x_HAL_Driver */

#ifdef __cplusplus
}
#endif


#endif /* __ZB32L03x_HAL_PWR_H */
