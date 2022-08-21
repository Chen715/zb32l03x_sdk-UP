/**
 ******************************************************************************
 * @file    zb32l03x_hal_i2c.c
 * @author  Wei-Lun
 * @Version V2.0.0
 * @Date    2022/01/06
 * @brief
 * @endverbatim
 ******************************************************************************
 **/


#include "zb32l03x_hal.h"
#include <stdbool.h>

#if defined(HAL_I2C_MODULE_ENABLED)

/** @addtogroup I2C
  * @brief I2C HAL module driver.
  * @{
  */

//=============================================================================
//                  Constant Definition
//=============================================================================
/** @addtogroup I2C_Private_Define
 * @{
 */
#define CONFIG_I2C_TIMEOUT     20U         /*!< Timeout 20 ms             */

#if defined(CONFIG_USE_ZB32L003S)
    #define CONFIG_I2C_IRQn             I2C_IRQn
#elif defined(CONFIG_USE_ZB32L030) || defined(CONFIG_USE_ZB32L032)
    #define CONFIG_I2C_IRQn             I2C0_1_IRQn
#endif

/**
 * @}
 */

/**
 * @brief  I2CStatus enum definition
 */

typedef enum
{
    I2C_SUCCESS     = 0,    /*!< Waited i2c status flag  */
    I2C_ERROR       = 1,    /*!< No i2c status flag      */
    I2C_WAITING     = 2,    /*!< Waiting i2c status flag */
    I2C_HOLD_DATA   = 3,    /*!< I2C hold data flag      */
    I2C_FORCE_STOP  = 4,    /*!< I2C force stop flag     */
    I2C_RESTART     = 5,    /*!< I2C restart flag        */
} I2CStatus;

typedef enum i2c_tx_stage
{
    I2C_TX_STAGE_START_BIT    = 0,
    I2C_TX_STAGE_ADDRESS,
    I2C_TX_STAGE_DATA,

} i2c_tx_stage_t;

#define I2C_START_BIT_H        (0x1u << I2C_CR_STA_Pos)
#define I2C_START_BIT_L        0x0u

#define I2C_STOP_BIT_H         (0x1u << I2C_CR_STO_Pos)
#define I2C_STOP_BIT_L         0x0u

#define I2C_ACK_BIT_H          (0x1u << I2C_CR_AA_Pos)
#define I2C_ACK_BIT_L          0x0u
//=============================================================================
//                  Macro Definition
//=============================================================================
#define __I2C_FORCE_DISABLE_ISR(irq_id)                 \
            do {                                        \
                HAL_NVIC_DisableIRQ((irq_id));          \
                HAL_NVIC_ClearPendingIRQ((irq_id));     \
            } while(0)

#define __I2C_FORCE_ENABLE_ISR(irq_id)                  \
            do {                                        \
                HAL_NVIC_ClearPendingIRQ((irq_id));     \
                HAL_NVIC_EnableIRQ((irq_id));           \
            } while(0)

#define __I2C_CONFIG(start_bit, stop_bit, ack_bit)                          \
            WRITE_REG_MASK(hi2c->Instance->CR,                              \
                           I2C_CR_STA_Msk | I2C_CR_STO_Msk | I2C_CR_AA_Msk, \
                           (start_bit) | (stop_bit) | (ack_bit))

//=============================================================================
//                  Structure Definition
//=============================================================================

//=============================================================================
//                  Global Data Definition
//=============================================================================

//=============================================================================
//                  Private Function Definition
//=============================================================================

static HAL_StatusTypeDef
_I2C_Wait_SI_Flag(I2C_HandleTypeDef *hi2c, uint32_t timeout_ms)
{
    uint32_t    start_ticks = 0;

    start_ticks = HAL_GetTick();

    while( __HAL_I2C_GET_SI_FLAG(hi2c) == LOW )
    {
        if( (HAL_GetTick() - start_ticks) > timeout_ms )
        {
            hi2c->ErrorCode = HAL_I2C_ERROR_TIMEOUT;
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}


static I2CStatus
_I2C_Master_Send_Byte(I2C_HandleTypeDef *hi2c, uint8_t **ppData, uint32_t is_end)
{
    __IO uint32_t   *pData_reg = &hi2c->Instance->DATA;
    I2CStatus       rval = I2C_SUCCESS;
    uint8_t         status = 0;

    status = __HAL_I2C_Get_Status(hi2c);

    switch( status )
    {
        case I2C_STATUS_MASTER_TX_START:
        case I2C_STATUS_MASTER_TX_RESTART:
        case I2C_STATUS_MASTER_TX_SLAW_ACK:
            *((__IO uint8_t*)pData_reg) = *((__IO uint8_t*)(*ppData));
            *ppData = *ppData + 1;
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_L, I2C_ACK_BIT_L);
            break;

        case I2C_STATUS_MASTER_TX_SLAW_NOACK:
        case I2C_STATUS_MASTER_TX_DATA_NOACK:
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_H, I2C_ACK_BIT_L);
            break;

        case I2C_STATUS_MASTER_TX_DATA_ACK:
            if( is_end )
            {
                __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_H, I2C_ACK_BIT_L);
                break;
            }

            *((__IO uint8_t*)pData_reg) = *((__IO uint8_t*)(*ppData));
            *ppData = *ppData + 1;
            break;

        case I2C_STATUS_MASTER_TX_LOST_SCL:
            __I2C_CONFIG(I2C_START_BIT_H, I2C_STOP_BIT_L, I2C_ACK_BIT_L);
            break;

        default:
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_H, I2C_ACK_BIT_L);
            rval = I2C_ERROR;
            break;
    }

    __HAL_I2C_CLR_SI_FLAG(hi2c);
    return rval;
}

