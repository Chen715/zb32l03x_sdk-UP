/**
 ******************************************************************************
 * @file    zb32l03x_hal_flash.h
 * @author  MCU Software Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   Header file of Flash HAL module.
 ******************************************************************************
 **/


#ifndef __ZB32L03x_HAL_FLASH_H
#define __ZB32L03x_HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif


#include "zb32l03x_hal_def.h"

/** @addtogroup ZB32L03x_HAL_Driver
 * @{
 */

/** @addtogroup FLASH
 * @{
 */

/** @addtogroup FLASH_Private_Constants
 * @{
 */
#define FLASH_TIMEOUT_VALUE                 50000U /* 50 s */
#define FLASH_REGUNLOCK_KEY1                0x5A5A
#define FLASH_REGUNLOCK_KEY2                0xA5A5

/**
 * @}
 */

/** @addtogroup FLASH_Private_Macros
 * @{
 */

#define IS_FLASH_TYPEPROGRAM(VALUE)         (((VALUE) == FLASH_TYPEPROGRAM_HALFWORD) || \
                                             ((VALUE) == FLASH_TYPEPROGRAM_WORD)     || \
                                             ((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD))


/**
 * @}
 */


/** @defgroup FLASH_Exported_Types FLASH Exported Types
 * @{
 */

/**
 * @brief  FLASH Procedure structure definition
 */
typedef enum
{
    FLASH_PROC_NONE              = 0U,
    FLASH_PROC_PAGEERASE         = 1U,
    FLASH_PROC_MASSERASE         = 2U,
    FLASH_PROC_PROGRAMHALFWORD   = 3U,
    FLASH_PROC_PROGRAMWORD       = 4U,
    FLASH_PROC_PROGRAMDOUBLEWORD = 5U
} FLASH_ProcedureTypeDef;

/**
 * @brief  FLASH handle Structure definition
 */
typedef struct
{
    __IO FLASH_ProcedureTypeDef ProcedureOnGoing; /*!< Internal variable to indicate which procedure is ongoing or not in IT context */

    __IO uint32_t               DataRemaining;    /*!< Internal variable to save the remaining pages to erase or half-word to program in IT context */

    __IO uint32_t               Address;          /*!< Internal variable to save address selected for program or erase */

    __IO uint64_t               Data;             /*!< Internal variable to save data to be programmed */

    HAL_LockTypeDef             Lock;             /*!< FLASH locking object                */

    __IO uint32_t               ErrorCode;        /*!< FLASH error code
                                                        This parameter can be a value of @ref FLASH_Error_Codes  */
} FLASH_ProcessTypeDef;


/**
 * @brief  FLASH Erase structure definition
 */
typedef struct
{
    uint32_t TypeErase;     /*!< TypeErase: Mass erase or page erase.
                                This parameter can be a value of @ref FLASH_Type_Erase */

    uint32_t PageAddress;   /*!< PageAdress: Initial FLASH page address to erase when page erase is selected
                                This parameter must be a number between Min_Data = 0x00000000 and Max_Data = 0x10000
                                (or 0x08000 depending on devices)*/

    uint32_t NbPages;       /*!< NbPages: Number of pages to be erased. In ZB32L03x a Page is a Sector and a Sector size is 512 bytes.
                                This parameter must be a value between Min_Data = 1 and Max_Data = (max number of pages - value of initial page)*/

} FLASH_EraseInitTypeDef;


/**
 * @}
 */


