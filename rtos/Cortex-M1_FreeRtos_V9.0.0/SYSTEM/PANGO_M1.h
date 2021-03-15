/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2019 PANGO 
 * 		
 * @file      PANGO_M1.h
 * @author    Embedded Development Team
 * @version   V1.0.0
 * @date      2019-09-09 09:09:09
 * @brief     CMSIS Cortex-M1 Core Peripheral Access Layer Header File for Device Cortex-M1.
 *				    This file contains all the peripheral register's definitions, bits 
 *				    definitions and memory mapping for Cortex-M1 Connectivity line, 
 *				    High density, High density value line, Medium density, 
 *				    Medium density Value line, Low density, Low density Value line 
 *				    and XL-density devices.
 *
 *				    The file is the unique include file that the application programmer
 *				    is using in the C source code, usually in main.c. This file contains:
 *					   - Configuration section that allows to select:
 *						  - The device used in the target application
 *						  - To use or not the peripheral drivers in application code(i.e. 
 *						    code will be based on direct access to peripheral registers 
 *						    rather than drivers API), this option is controlled by 
 *						    "#define USE_STDPERIPH_DRIVER"
 *						  - To change few application-specific parameters such as 
 *						    crystal frequency
 *						  - Data structures and the address mapping for all peripherals
 *						  - Peripheral's registers declarations and bits definition
 *						  - Macros to access peripheral registers hardware
 *
 ******************************************************************************************
 */

#ifndef PANGO_M1_H
#define PANGO_M1_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum IRQn
{
/* -------------------  Processor Exceptions Numbers  ----------------------------- */
  NonMaskableInt_IRQn           = -14,     /*  2 Non Maskable Interrupt */
  HardFault_IRQn                = -13,     /*  3 HardFault Interrupt */



  SVCall_IRQn                   =  -5,     /* 11 SV Call Interrupt */

  PendSV_IRQn                   =  -2,     /* 14 Pend SV Interrupt */
  SysTick_IRQn                  =  -1,     /* 15 System Tick Interrupt */

/* -------------------  Processor Interrupt Numbers  ------------------------------ */
  UART0_IRQn                    =   0,     /* 0 UART0 Interrupt */
  UART1_IRQn                    =   1,     /* 1 UART1 Interrupt */
  TIMER0_IRQn                   =   2,     /* 2 TIMER0 Interrupt */
  TIMER1_IRQn                   =   3,     /* 3 TIMER1 Interrupt */
  GPIO0_IRQn                    =   4,     /* 4 GPIO0 Interrupt */
  UARTOVF_IRQn                  =   5,     /* 5 UART0,1 Overflow Interrupt */
  ENT_IRQn                      =   6,     /* 6 Ethernet Interrupt */
  I2C_IRQn                      =   7,     /* 7 I2C Interrupt */
  CAN_IRQn                      =   8,     /* 8 CAN Interrupt */
  RTC_IRQn                      =   9,     /* 9 RTC Interrupt */
  Interrupt10_IRQn              =   10,
  DTimer_IRQn                   =   11,    /* 11 DualTimer Interrupt */
  TRNG_IRQn                     =   12,    /* 12 TRNG Interrupt */
  Interrupt13_IRQn              =   13,	   
  Interrupt14_IRQn              =   14,
  Interrupt15_IRQn              =   15,
  Interrupt16_IRQn              =   16,
  Interrupt17_IRQn              =   17,
  Interrupt18_IRQn              =   18,
  Interrupt19_IRQn              =   19,
  Interrupt20_IRQn              =   20,
  Interrupt21_IRQn              =   21,
  Interrupt22_IRQn              =   22,
  Interrupt23_IRQn              =   23,
  Interrupt24_IRQn              =   24,
  Interrupt25_IRQn              =   25,
  Interrupt26_IRQn              =   26,
  Interrupt27_IRQn              =   27,
  Interrupt28_IRQn              =   28,
  Interrupt29_IRQn              =   29,
  Interrupt30_IRQn              =   30,
  Interrupt31_IRQn              =   31
} IRQn_Type;


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

/* ----------------------------- Enumeration Definition ----------------------------------- */
typedef enum
{
  RESET = 0,
  SET = !RESET
}FlagStatus,ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
}FunctionalState;

typedef enum
{
  ERROR = 0,
  SUCCESS = !ERROR
}ErrorStatus;

/* --------  Configuration of Core Peripherals  ----------------------------------- */
#define __CM1_REV                 0x0100U   /* Core revision r1p0 */
#define __MPU_PRESENT             0U        /* no MPU present */
#define __VTOR_PRESENT            0U        /* no VTOR present */
#define __NVIC_PRIO_BITS          2U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */

#include "core_cm1.h"                       /* Processor and core peripherals */
#include "system_PANGO_M1.h"                /* System Header */


/* ================================================================================ */
/* ================     Peripheral Register Definition Section     ================ */
/* ================================================================================ */

/*--------- Universal Asynchronous Receiver Transmitter (UART) --------*/
typedef struct
{
  __IO   uint32_t  DATA;          /*!< Offset: 0x000 Data Register    (R/W)          */
  __IO   uint32_t  STATE;         /*!< Offset: 0x004 Status Register  (R/W)          */
  __IO   uint32_t  CTRL;          /*!< Offset: 0x008 Control Register (R/W)          */
  union
  {
    __I    uint32_t  INTSTATUS;   /*!< Offset: 0x00C Interrupt Status Register (R/ ) */
    __O    uint32_t  INTCLEAR;    /*!< Offset: 0x00C Interrupt Clear Register ( /W)  */
  };
  __IO   uint32_t  BAUDDIV;       /*!< Offset: 0x010 Baudrate Divider Register (R/W) */
}UART_TypeDef;