static I2CStatus
_I2C_Master_Recv_Byte(I2C_HandleTypeDef *hi2c, uint8_t **ppData, uint32_t is_end)
{
    __IO uint32_t   *pData_reg = &hi2c->Instance->DATA;
    I2CStatus       rval = I2C_SUCCESS;
    uint8_t         status = 0;

    status = __HAL_I2C_Get_Status(hi2c);

    switch( status )
    {
        case I2C_STATUS_MASTER_TX_DATA_ACK:
            __I2C_CONFIG(I2C_START_BIT_H, I2C_STOP_BIT_L, I2C_ACK_BIT_L);
            break;
        case I2C_STATUS_MASTER_RX_START:
        case I2C_STATUS_MASTER_RX_RESTART:
            *((__IO uint8_t*)pData_reg) = *((__IO uint8_t*)(*ppData));
            *ppData = *ppData + 1;
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_L, I2C_ACK_BIT_L);
            break;

        case I2C_STATUS_MASTER_RX_SLAW_ACK:
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_L, I2C_ACK_BIT_H);
            break;

        case I2C_STATUS_MASTER_RX_DATA_ACK:
            *(__IO uint8_t*)(*ppData) = *((__IO uint8_t*)pData_reg);
            *ppData = *ppData + 1;

            /**
             *  FIXME: if the last bytes, slave should send NACK to master
             *          How to get the xfer length ?
             */
            __I2C_CONFIG(I2C_START_BIT_L,
                         (is_end) ? I2C_STOP_BIT_H : I2C_STOP_BIT_L,
                         I2C_ACK_BIT_H);
            break;

        case I2C_STATUS_MASTER_RX_DATA_NOACK:
            *(__IO uint8_t*)(*ppData) = *((__IO uint8_t*)pData_reg);
            *ppData = *ppData + 1;

        case I2C_STATUS_MASTER_RX_SLAW_NOACK:
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_H, I2C_ACK_BIT_H);
            break;

        case I2C_STATUS_MASTER_RX_LOST_SCL:
            __I2C_CONFIG(I2C_START_BIT_H, I2C_STOP_BIT_L, I2C_ACK_BIT_H);
            break;

        default:
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_H, I2C_ACK_BIT_L);
            rval = I2C_ERROR;
            break;
    }

    __HAL_I2C_CLR_SI_FLAG(hi2c);

    return rval;
}

static I2CStatus
_I2C_Slave_Send_Byte(I2C_HandleTypeDef *hi2c, uint8_t **ppData, uint32_t is_end)
{
    __IO uint32_t   *pData_reg = &hi2c->Instance->DATA;
    I2CStatus       rval = I2C_SUCCESS;
    uint8_t         status = 0;

    status = __HAL_I2C_Get_Status(hi2c);

    switch( status )
    {
        case I2C_STATUS_SLAVE_TX_SLAW_ACK:
            hi2c->HasRecvAddr = true;
        case I2C_STATUS_SLAVE_TX_DATA_ACK:
            if( is_end )
            {
                __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_H, I2C_ACK_BIT_H);
                break;
            }

            *((__IO uint8_t*)pData_reg) = *((__IO uint8_t*)(*ppData));
            *ppData = *ppData + 1;
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_L, I2C_ACK_BIT_H);
            break;

        case I2C_STATUS_SLAVE_TX_LOST_SCL:
            *((__IO uint8_t*)pData_reg) = *((__IO uint8_t*)(*ppData));
            *ppData = *ppData + 1;

            __I2C_CONFIG(I2C_START_BIT_H, I2C_STOP_BIT_L, I2C_ACK_BIT_H);
            break;

        case I2C_STATUS_SLAVE_TX_DATA_NOACK:
        case I2C_STATUS_SLAVE_TX_DATA_LAST:
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_L, I2C_ACK_BIT_H);
            rval = I2C_HOLD_DATA;
            break;

        case I2C_STATUS_SLAVE_STOP_RESTART: // master force stop
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_L, I2C_ACK_BIT_H);
            rval = (hi2c->HasRecvAddr) ? I2C_FORCE_STOP : I2C_RESTART;
            break;

        default:
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_H, I2C_ACK_BIT_H);
            rval = I2C_ERROR;
            break;
    }

    __HAL_I2C_CLR_SI_FLAG(hi2c);
    return rval;
}