/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
 * @{
 */

/** @defgroup FLASH_Error_Codes FLASH Error Codes
 * @{
 */

#define HAL_FLASH_ERROR_NONE            0x00U  /*!< No error */
#define HAL_FLASH_ERROR_ERASEWP         0x02U  /*!< Erase write protected area error */
#define HAL_FLASH_ERROR_ERASEPC         0x04U  /*!< Erase area contained PC error */

/**
 * @}
 */

/** @defgroup FLASH_Type_Program FLASH Type Program
 * @{
 */
#define FLASH_TYPEPROGRAM_BYTE                  0x00U  /*!<Program a byte (8-bit) at a specified address.*/
#define FLASH_TYPEPROGRAM_HALFWORD              0x01U  /*!<Program a half-word (16-bit) at a specified address.*/
#define FLASH_TYPEPROGRAM_WORD                  0x02U  /*!<Program a word (32-bit) at a specified address.*/
#define FLASH_TYPEPROGRAM_DOUBLEWORD            0x03U  /*!<Program a double word (64-bit) at a specified address*/

/**
  * @}
  */


/** @defgroup FLASH_Flag_definition Flag definition
 * @brief Flag definition
 * @{
 */
#define FLASH_FLAG_BSY                              FLASH_CR_BUSY   /*!< FLASH Busy flag                          */
#define FLASH_FLAG_ALARM_ERASE_PROTADDR             FLASH_IFR_IF1   /*!< The address to be erased is protected interrupt flag */
#define FLASH_FLAG_ALARM_ERASE_PCADDR               FLASH_IFR_IF0   /*!< The address to be erased is PC interrupt source */

/**
 * @}
 */

/** @defgroup FLASH_Interrupt_definition Interrupt definition
 * @brief FLASH Interrupt definition
 * @{
 */
#define FLASH_IT_ALARM_ERASE_PROTADDR               (0x2u << FLASH_CR_IE_Pos)   /*!< The address to be erased is protected interrupt source */
#define FLASH_IT_ALARM_ERASE_PCADDR                 (0x1u << FLASH_CR_IE_Pos)   /*!< The address to be erased is $PC interrupt source */

/**
 * @}
 */


/** @defgroup FLASH_Type_Erase Type Erase
 * @{
 */
#define FLASH_TYPEERASE_PAGES                   0x00U  /*!<Pages erase only*/
#define FLASH_TYPEERASE_MASS                    0x02U  /*!<Flash mass erase activation*/

/**
 * @}
 */


/** @defgroup FLASH_Page_Size Page Size
 * @{
 */
#define FLASH_PAGE_SIZE                         0x200U
#define FLASH_SIZE_32K                          0x8000U
#define FLASH_SIZE_64K                          0x10000U
#define FLASH_ALLPAGE_SELECTED                  0xFFFFFFFFU

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup FLASH_Control FLASH Control Exported Macros
 *  @brief macros to handle FLASH registers and write protection
 * @{
 */

/**
 *  \brief  Set ISP_CON of Flash
 *  \param [in] __FLAG__    enable or not, @ref enum FlagStatus
 *          @arg @ref RESET    0.
 *          @arg @ref SET      1.
 *  \return
 *      none
 */
#define __HAL_FLASH_SET_ISPCON(__FLAG__)        (FLASH->ISPCON = (0x5A690000 | (__FLAG__)))

/**
 *  \brief  Get ISP_CON of Flash
 *  \return
 *      state of ISPCON
 */
#define __HAL_FLASH_GET_ISPCON()                (FLASH->ISPCON & FLASH_ISPCON_ISP_CON_Msk)

/**
 * @brief  Unlock the FLASH controller register write-protect.
 * @retval none
 */
#define __HAL_FLASH_REGISTER_UNLOCK                   \
            do {                                      \
                FLASH->BYPASS = FLASH_REGUNLOCK_KEY1; \
                FLASH->BYPASS = FLASH_REGUNLOCK_KEY2; \
            } while(0U)

#define __HAL_FLASH_REGISTER_LOCK                     \
            do {                                      \
                FLASH->BYPASS = FLASH_REGUNLOCK_KEY1; \
                FLASH->BYPASS = 0x00000000;           \
            } while(0U)

/**
 * @}
 */


/** @defgroup FLASH_Interrupt Flash Interrupt macros
 *  @brief macros to handle FLASH interrupts
 * @{
 */

/**
 * @brief  Enable the specified FLASH interrupt.
 * @param  __INTERRUPT__  FLASH interrupt
 *         This parameter can be any combination of the following values:
 *            @arg @ref FLASH_IT_ALARM_ERASE_PROTADDR      The address to be erased is protectd interrupt source
 *            @arg @ref FLASH_IT_ALARM_ERASE_PCADDR        The address to be erased is PC interrupt source
 * @retval none
 */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)    (FLASH->CR |= (__INTERRUPT__))

/**
 * @brief  Disable the specified FLASH interrupt.
 * @param  __INTERRUPT__  FLASH interrupt
 *         This parameter can be any combination of the following values:
 *            @arg @ref FLASH_IT_ALARM_ERASE_PROTADDR      The address to be erased is protectd interrupt source
 *            @arg @ref FLASH_IT_ALARM_ERASE_PCADDR        The address to be erased is PC interrupt source
 * @retval none
 */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)   (FLASH->CR &= ~(__INTERRUPT__))

