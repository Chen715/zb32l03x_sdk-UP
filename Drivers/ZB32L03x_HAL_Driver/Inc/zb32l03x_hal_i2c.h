/**
 ******************************************************************************
 * @file    zb32l03x_hal_i2c.h
 * @author  Wei-Lun
 * @Version V2.0.0
 * @Date    2022/01/06
 * @brief   Header file of I2C HAL module.
 ******************************************************************************
 **/

#ifndef __ZB32L03x_HAL_I2C_H
#define __ZB32L03x_HAL_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "zb32l03x_hal_def.h"


/** @defgroup I2C_Exported_Types I2C Exported Types
  * @{
  */

#define HAL_I2C_BLOCKING          0xFFFF

/**
  * @brief  HAL State structure definition
  *
  */
typedef enum
{
    HAL_I2C_STATE_RESET     = 0x00U,    /*!< Peripheral is not yet Initialized         */
    HAL_I2C_STATE_NONE,                 /*!< I2C not do anything                       */
    HAL_I2C_STATE_READY,                /*!< Peripheral Initialized and ready for use  */
    HAL_I2C_STATE_BUSY,                 /*!< An internal process is ongoing            */
    HAL_I2C_STATE_BUSY_TX,              /*!< Data Transmission process is ongoing      */
    HAL_I2C_STATE_BUSY_RX,              /*!< Data Reception process is ongoing         */
    HAL_I2C_STATE_ABORT,                /*!< Abort user request ongoing                */
    HAL_I2C_STATE_TIMEOUT,              /*!< Timeout state                             */
    HAL_I2C_STATE_ERROR                 /*!< Error                                     */

} HAL_I2C_StateTypeDef;


/**
  * @brief  HAL Mode structure definition
 */
typedef enum
{
    HAL_I2C_MODE_NONE   = 0x00U,   /*!< No I2C communication on going             */
    HAL_I2C_MODE_MASTER = 0x10U,   /*!< I2C communication is in Master Mode       */
    HAL_I2C_MODE_SLAVE  = 0x20U,   /*!< I2C communication is in Slave Mode        */
} HAL_I2C_ModeTypeDef;


/**
  * @brief  I2C Initial Configuration Structure definition
  */
typedef struct
{
    uint32_t                SpeedClock;    /*!< i2c speed clock set, SpeedClock = PCLK/(8*(baudcr+1)), uint KHz*/

    uint8_t                 SlaveAddr;      /*!< slave address */

    uint8_t                 BroadAck;       /*!< ACK enable or disable when as slave.
                                                This parameter can be a value of @ref I2C_BROAD */
    HAL_I2C_ModeTypeDef     Mode;
} I2C_InitTypeDef;

/**
  * @brief  I2C handle Structure definition
  */
typedef struct
{
    I2C_TypeDef                 *Instance;

    I2C_InitTypeDef             Init;

    uint8_t                    *pTxBuffPtr;    /*!< Pointer to I2C Tx transfer Buffer        */

    uint16_t                   TxXferSize;     /*!< I2C Tx Transfer size                     */
    __IO uint16_t              TxXferCount;    /*!< I2C Tx Transfer Counter                  */

    uint8_t                    *pRxBuffPtr;    /*!< Pointer to I2C Rx transfer Buffer        */

    uint16_t                   RxXferSize;     /*!< I2C Rx Transfer size                     */
    __IO uint16_t              RxXferCount;    /*!< I2C Rx Transfer Counter                  */

    __IO uint16_t               DevAddress;     /*!< I2C Target device address                */

    __IO HAL_I2C_ModeTypeDef    Mode;           /*!< I2C communication mode                   */

    __IO HAL_I2C_StateTypeDef   State;          /*!< I2C communication state                  */

    __IO uint16_t               ErrorCode;      /*!< I2C Error code                           */

    __IO uint8_t                HasRecvAddr;    /*!< Has receive address or not               */

    HAL_LockTypeDef             Lock;           /*!< I2C locking object                       */

} I2C_HandleTypeDef;


/**
  * @}
  */


/** @defgroup I2C_Exported_Constants I2C Exported Constants
  * @{
  */


/** @defgroup I2C_Error_Code I2C Error Code
  * @brief    I2C Error Code
  * @{
  */
#define HAL_I2C_ERROR_NONE                  0x00U    /*!< No error           */
#define HAL_I2C_ERROR_TIMEOUT               0x20U    /*!< Timeout Error      */
#define HAL_I2C_ERROR_UNKNOWN               0x30U    /*!< Unknown Error      */

/**
  * @}
  */


/** @defgroup I2C_BROAD  I2C broad ack enable/disable
  * @{
  */