static I2CStatus
_I2C_Slave_Recv_Byte(I2C_HandleTypeDef *hi2c, uint8_t **ppData, uint32_t is_end)
{
    __IO uint32_t   *pData_reg = &hi2c->Instance->DATA;
    I2CStatus       rval = I2C_SUCCESS;
    uint8_t         status = 0;

    status = __HAL_I2C_Get_Status(hi2c);

    switch( status )
    {
        case I2C_STATUS_SLAVE_RX_SADDR_LOST_SCL:
        case I2C_STATUS_SLAVE_RX_BADDR_LOST_SCL:
            __I2C_CONFIG(I2C_START_BIT_H, I2C_STOP_BIT_L, I2C_ACK_BIT_H);
            break;

        case I2C_STATUS_SLAVE_RX_SLAW_ACK:
        case I2C_STATUS_SLAVE_RX_SDATA_NOACK:
        case I2C_STATUS_SLAVE_RX_BDATA_NOACK:
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_L, I2C_ACK_BIT_H);
            rval = I2C_HOLD_DATA;
            break;

        case I2C_STATUS_SLAVE_RX_BROAD_ACK:
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_L, I2C_ACK_BIT_H);
            rval = I2C_HOLD_DATA;
            break;

        case I2C_STATUS_SLAVE_RX_SDATA_ACK:
            *(__IO uint8_t*)(*ppData) = *((__IO uint8_t*)pData_reg);
            *ppData = *ppData + 1;

            /**
             *  FIXME: if the last bytes, slave should send NACK to master
             *          How to get the xfer length ?
             */

            __I2C_CONFIG(I2C_START_BIT_L,
                         (is_end) ? I2C_STOP_BIT_H : I2C_STOP_BIT_L,
                         I2C_ACK_BIT_H);

            break;

        case I2C_STATUS_SLAVE_RX_BDATA_ACK:
            *(__IO uint8_t*)(*ppData) = *((__IO uint8_t*)pData_reg);
            *ppData = *ppData + 1;

            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_L, I2C_ACK_BIT_L);
            break;

        case I2C_STATUS_SLAVE_STOP_RESTART:
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_L, I2C_ACK_BIT_H);
            rval = I2C_FORCE_STOP;
            break;

        default:
            __I2C_CONFIG(I2C_START_BIT_L, I2C_STOP_BIT_H, I2C_ACK_BIT_H);
            rval = I2C_ERROR;
            break;
    }

    __HAL_I2C_CLR_SI_FLAG(hi2c);

    return rval;
}
//=============================================================================
//                  Public Function Definition
//=============================================================================

/** @addtogroup I2C_Exported_Functions
* @{
*/

/**
  * @brief  Initializes the I2C according to the specified parameters in the
  *         I2C_InitTypeDef and creates the associated handle.
  * @param  hi2c : I2C handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c)
{
    assert_param(hi2c);
    assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));
    assert_param(IS_I2C_SPEED_CLOCK(hi2c->Init.SpeedClock));

    if( !hi2c )
        return HAL_ERROR;

    if( hi2c->State == HAL_I2C_STATE_RESET )
    {
        /* Allocate lock resource and initialize it */
        __HAL_UNLOCK(hi2c);

        /* Init the low level hardware : GPIO, CLOCK, NVIC */
        HAL_I2C_MspInit(hi2c);
    }

    __HAL_I2C_DISABLE(hi2c);

    if( hi2c->Init.Mode == HAL_I2C_MODE_MASTER )
    {
        uint32_t    SCL = 0;

        SCL = ((HAL_RCC_GetPCLKFreq() / 1000) - (hi2c->Init.SpeedClock << 3)) / ((hi2c->Init.SpeedClock << 3));

        WRITE_REG_MASK(hi2c->Instance->BAUDCR, I2C_BAUDCR_TM, SCL);
        SET_BIT(hi2c->Instance->TIMRUN, I2C_TIMRUN_TME);

        __HAL_I2C_CLR_ACK_FLAG(hi2c);
    }
    else if( hi2c->Init.Mode == HAL_I2C_MODE_SLAVE )
    {
        /* Configure Slave Address */
        WRITE_REG_MASK(hi2c->Instance->ADDR, I2C_ADDR_I2CADR_Msk, hi2c->Init.SlaveAddr << I2C_ADDR_I2CADR_Pos);

        __HAL_I2C_SET_ACK_FLAG(hi2c);

        if( hi2c->Init.BroadAck == I2C_BROAD_ACK_ENABLE )
            __HAL_I2C_GC_ENABLE(hi2c);
        else
            __HAL_I2C_GC_DISABLE(hi2c);
    }
    else
        return HAL_ERROR;

    if( hi2c->Init.SpeedClock > 400 )
        SET_BIT(hi2c->Instance->CR, I2C_CR_H1M_Msk);
    else
        CLEAR_BIT(hi2c->Instance->CR, I2C_CR_H1M_Msk);

    __HAL_I2C_ENABLE(hi2c);
    __HAL_I2C_CLR_SI_FLAG(hi2c);

    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->State     = HAL_I2C_STATE_READY;
    hi2c->Mode      = HAL_I2C_MODE_NONE;
//    hi2c->PreviousState = HAL_I2C_STATE_NONE;
    return HAL_OK;
}

/**
  * @brief  DeInitializes the I2C peripheral.
  * @param  hi2c : I2C handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c)
{
    assert_param(hi2c);

    /* Check the I2C handle allocation */
    if( !hi2c )
        return HAL_ERROR;

    __HAL_LOCK(hi2c);

    hi2c->State = HAL_I2C_STATE_BUSY;

    hi2c->Instance->CR = 0x00;

    /* Disable the I2C */
    __HAL_I2C_DISABLE(hi2c);

    /* DeInit the low level hardware: CLOCK, NVIC.*/
    HAL_I2C_MspDeInit(hi2c);

    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->State     = HAL_I2C_STATE_RESET;
    hi2c->Mode      = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return HAL_OK;
}