/*------------------------ Timer (TIMER) ------------------------*/
typedef struct
{
  __IO   uint32_t  CTRL;          /*!< Offset: 0x000 Control Register (R/W)          */
  __IO   uint32_t  VALUE;         /*!< Offset: 0x004 Current Value Register (R/W)    */
  __IO   uint32_t  RELOAD;        /*!< Offset: 0x008 Reload Value Register  (R/W)    */
  union
  {
    __I    uint32_t  INTSTATUS;   /*!< Offset: 0x00C Interrupt Status Register (R/ ) */
    __O    uint32_t  INTCLEAR;    /*!< Offset: 0x00C Interrupt Clear Register ( /W)  */
  };
}TIMER_TypeDef;

/*--------------------- General Purpose Input Output (GPIO) ----------*/
typedef struct
{
  __IO   uint32_t  DATA;          /* Offset: 0x000 (R/W) DATA Register                     */
  __IO   uint32_t  DATAOUT;       /* Offset: 0x004 (R/W) Data Output Latch Register        */
         uint32_t  RESERVED0[2];  /* Offset: 0x010-0x004                                   */
  __IO   uint32_t  OUTENSET;      /* Offset: 0x010 (R/W) Output Enable Set Register        */
  __IO   uint32_t  OUTENCLR;      /* Offset: 0x014 (R/W) Output Enable Clear Register      */
  __IO   uint32_t  ALTFUNCSET;    /* Offset: 0x018 (R/W) Alternate Function Set Register   */
  __IO   uint32_t  ALTFUNCCLR;    /* Offset: 0x01C (R/W) Alternate Function Clear Register */
  __IO   uint32_t  INTENSET;      /* Offset: 0x020 (R/W) Interrupt Enable Set Register     */
  __IO   uint32_t  INTENCLR;      /* Offset: 0x024 (R/W) Interrupt Enable Clear Register   */
  __IO   uint32_t  INTTYPESET;    /* Offset: 0x028 (R/W) Interrupt Type Set Register       */
  __IO   uint32_t  INTTYPECLR;    /* Offset: 0x02C (R/W) Interrupt Type Clear Register     */
  __IO   uint32_t  INTPOLSET;     /* Offset: 0x030 (R/W) Interrupt Polarity Set Register   */
  __IO   uint32_t  INTPOLCLR;     /* Offset: 0x034 (R/W) Interrupt Polarity Clear Register */
  union
  {
    __I    uint32_t  INTSTATUS;    /* Offset: 0x038 (R/ ) Interrupt Status Register        */
    __O    uint32_t  INTCLEAR;     /* Offset: 0x038 ( /W) Interrupt Clear Register         */
  };
         uint32_t RESERVED1[241];    /* Offset : 0x400-0x0038                              */
  __IO   uint32_t MASKLOWBYTE[256];  /* Offset: 0x400 - 0x7FC Lower byte Masked Access Register (R/W) */
  __IO   uint32_t MASKHIGHBYTE[256]; /* Offset: 0x800 - 0xBFC Upper byte Masked Access Register (R/W) */
}GPIO_TypeDef;

/*----------------------------- WatchDog ------------------------*/
typedef struct
{
  __IO    uint32_t  LOAD;           /* Offset: 0x000 (R/W) Watchdog Load Register                         */
  __I     uint32_t  VALUE;          /* Offset: 0x004 (R/ ) Watchdog Value Register                        */
  __IO    uint32_t  CTRL;           /* Offset: 0x008 (R/W) Watchdog Control Register                      */
  __O     uint32_t  INTCLR;         /* Offset: 0x00C ( /W) Watchdog Clear Interrupt Register              */
  __I     uint32_t  RIS;            /* Offset: 0x010 (R/ ) Watchdog Raw Interrupt Status Register         */
  __I     uint32_t  MIS;            /* Offset: 0x014 (R/ ) Watchdog Interrupt Status Register             */
          uint32_t  RESERVED0[762]; /* Offset: 0xC00-0x014 */
  __IO    uint32_t  LOCK;           /* Offset: 0xC00 (R/W) Watchdog Lock Register */
          uint32_t  RESERVED1[191]; /* Offset: 0xF00-0xC00 */
  __IO    uint32_t  ITCR;           /* Offset: 0xF00 (R/W) Watchdog Integration Test Control Register     */
  __O     uint32_t  ITOP;           /* Offset: 0xF04 ( /W) Watchdog Integration Test Output Set Register  */
}WDOG_TypeDef;

/*----------------------------- I2C --------------------------*/
typedef struct {
	__IO uint32_t PRER;            	/* Offset: 0x00 (R/W) I2C Prescale Register                            */
	__IO uint32_t CTR;             	/* Offset: 0x04 (R/W) I2C Control Register                             */
	__O  uint32_t TXR;          	/* Offset: 0x08 ( /W) I2C Data Transmit Register                       */
	__I  uint32_t RXR;          	/* Offset: 0x0C (R/ ) I2C Data Receive Register                        */
	__O  uint32_t CR;           	/* Offset: 0x10 ( /W) I2C Command Register                             */
	__I  uint32_t SR;           	/* Offset: 0x14 (R/ ) I2C Status Register                              */
}I2C_TypeDef;

