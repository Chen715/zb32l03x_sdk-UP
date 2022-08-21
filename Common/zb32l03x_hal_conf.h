/**
 ******************************************************************************
 * @file    zb32l03x_hal_conf.h
 * @author  MCU Software Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   HAL configuration file.
 ******************************************************************************
 **/

#ifndef __ZB32L03x_HAL_CONF_H
#define __ZB32L03x_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif


/* ########################## Module Selection ############################## */
/**
 * @brief This is the list of modules to be used in the HAL driver
 */
#define HAL_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_CRC_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_IWDG_MODULE_ENABLED
#define HAL_WWDG_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_BASETIM_MODULE_ENABLED
#define HAL_LPTIM_MODULE_ENABLED
#define HAL_LVD_MODULE_ENABLED
#define HAL_BEEP_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_AWK_MODULE_ENABLED
#define HAL_SYSCON_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_LPUART_MODULE_ENABLED

#if defined(CONFIG_USE_ZB32L030)
    #define HAL_SPI_MODULE_ENABLED
#endif  /* CONFIG_USE_ZB32L030 */

#define HAL_VC_MODULE_ENABLED
#define HAL_CLKTRIM_MODULE_ENABLED
#define HAL_PCA_MODULE_ENABLED
#define HAL_I2C_MODULE_ENABLED
#define HAL_RTC_MODULE_ENABLED
#define HAL_OWIRE_MODULE_ENABLED
#define HAL_OPTION_BYTES_MODULE_ENABLED
#define HAL_OPA_MODULE_ENABLED

#if defined(CONFIG_USE_ZB32L032)
    #error "ZB32L032 coming soon (SDK currently not support ZB32L032) ~~~"
    #define HAL_DMA_MODULE_ENABLED
    #define HAL_CRYP_MODULE_ENABLED
    #define HAL_QSPI_MODULE_ENABLED
    #define HAL_SPI_I2S_MODULE_ENABLED
    #define HAL_IRDA_MODULE_ENABLED
    #define HAL_SMARTCARD_MODULE_ENABLED
    #define HAL_I2S_MODULE_ENABLED
    #define HAL_TRNG_MODULE_ENABLED
    #define HAL_USART_MODULE_ENABLED
#endif  /* CONFIG_USE_ZB32L032 */

/* ########################## Oscillator Values adaptation ####################*/

#if !defined(HIRC_VALUE_24M)
#define HIRC_VALUE_24M              ((uint32_t)24000000)    /*!< Value of the Internal oscillator select 24MHz */
#endif  /* HIRC_VALUE_24M */

#if !defined(HIRC_VALUE_22M)
#define HIRC_VALUE_22M              ((uint32_t)22120000)    /*!< Value of the Internal oscillator select 22.12MHz */
#endif  /* HIRC_VALUE_22M */

#if !defined(HIRC_VALUE_16M)
#define HIRC_VALUE_16M              ((uint32_t)16000000)    /*!< Value of the Internal oscillator select 16MHz */
#endif  /* HIRC_VALUE_16M */

#if !defined(HIRC_VALUE_8M)
#define HIRC_VALUE_8M               ((uint32_t)8000000)     /*!< Value of the Internal oscillator select 8MHz */
#endif  /* HIRC_VALUE_8M */

#if !defined(HIRC_VALUE_4M)
#define HIRC_VALUE_4M               ((uint32_t)4000000)     /*!< Value of the Internal oscillator select 4MHz */
#endif  /* HIRC_VALUE_4M */

/**
 * @brief Adjust the value of External High Speed oscillator (HXT) used in your application.
 *        This value is used by the RCC HAL module to compute the system frequency
 */
#if !defined(HXT_VALUE)
#define HXT_VALUE                   ((uint32_t)8000000) /*!< Value of the External oscillator in Hz */
#endif  /* HXT_VALUE */

#if !defined(HXT_STARTUP_TIMEOUT)
#define HXT_STARTUP_TIMEOUT         ((uint32_t)100)   /*!< Time out for HXT start up, in ms */
#endif  /* HXT_STARTUP_TIMEOUT */

