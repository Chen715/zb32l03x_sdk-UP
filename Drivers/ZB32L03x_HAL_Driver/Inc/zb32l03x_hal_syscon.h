/**
 ******************************************************************************
 * @file    zb32l03x_hal_syscon.h
 * @author  MCU Software Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   Header file of SYSCON HAL module.
 ******************************************************************************
 **/


#ifndef __ZB32L03x_HAL_SYSCON_H
#define __ZB32L03x_HAL_SYSCON_H

#ifdef __cplusplus
extern "C" {
#endif


#include "zb32l03x_hal_def.h"

/** @addtogroup SYSCON
 * @{
 */


/** @defgroup SYSCON_Exported_Types SYSCON Exported Types
 * @{
 */

/**
 * @}
 */


#define SYSCON_KEY_UNLOCK               (0x5A69)

#define SYSCON_DEFAULT                  (0x00U)
#define SYSCON_UART0_RXD                (0x01U)
#define SYSCON_UART1_RXD                (0x02U)
#define SYSCON_LPUART_RXD               (0x03U)
#define SYSCON_SIRC                     (0x04U)


#define SYSCON_SPISSN_HIGHLEVEL         (0x00U)
#define SYSCON_SPISSN_PA3               (0x01U)
#define SYSCON_SPISSN_PA4               (0x02U)
#define SYSCON_SPISSN_PA6               (0x03U)
#define SYSCON_SPISSN_PA8               (0x04U)
#define SYSCON_SPISSN_PA9               (0x05U)
#define SYSCON_SPISSN_PA12              (0x06U)
#define SYSCON_SPISSN_PA15              (0x07U)
#define SYSCON_SPISSN_PB1               (0x08U)
#define SYSCON_SPISSN_PB2               (0x09U)
#define SYSCON_SPISSN_PB5               (0x0AU)
#define SYSCON_SPISSN_PB6               (0x0BU)
#define SYSCON_SPISSN_PB9               (0x0CU)
#define SYSCON_SPISSN_PB10              (0x0DU)
#define SYSCON_SPISSN_PB12              (0x0EU)
#define SYSCON_SPISSN_PB14              (0x0FU)

#define SYSCON_TIM_ETR_LOWLEVEL         (0x00U)
#define SYSCON_TIM_ETR_PA1              (0x01U)
#define SYSCON_TIM_ETR_PA2              (0x02U)
#define SYSCON_TIM_ETR_PA3              (0x03U)
#define SYSCON_TIM_ETR_PB4              (0x04U)
#define SYSCON_TIM_ETR_PB5              (0x05U)
#define SYSCON_TIM_ETR_PA0              (0x06U)
#define SYSCON_TIM_ETR_PD0              (0x07U)
#define SYSCON_TIM_ETR_PC5              (0x08U)
#define SYSCON_TIM_ETR_PC6              (0x09U)
#define SYSCON_TIM_ETR_PC7              (0x0AU)
#define SYSCON_TIM_ETR_PD1              (0x0BU)
// #define SYSCON_TIM_ETR_PA3_ALT          (0x0CU) /* alternate, this definition will be discarded */
#define SYSCON_TIM_ETR_PA4              (0x0DU)
#define SYSCON_TIM_ETR_PA5              (0x0EU)
#define SYSCON_TIM_ETR_PA6              (0x0FU)

#define SYSCON_TIM1_CLKFAILBRKEN        SYSCON_TIM1CR_TIM1XCLKFAILBRKEN
#define SYSCON_TIM1_DSLPBRKEN           SYSCON_TIM1CR_TIM1XDSLPBRKEN

#define SYSCON_TIM1A_CLKFAILBRKEN       SYSCON_TIM1ACR_TIM1XCLKFAILBRKEN
#define SYSCON_TIM1A_DSLPBRKEN          SYSCON_TIM1ACR_TIM1XDSLPBRKEN

#define SYSCON_TIM1B_CLKFAILBRKEN       SYSCON_TIM1BCR_TIM1XCLKFAILBRKEN
#define SYSCON_TIM1B_DSLPBRKEN          SYSCON_TIM1BCR_TIM1XDSLPBRKEN

#define SYSCON_TIM1_OCOUT_LOWLEVEL      SYSCON_TIM1CR_TIM1XBRKOUTCFG
#define SYSCON_TIM1_OCOUT_BYTIM1        (0x00U)

#define SYSCON_TIM1A_OCOUT_LOWLEVEL     SYSCON_TIM1CR_TIM1XBRKOUTCFG
#define SYSCON_TIM1A_OCOUT_BYTIM1       (0x00U)

#define SYSCON_TIM1B_OCOUT_LOWLEVEL     SYSCON_TIM1CR_TIM1XBRKOUTCFG
#define SYSCON_TIM1B_OCOUT_BYTIM1       (0x00U)


/** @defgroup SYSCON_Exported_Macros SYSCON Exported Macros
 * @{
 */

#define __HAL_SYSCON_REGWR_LOCK()           (SYSCON->UNLOCK = (0x2AD5334C << SYSCON_UNLOCK_KEY_Pos) & SYSCON_UNLOCK_KEY)
#define __HAL_SYSCON_REGWR_UNLOCK()         (SYSCON->UNLOCK = SYSCON_UNLOCK_UNLOCK | (0x2AD5334C << SYSCON_UNLOCK_KEY_Pos))

/** @brief Macro to disable deep sleep mode in debug mode, allow to debug deep sleep mode.
 * @note  In debug mode, CPU will not enter deep sleep mode
 */
#define __HAL_SYSCON_DBGDEEPSLEEP_ENABLE()                                                                      \
            do{                                                                                                 \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                    \
                SET_BIT(SYSCON->CFGR0, SYSCON_CFGR0_DBGDLSP_DIS | (SYSCON_KEY_UNLOCK << SYSCON_CFGR0_KEY_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                      \
            }while(0U)

/** @brief Macro to enable deep sleep mode in debug mode, debug mode will quit in deep sleep mode.
 * @note  In debug mode, deep sleep mode will make debug mode quit
 */
#define __HAL_SYSCON_DBGDEEPSLEEP_DISABLE()                                                                        \
            do{                                                                                                    \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                       \
                CLEAR_WPBIT(SYSCON->CFGR0, SYSCON_CFGR0_DBGDLSP_DIS, (SYSCON_KEY_UNLOCK << SYSCON_CFGR0_KEY_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                         \
            }while(0U)

/** @brief Macro to enable cpu lock up function.
 */
#define __HAL_SYSCON_LOCKUP_ENABLE()                                                                            \
            do{                                                                                                 \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                    \
                SET_BIT(SYSCON->CFGR0, SYSCON_CFGR0_LOCKUPEN | (SYSCON_KEY_UNLOCK << SYSCON_CFGR0_KEY_Pos));    \
                __HAL_SYSCON_REGWR_LOCK();                                                                      \
            }while(0U)

/** @brief Macro to disable cpu lock up function.
  */
#define __HAL_SYSCON_LOCKUP_DISABLE()                                                                           \
            do{                                                                                                 \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                    \
                CLEAR_WPBIT(SYSCON->CFGR0, SYSCON_CFGR0_LOCKUPEN, (SYSCON_KEY_UNLOCK << SYSCON_CFGR0_KEY_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                      \
            }while(0U)

/** @brief Macro to config PAD interrupt mode as AUTO for deep sleep:.
 */
#define __HAL_SYSCON_DEEPSLEEP_PADINT_AUTO()                                                                                    \
            do{                                                                                                                 \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                    \
                CLEAR_WPBIT(SYSCON->PORTINTCR, SYSCON_PORTINTCR_PADDLSPCON, (SYSCON_KEY_UNLOCK << SYSCON_PORTINTCR_KEY_Pos));   \
                __HAL_SYSCON_REGWR_LOCK();                                                                                      \
            }while(0U)

/** @brief Macro to config PAD interrupt mode as ACTIVE for deep sleep.
 */
#define __HAL_SYSCON_DEEPSLEEP_PADINT_ACTIVE()                                                                                  \
            do{                                                                                                                 \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                    \
                SET_BIT(SYSCON->PORTINTCR, SYSCON_PORTINTCR_PADDLSPCON | (SYSCON_KEY_UNLOCK << SYSCON_PORTINTCR_KEY_Pos));      \
                CLEAR_WPBIT(SYSCON->PORTINTCR, SYSCON_PORTINTCR_PADINTSEL, (SYSCON_KEY_UNLOCK << SYSCON_PORTINTCR_KEY_Pos));    \
                __HAL_SYSCON_REGWR_LOCK();                                                                                      \
            }while(0U)


/** @brief  Macro to select low power timer gate signal input source from gpio.
 * @param  __SOURCE__: source for LPTIM gate input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : LPTIM_GATE alternate function is low power timer gate signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is low power timer gate signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is low power timer gate signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is low power timer gate signal input source
 */
#define __HAL_SYSCON_LPTIM_GATE(__SOURCE__)                                                                                         \
            do{                                                                                                                     \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                        \
                MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_LPTIM_GATE_SEL_Msk, ((__SOURCE__) << SYSCON_PORTCR_LPTIM_GATE_SEL_Pos));   \
                __HAL_SYSCON_REGWR_LOCK();                                                                                          \
            }while(0U)


/** @brief  Macro to select timer11 gate signal input source from gpio.
 * @param  __SOURCE__: source for TIM11 gate input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM11_GATE alternate function is timer11 gate signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is timer11 gate signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is timer11 gate signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is timer11 gate signal input source
 */
#define __HAL_SYSCON_TIM11_GATE(__SOURCE__)                                                                                         \
            do{                                                                                                                     \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                        \
                MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_TIM11_GATE_SEL_Msk, ((__SOURCE__) << SYSCON_PORTCR_TIM11_GATE_SEL_Pos));   \
                __HAL_SYSCON_REGWR_LOCK();                                                                                          \
            }while(0U)


/** @brief  Macro to select timer10 gate signal input source from gpio.
 * @param  __SOURCE__: source for TIM10 gate input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM10_GATE alternate function is timer10 gate signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is timer10 gate signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is timer10 gate signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is timer10 gate signal input source
 */
#define __HAL_SYSCON_TIM10_GATE(__SOURCE__)                                                                                         \
            do{                                                                                                                     \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                        \
                MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_TIM10_GATE_SEL_Msk, ((__SOURCE__) << SYSCON_PORTCR_TIM10_GATE_SEL_Pos));   \
                __HAL_SYSCON_REGWR_LOCK();                                                                                          \
            }while(0U)


/** @brief  Macro to select spi slave mode NCS signal input source from gpio.
 * @param  __SOURCE__: source for spi NCS signal input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_SPISSN_HIGHLEVEL: high level is spi NCS input source
 *         @arg SYSCON_SPISSN_PA3      : PA3  is spi NCS input source
 *         @arg SYSCON_SPISSN_PA4      : PA4  is spi NCS input source
 *         @arg SYSCON_SPISSN_PA6      : PA6  is spi NCS input source
 *         @arg SYSCON_SPISSN_PA8      : PA8  is spi NCS input source
 *         @arg SYSCON_SPISSN_PA9      : PA9  is spi NCS input source
 *         @arg SYSCON_SPISSN_PA12     : PA12 is spi NCS input source
 *         @arg SYSCON_SPISSN_PA15     : PA15 is spi NCS input source
 *         @arg SYSCON_SPISSN_PB1      : PB1  is spi NCS input source
 *         @arg SYSCON_SPISSN_PB2      : PB2  is spi NCS input source
 *         @arg SYSCON_SPISSN_PB5      : PB5  is spi NCS input source
 *         @arg SYSCON_SPISSN_PB6      : PB6  is spi NCS input source
 *         @arg SYSCON_SPISSN_PB9      : PB9  is spi NCS input source
 *         @arg SYSCON_SPISSN_PB10     : PB10 is spi NCS input source
 *         @arg SYSCON_SPISSN_PB12     : PB12 is spi NCS input source
 *         @arg SYSCON_SPISSN_PB14     : PB14 is spi NCS input source
 */
#define __HAL_SYSCON_SPISSN(__SOURCE__)                                                                                     \
            do{                                                                                                             \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                \
                MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_SPISSN_SEL_Msk, ((__SOURCE__) << SYSCON_PORTCR_SPISSN_SEL_Pos));   \
                __HAL_SYSCON_REGWR_LOCK();                                                                                  \
            }while(0U)


#if defined(CONFIG_USE_ZB32L030)
/** @brief  Macro to select spi1 slave mode NCS signal input source from gpio.
 * @param  __SOURCE__: source for spi NCS signal input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_SPISSN_HIGHLEVEL: high level is spi NCS input source
 *         @arg SYSCON_SPISSN_PA3      : PA3  is spi NCS input source
 *         @arg SYSCON_SPISSN_PA4      : PA4  is spi NCS input source
 *         @arg SYSCON_SPISSN_PA6      : PA6  is spi NCS input source
 *         @arg SYSCON_SPISSN_PA8      : PA8  is spi NCS input source
 *         @arg SYSCON_SPISSN_PA9      : PA9  is spi NCS input source
 *         @arg SYSCON_SPISSN_PA12     : PA12 is spi NCS input source
 *         @arg SYSCON_SPISSN_PA15     : PA15 is spi NCS input source
 *         @arg SYSCON_SPISSN_PB1      : PB1  is spi NCS input source
 *         @arg SYSCON_SPISSN_PB2      : PB2  is spi NCS input source
 *         @arg SYSCON_SPISSN_PB5      : PB5  is spi NCS input source
 *         @arg SYSCON_SPISSN_PB6      : PB6  is spi NCS input source
 *         @arg SYSCON_SPISSN_PB9      : PB9  is spi NCS input source
 *         @arg SYSCON_SPISSN_PB10     : PB10 is spi NCS input source
 *         @arg SYSCON_SPISSN_PB12     : PB12 is spi NCS input source
 *         @arg SYSCON_SPISSN_PB14     : PB14 is spi NCS input source
 */
#define __HAL_SYSCON_SPI1SSN(__SOURCE__)                                                                                    \
            do{                                                                                                             \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                \
                MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_SPI1SSN_SEL_Msk, ((__SOURCE__) << SYSCON_PORTCR_SPI1SSN_SEL_Pos));  \
                __HAL_SYSCON_REGWR_LOCK();                                                                                  \
            }while(0U)

#endif  /* CONFIG_USE_ZB32L030 */

/** @brief  Macro to select pca cap4 signal input source from gpio.
 * @param  __SOURCE__: source for pca cap4 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : PCA_CH4 alternate function is pca cap4 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is pca cap4 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is pca cap4 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap4 signal input source
 */
#define __HAL_SYSCON_PCA_CAP4(__SOURCE__)                                                                                   \
            do{                                                                                                             \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                \
                MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP4_SEL_Msk, ((__SOURCE__) << SYSCON_PCACR_PCA_CAP4_SEL_Pos));  \
                __HAL_SYSCON_REGWR_LOCK();                                                                                  \
            }while(0U)


/** @brief  Macro to select pca cap3 signal input source from gpio.
 * @param  __SOURCE__: source for pca cap3 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : PCA_CH3 alternate function is pca cap3 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is pca cap3 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is pca cap3 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap3 signal input source
 */
#define __HAL_SYSCON_PCA_CAP3(__SOURCE__)                                                                                   \
            do{                                                                                                             \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                \
                MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP3_SEL_Msk, ((__SOURCE__) << SYSCON_PCACR_PCA_CAP3_SEL_Pos));  \
                __HAL_SYSCON_REGWR_LOCK();                                                                                  \
            }while(0U)