/**
 *  @brief  HAL_I2C_Master_Transmit
 *              Transmits in master mode an amount of data in blocking mode.
 *
 *  @param [in] hi2c            Pointer to a I2C_HandleTypeDef structure that contains
 *                                  the configuration information for the specified I2C.
 *  @param [in] DevAddr         Target device address: The device 7 bits address value
 *                                  in datasheet must be shift at right before call interface
 *  @param [in] pData           Pointer to data buffer
 *  @param [in] Size            Amount of data to be sent
 *  @return                     HAL status
 */
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddr, uint8_t *pData, uint16_t Size)
{
    i2c_tx_stage_t  stage = I2C_TX_STAGE_START_BIT;
    uint16_t        tx_nbytes = 0;

    assert_param(hi2c);
    assert_param(pData);
    assert_param(Size);
    assert_param(DevAddr);

    if( hi2c->State != HAL_I2C_STATE_READY )
        return HAL_BUSY;

    __HAL_LOCK(hi2c);

    __I2C_FORCE_DISABLE_ISR(CONFIG_I2C_IRQn);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    __HAL_I2C_SET_START_FLAG(hi2c);
    stage = I2C_TX_STAGE_ADDRESS;

    while( tx_nbytes < Size )
    {
        I2CStatus       rval = I2C_SUCCESS;

        if( _I2C_Wait_SI_Flag(hi2c, CONFIG_I2C_TIMEOUT) != HAL_OK )
            break;

        if( stage == I2C_TX_STAGE_ADDRESS )
        {
            uint8_t     addr = (uint8_t)DevAddr & ~0x1u; // write mode
            uint8_t     *pAddr = 0;

            pAddr = &addr;
            rval = _I2C_Master_Send_Byte(hi2c, &pAddr, false);
            if( rval == I2C_ERROR )
            {
                hi2c->ErrorCode = HAL_I2C_ERROR_UNKNOWN;
                break;
            }

            stage = I2C_TX_STAGE_DATA;
            continue;
        }
        else
        {
            rval = _I2C_Master_Send_Byte(hi2c, &pData, false);
            if( rval == I2C_ERROR )
            {
                hi2c->ErrorCode = HAL_I2C_ERROR_UNKNOWN;
                break;
            }
        }

        tx_nbytes = (rval == I2C_SUCCESS) ? tx_nbytes + 1 : tx_nbytes;
    }

    if( hi2c->ErrorCode == HAL_I2C_ERROR_NONE )
    {
        // send STOP-bit
        _I2C_Wait_SI_Flag(hi2c, CONFIG_I2C_TIMEOUT);
        _I2C_Master_Send_Byte(hi2c, &pData, true);
    }

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode  = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return (hi2c->ErrorCode == HAL_I2C_ERROR_NONE) ? HAL_OK : HAL_ERROR;
}

/**
 *  @brief  HAL_I2C_Master_Receive
 *              Receives in master mode an amount of data in blocking mode.
 *
 *  @param [in] hi2c            Pointer to a I2C_HandleTypeDef structure that contains
 *                                  the configuration information for the specified I2C.
 *  @param [in] DevAddr         Target device address: The device 7 bits address value
 *                                  in datasheet must be shift at right before call interface
 *  @param [in] pData           Pointer to data buffer
 *  @param [in] pSize           Amount of data to be received
 *  @param [in] Timeout_ms      Timeout with mseconds. If Timeout_ms == 0xFFFF, slave receives with blocking mode
 *  @return                     HAL status
 */
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint8_t DevAddr, uint8_t *pData, uint16_t *pSize, uint16_t Timeout_ms)
{
    i2c_tx_stage_t  stage = I2C_TX_STAGE_START_BIT;
    uint16_t        buf_size = *pSize;
    int             rx_nbytes = 0;

    assert_param(hi2c);
    assert_param(pData);
    assert_param(pSize);
    assert_param(*pSize);
    assert_param(DevAddr);

    if( hi2c->State != HAL_I2C_STATE_READY )
        return HAL_BUSY;

    __HAL_LOCK(hi2c);

    __I2C_FORCE_DISABLE_ISR(CONFIG_I2C_IRQn);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    __HAL_I2C_SET_START_FLAG(hi2c);
    stage = I2C_TX_STAGE_ADDRESS;

    if( pSize )      *pSize = 0;

    while( rx_nbytes < buf_size )
    {
        I2CStatus       rval = I2C_SUCCESS;

        if( _I2C_Wait_SI_Flag(hi2c, Timeout_ms) != HAL_OK )
        {
            if( Timeout_ms != HAL_I2C_BLOCKING )
                break;

            hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        }

        if( stage == I2C_TX_STAGE_ADDRESS )
        {
            uint8_t     addr = (uint8_t)DevAddr | 0x1u; // read mode
            uint8_t     *pAddr = 0;

            pAddr = &addr;
            rval = _I2C_Master_Recv_Byte(hi2c, &pAddr, false);
            if( rval == I2C_ERROR )
                break;

            /**
             *  send DevAddr+R and then receive data
             *  ps. Decrease the DevAddr+R byte
             */
            rx_nbytes = -1;
            stage = I2C_TX_STAGE_DATA;
            continue;
        }
        else
        {
            rval = _I2C_Master_Recv_Byte(hi2c, &pData, ((rx_nbytes + 1) == buf_size));
            if( rval == I2C_ERROR )
                break;
        }

        rx_nbytes = (rval == I2C_SUCCESS) ? rx_nbytes + 1 : rx_nbytes;
    }

    if( pSize )      *pSize = rx_nbytes;

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode  = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return (hi2c->ErrorCode == HAL_I2C_ERROR_NONE) ? HAL_OK : HAL_ERROR;
}