/*----------------------------- CAN --------------------------*/
typedef struct {
	__IO uint32_t SRST;       /* 0x0000 software reset register                             */
	__IO uint32_t CMD;        /* 0x0004 command register                                    */
	__IO uint32_t BRP;        /* 0x0008 baud rate prescalar register                        */
	__IO uint32_t BTN;        /* 0x000C bit timing (nominal) register                       */
	__IO uint32_t BTD;        /* 0x0010 bit timing (data)register                           */
	__I  uint32_t RSVD0[3];   /* 0x001C reserved                                            */
	__I  uint32_t IS;         /* 0x0020 interrupt status register                           */
	__IO uint32_t IE;         /* 0x0024 interrupt enable register                           */
	__O  uint32_t IC;         /* 0x0028 interrupt clear register                            */
	__I  uint32_t RSVD1;      /* 0x002C reserved                                            */
	__IO uint32_t CFG;        /* 0x0030 configuration register                              */
	__I  uint32_t RSVD2[3];   /* 0x0034~0x003c reserved                                     */
	__IO uint32_t RXBCFG;     /* 0x0040 rx buffer/fifo configuration register               */
	__IO uint32_t TXBCFG;     /* 0x0044 tx buffer/fifo configuration register               */
	__IO uint32_t TXHBCFG;    /* 0x0048 tx high-priority/fifo configuration register        */
	__I  uint32_t RSVD3;	  /* 0x004C reserved                                            */
	__IO uint32_t TXBRETRY;   /* 0x0050 tx buffer retry count                               */
	__IO uint32_t TXHBRETRY;  /* 0x0054 tx high-priority buffer retry count                 */
	__I  uint32_t TXMSGSTS;   /* 0x0058 transmit message status register                    */
	__I  uint32_t TXHMSGSTS;  /* 0x005C transmit high-priority message status register      */
	__IO uint32_t ERRSTS;     /* 0x0060 error status register                               */
	__I  uint32_t ERRCNTR;    /* 0x0064 error counter register                              */
	__I  uint32_t RSVD4[38];  /* 0x0068~0x00fc reserved                                     */
	__IO uint32_t AF[16];     /* 0x0100 receive acceptance filter register                  */
	__IO uint32_t AFM[16];    /* 0x0140 receive acceptance filter mask register             */
	__I  uint32_t RSVD5[32];  /* 0x0180~0x01fc reserved                                     */
	__I  uint32_t RXB;        /* 0x0200 receive buffer/fifo window register                 */
	__O  uint32_t TXB;        /* 0x0204 transmit buffer/fifo window register                */
	__O  uint32_t TXHB;       /* 0x0208 transmit high-priority buffer/fifo window register  */
	__I  uint32_t TXBSTS;     /* 0x020C transmit buffer/fifo status                         */
	__I  uint32_t TXHBSTS;    /* 0x0210 transmit high-priority byffer/fifo status           */
	__I  uint32_t RXBSTS;     /* 0x0214 receive buffer/fifo status                          */
}CAN_RegDef;

/*----------------------------- Ethernet Mac--------------------------*/
typedef struct {
	union
	{
		__O  uint32_t ETH_TX_DATA[384];     /* 0x000~0x5ff transmit data registers          */
		__I  uint32_t ETH_RX_DATA[384];     /* 0x000~0x5ff receive data registers           */
	};
	__IO uint32_t ETH_TX_LENGTH;            /* 0x600 transmit data length, bit[10:0]        */
	__IO uint32_t ETH_TX_EN;                /* 0x604 transmit enable, bit[0]                */
	__IO uint32_t ETH_TX_FAIL;              /* 0x608 transmit fail, bit[2,1,0]              */
	__I  uint32_t ETH_TX_IS;                /* 0x60c transmit interrupt status, bit[0]      */
	__O  uint32_t ETH_TX_IC;                /* 0x610 transmit interrupt clear, bit[0]       */
	__IO uint32_t ETH_TX_IE;                /* 0x614 transmit interrupt enable, bit[0]      */
	     uint32_t RESERVED_1[26];           /* 0x618~0x67f reserved                         */
	__I  uint32_t ETH_RX_LENGTH;            /* 0x680 receive data length                    */
	__I  uint32_t ETH_RX_IS;                /* 0x684 receive interrupt status, bit[0]       */
	__IO uint32_t ETH_RX_IE;                /* 0x688 receive interrupt enable, bit[0]       */
	__O  uint32_t ETH_RX_IC;                /* 0x68c receive interrupt clear, bit[0]        */
	     uint32_t RESERVED_2[28];           /* 0x690~0x6ff reserved                         */
	__IO uint32_t MIIM_OP_MODE;             /* 0x700 miim operation mode, bit[0]            */
	__IO uint32_t MIIM_PHY_ADDR;            /* 0x704 miim phy address, bit[4:0]             */
	__IO uint32_t MIIM_REG_ADDR;            /* 0x708 miim reg address, bit[4:0]             */
	__IO uint32_t MIIM_WR_DATA;             /* 0x70c miim write data, bit[15:0]             */
	__I  uint32_t MIIM_RD_DATA;             /* 0x710 miim read data, bit[15:0]              */
	__I  uint32_t MIIM_IS;                  /* 0x714 miim interrupt status, bit[1,0]        */
	__IO uint32_t MIIM_IE;                  /* 0x718 miim interrupt enable, bit[1,0]        */
	__O  uint32_t MIIM_IC;                  /* 0x71c miim interrupt clear, bit[1,0]         */
	__IO uint32_t MIIM_OP_EN;               /* 0x720 miim operation enable, bit[0]          */
	__IO uint32_t ETH_MODE;                 /* 0x724 ethernet operation mode, bit[2,1,0]    */
}ETH_RegDef;