/**
 * @brief Internal Low Speed Internal oscillator (SIRC) value.
 */
#if !defined(SIRC_VALUE)
#define SIRC_VALUE                  38400U      /*!< SIRC Typical Value in Hz */
                                                /*!< Value of the Internal Low Speed oscillator in Hz
                                                    The real value may vary depending on the variations
                                                    in voltage and temperature. */
#endif  /* SIRC_VALUE */

/**
 * @brief Adjust the value of External Low Speed oscillator (LXT) used in your application.
 *        This value is used by the RCC HAL module to compute the system frequency
 */
#if !defined(LXT_VALUE)
#define LXT_VALUE                   ((uint32_t)32768) /*!< Value of the External oscillator in Hz*/
#endif  /* LXT_VALUE */

/**
 * @brief External Low Speed oscillator (LSE) value.
 *        This value is used by the UART, RTC HAL module to compute the system frequency
 */
#if !defined(LSE_VALUE)
#define LSE_VALUE                   ((uint32_t)32768) /*!< Value of the External oscillator in Hz*/
#endif  /* LSE_VALUE */

#if !defined(LXT_STARTUP_TIMEOUT)
#define LXT_STARTUP_TIMEOUT         ((uint32_t)5000)   /*!< Time out for LXT start up, in ms */
#endif  /* LXT_STARTUP_TIMEOUT */

/* Tip: To avoid modifying this file each time you need to use different HSE,
   ===  you can define the HSE value in your toolchain compiler preprocessor. */

/* ########################### System Configuration ######################### */
/**
 * @brief This is the HAL system configuration section
 */
#define  VDD_VALUE                    ((uint32_t)3300) /*!< Value of VDD in mv */
#define  PRIORITY_HIGHEST             0
#define  PRIORITY_HIGH                1
#define  PRIORITY_LOW                 2
#define  PRIORITY_LOWEST              3
#define  TICK_INT_PRIORITY            ((uint32_t)PRIORITY_LOWEST)    /*!< tick interrupt priority (lowest by default)  */
#define  USE_RTOS                     0
#define  PREFETCH_ENABLE              1

/* ########################## Assert Selection ############################## */
/**
 * @brief Uncomment the line below to expanse the "assert_param" macro in the
 *        HAL drivers code
 */
#define USE_FULL_ASSERT         0U


/* ########################## Include Header files ############################## */
/**
 * @brief Include module's header file
 */

#ifdef HAL_SYSCON_MODULE_ENABLED
#include "zb32l03x_hal_syscon.h"
#endif  /* HAL_SYSCON_MODULE_ENABLED */

#ifdef HAL_RCC_MODULE_ENABLED
#include "zb32l03x_hal_rcc.h"
#endif  /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
#include "zb32l03x_hal_gpio.h"
#endif  /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_CORTEX_MODULE_ENABLED
#include "zb32l03x_hal_cortex.h"
#endif  /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
#include "zb32l03x_hal_adc.h"
#endif  /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_CRC_MODULE_ENABLED
#include "zb32l03x_hal_crc.h"
#endif  /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
#include "zb32l03x_hal_flash.h"
#endif  /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
#include "zb32l03x_hal_i2c.h"
#endif  /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_IWDG_MODULE_ENABLED
#include "zb32l03x_hal_iwdg.h"
#endif  /* HAL_IWDG_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
#include "zb32l03x_hal_pwr.h"
#endif  /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
#include "zb32l03x_hal_rtc.h"
#endif  /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
#include "zb32l03x_hal_spi.h"
#endif  /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
#include "zb32l03x_hal_tim.h"
#endif  /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_BASETIM_MODULE_ENABLED
#include "zb32l03x_hal_basetim.h"
#endif  /* HAL_BASETIM_MODULE_ENABLED */