/**
 *  @brief  HAL_I2C_Master_Mem_Read
 *              Read an amount of data in blocking mode from a specific memory address or commands
 *
 *  @param [in] hi2c            Pointer to a I2C_HandleTypeDef structure that contains
 *                                  the configuration information for the specified I2C.
 *  @param [in] DevAddr         Target device address: The device 7 bits address value
 *                                  in datasheet must be shift at right before call interface
 *  @param [in] pSend_buf       Pointer to data buffer for send to slave
 *  @param [in] tx_nbytes       Amount of data to be sent
 *  @param [in] pRecv_buf       Pointer to data buffer
 *  @param [in] pRx_nbytes      Amount of data to be received
 *  @param [in] Timeout_ms      Timeout with mseconds. If Timeout_ms == 0xFFFF, slave receives with blocking mode
 *  @return                     HAL status
 */
HAL_StatusTypeDef HAL_I2C_Master_Mem_Read(I2C_HandleTypeDef *hi2c, uint8_t DevAddr,
                                          uint8_t *pSend_buf, uint16_t tx_nbytes,
                                          uint8_t *pRecv_buf, uint16_t *pRx_nbytes,
                                          uint16_t Timeout_ms)
{
    i2c_tx_stage_t  stage = I2C_TX_STAGE_START_BIT;
    short           nbytes = 0;
    uint16_t        rx_nbytes = *pRx_nbytes;

    assert_param(hi2c);
    assert_param(pSend_buf);
    assert_param(tx_nbytes);
    assert_param(pRecv_buf);
    assert_param(pRx_nbytes);
    assert_param(*pRx_nbytes);
    assert_param(DevAddr);

    if( hi2c->State != HAL_I2C_STATE_READY )
        return HAL_BUSY;

    __HAL_LOCK(hi2c);

    __I2C_FORCE_DISABLE_ISR(CONFIG_I2C_IRQn);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    /**
     *  send the specific address
     */
    __HAL_I2C_SET_START_FLAG(hi2c);
    stage = I2C_TX_STAGE_ADDRESS;

    while( nbytes < tx_nbytes )
    {
        I2CStatus       rval = I2C_SUCCESS;

        if( _I2C_Wait_SI_Flag(hi2c, CONFIG_I2C_TIMEOUT) != HAL_OK )
            break;

        if( stage == I2C_TX_STAGE_ADDRESS )
        {
            uint8_t     addr = (uint8_t)DevAddr & ~0x1u; // write mode
            uint8_t     *pAddr = 0;

            pAddr = &addr;
            rval = _I2C_Master_Send_Byte(hi2c, &pAddr, false);
            if( rval == I2C_ERROR )
            {
                hi2c->ErrorCode = HAL_I2C_ERROR_UNKNOWN;
                break;
            }

            stage = I2C_TX_STAGE_DATA;
            continue;
        }
        else
        {
            rval = _I2C_Master_Send_Byte(hi2c, &pSend_buf, false);
            if( rval == I2C_ERROR )
            {
                hi2c->ErrorCode = HAL_I2C_ERROR_UNKNOWN;
                break;
            }
        }

        nbytes = (rval == I2C_SUCCESS) ? nbytes + 1 : nbytes;
    }

    /**
     *  receive the data of specific address
     */
    hi2c->State = HAL_I2C_STATE_BUSY_RX;
    nbytes      = 0;
    *pRx_nbytes = 0u;

    if( hi2c->ErrorCode == HAL_I2C_ERROR_NONE )
    {
        /* receive the ACK of the last byte */
        _I2C_Wait_SI_Flag(hi2c, CONFIG_I2C_TIMEOUT);
        _I2C_Master_Recv_Byte(hi2c, &pSend_buf, false);

        /* switch to read mode */
        stage = I2C_TX_STAGE_ADDRESS;
    }
    else
    {
        rx_nbytes = 0;
    }

    while( nbytes < rx_nbytes )
    {
        I2CStatus       rval = I2C_SUCCESS;

        if( _I2C_Wait_SI_Flag(hi2c, Timeout_ms) != HAL_OK )
        {
            if( Timeout_ms != HAL_I2C_BLOCKING )
                break;

            hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        }

        if( stage == I2C_TX_STAGE_ADDRESS )
        {
            uint8_t     addr = (uint8_t)DevAddr | 0x1u; // read mode
            uint8_t     *pAddr = 0;

            pAddr = &addr;
            rval = _I2C_Master_Recv_Byte(hi2c, &pAddr, false);
            if( rval == I2C_ERROR )
                break;

            /**
             *  send DevAddr+R and then receive data
             *  ps. Decrease the DevAddr+R byte
             */
            nbytes = -1;
            stage = I2C_TX_STAGE_DATA;
            continue;
        }
        else
        {
            rval = _I2C_Master_Recv_Byte(hi2c, &pRecv_buf, ((nbytes + 1) == rx_nbytes));
            if( rval == I2C_ERROR )
                break;
        }

        nbytes = (rval == I2C_SUCCESS) ? nbytes + 1 : nbytes;
    }

    if( pRx_nbytes )    *pRx_nbytes = nbytes;

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode  = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return (hi2c->ErrorCode == HAL_I2C_ERROR_NONE) ? HAL_OK : HAL_ERROR;
}