/*----------------Serial Peripheral Interface (SPI)-----------------*/
typedef struct
{
  __I     uint32_t RDATA;        /* Offset: 0x00 (R/ ) Data Read Register          */
  __O     uint32_t WDATA;        /* Offset: 0x04 (/W ) Data Write Register         */
  __IO    uint32_t STATUS;       /* Offset: 0x08 (R/W) Status Register             */
  __IO    uint32_t SSMASK;       /* Offset: 0x0C (R/W) Unused Select slave address */
  __IO    uint32_t CTRL;         /* Offset: 0x10 (R/W) Control Register            */
}SPI_TypeDef;

/*--------------------------------DUALTIMER-----------------------------*/
typedef struct 
{
	__IO uint32_t TIMER1LOAD;         /* Offset: 0x00 (R/W) Load Register                   */
	__I  uint32_t TIMER1VALUE ;       /* Offset: 0x04 (R/ ) Current Value Register          */
	__IO uint32_t TIMER1CONTROL;      /* Offset: 0x08 (R/W) Timer Control Register          */
	__O  uint32_t TIMER1INTCLR ;      /* Offset: 0x0C ( /W) Interrupt Clear Register        */
	__I  uint32_t TIMER1RIS    ;      /* Offset: 0x10 (R/ ) Raw Interrupt Status Register   */
	__I  uint32_t TIMER1MIS    ;      /* Offset: 0x14 (R/ ) Interrupt Status Register       */
	__IO uint32_t TIMER1BGLOAD ;      /* Offset: 0x18 (R/W) Background Load Register        */

	__IO uint32_t RESERVE1;           /* Reserved                                           */
	
	__IO uint32_t TIMER2LOAD;         /* Offset: 0x20 (R/W) Load Register                   */
	__I  uint32_t TIMER2VALUE ;       /* Offset: 0x24 (R/ ) Current Value Register          */
	__IO uint32_t TIMER2CONTROL;      /* Offset: 0x28 (R/W) Timer Control Register          */
	__O  uint32_t TIMER2INTCLR ;      /* Offset: 0x2C ( /W) Interrupt Clear Register        */
	__I  uint32_t TIMER2RIS    ;      /* Offset: 0x30 (R/ ) Raw Interrupt Status Register   */
	__I  uint32_t TIMER2MIS    ;      /* Offset: 0x34 (R/ ) Interrupt Status Register       */
	__IO uint32_t TIMER2BGLOAD ;	  /* Offset: 0x38 (R/W) Background Load Register        */
}DUALTIMER_RegDef;

/*--------------------------RTC----------------------------*/
typedef struct
{
	__I  uint32_t RTC_CURRENT_DATA;       /* Offset: 0x000 (R/ ) Data Register                          */
	__IO uint32_t RTC_MATCH_VALUE;        /* Offset: 0x004 (R/W) Match Register                         */
	__IO uint32_t RTC_LOAD_VALUE;         /* Offset: 0x008 (R/W) Load Register                          */
	__IO uint32_t RTC_CTROLLER_REG;       /* Offset: 0x00C (R/W) Control Register                       */
	__IO uint32_t RTC_IMSC;               /* Offset: 0x010 (R/W) Interrupt Mask Set and Clear Register  */
	__I  uint32_t RTC_RIS;                /* Offset: 0x014 (R/ ) Raw Interrupt Status Register          */
	__I  uint32_t RTC_MIS;                /* Offset: 0x018 (R/ ) Masked Interrupt Status Register       */
	__O  uint32_t RTC_INTR_CLEAR;         /* Offset: 0x01C ( /W) Interrupt Clear Register               */
}RTC_RefDef;

