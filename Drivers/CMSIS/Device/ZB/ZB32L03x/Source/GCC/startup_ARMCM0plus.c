/**************************************************************************//**
 * @file     startup_ARMCM0plus.s
 * @brief    CMSIS Core Device Startup File for
 *           ARMCM0plus Device
 * @version  V5.3.1
 * @date     09. July 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

#include "zb32l03x.h"

/*----------------------------------------------------------------------------
  Linker generated Symbols
 *----------------------------------------------------------------------------*/
extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __copy_table_start__;
extern uint32_t __copy_table_end__;
extern uint32_t __zero_table_start__;
extern uint32_t __zero_table_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __StackTop;


/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void( *pFunc )( void );


/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern void _start     (void) __attribute__((noreturn)); /* PreeMain (C library entry point) */


/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void Default_Handler(void) __attribute__ ((noreturn));
void Reset_Handler  (void) __attribute__ ((noreturn));


/*----------------------------------------------------------------------------
  User Initial Stack & Heap
 *----------------------------------------------------------------------------*/
//<h> Stack Configuration
//  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//</h>
#define  __STACK_SIZE  0x00000400
static uint8_t stack[__STACK_SIZE] __attribute__ ((aligned(8), used, section(".stack")));

//<h> Heap Configuration
//  <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
//</h>
#define  __HEAP_SIZE   0x00000C00
#if __HEAP_SIZE > 0
    static uint8_t heap[__HEAP_SIZE]   __attribute__ ((aligned(8), used, section(".heap")));
#endif


/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

void GPIOA_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOB_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOC_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOD_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void UART0_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void UART1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void LPUART_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM10_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM11_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void LPTIM_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void PCA_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void IWDG_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void LVD_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void VC_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void AWK_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void OWIRE_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void CLKTRIM_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));



/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/
extern const pFunc __Vectors[ 48];
const pFunc __Vectors[ 48] __attribute__ ((section(".vectors"))) =
{
    (pFunc)(&__StackTop),                     /*     Initial Stack Pointer */
    Reset_Handler,                            /*     Reset Handler */
    NMI_Handler,                              /* -14 NMI Handler */
    HardFault_Handler,                        /* -13 Hard Fault Handler */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    SVC_Handler,                              /*  -5 SVCall Handler */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    PendSV_Handler,                           /*  -2 PendSV Handler */
    SysTick_Handler,                          /*  -1 SysTick Handler */

    /* Interrupts */
    GPIOA_IRQHandler,          // GPIOA_IRQn          = 0,
    GPIOB_IRQHandler,          // GPIOB_IRQn          = 1,
    GPIOC_IRQHandler,          // GPIOC_IRQn          = 2,
    GPIOD_IRQHandler,          // GPIOD_IRQn          = 3,
    FLASH_IRQHandler,          // FLASH_IRQHandler    = 4,
    0,                         // Reserved--------------5,
    UART0_IRQHandler,          // UART0_IRQn          = 6,
    UART1_IRQHandler,          // UART1_IRQn          = 7,
    LPUART_IRQHandler,         // LPUART_IRQn         = 8,
    0,                         // Reserved--------------9,
    SPI_IRQHandler,            // SPI_IRQn            = 10,
    0,                         // Reserved--------------11,
    I2C_IRQHandler,            // I2C0_IRQn           = 12,
    0,                         // Reserved--------------13,
    TIM10_IRQHandler,          // TIM10_IRQn          = 14,
    TIM11_IRQHandler,          // TIM11_IRQn          = 15,
    LPTIM_IRQHandler,          // LPTIMER_IRQn        = 16,
    0,                         // Reserved--------------17,
    TIM1_IRQHandler,           // ADVTIM1             = 18,
    TIM2_IRQHandler,           // ADVTIM2---------------19,
    0,                         // Reserved--------------20,
    PCA_IRQHandler,            // PCA_IRQn            = 21,
    WWDG_IRQHandler,           // WWDT_IRQn           = 22,
    IWDG_IRQHandler,           // IWDT_IRQn           = 23,
    ADC_IRQHandler,            // ADC_IRQn            = 24,
    LVD_IRQHandler,            // LVD_IRQn            = 25,
    VC_IRQHandler,             // VC_IRQn             = 26,
    0,                         // Reserved--------------27,
    AWK_IRQHandler,            // AWK_IRQn            = 28,
    OWIRE_IRQHandler,          // OWIRE_IRQn          = 29,
    RTC_IRQHandler,            // RTC_MATCH0_IRQn     = 30,
    CLKTRIM_IRQHandler,        // CLKTRIM_IRQn        = 31
};


