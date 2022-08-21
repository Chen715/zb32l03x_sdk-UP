/**
 ******************************************************************************
 * @file    log.h
 * @author  Application Team
 * @Version V1.0.0
 * @Date    2022/01/19
 * @brief   Header file of log module.
 ******************************************************************************
 */


#ifndef __ZB32L03x_LOG_H
#define __ZB32L03x_LOG_H


#include "io_mapping.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
//=============================================================================
//                  Constant Definition
//=============================================================================
/* Choose one from below */
#define LOG_METHOD_SERIAL   1
#define LOG_METHOD_RAM

#if defined(LOG_METHOD_SERIAL) && (LOG_METHOD_SERIAL)
    /* Serial port baud rate */
    #define LOG_SERIAL_BPS          9600
#elif defined(LOG_METHOD_RAM)
    /* Choose a valid address without any confliction */
    #define LOG_RAM_ADDRESS         0x20000FFC
    #define LOG_RAM_CHAR            ((volatile char *)(LOG_RAM_ADDRESS))
#endif


#define LOG_BLACK               "\033[30m"
#define LOG_RED                 "\033[31m"
#define LOG_GREEN               "\033[32m"
#define LOG_YELLOW              "\033[33m"
#define LOG_BLUE                "\033[34m"
#define LOG_MAGENTA             "\033[35m"
#define LOG_CYAN                "\033[36m"
#define LOG_WHITE               "\033[97m"
#define LOG_DEFAULT             "\033[39m"
#define LOG_RESET               "\033[m"

#define LOG_RED2                "\33[91m"
#define LOG_GREEN2              "\33[92m"
#define LOG_YELLOW2             "\33[93m"
#define LOG_BLUE2               "\33[94m"
#define LOG_VIOLET2             "\33[95m"
#define LOG_BEIGE2              "\33[96m"

//=============================================================================
//                  Macro Definition
//=============================================================================
#define stringize(s)            #s
#define _toStr(a)               stringize(a)

#define info(str, ...)                      printf(LOG_YELLOW str LOG_RESET, ##__VA_ARGS__)
#define msg(str, ...)                       printf(str, ##__VA_ARGS__)
#define err(str, ...)                       printf(LOG_RED "[error] " str LOG_RESET, ##__VA_ARGS__)
#define log_color(COLOR, str, ...)          printf(COLOR str LOG_RESET, ##__VA_ARGS__)
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
/**
 *  \brief  Initialize logging message
 *              It will use UART as debug port
 *  \return
 *      none
 */
void LogInit(void);

/**
 *  \brief  Dump memory context
 *
 *  \param [in] prefix          the prefix string when dump memory context
 *  \param [in] pAddr           The target memory address
 *  \param [in] bytes           The dumped bytes
 *  \param [in] has_out_u32le   layout format: use 32-bits Little-Endian or byte to byte
 *  \return
 *      none
 */
void
LogMemory(
    char        *prefix,
    uint32_t    *pAddr,
    int         bytes,
    int         has_out_u32le);



#endif /* __ZB32L03x_LOG_H */
