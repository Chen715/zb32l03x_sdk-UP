/**
 ******************************************************************************
 * @file    io_mapping.h
 * @author  Application Team
 * @Version V1.0.0
 * @Date    2022/01/19
 ******************************************************************************
 **/
#ifndef __ZB32L03x_IO_MAPPING_H
#define __ZB32L03x_IO_MAPPING_H

#ifdef __cplusplus
extern "C" {
#endif

#define UART1_TX_PIN                    GPIO_PIN_14
#define UART1_TX_GPIO_PORT              GPIOA
#define UART1_TX_GPIO_AF                GPIO_AF_MODE_1
#define UART1_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define UART1_RX_PIN                    GPIO_PIN_3
#define UART1_RX_GPIO_PORT              GPIOA
#define UART1_RX_GPIO_AF                GPIO_AF_MODE_1
#define UART1_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()



#ifdef __cplusplus
}
#endif


#endif /* __ZB32L03x_IO_MAPPING_H */