/** @brief  Macro to select pca cap2 signal input source from gpio.
 * @param  __SOURCE__: source for pca cap2 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : PCA_CH2 alternate function is pca cap2 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is pca cap2 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is pca cap2 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap2 signal input source
 */
#define __HAL_SYSCON_PCA_CAP2(__SOURCE__)                                                                                   \
            do{                                                                                                             \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                \
                MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP2_SEL_Msk, ((__SOURCE__) << SYSCON_PCACR_PCA_CAP2_SEL_Pos));  \
                __HAL_SYSCON_REGWR_LOCK();                                                                                  \
            }while(0U)


/** @brief  Macro to select pca cap1 signal input source from gpio.
 * @param  __SOURCE__: source for pca cap1 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : PCA_CH1 alternate function is pca cap1 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is pca cap1 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is pca cap1 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap1 signal input source
 */
#define __HAL_SYSCON_PCA_CAP1(__SOURCE__)                                                                                   \
            do{                                                                                                             \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                \
                MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP1_SEL_Msk, ((__SOURCE__) << SYSCON_PCACR_PCA_CAP1_SEL_Pos));  \
                __HAL_SYSCON_REGWR_LOCK();                                                                                  \
            }while(0U)


/** @brief  Macro to select pca cap0 signal input source from gpio.
 * @param  __SOURCE__: source for pca cap0 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : PCA_CH0 alternate function is pca cap0 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is pca cap0 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is pca cap0 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap0 signal input source
 */
