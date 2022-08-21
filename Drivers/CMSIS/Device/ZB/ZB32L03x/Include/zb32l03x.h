/**
  ******************************************************************************
  * @file   zb32l03x.h
  * @author  Software Team
  * @version V1.0.0
  * @date    21-06-2021
  * @brief   CMSIS Cortex-M+ Device Peripheral Access Layer Header File.
  *          This file contains all the peripheral register's definitions, bits
  *          definitions and memory mapping for ZB32L03x devices.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *
  ******************************************************************************
  */


/** @addtogroup ZB32L03x
  * @{
  */

#ifndef ZB32L03x_H
#define ZB32L03x_H

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup Configuration_of_CMSIS
  * @{
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(CONFIG_USE_ZB32L030)
    #include "zb32l030.h"
#elif defined(CONFIG_USE_ZB32L032)
    // #include "zb32l032.h"
    #error "zb32l032 coming soon ~~~"
#else
    #error "Please select first the target device !"
#endif

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* ZB32L03x_H */

/** @} */ /* End of group ZB32L03x */