/**
 *  @brief  HAL_I2C_Master_Mem_Write
 *              Write an amount of data in blocking mode to a specific memory address or commands
 *
 *  @param [in] hi2c            Pointer to a I2C_HandleTypeDef structure that contains
 *                                  the configuration information for the specified I2C.
 *  @param [in] DevAddr         Target device address: The device 7 bits address value
 *                                  in datasheet must be shift at right before call interface
 *  @param [in] pSend_buf       Pointer to data buffer for send to slave
 *  @param [in] tx_nbytes       Amount of data to be sent
 *  @param [in] pData_buf       Pointer to data buffer which write to slave
 *  @param [in] pData_nbytes    Amount of data to be written
 *  @param [in] Timeout_ms      Timeout with mseconds. If Timeout_ms == 0xFFFF, slave receives with blocking mode
 *  @return                     HAL status
 */
HAL_StatusTypeDef HAL_I2C_Master_Mem_Write(I2C_HandleTypeDef *hi2c, uint8_t DevAddr,
                                           uint8_t *pSend_buf, uint16_t tx_nbytes,
                                           uint8_t *pData_buf, uint16_t *pData_nbytes,
                                           uint16_t Timeout_ms)
{
    i2c_tx_stage_t  stage = I2C_TX_STAGE_START_BIT;
    uint16_t        nbytes = 0;
    uint16_t        data_nbytes = *pData_nbytes;

    assert_param(hi2c);
    assert_param(pSend_buf);
    assert_param(tx_nbytes);
    assert_param(pData_buf);
    assert_param(pData_nbytes);
    assert_param(*pData_nbytes);
    assert_param(DevAddr);

    if( hi2c->State != HAL_I2C_STATE_READY )
        return HAL_BUSY;

    __HAL_LOCK(hi2c);

    __I2C_FORCE_DISABLE_ISR(CONFIG_I2C_IRQn);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    /**
     *  send the specific address
     */
    __HAL_I2C_SET_START_FLAG(hi2c);
    stage = I2C_TX_STAGE_ADDRESS;

    data_nbytes += tx_nbytes;

    while( nbytes < data_nbytes )
    {
        I2CStatus       rval = I2C_SUCCESS;

        if( _I2C_Wait_SI_Flag(hi2c, CONFIG_I2C_TIMEOUT) != HAL_OK )
            break;

        if( stage == I2C_TX_STAGE_ADDRESS )
        {
            uint8_t     addr = (uint8_t)DevAddr & ~0x1u; // write mode
            uint8_t     *pAddr = 0;

            pAddr = &addr;
            rval = _I2C_Master_Send_Byte(hi2c, &pAddr, false);
            if( rval == I2C_ERROR )
            {
                hi2c->ErrorCode = HAL_I2C_ERROR_UNKNOWN;
                break;
            }

            stage = I2C_TX_STAGE_DATA;
            continue;
        }
        else
        {
            rval = _I2C_Master_Send_Byte(hi2c, (nbytes < tx_nbytes) ? &pSend_buf : &pData_buf, false);
            if( rval == I2C_ERROR )
            {
                hi2c->ErrorCode = HAL_I2C_ERROR_UNKNOWN;
                break;
            }
        }

        nbytes = (rval == I2C_SUCCESS) ? nbytes + 1 : nbytes;
    }

    if( hi2c->ErrorCode == HAL_I2C_ERROR_NONE )
    {
        // send STOP-bit
        _I2C_Wait_SI_Flag(hi2c, CONFIG_I2C_TIMEOUT);
        _I2C_Master_Send_Byte(hi2c, &pData_buf, true);
    }

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode  = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return (hi2c->ErrorCode == HAL_I2C_ERROR_NONE) ? HAL_OK : HAL_ERROR;
}


/**
 *  @brief  HAL_I2C_Slave_Transmit
 *              Transmits in slave mode an amount of data in blocking mode.
 *
 *  @param [in] hi2c        Pointer to a I2C_HandleTypeDef structure that contains
 *                              the configuration information for the specified I2C.
 *  @param [in] pData       Pointer to data buffer
 *  @param [in] Size        Amount of data to be sent
 *  @param [in] Timeout_ms  Timeout with mseconds. If Timeout_ms == 0xFFFF, slave transmit with blocking mode
 *  @return                 HAL status
 */
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint16_t Timeout_ms)
{
    __IO uint16_t        tx_nbytes = 0;

    assert_param(hi2c);
    assert_param(pData);
    assert_param(Size);

    if( hi2c->State != HAL_I2C_STATE_READY )
        return HAL_BUSY;

    __HAL_LOCK(hi2c);

    __I2C_FORCE_DISABLE_ISR(CONFIG_I2C_IRQn);

    hi2c->State       = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode        = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;
    hi2c->HasRecvAddr = false;

    while( tx_nbytes < Size )
    {
        I2CStatus       rval = I2C_SUCCESS;

        if( _I2C_Wait_SI_Flag(hi2c, Timeout_ms) != HAL_OK )
        {
            if( Timeout_ms != HAL_I2C_BLOCKING )
                break;

            hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        }

        rval = _I2C_Slave_Send_Byte(hi2c, &pData, false);
        if( rval == I2C_ERROR || rval == I2C_FORCE_STOP )
        {
            hi2c->ErrorCode = (rval == I2C_ERROR)
                            ? HAL_I2C_ERROR_UNKNOWN : hi2c->ErrorCode;
            break;
        }

        tx_nbytes = (rval == I2C_SUCCESS) ? tx_nbytes + 1 : tx_nbytes;
    }

    if( hi2c->ErrorCode == HAL_I2C_ERROR_NONE )
    {
        // send STOP-bit
        _I2C_Wait_SI_Flag(hi2c, CONFIG_I2C_TIMEOUT);
        _I2C_Slave_Send_Byte(hi2c, &pData, true);
    }

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode  = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return (hi2c->ErrorCode == HAL_I2C_ERROR_NONE) ? HAL_OK : HAL_ERROR;
}