#define __HAL_SYSCON_PCA_CAP0(__SOURCE__)                                                                                   \
            do{                                                                                                             \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                \
                MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP0_SEL_Msk, ((__SOURCE__) << SYSCON_PCACR_PCA_CAP0_SEL_Pos));  \
                __HAL_SYSCON_REGWR_LOCK();                                                                                  \
            }while(0U)


/** @brief  Macro to select timer1 break signal input source from other peripheral.
 * @param  __SOURCE__: source for timer1 break signal input
 *         This parameter can be any combination the following values:
 *         @arg SYSCON_TIM1_CLKFAILBRKEN: clock fail is timer1 break signal input source
 *         @arg SYSCON_TIM1_DSLPBRKEN   : deep sleep is timer1 break signal input source
 */
#define __HAL_SYSCON_TIM1_BREAKIN_SEL(__SOURCE__)                                                                                 \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1XCLKFAILBRKEN_Msk | SYSCON_TIM1CR_TIM1XDSLPBRKEN_Msk, (__SOURCE__)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to configure timer1 ocxp/ocxnp output signal when break.
 * @param  __CONFIG__: config ocxp/ocxnp output signal when break received
 *         This parameter can be one of the following values:
 *         @arg SYSCON_TIM1_OCOUT_LOWLEVEL: ocxp/ocxnp output low level when break received
 *         @arg SYSCON_TIM1_OCOUT_BYTIM1  : ocxp/ocxnp output controlled by timer1 configuration when break received
 */