/**
 * @brief  Get the specified FLASH flag status.
 * @param  __FLAG__ specifies the FLASH flag to check.
 *          This parameter can be following value:
 *            @arg @ref FLASH_FLAG_BSY                                     FLASH Busy flag
 *            @arg @ref FLASH_FLAG_ALARM_ERASE_PROTADDR    The address to be erased is protectd interrupt flag
 *            @arg @ref FLASH_FLAG_ALARM_ERASE_PCADDR          The address to be erased is PC interrupt flag
 * @retval The new state of __FLAG__ (SET or RESET).
 */
#define __HAL_FLASH_GET_FLAG(__FLAG__)          (((__FLAG__) == FLASH_FLAG_BSY) ? \
                                                 (FLASH->CR & (__FLAG__)) : (FLASH->IFR & (__FLAG__)))

/**
 * @brief  Clear the specified FLASH flag.
 * @param  __FLAG__ specifies the FLASH flags to clear.
 *          This parameter can be any combination of the following values:
 *            @arg @ref FLASH_FLAG_ALARM_ERASE_PROTADDR    The address to be erased is protectd interrupt flag
 *            @arg @ref FLASH_FLAG_ALARM_ERASE_PCADDR          The address to be erased is PC interrupt source
 * @retval none
 */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)                      \
            do {                                              \
                /* Clear alarm flag, 0: clear, 1: no action*/ \
                FLASH->ICLR  = ~(__FLAG__);                   \
            } while(0U)


#if defined(CONFIG_USE_ZB32L032)
/* Only ZB32L032 support */

/**
 *  \brief  Set wait cycles when fetch flash
 *              Flash clock max = 32MHz.
 *              If system clock > 32MHz, it MUST wait cycles to fetch flash.
 */
#define __HAL_FLASH_WAIT_CYCLES_ENABLE()        \
            (FLASH->RCR = 0x96A50000ul)

/**
 *  \brief  Set no wait cycles when fetch flash
 *              Flash clock max = 32MHz.
 *              If system clock < 32MHz, it don't wait cycles to fetch flash.
 */
#define __HAL_FLASH_WAIT_CYCLES_DISABLE()       \
            (FLASH->RCR = (0x96A50000ul | FLASH_RCR_WCYCLE))

#endif /* CONFIG_USE_ZB32L032 */

/**
 * @}
 */



/** @defgroup FLASH_Trim Flash Trimming macros
 *  @brief macros to handle FLASH trimming
 * @{
 */

/**
 *  \brief  Get trimming value
 *
 *  \return
 *      trimming value
 */
#define __HAL_FLASH_GET_HWCFG_BGRVT()       ((FLASH->HWCFG & FLASH_HWCFG_HWCFG_BGRVT_Msk) >> FLASH_HWCFG_HWCFG_BGRVT_Pos)
#define __HAL_FLASH_GET_HWCFG_BGRTT()       ((FLASH->HWCFG & FLASH_HWCFG_HWCFG_BGRTT_Msk) >> FLASH_HWCFG_HWCFG_BGRTT_Pos)
#define __HAL_FLASH_GET_HWCFG_FT()          ((FLASH->HWCFG & FLASH_HWCFG_HWCFG_FT_Msk)    >> FLASH_HWCFG_HWCFG_FT_Pos)
#define __HAL_FLASH_GET_HWCFG_CT()          ((FLASH->HWCFG & FLASH_HWCFG_HWCFG_CT_Msk)    >> FLASH_HWCFG_HWCFG_CT_Pos)
#define __HAL_FLASH_GET_HWCFG_RT()          ((FLASH->HWCFG & FLASH_HWCFG_HWCFG_RT_Msk)    >> FLASH_HWCFG_HWCFG_RT_Pos)
#define __HAL_FLASH_GET_HWCFG_HVSEL()       ((FLASH->HWCFG & FLASH_HWCFG_HWCFG_HVSEL_Msk) >> FLASH_HWCFG_HWCFG_HVSEL_Pos)
#define __HAL_FLASH_GET_HWCFG_MT()          ((FLASH->HWCFG & FLASH_HWCFG_HWCFG_MT_Msk)    >> FLASH_HWCFG_HWCFG_MT_Pos)