/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void)
{
    extern int main(void);
    uint32_t *pSrc, *pDest;
    uint32_t *pTable __attribute__((unused));

    /* Firstly it copies data from read only memory to RAM.
     * There are two schemes to copy. One can copy more than one sections.
     * Another can copy only one section. The former scheme needs more
     * instructions and read-only data to implement than the latter.
     * Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.
     */

#ifdef __STARTUP_COPY_MULTIPLE
    /* Multiple sections scheme.
     *
     * Between symbol address __copy_table_start__ and __copy_table_end__,
     * there are array of triplets, each of which specify:
     *   offset 0: LMA of start of a section to copy from
     *   offset 4: VMA of start of a section to copy to
     *   offset 8: size of the section to copy. Must be multiply of 4
     *
     * All addresses must be aligned to 4 bytes boundary.
     */
    pTable = &__copy_table_start__;

    for (; pTable < &__copy_table_end__; pTable = pTable + 3)
    {
        pSrc  = (uint32_t *) * (pTable + 0);
        pDest = (uint32_t *) * (pTable + 1);
        for (; pDest < (uint32_t *)(*(pTable + 1) + * (pTable + 2)) ; )
        {
            *pDest++ = *pSrc++;
        }
    }
#else
    /* Single section scheme.
    *
    * The ranges of copy from/to are specified by following symbols
    *   __etext: LMA of start of the section to copy from. Usually end of text
    *   __data_start__: VMA of start of the section to copy to
    *   __data_end__: VMA of end of the section to copy to
    *
    * All addresses must be aligned to 4 bytes boundary.
    */
    pSrc  = &__etext;
    pDest = &__data_start__;

    for ( ; pDest < &__data_end__ ; )
    {
        *pDest++ = *pSrc++;
    }
#endif /*__STARTUP_COPY_MULTIPLE */

    /* This part of work usually is done in C library startup code.
     * Otherwise, define this macro to enable it in this startup.
     *
     * There are two schemes too.
     * One can clear multiple BSS sections. Another can only clear one section.
     * The former is more size expensive than the latter.
     *
     * Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
     * Otherwise define macro __STARTUP_CLEAR_BSS to choose the later.
     */
#ifdef __STARTUP_CLEAR_BSS_MULTIPLE
    /* Multiple sections scheme.
    *
    * Between symbol address __copy_table_start__ and __copy_table_end__,
    * there are array of tuples specifying:
    *   offset 0: Start of a BSS section
    *   offset 4: Size of this BSS section. Must be multiply of 4
    */
    pTable = &__zero_table_start__;

    for (; pTable < &__zero_table_end__; pTable = pTable + 2)
    {
        pDest = (uint32_t *) * (pTable + 0);
        for (; pDest < (uint32_t *)(*(pTable + 0) + * (pTable + 1)) ; )
        {
            *pDest++ = 0;
        }
    }
#elif defined (__STARTUP_CLEAR_BSS)
    /* Single BSS section scheme.
     *
     * The BSS section is specified by following symbols
     *   __bss_start__: start of the BSS section.
     *   __bss_end__: end of the BSS section.
     *
     * Both addresses must be aligned to 4 bytes boundary.
     */
    pDest = &__bss_start__;

    for ( ; pDest < &__bss_end__ ; )
    {
        *pDest++ = 0UL;
    }
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

    SystemInit();                             /* CMSIS System Initialization */
//  _start();                                 /* Enter PreeMain (C library entry point) */
    main();
}


/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
    while(1);
}