/*---------------------------TRNG------------------------------*/
typedef struct
{
	__I  uint8_t  RESEVE1[0x100];         /* Offset: 0x000-0x0FC Reserved                                        */
	__IO uint32_t RNG_IMR;                /* Offset: 0x100 (R/W) Interrupt Mask Register                         */
	__I  uint32_t RNG_ISR;                /* Offset: 0x104 (R/ ) Interrupt Status Register                       */
	__O  uint32_t RNG_ICR;                /* Offset: 0x108 ( /W) Interrupt Clear Register                        */
	__IO uint32_t TRNG_CONFIG;            /* Offset: 0x10C (R/W) Configuration Register                          */
	__I  uint32_t TRNG_VALID;             /* Offset: 0x110 (R/ ) Valid Register                                  */
	__I  uint32_t EHR_DATA0;              /* Offset: 0x114-0x128 (R/ ) Entropy Holding Register Data Registers   */
	__I  uint32_t EHR_DATA1;
	__I  uint32_t EHR_DATA2;
	__I  uint32_t EHR_DATA3;
	__I  uint32_t EHR_DATA4;
	__I  uint32_t EHR_DATA5;
	__IO uint32_t RND_SOURCE_ENABLE;      /* Offset: 0x12C (R/W) Random Source Enable Register                   */
	__IO uint32_t SAMPLE_CNT1;            /* Offset: 0x130 (R/W) Sample Count Register                           */
	__IO uint32_t AUTOCORR_STATISTIC;     /* Offset: 0x134 (R/W) Autocorrelation Register                        */
	__I  uint32_t TRNG_DEBUG_CONTROL;     /* Offset: 0x138 (R/ ) Debug Control Register                          */
	__I  uint32_t RESEVE2;                /* Offset: 0x13C Reserved                                              */
	__O  uint32_t TRNG_SW_RESET;          /* Offset: 0x140 ( /W) Reset Register                                  */
	__I  uint8_t  RESEVE3[0x74];          /* Offset: 0x144-0x1B4 Reserved                                        */
	__I  uint32_t TRNG_BUSY;              /* Offset: 0x1B8 (R/ ) Busy Register                                   */
	__O  uint32_t RST_BIT_COUNT;          /* Offset: 0x1BC ( /W) Reset Bits Counter Register                     */
	__I  uint8_t  RESEVE4[0x20];          /* Offset: 0x1C0-0x1DC Reserved                                        */
	__I  uint32_t RNG_BIST_CNTR0;         /* Offset: 0x1E0-0x1E8 BIST Counter Registers                          */
	__I  uint32_t RNG_BIST_CNTR1;
	__I  uint32_t RNG_BIST_CNTR2;
}TRNG_RefDef;

/*--------------------------SD-Card-----------------------------*/
typedef struct {
	__IO uint32_t TRANSDATA[128];    /* Offset: 0x000-0x1FF (R/ ) Data Registers    */
	__IO uint32_t BASEADDR;          /* Offset: 0x200 (R/W) Base Address Register   */
	__IO uint32_t READEN;            /* Offset: 0x204 (R/W) Read Enable Register    */
	__IO uint32_t INITIALISED;       /* Offset: 0x208 (R/ ) Initialization Register */
}SDCard_TypeDef;

/*---------------------------DDR------------------------------*/
typedef struct {
	__IO uint32_t CTRL;    	 		/* Offset: 0x00 (R/W) Control Register            */
	__IO uint32_t STATUS;          	/* Offset: 0x04 (R/W) Status Register            */
	__IO uint32_t READ_ADDR;        /* Offset: 0x08 (R/W) Read Data Start Address    */
	__IO uint32_t CMD;        	    /* Offset: 0x0c (R/W) Command  Register  */
}DDR_TypeDef;

/*---------------------------ICache------------------------------*/
typedef struct {
	__IO uint32_t CTRL;          	/* Offset: 0x00 (R/W) Control Register            */
	__IO uint32_t STATUS;        	/* Offset: 0x04 (R/W) Status Register    		*/
}ICACHE_TypeDef;

/*---------------------------DCache------------------------------*/
typedef struct {
	__IO uint32_t CTRL;    	 		/* Offset: 0x00 (R/W) Control Register            */
	__IO uint32_t STATUS;          	/* Offset: 0x04 (R/W) Status Register            */
	__IO uint32_t START_ADDR;       /* Offset: 0x08 (R/W) Data Start Address    */
	__IO uint32_t LEN;        	    /* Offset: 0x0c (R/W) Data Len  */
}DCACHE_TypeDef;

/*---------------------------DMAC0------------------------------*/
typedef struct{
	__O uint32_t DESCRIPTOR_NUM;	/* Offset: 0x00 ( /W) Descriptor RX/TX Register Num  */
	__O uint32_t DESCRIPTOR_CTRL;	/* Offset: 0x04 ( /W) Descriptor Control Register    */
	__O uint32_t DESCRIPTOR_TX_ADDR;/* Offset: 0x08 ( /W) Descriptor Tx Address          */
	__O uint32_t DESCRIPTOR_RX_ADDR;/* Offset: 0x0c ( /W) Descriptor Rx Address          */
	__O uint32_t DESCRIPTOR_LEN;	/* Offset: 0x10 ( /W) Descriptor Length              */
	__O uint32_t DMAC_CTRL;    	 	/* Offset: 0x14 ( /W) DMAC Control Register          */
	__O uint32_t DMAC_TX_LEN;		/* Offset: 0x18 ( /W) DMAC Tx Data Length            */
	__I uint32_t DMAC_RX_LEN;		/* Offset: 0x1c (R/ ) DMAC Rx Data Length            */
	__I uint32_t DMAC_TX_NUM;		/* Offset: 0x20 (R/ ) DMAC Tx Descriptor Num         */
	__I uint32_t DMAC_RX_NUM;		/* Offset: 0x24 (R/ ) DMAC Rx Descriptor Num         */
	union
	{
		__I uint32_t  INTSTATUS;    /* Offset: 0x28 (R/ ) Interrupt Status Register      */
		__O uint32_t  INTCLEAR;     /* Offset: 0x28 ( /W) Interrupt Clear Register       */
	};
	__O uint32_t CTRL;    	 		/* Offset: 0x2c ( /W) Interrupt Control Register     */
	__IO uint32_t STATUS;    		/* Offset: 0x30 (R/W) Interrupt Status Register      */
}DMAC0_TypeDef;

/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* ================================================================================ */
/* ================         Peripheral Address Map Section         ================ */
/* ================================================================================ */