#define __HAL_SYSCON_TIM1_BREAKOUT_CFG(__CONFIG__)                                           \
            do{                                                                              \
                __HAL_SYSCON_REGWR_UNLOCK();                                                 \
                MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1XBRKOUTCFG_Msk, (__CONFIG__));  \
                __HAL_SYSCON_REGWR_LOCK();                                                   \
            }while(0U)


/** @brief  Macro to select timer1 etr signal input source from gpio.
 * @param  __SOURCE__: source for timer1 etr input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_TIM_ETR_LOWLEVEL : low level is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA1      : PA1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA2      : PA2 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3      : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB4      : PB4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB5      : PB5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA0      : PA0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD0      : PD0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC5      : PC5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC6      : PC6 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC7      : PC7 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD1      : PD1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3_ALT  : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA4      : PA4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA5      : PA5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA6      : PA6 is timer1 etr input source
 */
#define __HAL_SYSCON_TIM1ETR_SEL(__SOURCE__)                                                                                  \
            do{                                                                                                               \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                  \
                MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1XETR_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1CR_TIM1XETR_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                    \
            }while(0U)


/** @brief  Macro to select tim1 ch4 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch4 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH4 alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch4 signal input source
 */
#define __HAL_SYSCON_TIM1CH4IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1XCH4IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1CR_TIM1XCH4IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim1 ch3 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch3 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH3 alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch3 signal input source
 */
