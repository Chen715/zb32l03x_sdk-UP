/**
  ******************************************************************************
  * @file    system_zb32l03x.h
  * @author  Software Team
  * @version V1.0.0
  * @date    21-Oct-2019
  * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer Header File.
  *          This file contains all the peripheral register's definitions, bits
  *          definitions and memory mapping for ZB32L03x devices.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *
  ******************************************************************************
  */

#include "stdint.h"

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup zb32l03x_system
  * @{
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_ZB32L03x_H
#define __SYSTEM_ZB32L03x_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/** @addtogroup ZB32L03x_System_Includes
  * @{
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @addtogroup ZB32L03x_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @addtogroup ZB32L03x_System_Exported_types
  * @{
  */
extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @addtogroup ZB32L03x_System_Exported_Macros
  * @{
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup ZB32L03x_System_Exported_Functions
  * @{
  */
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_ZB32L03x_H */

/**
  * @}
  */ /* End of group zb32l03x_system */

/**
  * @}
  */ /* End of group CMSIS */

/************************ (C) COPYRIGHT ZBit *****END OF FILE****/