/* Memory and Peripheral base Address */
#define FLASH_BASE        ((uint32_t)0x00000000)   			/*!< (FLASH     ) Base Address */
#define SRAM_BASE         ((uint32_t)0x20000000)   			/*!< (SRAM      ) Base Address */
#define SMEN_BASE 	      ((uint32_t)0x60000000)   			/*!< (SMEN      ) Base Address */
#define UDP_SPEED_UP_BASE ((uint32_t)0x70000000)			/*!< (UDP SPEED UP ) Base Address */
#define DDR_DATA_BASE 	  ((uint32_t)0x80000000)   			/*!< (DDR DATA  ) Base Address */
#define DDR_BASE          ((uint32_t)0x9ffffff0)   			/*!< (DDR       ) Base Address */

#define AHB1PERIPH_BASE   ((uint32_t)0x40000000)   			/*!< (AHB1 Peripheral) Base Address */
#define AHB2PERIPH_BASE   ((uint32_t)0xA0000000)   			/*!< (AHB2 Peripheral) Base Address*/
#define APB1PERIPH_BASE   ((uint32_t)0x50000000)   			/*!< (APB1 Peripheral) Base Address*/
#define APB2PERIPH_BASE   ((uint32_t)0xB0000000)   			/*!< (APB2 Peripheral) Base Address*/

/* AHB1 Peripheral base address */
#define GPIO0_BASE        (AHB1PERIPH_BASE + 0x0000000)    	/* !< GPIO0 Base Address     */
#define CAN_BASE          (AHB1PERIPH_BASE + 0x5000000)    	/* !< CAN Base Address       */
#define ENT_BASE          (AHB1PERIPH_BASE + 0x6000000)    	/* !< Ethernet Base Address  */
#define ICACHE_BASE       (AHB1PERIPH_BASE + 0x7000000)    	/* !< ICache Base Address  */
#define DCACHE_BASE       (AHB1PERIPH_BASE + 0x8000000)    	/* !< ICache Base Address  */
#define DMAC0_BASE        (AHB1PERIPH_BASE + 0x9000000)    	/* !< DMA0 Base Address  */

/* APB1 Peripheral base address */
#define TIMER0_BASE       (APB1PERIPH_BASE + 0x0000)    	/* !< TIMER0 Base Address     */
#define TIMER1_BASE       (APB1PERIPH_BASE + 0x1000)    	/* !< TIMER1 Base Address     */
#define DUALTIMER_BASE    (APB1PERIPH_BASE + 0x2000)    	/* !< DUAL timer ADDRESS      */
#define UART0_BASE        (APB1PERIPH_BASE + 0x4000)    	/* !< UART0  Base Address     */
#define UART1_BASE        (APB1PERIPH_BASE + 0x5000)    	/* !< UART1  Base Address     */
#define RTC_BASE          (APB1PERIPH_BASE + 0x6000)    	/* !< RTC Base Address        */
#define WDOG_BASE         (APB1PERIPH_BASE + 0x8000)    	/* !< WATCHDOG  Base Address  */
#define SDCARD_BASE       (APB1PERIPH_BASE + 0x9000)    	/* !< SD-Card Base Address    */
#define I2C_BASE          (APB1PERIPH_BASE + 0xA000)    	/* !< I2C Base Address        */
#define SPI_BASE          (APB1PERIPH_BASE + 0xB000)    	/* !< SPI Base Address        */
#define USER_BASE         (APB1PERIPH_BASE + 0xC300)    	/* !< USER Base Address        */
#define TRNG_BASE         (APB1PERIPH_BASE + 0xF000)    	/* !< TRNG Base Address       */



/* BANK RAM base address */
#define BANK_RAM_BASE0 	  (SMEN_BASE + 0x0000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE1 	  (SMEN_BASE + 0x1000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE2 	  (SMEN_BASE + 0x2000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE3 	  (SMEN_BASE + 0x3000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE4 	  (SMEN_BASE + 0x4000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE5 	  (SMEN_BASE + 0x5000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE6 	  (SMEN_BASE + 0x6000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE7 	  (SMEN_BASE + 0x7000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE8 	  (SMEN_BASE + 0x8000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE9 	  (SMEN_BASE + 0x9000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE10   (SMEN_BASE + 0xA000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE11   (SMEN_BASE + 0xB000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE12   (SMEN_BASE + 0xC000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE13   (SMEN_BASE + 0xD000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE14   (SMEN_BASE + 0xE000000)   	   	/* !< RAM0 Base Address      */
#define BANK_RAM_BASE15   (SMEN_BASE + 0xF000000)   	   	/* !< RAM0 Base Address      */