#define __HAL_SYSCON_TIM1CH3IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1XCH3IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1CR_TIM1XCH3IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim1 ch2 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch2 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH2 alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch2 signal input source
 */
#define __HAL_SYSCON_TIM1CH2IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1XCH2IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1CR_TIM1XCH2IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim1 ch1 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch1 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH1 alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch1 signal input source
 */
#define __HAL_SYSCON_TIM1CH1IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1XCH1IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1CR_TIM1XCH1IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select timer1 break signal input source from other peripheral.
 * @param  __SOURCE__: source for timer1 break signal input
 *         This parameter can be any combination the following values:
 *         @arg SYSCON_TIM1A_CLKFAILBRKEN: clock fail is timer1 break signal input source
 *         @arg SYSCON_TIM1A_DSLPBRKEN   : deep sleep is timer1 break signal input source
 */
#define __HAL_SYSCON_TIM1A_BREAKIN_SEL(__SOURCE__)                                                                                 \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1ACR, SYSCON_TIM1ACR_TIM1XCLKFAILBRKEN_Msk | SYSCON_TIM1ACR_TIM1XDSLPBRKEN_Msk, (__SOURCE__)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to configure timer1 ocxp/ocxnp output signal when break.
 * @param  __CONFIG__: config ocxp/ocxnp output signal when break received
 *         This parameter can be one of the following values:
 *         @arg SYSCON_TIM1A_OCOUT_LOWLEVEL: ocxp/ocxnp output low level when break received
 *         @arg SYSCON_TIM1A_OCOUT_BYTIM1  : ocxp/ocxnp output controlled by timer1 configuration when break received
 */
#define __HAL_SYSCON_TIM1A_BREAKOUT_CFG(__CONFIG__)                                           \
            do{                                                                              \
                __HAL_SYSCON_REGWR_UNLOCK();                                                 \
                MODIFY_REG(SYSCON->TIM1ACR, SYSCON_TIM1ACR_TIM1XBRKOUTCFG_Msk, (__CONFIG__));  \
                __HAL_SYSCON_REGWR_LOCK();                                                   \
            }while(0U)


