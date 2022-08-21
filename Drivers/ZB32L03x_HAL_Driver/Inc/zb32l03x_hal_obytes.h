/**
 ******************************************************************************
 * @file    zb32l03x_hal_obytes.h
 * @author  MCU Software Team
 * @Version V1.0.0
 * @Date    2021/06/25
 * @brief   Header file of Option Bytes HAL module.
 ******************************************************************************
 **/

#ifndef __ZB32L03x_HAL_OBYTES_H
#define __ZB32L03x_HAL_OBYTES_H

#ifdef __cplusplus
extern "C" {
#endif


#include "zb32l03x_hal_def.h"

/** @addtogroup Option Bytes
  * @{
  */


/** @defgroup OBYTES_Exported_Types Option Bytes Exported Types
  * @{
  */

/**
  * @brief  Option Bytes HAL State Structure definition
  */


/**
  * @brief  Option Bytes handle Structure definition
  */
#if defined(__CC_ARM)
#pragma anon_unions
#endif
typedef struct
{
    union {
        __IO uint32_t    usercfg0;
        struct {
            __IO uint32_t    ISP_CON  : 1;
            __IO uint32_t    IAP_CON  : 1;
            __IO uint32_t             : 2;
            __IO uint32_t    IAP_SIZE : 2;
        } USERCFG0b;
    };

    union {
        __IO uint32_t    usercfg1;
        struct {
            __IO uint32_t    SWDP : 1;
        } USERCFG1b;
    };

    union {
        __IO uint32_t    usercfg2;
        struct {
            __IO uint32_t    WDTCNT      : 20;
            __IO uint32_t                : 8;
            __IO uint32_t    WDTMODE     : 1;
            __IO uint32_t    WDTINTMASK  : 1;
            __IO uint32_t                : 1;
            __IO uint32_t    WDTON       : 1;
        } USERCFG2b;
    };

} OBYTES_HandleTypeDef;

/**
  * @}
  */

#define OBYTES_DATA_ADDRESS         OBYTES_BASE


/** @defgroup OBYTES_Exported_Macros Option Bytes Exported Macros
  * @{
  */


/**
  * @}
  */


/** @addtogroup OBYTES_Exported_Functions
  * @{
  */

/** @addtogroup OBYTES_Exported_Functions_Group1
  * @{
  */


/**
  * @}
  */

/** @addtogroup OBYTES_Exported_Functions_Group2
  * @{
  */


/**
  * @}
  */

/** @addtogroup OBYTES_Exported_Functions_Group3
  ** @{
  */


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

#endif /* __ZB32L03x_HAL_OBYTES_H */

