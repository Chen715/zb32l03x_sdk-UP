
/**
 ******************************************************************************
 * @file    log.c
 * @author  MCU Team
 * @Version V1.0.0
 * @Date    2022/01/17
 * @brief   log function
 ******************************************************************************
 */

#include "log.h"
#include "zb32l03x_hal.h"

//=============================================================================
//                  Constant Definition
//=============================================================================

//=============================================================================
//                  Macro Definition
//=============================================================================
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
//=============================================================================
//                  Structure Definition
//=============================================================================

//=============================================================================
//                  Global Data Definition
//=============================================================================
UART_HandleTypeDef      g_hUart1 = {0};

//=============================================================================
//                  Private Function Definition
//=============================================================================
/**
  * @brief  Configures the UART peripheral.
  * @param  huart: pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
static void Log_UART_SetConfig(UART_HandleTypeDef *huart)
{
    /*------- UART-associated registers setting : SCON Configuration ------*/
    /* Configure the UART Word Length and mode:
        Set the DBAUD bits according to huart->Init.BaudDouble value
        Set the SM bits according to huart->Init.WordLength value
        Set REN bits according to huart->Init.Mode value */
    MODIFY_REG(huart->Instance->SCON,
               (UART_SCON_DBAUD | UART_SCON_SM0_SM1 | UART_SCON_REN),
               huart->Init.BaudDouble | huart->Init.WordLength | huart->Init.Mode);

    {   // UART BAUDCR Configuration
        uint32_t    bardrate = ((((huart->Init.BaudDouble >> UART_SCON_DBAUD_Pos) + 1) * HAL_RCC_GetPCLKFreq()) / (32 * (huart->Init.BaudRate))) - 1;

        WRITE_REG_MASK(huart->Instance->BAUDCR,
                       UART_BAUDCR_BRG_Msk | UART_BAUDCR_SELF_BRG_Msk,
                       bardrate | UART_BAUDCR_SELF_BRG);
    }

    __HAL_UART_ENABLE_IT(huart, UART_IT_TC | UART_IT_RXNE);
}


/**
 * @brief UART1 Initialization Function
 * @param None
 * @retval None
 */
static void _SerialInit(uint32_t baud_rate)
{
    g_hUart1.Instance        = UART1;
    g_hUart1.Init.BaudRate   = baud_rate;
    g_hUart1.Init.BaudDouble = UART_BAUDDOUBLE_ENABLE;
    g_hUart1.Init.WordLength = UART_WORDLENGTH_8B;
    g_hUart1.Init.Parity     = UART_PARITY_NONE;
    g_hUart1.Init.Mode       = UART_MODE_TX_RX;

    if(g_hUart1.gState == HAL_UART_STATE_RESET)
    {
        GPIO_InitTypeDef    GPIO_InitStruct = {0};

        /* Allocate lock resource and initialize it */
        g_hUart1.Lock = HAL_UNLOCKED;

        /* Peripheral clock enable */
        __HAL_RCC_UART1_CLK_ENABLE();

        UART1_TX_GPIO_CLK_ENABLE();
        UART1_RX_GPIO_CLK_ENABLE();
        /**
         *  UART1 GPIO Configuration
         *  PA14     ------> UART1_TXD
         *  PA03     ------> UART1_RXD
         */
        GPIO_InitStruct.Pin             = UART1_TX_PIN;
        GPIO_InitStruct.Mode            = GPIO_MODE_AF;
        GPIO_InitStruct.OpenDrain       = GPIO_PUSHPULL;
        GPIO_InitStruct.Debounce.Enable = GPIO_DEBOUNCE_DISABLE;
        GPIO_InitStruct.SlewRate        = GPIO_SLEW_RATE_HIGH;
        GPIO_InitStruct.DrvStrength     = GPIO_DRV_STRENGTH_HIGH;
        GPIO_InitStruct.Pull            = GPIO_PULLUP;
        GPIO_InitStruct.Alternate       = UART1_TX_GPIO_AF;
        HAL_GPIO_Init(UART1_TX_GPIO_PORT, &GPIO_InitStruct);

        GPIO_InitStruct.Pin       = UART1_RX_PIN;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF;
        GPIO_InitStruct.Alternate = UART1_RX_GPIO_AF;
        HAL_GPIO_Init(UART1_RX_GPIO_PORT, &GPIO_InitStruct);
    }

    g_hUart1.gState = HAL_UART_STATE_BUSY;

    /* Set the UART Communication parameters */
    Log_UART_SetConfig(&g_hUart1);

    /* Initialize the UART state */
    g_hUart1.ErrorCode = HAL_UART_ERROR_NONE;
    g_hUart1.gState    = HAL_UART_STATE_READY;
    g_hUart1.RxState   = HAL_UART_STATE_READY;

    return;
}

static void _SerialOutput(char *pData)
{
    while( *pData != 0 )
        HAL_UART_Transmit(&g_hUart1, (uint8_t *)pData++, 1, 1000);

    return;
}

static void _SerialSend(uint8_t data)
{
    HAL_UART_Transmit(&g_hUart1, &data, 1, 1000);
    return;
}

//=============================================================================
//                  Public Function Definition
//=============================================================================
/**
  * @brief  This function initializes the log interface
  * @param  None
  * @retval None
  */
void LogInit(void)
{
#if defined(LOG_METHOD_SERIAL) && (LOG_METHOD_SERIAL)
    _SerialInit(LOG_SERIAL_BPS);
#endif
}

void
LogMemory(
    char        *prefix,
    uint32_t    *pAddr,
    int         bytes,
    int         has_out_u32le)
{
    if( has_out_u32le )
    {
        uintptr_t   addr = (uintptr_t)pAddr;
        uint32_t    cnt = (bytes + 0x3) >> 2;
        uint32_t    *pCur = (uint32_t*)pAddr;

        for(int i = 0; i < cnt; i++)
        {
            if( (i & 0x3) == 2 )
                printf(" -");
            else if( !(i & 0x3) )
            {
                printf("\n%s%08X |", prefix, addr);
                addr += 16;
            }

            printf(" %08X", pCur[i]);
        }
        printf("\n\n");
    }
    else
    {
        uintptr_t   addr = (uintptr_t)pAddr;
        uint8_t     *pCur = (uint8_t*)pAddr;

        for(int i = 0; i < bytes; i++)
        {
            if( (i & 0xF) == 8 )
                printf(" -");
            else if( !(i & 0xF) )
            {
                printf("\n%s%08X |", prefix, addr);
                addr += 16;
            }

            printf(" %02X", pCur[i]);
        }
        printf("\n\n");
    }

    return;
}


PUTCHAR_PROTOTYPE
{
#if defined(LOG_METHOD_SERIAL)
    _SerialSend(ch);
#elif defined(LOG_METHOD_RAM)
    *LOG_RAM_CHAR = (char)(ch & 0xFF);
#endif
    return ch;
}


void panic(const char *func)
{
    // If panic info enabled, print it out

    _SerialOutput("Panic call from ");
    _SerialOutput((char *)func);
    _SerialOutput("\n");

    /* Add any panic string desired or while loop as needed */
}