/** @brief  Macro to select timer1 etr signal input source from gpio.
 * @param  __SOURCE__: source for timer1 etr input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_TIM_ETR_LOWLEVEL : low level is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA1      : PA1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA2      : PA2 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3      : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB4      : PB4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB5      : PB5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA0      : PA0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD0      : PD0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC5      : PC5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC6      : PC6 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC7      : PC7 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD1      : PD1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3_ALT  : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA4      : PA4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA5      : PA5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA6      : PA6 is timer1 etr input source
 */
#define __HAL_SYSCON_TIM1AETR_SEL(__SOURCE__)                                                                                  \
            do{                                                                                                               \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                  \
                MODIFY_REG(SYSCON->TIM1ACR, SYSCON_TIM1ACR_TIM1XETR_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1ACR_TIM1XETR_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                    \
            }while(0U)


/** @brief  Macro to select tim1 ch4 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch4 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH4 alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch4 signal input source
 */
#define __HAL_SYSCON_TIM1ACH4IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1ACR, SYSCON_TIM1ACR_TIM1XCH4IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1ACR_TIM1XCH4IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim1 ch3 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch3 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH3 alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch3 signal input source
 */
#define __HAL_SYSCON_TIM1ACH3IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1ACR, SYSCON_TIM1ACR_TIM1XCH3IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1ACR_TIM1XCH3IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim1 ch2 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch2 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH2 alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch2 signal input source
 */
#define __HAL_SYSCON_TIM1ACH2IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1ACR, SYSCON_TIM1ACR_TIM1XCH2IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1ACR_TIM1XCH2IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim1 ch1 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch1 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH1 alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch1 signal input source
 */
#define __HAL_SYSCON_TIM1ACH1IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1ACR, SYSCON_TIM1ACR_TIM1XCH1IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1ACR_TIM1XCH1IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select timer1 break signal input source from other peripheral.
 * @param  __SOURCE__: source for timer1 break signal input
 *         This parameter can be any combination the following values:
 *         @arg SYSCON_TIM1B_CLKFAILBRKEN: clock fail is timer1 break signal input source
 *         @arg SYSCON_TIM1B_DSLPBRKEN   : deep sleep is timer1 break signal input source
 */
#define __HAL_SYSCON_TIM1B_BREAKIN_SEL(__SOURCE__)                                                                                 \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1BCR, SYSCON_TIM1BCR_TIM1XCLKFAILBRKEN_Msk | SYSCON_TIM1BCR_TIM1XDSLPBRKEN_Msk, (__SOURCE__)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to configure timer1 ocxp/ocxnp output signal when break.
 * @param  __CONFIG__: config ocxp/ocxnp output signal when break received
 *         This parameter can be one of the following values:
 *         @arg SYSCON_TIM1B_OCOUT_LOWLEVEL: ocxp/ocxnp output low level when break received
 *         @arg SYSCON_TIM1B_OCOUT_BYTIM1  : ocxp/ocxnp output controlled by timer1 configuration when break received
 */
#define __HAL_SYSCON_TIM1B_BREAKOUT_CFG(__CONFIG__)                                           \
            do{                                                                              \
                __HAL_SYSCON_REGWR_UNLOCK();                                                 \
                MODIFY_REG(SYSCON->TIM1BCR, SYSCON_TIM1BCR_TIM1XBRKOUTCFG_Msk, (__CONFIG__));  \
                __HAL_SYSCON_REGWR_LOCK();                                                   \
            }while(0U)


/** @brief  Macro to select timer1 etr signal input source from gpio.
 * @param  __SOURCE__: source for timer1 etr input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_TIM_ETR_LOWLEVEL : low level is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA1      : PA1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA2      : PA2 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3      : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB4      : PB4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB5      : PB5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA0      : PA0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD0      : PD0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC5      : PC5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC6      : PC6 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC7      : PC7 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD1      : PD1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3_ALT  : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA4      : PA4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA5      : PA5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA6      : PA6 is timer1 etr input source
 */
#define __HAL_SYSCON_TIM1BETR_SEL(__SOURCE__)                                                                                  \
            do{                                                                                                               \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                  \
                MODIFY_REG(SYSCON->TIM1BCR, SYSCON_TIM1BCR_TIM1XETR_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1BCR_TIM1XETR_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                    \
            }while(0U)


/** @brief  Macro to select tim1 ch4 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch4 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH4 alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch4 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch4 signal input source
 */
#define __HAL_SYSCON_TIM1BCH4IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1BCR, SYSCON_TIM1BCR_TIM1XCH4IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1BCR_TIM1XCH4IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim1 ch3 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch3 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH3 alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch3 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch3 signal input source
 */
#define __HAL_SYSCON_TIM1BCH3IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1BCR, SYSCON_TIM1BCR_TIM1XCH3IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1BCR_TIM1XCH3IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim1 ch2 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch2 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH2 alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch2 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch2 signal input source
 */
#define __HAL_SYSCON_TIM1BCH2IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1BCR, SYSCON_TIM1BCR_TIM1XCH2IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1BCR_TIM1XCH2IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim1 ch1 signal input source from gpio.
 * @param  __SOURCE__: source for tim1 ch1 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM1_CH1 alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch1 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim1 ch1 signal input source
 */
#define __HAL_SYSCON_TIM1BCH1IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM1BCR, SYSCON_TIM1BCR_TIM1XCH1IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM1BCR_TIM1XCH1IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)





/** @brief  Macro to select timer2 etr signal input source from gpio.
 * @param  __SOURCE__: source for timer2 etr input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_TIM_ETR_LOWLEVEL : low level is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA1      : PA1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA2      : PA2 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3      : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB4      : PB4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB5      : PB5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA0      : PA0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD0      : PD0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC5      : PC5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC6      : PC6 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC7      : PC7 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD1      : PD1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3_ALT  : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA4      : PA4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA5      : PA5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA6      : PA6 is timer1 etr input source
 */
#define __HAL_SYSCON_TIM2ETR_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                 \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                    \
                MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2XETR_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2CR_TIM2XETR_SEL_Pos));   \
                __HAL_SYSCON_REGWR_LOCK();                                                                                      \
            }while(0U)