/**
 *  @brief  HAL_I2C_Slave_Receive
 *              Receive in slave mode an amount of data in blocking mode
 *
 *  @param [in] hi2c            Pointer to a I2C_HandleTypeDef structure that contains
 *                                  the configuration information for the specified I2C.
 *  @param [in] pData           Pointer to data buffer
 *  @param [in] pSize           Amount of data to be receive
 *  @param [in] Timeout_ms      Timeout with mseconds. If Timeout_ms == 0xFFFF, slave receives with blocking mode
 *  @return                     HAL status
 */
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t *pSize, uint16_t Timeout_ms)
{
    uint16_t        rx_nbytes = 0;
    uint16_t        buf_size = *pSize;

    assert_param(hi2c);
    assert_param(pData);
    assert_param(pSize);
    assert_param(*pSize);

    if( hi2c->State != HAL_I2C_STATE_READY )
        return HAL_BUSY;

    __HAL_LOCK(hi2c);

    __I2C_FORCE_DISABLE_ISR(CONFIG_I2C_IRQn);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    if( pSize )      *pSize = 0;

    while( rx_nbytes < buf_size )
    {
        I2CStatus   rval = I2C_SUCCESS;

        if( _I2C_Wait_SI_Flag(hi2c, Timeout_ms) != HAL_OK )
        {
            if( Timeout_ms != HAL_I2C_BLOCKING )
                break;

            hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        }

        rval = _I2C_Slave_Recv_Byte(hi2c, &pData, ((rx_nbytes + 1) == buf_size));
        if( rval == I2C_ERROR || rval == I2C_FORCE_STOP )
        {
            hi2c->ErrorCode = (rval == I2C_ERROR)
                            ? HAL_I2C_ERROR_UNKNOWN : hi2c->ErrorCode;
            break;
        }


        rx_nbytes = (rval == I2C_SUCCESS) ? rx_nbytes + 1 : rx_nbytes;
    }

    if( pSize )      *pSize = rx_nbytes;

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode  = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return (hi2c->ErrorCode == HAL_I2C_ERROR_NONE) ? HAL_OK : HAL_ERROR;
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddr, uint8_t *pData, uint16_t Size)
{
    assert_param(hi2c);
    assert_param(pData);
    assert_param(Size);
    assert_param(DevAddr);

    if( hi2c->State != HAL_I2C_STATE_READY )
        return HAL_BUSY;

    __HAL_LOCK(hi2c);

    __I2C_FORCE_ENABLE_ISR(CONFIG_I2C_IRQn);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->DevAddress  = DevAddr;
    hi2c->pTxBuffPtr  = pData;
    hi2c->TxXferSize  = Size;
    hi2c->TxXferCount = Size;

    __HAL_I2C_SET_START_FLAG(hi2c);

    __HAL_UNLOCK(hi2c);

    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t DevAddr, uint8_t *pData, uint8_t Size)
{
    assert_param(hi2c);
    assert_param(pData);
    assert_param(Size);
    assert_param(DevAddr);

    if( hi2c->State != HAL_I2C_STATE_READY )
        return HAL_BUSY;

    __HAL_LOCK(hi2c);

    __I2C_FORCE_ENABLE_ISR(CONFIG_I2C_IRQn);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->DevAddress  = DevAddr;
    hi2c->pRxBuffPtr  = pData;
    hi2c->RxXferSize  = Size;
    hi2c->RxXferCount = Size;

    __HAL_I2C_SET_START_FLAG(hi2c);

    __HAL_UNLOCK(hi2c);

    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{
    assert_param(hi2c);
    assert_param(pData);
    assert_param(Size);

    if( hi2c->State != HAL_I2C_STATE_READY )
        return HAL_BUSY;

    __HAL_LOCK(hi2c);

    __I2C_FORCE_ENABLE_ISR(CONFIG_I2C_IRQn);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pTxBuffPtr  = pData;
    hi2c->TxXferSize  = Size;
    hi2c->TxXferCount = Size;

    __HAL_UNLOCK(hi2c);

    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{
    assert_param(hi2c);
    assert_param(pData);
    assert_param(Size);

    if( hi2c->State != HAL_I2C_STATE_READY )
        return HAL_BUSY;

    __HAL_LOCK(hi2c);

    __I2C_FORCE_ENABLE_ISR(CONFIG_I2C_IRQn);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pRxBuffPtr  = pData;
    hi2c->RxXferSize  = Size;
    hi2c->RxXferCount = Size;

    __HAL_UNLOCK(hi2c);

    return HAL_OK;
}

/**
  * @brief  This function handles I2C  interrupt request.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c)
{
    I2CStatus   rval = I2C_SUCCESS;

    if( hi2c->Mode == HAL_I2C_MODE_MASTER )
    {
        if( hi2c->State == HAL_I2C_STATE_BUSY_TX )
        {
            if( hi2c->DevAddress & 0x8000 )
            {
                // xfer data stage, if hi2c->TxXferCount == 0, I2C should send STOP-bit
                rval = _I2C_Master_Send_Byte(hi2c, &hi2c->pTxBuffPtr, (hi2c->TxXferCount) ? false : true);
                if( rval == I2C_SUCCESS )
                    hi2c->TxXferCount--;

                if( hi2c->TxXferCount == 0xFFFF )
                {
                    HAL_I2C_MasterTxCmpltCallback(hi2c);

                    hi2c->State = HAL_I2C_STATE_READY;
                    hi2c->Mode  = HAL_I2C_MODE_NONE;
                }
            }
            else
            {
                uint8_t     *pAddr = 0;
                hi2c->DevAddress &= ~0x1u; // write mode

                pAddr = (uint8_t*)&hi2c->DevAddress;
                rval = _I2C_Master_Send_Byte(hi2c, &pAddr, false);
                if( rval == I2C_SUCCESS )
                    hi2c->DevAddress |= 0x8000;
            }
        }
        else  /* hi2c->State == HAL_I2C_STATE_BUSY_RX */
        {
            if( hi2c->DevAddress & 0x8000 )
            {
                rval = _I2C_Master_Recv_Byte(hi2c, &hi2c->pRxBuffPtr, (hi2c->RxXferCount) ? false : true);
                if( rval == I2C_SUCCESS )
                    hi2c->RxXferCount--;

                if( hi2c->RxXferCount == 0 )
                {
                    HAL_I2C_MasterRxCmpltCallback(hi2c);

                    hi2c->State = HAL_I2C_STATE_READY;
                    hi2c->Mode  = HAL_I2C_MODE_NONE;
                }
            }
            else
            {
                uint8_t     *pAddr = 0;
                hi2c->DevAddress |= 0x1u; // read mode

                pAddr = (uint8_t*)&hi2c->DevAddress;
                rval = _I2C_Master_Recv_Byte(hi2c, &pAddr, false);
                if( rval == I2C_SUCCESS )
                {
                    hi2c->DevAddress |= 0x8000;

                    /**
                     *  send DevAddr+R and then receive data
                     *  ps. Decrease the DevAddr+R byte
                     */
                    hi2c->RxXferCount++;
                }
            }
        }
    }
    else  /* Slave */
    {
        if( hi2c->State == HAL_I2C_STATE_BUSY_TX )
        {
            // xfer data stage, if hi2c->TxXferCount == 0, I2C should send STOP-bit
            rval = _I2C_Slave_Send_Byte(hi2c, &hi2c->pTxBuffPtr, (hi2c->TxXferCount) ? false : true);
            hi2c->TxXferCount = (rval == I2C_SUCCESS)    ? hi2c->TxXferCount - 1
                              : (rval == I2C_FORCE_STOP) ? 0xFFFF
                              : hi2c->TxXferCount;

            if( hi2c->TxXferCount == 0xFFFF )
            {
                HAL_I2C_SlaveTxCmpltCallback(hi2c);

                hi2c->State = HAL_I2C_STATE_READY;
                hi2c->Mode  = HAL_I2C_MODE_NONE;
            }
        }
        else  /* hi2c->State == HAL_I2C_STATE_BUSY_RX */
        {
            rval = _I2C_Slave_Recv_Byte(hi2c, &hi2c->pRxBuffPtr, (hi2c->RxXferCount == 1));
            hi2c->RxXferCount = (rval == I2C_SUCCESS)    ? hi2c->RxXferCount - 1
                              : (rval == I2C_FORCE_STOP) ? 0
                              : hi2c->RxXferCount;

            if( hi2c->RxXferCount == 0 )
            {
                HAL_I2C_SlaveRxCmpltCallback(hi2c);

                hi2c->State = HAL_I2C_STATE_READY;
                hi2c->Mode  = HAL_I2C_MODE_NONE;
            }
        }
    }

    return;
}

/**
 * @brief  Initializes the I2C MSP.
 * @param  hi2c : I2C handle
 * @retval None
 */
__weak void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hi2c);
}

/**
 * @brief  DeInitializes the I2C MSP.
 * @param  hi2c : I2C handle
 * @retval None
 */
__weak void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hi2c);
}

__weak void HAL_I2C_MasterTxCmpltCallback(I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hi2c);
}

__weak void HAL_I2C_SlaveTxCmpltCallback(I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hi2c);
}

__weak void HAL_I2C_MasterRxCmpltCallback(I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hi2c);
}

__weak void HAL_I2C_SlaveRxCmpltCallback(I2C_HandleTypeDef *hi2c)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hi2c);
}



/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif  /* HAL_I2C_MODULE_ENABLED */
