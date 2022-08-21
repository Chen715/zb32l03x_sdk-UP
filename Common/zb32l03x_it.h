/**
 ******************************************************************************
 * @file    zb32l03x_it.h
 * @author  Application Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   This file contains the headers of the interrupt handlers.
 ******************************************************************************
 */


#ifndef __ZB32L03X_IT_H
#define __ZB32L03X_IT_H

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
//                  Constant Definition
//=============================================================================

//=============================================================================
//                  Macro Definition
//=============================================================================

//=============================================================================
//                  Structure Definition
//=============================================================================

//=============================================================================
//                  Global Data Definition
//=============================================================================

//=============================================================================
//                  Private Function Definition
//=============================================================================

//=============================================================================
//                  Public Function Definition
//=============================================================================
void GPIOA_IRQHandler(void);
void GPIOB_IRQHandler(void);
void GPIOC_IRQHandler(void);
void GPIOD_IRQHandler(void);
void FLASH_IRQHandler(void);
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void UART2_3_IRQHandler(void);
void LPUART_IRQHandler(void);
void SPI0_1_IRQHandler(void);
void I2C0_1_IRQHandler(void);
void TIM10_IRQHandler(void);
void TIM11_IRQHandler(void);
void LPTIM_IRQHandler(void);
void TIM1_IRQHandler(void);
void TIM1A_IRQHandler(void);
void TIM1B_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM2A_IRQHandler(void);
void TIM2B_IRQHandler(void);
void TIM2C_IRQHandler(void);
void PCA_IRQHandler(void);
void WWDG_IRQHandler(void);
void IWDG_IRQHandler(void);
void ADC_IRQHandler(void);
void LVD_IRQHandler(void);
void VC0_1_IRQHandler(void);
void AWK_IRQHandler(void);
void OWIRE_IRQHandler(void);
void RTC_IRQHandler(void);
void CLKTRIM_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __ZB32L03X_IT_H */