#define I2C_BROAD_ACK_ENABLE                (0x01U)
#define I2C_BROAD_ACK_DISABLE               (0x00U)

/**
  * @}
  */

/** @defgroup I2C_HIGH_RATE  I2C high rate enable/disable
  * @{
  */
#define I2C_HIGH_RATE_ENABLE                I2C_CR_H1M
#define I2C_HIGH_RATE_DISABLE               (0x00U)

/**
  * @}
  */

/** @defgroup I2C_Status_definition I2C Status definition
  * @{
  */
#define I2C_STATUS_ERROR_UNDER                 (0x00U)
#define I2C_STATUS_IDLE                        (0xF8U)

#define I2C_STATUS_MASTER_TX_START             (0x08U)
#define I2C_STATUS_MASTER_TX_RESTART           (0x10U)
#define I2C_STATUS_MASTER_TX_SLAW_ACK          (0x18U) // sent (SlaveAddress + W-bit) and received ACK
#define I2C_STATUS_MASTER_TX_SLAW_NOACK        (0x20U)
#define I2C_STATUS_MASTER_TX_DATA_ACK          (0x28U) // sent data and received ACK
#define I2C_STATUS_MASTER_TX_DATA_NOACK        (0x30U)
#define I2C_STATUS_MASTER_TX_LOST_SCL          (0x38U)


#define I2C_STATUS_MASTER_RX_START             (0x08U)
#define I2C_STATUS_MASTER_RX_RESTART           (0x10U)
#define I2C_STATUS_MASTER_RX_SLAW_ACK          (0x40U) // sent (SlaveAddress + R-bit) and received ACK
#define I2C_STATUS_MASTER_RX_SLAW_NOACK        (0x48U)
#define I2C_STATUS_MASTER_RX_DATA_ACK          (0x50U) // received data and received ACK
#define I2C_STATUS_MASTER_RX_DATA_NOACK        (0x58U)
#define I2C_STATUS_MASTER_RX_LOST_SCL          (0x38U)


#define I2C_STATUS_SLAVE_TX_SLAW_ACK           (0xA8U)
#define I2C_STATUS_SLAVE_TX_LOST_SCL           (0xB0U)
#define I2C_STATUS_SLAVE_TX_DATA_ACK           (0xB8U)
#define I2C_STATUS_SLAVE_TX_DATA_NOACK         (0xC0U)
#define I2C_STATUS_SLAVE_TX_DATA_LAST          (0xC8U)


#define I2C_STATUS_SLAVE_RX_SLAW_ACK           (0x60U)
#define I2C_STATUS_SLAVE_RX_SADDR_LOST_SCL     (0x68U)
#define I2C_STATUS_SLAVE_RX_BROAD_ACK          (0x70U) // received broad address and sent ACK
#define I2C_STATUS_SLAVE_RX_BADDR_LOST_SCL     (0x78U)
#define I2C_STATUS_SLAVE_RX_SDATA_ACK          (0x80U) // received data and sent ACK
#define I2C_STATUS_SLAVE_RX_SDATA_NOACK        (0x88U)
#define I2C_STATUS_SLAVE_RX_BDATA_ACK          (0x90U) // received data (with broad address) and sent ACK
#define I2C_STATUS_SLAVE_RX_BDATA_NOACK        (0x98U)

#define I2C_STATUS_SLAVE_STOP_RESTART          (0xA0U)

/**
  * @}
  */

/** @defgroup I2C_Read_Write_Bit I2C transfer direction selection
 * @{
 */

#define I2C_WRITE_BIT           ((uint8_t)0x00)
#define I2C_READ_BIT            ((uint8_t)0x01)

/**
 * @}
 */


/**
 * @}
 */


/** @defgroup I2C_Exported_Macros I2C Exported Macros
 * @{
 */

/**
 * @brief  Enable/Disable the I2C peripheral.
 * @param  __HANDLE__: I2C handle
 * @retval None
 */
#define __HAL_I2C_ENABLE(__HANDLE__)                SET_BIT((__HANDLE__)->Instance->CR, I2C_CR_ENS)
#define __HAL_I2C_DISABLE(__HANDLE__)               CLEAR_BIT((__HANDLE__)->Instance->CR, I2C_CR_ENS)


/** @brief  Check whether the I2C interrupt SI is enabled or not.
 * @param  __HANDLE__ specifies the I2C Handle.
 * @retval The new state of __INTERRUPT__ (HIGH or LOW).
 */
#define __HAL_I2C_GET_SI_FLAG(__HANDLE__)           (((__HANDLE__)->Instance->CR & (I2C_CR_SI)) ? HIGH : LOW)

/** @brief  Clear the I2C interrupt set flags which are cleared by write 0 to specific bit.
 * @param  __HANDLE__ specifies the I2C Handle.
 * @retval None
 */
