/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**          File:  Mcu_HW.h
 *         Module: Mcu_HW
 * 
 *    Description: header file for registers  definition
 *
 * 
 * ***************************************************************************/

/*****************************************************************************
 * File guard 
/*****************************************************************************/


#ifndef MCU_HW_H
#define MCU_HW_H

/*****************************************************************************
 *      INCLUDES
 * ***************************************************************************/
#include "Std_Types.h"

/*****************************************************************************
 *      GLOBAL DATA TYPES AND STRUCTURES
 * ***************************************************************************/
typedef struct 
{
    uint32 VECACT   :8;
    uint32          :3;
    uint32 RETBASE  :1;
    uint32 VECPEND  :8;   
    uint32          :2;
    uint32 ISRPEND  :1;
    uint32 ISRPRE   :1;
    uint32          :1;
    uint32 PENDSTCLR:1;
    uint32 PENDSTSET:1;
    uint32 UNPENDSV :1;
    uint32 PENDSV   :1;
    uint32          :2;
    uint32 NMISET   :1;
    
}INTCTRL_BF;

typedef struct 
{
    uint32 VECTRESET    :1;
    uint32 VECTCLRACT   :1;
    uint32 SYSRESREQ    :1;
    uint32              :5;   
    uint32 PRIFROUP     :3;
    uint32              :4;
    uint32 ENDIANESS    :1;
    uint32 VECTKEY      :16;
    
}APINT_BF;


typedef union 
{
    uint32 R;
    INTCTRL_BF B;
}INTCTRL_Tag;


typedef union 
{
    uint32 R;
    APINT_BF B;
}APINT_Tag;


/*****************************************************************************
 *      GLOBAL CONSTANT MACROS
 * ***************************************************************************/

//Cortex M4 Core Registers

#define PRIMASK   PRIMASK  //Enable/Disable All interrupts
#define FAULTMSK FAULTMSK //Enable/Disable All exceptions except NMI
#define BASEPRI  BASEPRI  //Defines minimuim priority for exception processing
#define PSR      PSR      //Current active exception

// Cortex M4 Peripheral Table and registers

#define CORTEXM4_PERI_BASE_ADDRESS         0xE000E000

// NVIC REGISTERS
#define INT_EN_BASE_ADDRESS                 0xE000E100      // RW
#define INT_DIS_BASE_ADDRESS                0xE000E180      // RW
#define INT_PEND_BASE_ADDRESS               0xE000E200      // RW
#define INT_UNPEND_BASE_ADDRESS             0xE000E280      // RW
#define INT_ACTIVE_BASE_ADDRESS             0xE000E300      // RO
#define INT_PRIORITY_BASE_ADDRESS           0xE000E400      // RW
// -->define SWTRIG REG

// SCB REGISTERS
#define APINT                              ((volatile APINT_Tag*)(CORTEXM4_PERI_BASE_ADDRESS+0xD0C))
#define INTCTRL                            ((volatile INTCTRL_Tag*)(CORTEXM4_PERI_BASE_ADDRESS+0xD04))
// --> define VTable base register
// --> define FAULTSTAT\ HFAULTSTAT
// --> define SYSHNDCTRL 
// --> SYSPRIx  

// System Control registers
#define SYS_CTRL_BASE_ADDRESS              0x400FE000
#define GPIO_HBCTL_OFFSET                  0x06C 
#define RCGCGPIO_OFFSET                    0x608
#define RCGCTIMER_OFFSET                   0x604
#define RCGCWTIMER_OFFSET                  0x65C
// System Control Registers

        /* GPIO*/

/* PORT BASE ADDRESSES APB*/

#define  GPIO_Port_A_APB                     0x40004000
#define  GPIO_Port_B_APB                     0x40005000
#define  GPIO_Port_C_APB                     0x40006000
#define  GPIO_Port_D_APB                     0x40007000
#define  GPIO_Port_E_APB                     0x40024000
#define  GPIO_Port_F_APB                     0x40025000


/* PORT BASE ADDRESSES AHB*/

#define  GPIO_Port_A_AHB                     0x40058000
#define  GPIO_Port_B_AHB                     0x40059000
#define  GPIO_Port_C_AHB                     0x4005A000
#define  GPIO_Port_D_AHB                     0x4005B000
#define  GPIO_Port_E_AHB                     0x4005C000
#define  GPIO_Port_F_AHB                     0x4005D000

/*GPIO Registers Offsets */

