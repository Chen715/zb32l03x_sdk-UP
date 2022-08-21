;*******************************************************************************
;* File Name          : startup_zb32l03x.s
;* Author             : Software Team
;* Version            : V1.0.0
;* Date               : 21-Oct-2019
;* Description        : ZB32L03x vector table for MDK-ARM
;*                      toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure the clock system
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM0+ processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;*******************************************************************************


                IF   :DEF:CONFIG_USE_ZB32L032

                    GET startup_zb32l032.s

                ELIF :DEF:CONFIG_USE_ZB32L030

                    GET startup_zb32l030.s

                ENDIF


                END
