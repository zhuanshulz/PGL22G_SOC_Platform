; **************************************************************************************
; *
; 		(C) COPYRIGHT 2014-2019 PANGO 
; *
; * File Name	:	startup_PANGO_M1.s
; * Author		:	Embedded Development Team
; * Version		:	V1.0.0
; * Date		:	2019-09-09 09:09:09
; * Description	:	Cortex-M1 vector table for ARM toolchain
; *					This module performs:
; *					- Set the initial SP
; *					- Set the initial PC == Reset_Handler
; *					- Set the vector table entries with exceptions ISR address
; *					- Configure the system clock
; *					- Branches to __main in the C library(which eventually calls main())
; *					After Reset the Cortex-M1 processor is in Thread mode,
; *					priority is Privileged and the Stach is set to Main
; *
; * <<< Use Configuration Wizard in Context Menu >>>
; *
; ****************************************************************************************

;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>

Stack_Size      EQU      0x00001000

                AREA     STACK, NOINIT, READWRITE, ALIGN=3
__stack_limit
Stack_Mem       SPACE    Stack_Size
__initial_sp


;<h> Heap Configuration
;  <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>

Heap_Size       EQU      0x00001000

                IF       Heap_Size != 0                      ; Heap is provided
                AREA     HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE    Heap_Size
__heap_limit
                ENDIF


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA     RESET, DATA, READONLY
                EXPORT   __Vectors
                EXPORT   __Vectors_End
                EXPORT   __Vectors_Size

__Vectors       DCD      __initial_sp                        ;     Top of Stack
                DCD      Reset_Handler                       ;     Reset Handler
                DCD      NMI_Handler                         ; -14 NMI Handler
                DCD      HardFault_Handler                   ; -13 Hard Fault Handler
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      SVC_Handler                         ;  -5 SVCall Handler
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      PendSV_Handler                      ;  -2 PendSV Handler
                DCD      SysTick_Handler                     ;  -1 SysTick Handler

                ; Interrupts
                DCD      UART0_Handler                       ;   0 UART0 Interrupt handler
                DCD      UART1_Handler                       ;   1 UART1 Interrupt handler
                DCD      TIMER0_Handler                      ;   2 TIMER0 Interrupt handler
                DCD      TIMER1_Handler                      ;   3 TIMER1 Interrupt handler
                DCD      GPIO0_Handler                       ;   4 GPIO0 Interrupt handler
                DCD      UARTOVF_Handler                     ;   5 UART0,1 Overflow Interrupt handler
                DCD      ENT_Handler                         ;   6 Ethernet Interrupt handler
                DCD      I2C_Handler                         ;   7 I2C Interrupt handler
                DCD      CAN_Handler                         ;   8 CAN Interrupt handler
                DCD      RTC_Handler                         ;   9 RTC Interrupt handler
				DCD      Interrupt10_Handler                 ;   10 Interrupt 10
				DCD      DTimer_Handler                      ;   11 DualTimer Interrupt handler
				DCD      TRNG_Handler                        ;   12 TRNG Interrupt handler
				DCD      Interrupt13_Handler              	 ;	 13 Interrupt 13
				DCD      Interrupt14_Handler                 ;   14 Interrupt 14
				DCD      Interrupt15_Handler                 ;   15 Interrupt 15
				DCD      Interrupt16_Handler                 ;   16 Interrupt 16
				DCD      Interrupt17_Handler                 ;   17 Interrupt 17
				DCD      Interrupt18_Handler                 ;   18 Interrupt 18
				DCD      Interrupt19_Handler                 ;   19 Interrupt 19
				DCD      Interrupt20_Handler                 ;   20 Interrupt 20
				DCD      Interrupt21_Handler                 ;   21 Interrupt 21
				DCD      Interrupt22_Handler                 ;   22 Interrupt 22
				DCD      Interrupt23_Handler                 ;   23 Interrupt 23
				DCD      Interrupt24_Handler                 ;   24 Interrupt 24
				DCD      Interrupt25_Handler                 ;   25 Interrupt 25
				DCD      Interrupt26_Handler                 ;   26 Interrupt 26
				DCD      Interrupt27_Handler                 ;   27 Interrupt 27
				DCD      Interrupt28_Handler                 ;   28 Interrupt 28
				DCD      Interrupt29_Handler                 ;   29 Interrupt 29
				DCD      Interrupt30_Handler                 ;   30 Interrupt 30
				DCD      Interrupt31_Handler                 ;   31 Interrupt 31
__Vectors_End
__Vectors_Size  EQU      __Vectors_End - __Vectors


                AREA     |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT   Reset_Handler             [WEAK]
                IMPORT   SystemInit
                IMPORT   __main

                LDR      R0, =SystemInit
                BLX      R0
                LDR      R0, =__main
                BX       R0
                ENDP


; Macro to define default exception/interrupt handlers.
; Default handler are weak symbols with an endless loop.
; They can be overwritten by real handlers.
                MACRO
                Set_Default_Handler  $Handler_Name
$Handler_Name   PROC
                EXPORT   $Handler_Name             [WEAK]
                B        .
                ENDP
                MEND


; Default exception/interrupt handler

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  HardFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

                Set_Default_Handler  UART0_Handler
                Set_Default_Handler  UART1_Handler
                Set_Default_Handler  TIMER0_Handler
                Set_Default_Handler  TIMER1_Handler
                Set_Default_Handler  GPIO0_Handler
                Set_Default_Handler  UARTOVF_Handler
                Set_Default_Handler  ENT_Handler
                Set_Default_Handler  I2C_Handler
                Set_Default_Handler  CAN_Handler
                Set_Default_Handler  RTC_Handler
				Set_Default_Handler  Interrupt10_Handler
				Set_Default_Handler  DTimer_Handler
				Set_Default_Handler  TRNG_Handler
				Set_Default_Handler  Interrupt13_Handler
				Set_Default_Handler  Interrupt14_Handler
				Set_Default_Handler  Interrupt15_Handler
				Set_Default_Handler  Interrupt16_Handler
				Set_Default_Handler  Interrupt17_Handler
				Set_Default_Handler  Interrupt18_Handler
				Set_Default_Handler  Interrupt19_Handler
				Set_Default_Handler  Interrupt20_Handler
				Set_Default_Handler  Interrupt21_Handler
				Set_Default_Handler  Interrupt22_Handler
				Set_Default_Handler  Interrupt23_Handler
				Set_Default_Handler  Interrupt24_Handler
				Set_Default_Handler  Interrupt25_Handler
				Set_Default_Handler  Interrupt26_Handler
				Set_Default_Handler  Interrupt27_Handler
				Set_Default_Handler  Interrupt28_Handler
				Set_Default_Handler  Interrupt29_Handler
				Set_Default_Handler  Interrupt30_Handler
				Set_Default_Handler  Interrupt31_Handler

                ALIGN


; User setup Stack & Heap

                EXPORT   __stack_limit
                EXPORT   __initial_sp
                IF       Heap_Size != 0                      ; Heap is provided
                EXPORT   __heap_base
                EXPORT   __heap_limit
                ENDIF

                END