#define  GPIODATA_OFFSET                     0x000
#define  GPIODIR_OFFSET                      0x400
#define  GPIOIS_OFFSET                       0x404
#define  GPIOIBE_OFFSET                      0x408
#define  GPIOIEV_OFFSET                      0x40C
#define  GPIOIM_OFFSET                       0x410
#define  GPIORIS_OFFSET                      0x414
#define  GPIOMIS_OFFSET                      0x418
#define  GPIOICR_OFFSET                      0x41C
#define  GPIOAFSEL_OFFSET                    0x420
#define  GPIODR2R_OFFSET                     0x500
#define  GPIODR4R_OFFSET                     0x504
#define  GPIODR8R_OFFSET                     0x508
#define  GPIOODR_OFFSET                      0x50C
#define  GPIOPUR_OFFSET                      0x510
#define  GPIOPDR_OFFSET                      0x514
#define  GPIOSLR_OFFSET                      0x518
#define  GPIODEN_OFFSET                      0x51C
#define  GPIOLOCK_OFFSET                     0x520
#define  GPIOCR_OFFSET                       0x524
#define  GPIOAMSEL_OFFSET                    0x528
#define  GPIOPCTL_OFFSET                     0x52C
#define  GPIOADCCTL_OFFSET                   0x530
#define  GPIODMACTL_OFFSET                   0x534
#define  GPIOPeriphID4_OFFSET                0xFD0
#define  GPIOPeriphID5_OFFSET                0xFD4
#define  GPIOPeriphID6_OFFSET                0xFD8
#define  GPIOPeriphID7_OFFSET                0xFDC
#define  GPIOPeriphID0_OFFSET                0xFE0
#define  GPIOPeriphID1_OFFSET                0xFE4
#define  GPIOPeriphID2_OFFSET                0xFE8
#define  GPIOPeriphID3_OFFSET                0xFEC
#define  GPIOPCellID0_OFFSET                 0xFF0
#define  GPIOPCellID1_OFFSET                 0xFF4
#define  GPIOPCellID2_OFFSET                 0xFF8
#define  GPIOPCellID3_OFFSET                 0xFFC




/* General Purpose Timer Registers*/
#define TimerBaseAddressesNumber     12    

        /*Timer Base Addresses*/
#define _16_32_BIT_TIMER_0_BASE_ADDRESS      0x40030000
#define _16_32_BIT_TIMER_1_BASE_ADDRESS      0x40031000
#define _16_32_BIT_TIMER_2_BASE_ADDRESS      0x40032000
#define _16_32_BIT_TIMER_3_BASE_ADDRESS      0x40033000
#define _16_32_BIT_TIMER_4_BASE_ADDRESS      0x40034000
#define _16_32_BIT_TIMER_5_BASE_ADDRESS      0x40035000

#define _32_64_BIT_TIMER_0_BASE_ADDRESS      0x40036000
#define _32_64_BIT_TIMER_1_BASE_ADDRESS      0x40037000
#define _32_64_BIT_TIMER_2_BASE_ADDRESS      0x4003C000
#define _32_64_BIT_TIMER_3_BASE_ADDRESS      0x4004C000
#define _32_64_BIT_TIMER_4_BASE_ADDRESS      0x4003D000
#define _32_64_BIT_TIMER_5_BASE_ADDRESS      0x4003F000

        /*Register Offset*/

#define GPTMCFG_OFFSET                       0x000
#define GPTMTAMR_OFFSET                      0x004
#define GPTMTBMR_OFFSET                      0x008
#define GPTMCTL_OFFSET                       0x00C
#define GPTMSYNC_OFFSET                      0x010
#define GPTMIMR_OFFSET                       0x018
#define GPTMRIS_OFFSET                       0x01C
#define GPTMMIS_OFFSET                       0x020
#define GPTMICR_OFFSET                       0x024
#define GPTMTAILR_OFFSET                     0x028
#define GPTMTBILR_OFFSET                     0x02C
#define GPTMTAMATCHR_OFFSET                  0x030
#define GPTMTBMATCHR_OFFSET                  0x034
#define GPTMTAPR_OFFSET                      0x038
#define GPTMTBPR_OFFSET                      0x03C
#define GPTMTAPMR_OFFSET                     0x040
#define GPTMTBPMR_OFFSET                     0x044
#define GPTMTAR_OFFSET                       0x048
#define GPTMTBR_OFFSET                       0x04C
#define GPTMTAV_OFFSET                       0x050
#define GPTMTBV_OFFSET                       0x054
#define GPTMRTCPD_OFFSET                     0x058
#define GPTMTAPS_OFFSET                      0x05C
#define GPTMTBPS_OFFSET                      0x060
#define GPTMTAPV_OFFSET                      0x064
#define GPTMTBPV_OFFSET                      0x068
#define GPTMPP_OFFSET                        0xFC0

 /*****************************************************************************
 *      GLOBAL DATA  Prototypes
 * ***************************************************************************/

/*****************************************************************************
 *      GLOBAL Function MACROS
 * ***************************************************************************/
#define DISABLE_INT_I()        __asm__("CPSID i");         /*  Disable interrupts and configurable fault handlers (set PRIMASK) */
#define DISABLE_INT_F()        __asm__("CPSID f");         /*  Disable interrupts and all fault handlers (set PRIMASK)          */

#define ENABLE_INT_I()         __asm__("CPSIE i");         /* Enable interrupts and configurable fault handlers (clear PRIMASK) */
#define ENABLE_INT_F()         __asm__("CPSIE f");         /* Enable interrupts and configurable fault handlers (clear PRIMASK) */



#endif   /* MCU_HW_H */

/****************************************************************************
 *      END OF FILE: Mcu_HW.h
 * **************************************************************************/