/** @brief  Macro to select tim2 ch4 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch4 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH4 alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch4 signal input source
 */
#define __HAL_SYSCON_TIM2CH4IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2XCH4IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2CR_TIM2XCH4IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch3 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch3 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH3 alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch3 signal input source
 */
#define __HAL_SYSCON_TIM2CH3IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2XCH3IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2CR_TIM2XCH3IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch2 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch2 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH2 alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch2 signal input source
 */
#define __HAL_SYSCON_TIM2CH2IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2XCH2IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2CR_TIM2XCH2IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch1 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch1 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH1 alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch1 signal input source
 */
#define __HAL_SYSCON_TIM2CH1IN_SEL(__SOURCE__)                                                                                    \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2XCH1IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2CR_TIM2XCH1IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select timer2 etr signal input source from gpio.
 * @param  __SOURCE__: source for timer2 etr input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_TIM_ETR_LOWLEVEL : low level is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA1      : PA1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA2      : PA2 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3      : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB4      : PB4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB5      : PB5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA0      : PA0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD0      : PD0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC5      : PC5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC6      : PC6 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC7      : PC7 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD1      : PD1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3_ALT  : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA4      : PA4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA5      : PA5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA6      : PA6 is timer1 etr input source
 */
#define __HAL_SYSCON_TIM2AETR_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                 \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                    \
                MODIFY_REG(SYSCON->TIM2ACR, SYSCON_TIM2ACR_TIM2XETR_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2ACR_TIM2XETR_SEL_Pos));\
                __HAL_SYSCON_REGWR_LOCK();                                                                                      \
            }while(0U)


/** @brief  Macro to select tim2 ch4 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch4 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH4 alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch4 signal input source
 */
#define __HAL_SYSCON_TIM2ACH4IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2ACR, SYSCON_TIM2ACR_TIM2XCH4IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2ACR_TIM2XCH4IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch3 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch3 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH3 alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch3 signal input source
 */
#define __HAL_SYSCON_TIM2ACH3IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2ACR, SYSCON_TIM2ACR_TIM2XCH3IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2ACR_TIM2XCH3IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch2 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch2 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH2 alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch2 signal input source
 */
#define __HAL_SYSCON_TIM2ACH2IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2ACR, SYSCON_TIM2ACR_TIM2XCH2IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2ACR_TIM2XCH2IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch1 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch1 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH1 alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch1 signal input source
 */
#define __HAL_SYSCON_TIM2ACH1IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2ACR, SYSCON_TIM2ACR_TIM2XCH1IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2ACR_TIM2XCH1IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)