#define DDR				  ((DDR_TypeDef       *) DDR_BASE)
#define UART0             ((UART_TypeDef      *) UART0_BASE)
#define UART1             ((UART_TypeDef      *) UART1_BASE)
#define TIMER0            ((TIMER_TypeDef     *) TIMER0_BASE)
#define TIMER1            ((TIMER_TypeDef     *) TIMER1_BASE)
#define WDOG              ((WDOG_TypeDef      *) WDOG_BASE)
#define I2C               ((I2C_TypeDef       *) I2C_BASE) 
#define GPIO0             ((GPIO_TypeDef      *) GPIO0_BASE)
#define CAN               ((CAN_RegDef        *) CAN_BASE)
#define Ethernet          ((ETH_RegDef        *) ENT_BASE)
#define SPI               ((SPI_TypeDef       *) SPI_BASE)
#define DUALTIMER         ((DUALTIMER_RegDef  *) DUALTIMER_BASE)
#define RTC               ((RTC_RefDef        *) RTC_BASE)
#define TRNG              ((TRNG_RefDef       *) TRNG_BASE)
#define SDCARD            ((SDCard_TypeDef    *) SDCARD_BASE)
#define ICACHE            ((ICACHE_TypeDef    *) ICACHE_BASE)
#define DCACHE            ((DCACHE_TypeDef    *) DCACHE_BASE)
#define DMAC0             ((DMAC0_TypeDef     *) DMAC0_BASE)
/* ================================================================================ */
/* ================  Peripheral Register Bit Definition Section    ================ */
/* ================================================================================ */

/******************************************************************************/
/*           Universal Asynchronous Receiver Transmitter (UART)               */
/******************************************************************************/
/* bit definitions for DATA register */
#define UART_DATA              ((uint32_t) 0x000000FF) /* UART DATA: Data value */

/* bit definitions for STATE register */
#define UART_STATE_TXBF        ((uint32_t) 0x00000001) /* UART STATE: Tx buffer full    */
#define UART_STATE_RXBF        ((uint32_t) 0x00000002) /* UART STATE: Rx buffer full    */
#define UART_STATE_TXOR        ((uint32_t) 0x00000004) /* UART STATE: Tx buffer overrun */
#define UART_STATE_RXOR        ((uint32_t) 0x00000008) /* UART STATE: Rx buffer overrun */

/* bit definitions for CTRL register */
#define UART_CTRL_TXEN         ((uint32_t) 0x00000001) /* UART CTRL: TX enable                           */
#define UART_CTRL_RXEN         ((uint32_t) 0x00000002) /* UART CTRL: RX enable           
            */
#define UART_CTRL_TXIRQEN      ((uint32_t) 0x00000004) /* UART CTRL: TX interrupt enable 
            */
#define UART_CTRL_RXIRQEN      ((uint32_t) 0x00000008) /* UART CTRL: RX interrupt enable 
            */
#define UART_CTRL_TXORIRQEN    ((uint32_t) 0x00000010) /* UART CTRL: TX overrun interrupt enable         */
#define UART_CTRL_RXORIRQEN    ((uint32_t) 0x00000020) /* UART CTRL: RX overrun interrupt enable         */
#define UART_CTRL_HSTM         ((uint32_t) 0x00000040) /* UART CTRL: High-speed test mode for TX enable  */

/* bit definitions for INTSTATUS register */
#define UART_INTSTATUS_TXIRQ    ((uint32_t) 0x00000001) /* UART INTCLEAR: Get TX interrupt status         */
#define UART_INTSTATUS_RXIRQ    ((uint32_t) 0x00000002) /* UART INTCLEAR: Get RX interrupt status         */
#define UART_INTSTATUS_TXORIRQ  ((uint32_t) 0x00000004) /* UART INTCLEAR: Get TX overrun interrupt status */
#define UART_INTSTATUS_RXORIRQ  ((uint32_t) 0x00000008) /* UART INTCLEAR: Get RX overrun interrupt status */

/* bit definitions for INTCLEAR register */
#define UART_INTCLEAR_TXIRQ    ((uint32_t) 0x00000001) /* UART INTCLEAR: Clear TX interrupt         */
#define UART_INTCLEAR_RXIRQ    ((uint32_t) 0x00000002) /* UART INTCLEAR: Clear RX interrupt         */
#define UART_INTCLEAR_TXORIRQ  ((uint32_t) 0x00000004) /* UART INTCLEAR: Clear TX overrun interrupt */
#define UART_INTCLEAR_RXORIRQ  ((uint32_t) 0x00000008) /* UART INTCLEAR: Clear RX overrun interrupt */

/* bit definitions for BAUDDIV register */
#define UART_BAUDDIV           ((uint32_t) 0x000FFFFF) /* UART BAUDDIV: Baud rate divider*/


/******************************************************************************/
/*                                Timer (TIMER)                               */
/******************************************************************************/
/* bit definitions for CTRL register */
#define TIMER_CTRL_EN          ((uint32_t) 0x00000001) /* TIMER CTRL: Enable                          */
#define TIMER_CTRL_SELEXTEN    ((uint32_t) 0x00000002) /* TIMER CTRL: Select external input as enable */
#define TIMER_CTRL_SELEXTCLK   ((uint32_t) 0x00000004) /* TIMER CTRL: Select external input as clock  */
#define TIMER_CTRL_IRQEN       ((uint32_t) 0x00000008) /* TIMER CTRL: Timer interrupt enable */

/* bit definitions for VALUE register */
#define TIMER_VALUE            ((uint32_t) 0xFFFFFFFF) /* TIMER VALUE: Current value */

/* bit definitions for RELOAD register */
#define TIMER_RELOAD           ((uint32_t) 0xFFFFFFFF) /* TIMER RELOAD: Reload value */

/* bit definitions for INTSTATUS register */
#define TIMER_INTSTATUS        ((uint32_t) 0x00000001) /* TIMER INTSTATUS: Get Timer interrupt status */

/* bit definitions for INTCLEAR register */
#define TIMER_INTCLEAR         ((uint32_t) 0x00000001) /* TIMER INTCLEAR: Clear Timer interrupt */