#define __HAL_I2C_CLR_SI_FLAG(__HANDLE__)           CLEAR_BIT((__HANDLE__)->Instance->CR, I2C_CR_SI)

/**
 *  \brief  Set/Clear start bit
 *
 *  \param [in] __HANDLE__      The handle of I2C
 *  \return                     None
 */
#define __HAL_I2C_SET_START_FLAG(__HANDLE__)        SET_BIT((__HANDLE__)->Instance->CR, I2C_CR_STA_Msk)
#define __HAL_I2C_CLR_START_FLAG(__HANDLE__)        CLEAR_BIT((__HANDLE__)->Instance->CR, I2C_CR_STA_Msk)

/**
 *  \brief  Set/Clear stop bit
 *
 *  \param [in] __HANDLE__      The handle of I2C
 *  \return                     None
 */
#define __HAL_I2C_SET_STOP_FLAG(__HANDLE__)         SET_BIT((__HANDLE__)->Instance->CR, I2C_CR_STO_Msk)
#define __HAL_I2C_CLR_STOP_FLAG(__HANDLE__)         CLEAR_BIT((__HANDLE__)->Instance->CR, I2C_CR_STO_Msk)

/**
 *  \brief  Set/Clear Ack bit
 *
 *  \param [in] __HANDLE__      The handle of I2C
 *  \return                     None
 */
#define __HAL_I2C_SET_ACK_FLAG(__HANDLE__)         SET_BIT((__HANDLE__)->Instance->CR, I2C_CR_AA_Msk)
#define __HAL_I2C_CLR_ACK_FLAG(__HANDLE__)         CLEAR_BIT((__HANDLE__)->Instance->CR, I2C_CR_AA_Msk)

/**
 *  \brief  Enable/Disable General Call
 *
 *  \param [in] __HANDLE__      The handle of I2C
 *  \return                     None
 */
#define __HAL_I2C_GC_ENABLE(__HANDLE__)             SET_BIT((__HANDLE__)->Instance->ADDR, I2C_ADDR_GC_Msk)
#define __HAL_I2C_GC_DISABLE(__HANDLE__)            CLEAR_BIT((__HANDLE__)->Instance->ADDR, I2C_ADDR_GC_Msk)

/**
 *  \brief  Get current status of I2C
 *
 *  \param [in] __HANDLE__      The handle of I2C
 *  \return                     The status of I2C
 */
#define __HAL_I2C_Get_Status(__HANDLE__)            ((__HANDLE__)->Instance->SR & I2C_SR_I2CSTA_Msk)

/** @brief  CHECK the parameter used init
  * @param
  * @retval None
  */

#define IS_I2C_ALL_INSTANCE(INSTANCE)       ((INSTANCE) == I2C)
#define IS_I2C_SLAVE_MODE(MODE)             ((MODE) == HAL_I2C_MODE_SLAVE)
#define IS_I2C_MASTER_MODE(MODE)            ((MODE) == HAL_I2C_MODE_MASTER)
#define IS_I2C_BROAD_ACK(ACK)               (((ACK) == I2C_BROAD_ACK_ENABLE) || ((ACK) == I2C_BROAD_ACK_DISABLE))
#define IS_I2C_SPEED_CLOCK(CLOCK)           ((CLOCK) <= 1000 /* KHz*/ )

/**
 * @}
 */


/**
 * @{
 */

/* Initialization/de-initialization functions  ********************************/
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c);


/* MSP functions  *************************************************************/
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);


HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddr, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint8_t DevAddr, uint8_t *pData, uint16_t *pSize, uint16_t Timeout_ms);

HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint16_t Timeout_ms);
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t *pSize, uint16_t Timeout_ms);

HAL_StatusTypeDef HAL_I2C_Master_Mem_Read(I2C_HandleTypeDef *hi2c, uint8_t DevAddr,
                                          uint8_t *pSend_buf, uint16_t tx_nbytes,
                                          uint8_t *pRecv_buf, uint16_t *pRx_nbytes,
                                          uint16_t Timeout_ms);

HAL_StatusTypeDef HAL_I2C_Master_Mem_Write(I2C_HandleTypeDef *hi2c, uint8_t DevAddr,
                                           uint8_t *pSend_buf, uint16_t tx_nbytes,
                                           uint8_t *pData_buf, uint16_t *pData_nbytes,
                                           uint16_t Timeout_ms);


HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddr, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t DevAddr, uint8_t *pData, uint8_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);

void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterTxCmpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveTxCmpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterRxCmpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveRxCmpltCallback(I2C_HandleTypeDef *hi2c);


/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif  /* __ZB32L03x_HAL_I2C_H */