/** @brief  Macro to select timer2 etr signal input source from gpio.
 * @param  __SOURCE__: source for timer2 etr input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_TIM_ETR_LOWLEVEL : low level is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA1      : PA1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA2      : PA2 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3      : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB4      : PB4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB5      : PB5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA0      : PA0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD0      : PD0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC5      : PC5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC6      : PC6 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC7      : PC7 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD1      : PD1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3_ALT  : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA4      : PA4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA5      : PA5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA6      : PA6 is timer1 etr input source
 */
#define __HAL_SYSCON_TIM2BETR_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                 \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                    \
                MODIFY_REG(SYSCON->TIM2BCR, SYSCON_TIM2BCR_TIM2XETR_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2BCR_TIM2XETR_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                      \
            }while(0U)


/** @brief  Macro to select tim2 ch4 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch4 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH4 alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch4 signal input source
 */
#define __HAL_SYSCON_TIM2BCH4IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2BCR, SYSCON_TIM2BCR_TIM2XCH4IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2BCR_TIM2XCH4IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch3 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch3 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH3 alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch3 signal input source
 */
#define __HAL_SYSCON_TIM2BCH3IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2BCR, SYSCON_TIM2BCR_TIM2XCH3IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2BCR_TIM2XCH3IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch2 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch2 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH2 alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch2 signal input source
 */
#define __HAL_SYSCON_TIM2BCH2IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2BCR, SYSCON_TIM2BCR_TIM2XCH2IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2BCR_TIM2XCH2IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch1 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch1 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH1 alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch1 signal input source
 */
#define __HAL_SYSCON_TIM2BCH1IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2BCR, SYSCON_TIM2BCR_TIM2XCH1IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2BCR_TIM2XCH1IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)



/** @brief  Macro to select timer2 etr signal input source from gpio.
 * @param  __SOURCE__: source for timer2 etr input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_TIM_ETR_LOWLEVEL : low level is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA1      : PA1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA2      : PA2 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3      : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB4      : PB4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PB5      : PB5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA0      : PA0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD0      : PD0 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC5      : PC5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC6      : PC6 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PC7      : PC7 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PD1      : PD1 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA3_ALT  : PA3 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA4      : PA4 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA5      : PA5 is timer1 etr input source
 *         @arg SYSCON_TIM_ETR_PA6      : PA6 is timer1 etr input source
 */
#define __HAL_SYSCON_TIM2CETR_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                 \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                    \
                MODIFY_REG(SYSCON->TIM2CCR, SYSCON_TIM2CCR_TIM2XETR_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2CCR_TIM2XETR_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                      \
            }while(0U)


/** @brief  Macro to select tim2 ch4 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch4 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH4 alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch4 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch4 signal input source
 */
#define __HAL_SYSCON_TIM2CCH4IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2CCR, SYSCON_TIM2CCR_TIM2XCH4IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2CCR_TIM2XCH4IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch3 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch3 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH3 alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch3 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch3 signal input source
 */
#define __HAL_SYSCON_TIM2CCH3IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2CCR, SYSCON_TIM2CCR_TIM2XCH3IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2CCR_TIM2XCH3IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch2 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch2 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH2 alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch2 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch2 signal input source
 */
#define __HAL_SYSCON_TIM2CCH2IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2CCR, SYSCON_TIM2CCR_TIM2XCH2IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2CCR_TIM2XCH2IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/** @brief  Macro to select tim2 ch1 signal input source from gpio.
 * @param  __SOURCE__: source for tim2 ch1 input
 *         This parameter can be one of the following values:
 *         @arg SYSCON_DEFAULT   : TIM2_CH1 alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_UART0_RXD : UART0_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_UART1_RXD : UART1_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch1 signal input source
 *         @arg SYSCON_SIRC      : SIRC is tim2 ch1 signal input source
 */
#define __HAL_SYSCON_TIM2CCH1IN_SEL(__SOURCE__)                                                                                   \
            do{                                                                                                                   \
                __HAL_SYSCON_REGWR_UNLOCK();                                                                                      \
                MODIFY_REG(SYSCON->TIM2CCR, SYSCON_TIM2CCR_TIM2XCH1IN_SEL_Msk, ((__SOURCE__) << SYSCON_TIM2CCR_TIM2XCH1IN_SEL_Pos)); \
                __HAL_SYSCON_REGWR_LOCK();                                                                                        \
            }while(0U)


/**
 * @}
 */


/**
 * @}
 */ /* End of group SYSCON */

#ifdef __cplusplus
}
#endif

#endif /* __ZB32L03x_HAL_SYSCON_H */