/**
 *  \brief  __HAL_FLASH_SET_SWCFG_BGRVT()
 *              Set BGRVT of S/w configuration
 *
 *  \param [in] __VALUE__       The bandgap trimming value
 */
#define __HAL_FLASH_SET_SWCFG_BGRVT(__VALUE__)      MODIFY_REG(FLASH->SWCFG, FLASH_SWCFG_SWCFG_BGRVT_Msk, ((__VALUE__) << FLASH_SWCFG_SWCFG_BGRVT_Pos))

/**
 *  \brief  __HAL_FLASH_GET_SWCFG_BGRVT()
 *              Get BGRVT of S/w configuration
 *  \return
 *      value (5-bits)
 */
#define __HAL_FLASH_GET_SWCFG_BGRVT()               ((FLASH->SWCFG & FLASH_SWCFG_SWCFG_BGRVT_Msk) >> FLASH_SWCFG_SWCFG_BGRVT_Pos)

/**
 *  \brief  __HAL_FLASH_SET_SWCFG_BGRTT()
 *              Set BGRTT of S/w configuration
 *
 *  \param [in] __VALUE__       The BGR temperature trimming value
 */
#define __HAL_FLASH_SET_SWCFG_BGRTT(__VALUE__)      MODIFY_REG(FLASH->SWCFG, FLASH_SWCFG_SWCFG_BGRTT_Msk, ((__VALUE__)) << FLASH_SWCFG_SWCFG_BGRTT_Pos)

/**
 *  \brief  __HAL_FLASH_GET_SWCFG_BGRTT()
 *              Get BGRTT of S/w configuration
 *  \return
 *      value (5-bits)
 */
#define __HAL_FLASH_GET_SWCFG_BGRTT()               ((FLASH->SWCFG & FLASH_SWCFG_SWCFG_BGRTT_Msk) >> FLASH_SWCFG_SWCFG_BGRTT_Pos)

/**
 *  \brief  __HAL_FLASH_ENABLE_SWCFG_BGRVT()/__HAL_FLASH_DISABLE_SWCFG_BGRVT()
 *              Enable SW trimming value or not
 */
#define __HAL_FLASH_ENABLE_SWCFG_BGRVT()            SET_BIT(FLASH->HWCFG, FLASH_HWCFG_SWCFG_BGRVT_EN)
#define __HAL_FLASH_DISABLE_SWCFG_BGRVT()           CLEAR_BIT(FLASH->HWCFG, FLASH_HWCFG_SWCFG_BGRVT_EN)

/**
 *  \brief  __HAL_FLASH_ENABLE_SWCFG_BGRTT()/__HAL_FLASH_DISABLE_SWCFG_BGRTT()
 *              Enable SW trimming value or not
 */
#define __HAL_FLASH_ENABLE_SWCFG_BGRTT()            SET_BIT(FLASH->HWCFG, FLASH_HWCFG_SWCFG_BGRTT_EN)
#define __HAL_FLASH_DISABLE_SWCFG_BGRTT()           CLEAR_BIT(FLASH->HWCFG, FLASH_HWCFG_SWCFG_BGRTT_EN)

/**
 * @}
 */


/** @addtogroup FLASH_Exported_Functions
 * @{
 */

/** @addtogroup FLASH_Exported_Functions_Group1
 * @{
 */

/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
HAL_StatusTypeDef HAL_FLASH_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);

/* FLASH IRQ handler function */
void HAL_FLASH_IRQHandler(void);
/* Callbacks in non blocking modes */
void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);

/**
 * @}
 */

/** @addtogroup FLASH_Exported_Functions_Group2
 * @{
 */

/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_FLASH_OPERATION_Unlock(uint32_t PageAddress);
HAL_StatusTypeDef HAL_FLASH_OPERATION_Lock(uint32_t PageAddress);

/**
 * @}
 */

/** @addtogroup FLASH_Exported_Functions_Group3
 * @{
 */

/* Peripheral State and Error functions ***************************************/
uint32_t HAL_FLASH_GetError(void);

/**
 * @}
 */

/**
 * @}
 */


/**
 * @}
 */ /* End of group FLASH */

/**
 * @}
 */ /* End of group ZB32L03x_HAL_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __ZB32L03x_HAL_FLASH_H */