#ifdef HAL_LPTIM_MODULE_ENABLED
#include "zb32l03x_hal_lptim.h"
#endif  /* HAL_LPTIM_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
#include "zb32l03x_hal_uart.h"
#endif  /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_LPUART_MODULE_ENABLED
#include "zb32l03x_hal_lpuart.h"
#endif  /* HAL_LPUART_MODULE_ENABLED */

#ifdef HAL_WWDG_MODULE_ENABLED
#include "zb32l03x_hal_wwdg.h"
#endif  /* HAL_WWDG_MODULE_ENABLED */

#ifdef HAL_BEEP_MODULE_ENABLED
#include "zb32l03x_hal_beep.h"
#endif  /* HAL_BEEP_MODULE_ENABLED */

#ifdef HAL_AWK_MODULE_ENABLED
#include "zb32l03x_hal_awk.h"
#endif  /* HAL_AWK_MODULE_ENABLED */

#ifdef HAL_LVD_MODULE_ENABLED
#include "zb32l03x_hal_lvd.h"
#endif  /* HAL_LVD_MODULE_ENABLED */

#ifdef HAL_VC_MODULE_ENABLED
#include "zb32l03x_hal_vc.h"
#endif  /* HAL_VC_MODULE_ENABLED */

#ifdef HAL_CLKTRIM_MODULE_ENABLED
#include "zb32l03x_hal_clktrim.h"
#endif  /* HAL_CLKTRIM_MODULE_ENABLED */

#ifdef HAL_PCA_MODULE_ENABLED
#include "zb32l03x_hal_pca.h"
#endif  /* HAL_PCA_MODULE_ENABLED */

#ifdef HAL_OWIRE_MODULE_ENABLED
#include "zb32l03x_hal_owire.h"
#endif  /* HAL_OWIRE_MODULE_ENABLED */

#ifdef HAL_OPTION_BYTES_MODULE_ENABLED
#include "zb32l03x_hal_obytes.h"
#endif  /* HAL_OPTION_BYTES_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
#include "zb32l03x_hal_dma.h"
#endif  /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_CRYP_MODULE_ENABLED
#include "zb32l03x_hal_cryp.h"
#endif  /* HAL_CRYP_MODULE_ENABLED */

#ifdef HAL_QSPI_MODULE_ENABLED
#include "zb32l03x_hal_qspi.h"
#endif  /* HAL_QSPI_MODULE_ENABLED */

#ifdef HAL_SPI_I2S_MODULE_ENABLED
#include "zb32l03x_hal_spi_i2s.h"
#endif  /* HAL_SPI_I2S_MODULE_ENABLED */

#ifdef HAL_SMARTCARD_MODULE_ENABLED
#include "zb32l03x_hal_smartcard.h"
#endif  /* HAL_SMARTCARD_MODULE_ENABLED */

#ifdef HAL_IRDA_MODULE_ENABLED
#include "zb32l03x_hal_irda.h"
#endif  /* HAL_IRDA_MODULE_ENABLED */

#ifdef HAL_I2S_MODULE_ENABLED
#include "zb32l03x_hal_i2s.h"
#endif  /* HAL_I2S_MODULE_ENABLED */

#ifdef HAL_TRNG_MODULE_ENABLED
#include "zb32l03x_hal_trng.h"
#endif  /* HAL_TRNG_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
#include "zb32l03x_hal_usart.h"
#endif  /* HAL_USART_MODULE_ENABLED */

#ifdef HAL_OPA_MODULE_ENABLED
#include "zb32l03x_hal_opa.h"
#endif  /* HAL_OPA_MODULE_ENABLED */

#include "zb32l03x_it.h"

#if defined(USE_FULL_ASSERT) && (USE_FULL_ASSERT)
/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param  expr: If expr is false, it calls assert_failed function
 *         which reports the name of the source file and the source
 *         line number of the call that failed.
 *         If expr is true, it returns no value.
 * @retval None
 */
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((const char *)__func__, __LINE__))
void assert_failed(const char *func_name, uint32_t line);
#else   /* USE_FULL_ASSERT */
#define assert_param(expr) ((void)0U)
#endif  /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif  /* __ZB32L03x_HAL_CONF_H */