/******************************************************************************/
/*                   General Purpose Input Output (GPIO)                      */
/******************************************************************************/
/* bit definitions for  DATA register */
#define GPIO_DATA           ((uint32_t) 0x0000FFFF)  /* GPIO DATA: Data value */

/* bit definitions for DATAOUT register */
#define GPIO_DATAOUT        ((uint32_t) 0x0000FFFF)  /* GPIO DATAOUT: Data output value */

/* bit definitions for OUTENSET register */
#define GPIO_OUTENSET       ((uint32_t) 0x0000FFFF)  /* GPIO OUTENSET: Output enable set */

/* bit definitions for OUTENCLR register */
#define GPIO_OUTENCLR       ((uint32_t) 0x0000FFFF)  /* GPIO OUTENCLR: Output enable clear */

/* bit definitions for ALTFUNCSET register */
#define GPIO_ALTFUNSET      ((uint32_t) 0x0000FFFF)  /* GPIO ALTFUNCSET: Alternative function set */

/* bit definitions for ALTFUNCCLR register */
#define GPIO_ALTFUNCCLR     ((uint32_t) 0x0000FFFF)  /* GPIO ALTFUNCCLR: Alternative function clear */

/* bit definitions for INTENSET register */
#define GPIO_INTENSET       ((uint32_t) 0x0000FFFF)  /* GPIO INTENSET: Interrupt enable set */

/* bit definitions for INTENCLR register */
#define GPIO_INTENCLR       ((uint32_t) 0x0000FFFF)  /* GPIO INTENCLR: Interrupt enable clear */

/* bit definitions for INTTYPESET register */
#define GPIO_INTTYPESET     ((uint32_t) 0x0000FFFF)  /* GPIO INTTYPESET: Interrupt type set */

/* bit definitions for INTTYPECLR register */
#define GPIO_INTTYPECLR     ((uint32_t) 0x0000FFFF)  /* GPIO INTTYPECLR: Interrupt type clear */

/* bit definitions for INTPOLSET register */
#define GPIO_INTPOLSET      ((uint32_t) 0x0000FFFF)  /* GPIO INTPOLSET: Interrupt polarity set */

/* bit definitions for INTPOLCLR register */
#define GPIO_INTPOLCLR      ((uint32_t) 0x0000FFFF)  /* GPIO INTPOLCLR: Interrupt polarity clear */

/*  bit definitions for INTSTATUS register */
#define GPIO_INTSTATUS      ((uint32_t) 0x0000FFFF)  /* GPIO INTSTATUS: Get Interrupt status */

/*  bit definitions for INTCLEAR register */
#define GPIO_INTCLEAR       ((uint32_t) 0x0000FFFF)  /* GPIO INTCLEAR: Interrupt request clear*/

/*  bit definitions for MASKLOWBYTE register */
#define GPIO_MASKLOWBYTE    ((uint32_t) 0x000000FF)  /* GPIO MASKLOWBYTE: Data for lower byte access */

/*  bit definitions for MASKHIGHBYTE register */
#define GPIO_MASKHIGHBYTE   ((uint32_t) 0x0000FF00)  /* GPIO MASKHIGHBYTE: Data for high byte access */

/******************************************************************************/
/*                             WatchDog (WDOG)                                */
/******************************************************************************/
/*  bit definitions for LOAD register */
#define WDOG_LOAD              ((uint32_t) 0xFFFFFFFF)  /* the value from which the counter is to decrement */

/*  bit definitions for VALUE register */
#define WDOG_VALUE             ((uint32_t) 0xFFFFFFFF) /* the current value of the decrementing counter     */

/*  bit definitions for CTRL register */
#define WDOG_CTRL_INTEN        ((uint32_t) 0x00000001)  /* Enable the interrupt         */
#define WDOG_CTRL_RESEN        ((uint32_t) 0x00000002)  /* Enable watchdog reset output */

/*  bit definitions for INTCLR register */
#define WDOG_INTCLR            ((uint32_t) 0x00000001)  /* clear the watchdog interrupt and reloads the counter */

/*  bit definitions for RAWINTSTAT register */
#define WDOG_RAWINTSTAT        ((uint32_t) 0x00000001)  /* Raw interrupt status from the counter */

/*  bit definitions for MASKINTSTAT register */
#define WDOG_MASKINTSTAT       ((uint32_t) 0x00000001)  /* Enable interrupt status from the counter */

/*  bit definitions for LOCK register */
#define WDOG_LOCK_ENSTAT       ((uint32_t) 0x00000001)  /* Register write enable status */
#define WDOG_LOCK_EN           ((uint32_t) 0xFFFFFFFE)  /* Enable register writes */

/*  bit definitions for ITCR register */
#define WDOG_ITCR_INTEGTESTEN  ((uint32_t) 0x00000001)  /* Integration test mode enable */

/*  bit definitions for ITOP register */
#define WDOG_ITOP_WDOGRES      ((uint32_t) 0x00000001)  /* Integration test WDOGINT value */
#define WDOG_ITOP_WDOGINT      ((uint32_t) 0x00000002)  /* Integration test WDOGRES value */


/* ------------------------ Peripheral Includes -------------------------------------*/
#include "PANGO_M1_conf.h"


#ifdef __cplusplus
}
#endif

#endif  /* PANGO_M1_H */
