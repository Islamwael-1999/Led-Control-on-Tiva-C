/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   IntCtrl.h
 *          \brief
 * 
 *          \details
 *
 * 
 * ***************************************************************************/

/*****************************************************************************
 * File guard 
/*****************************************************************************/


#ifndef INTCTRL_TYPES_H
#define INTCTRL_TYPES_H

/*****************************************************************************
 *      INCLUDES
 * ***************************************************************************/
#include "Std_Types.h"

/*****************************************************************************
 *      GLOBAL CONSTANT MACROS
 * ***************************************************************************/

/*****************************************************************************
 *      GLOBAL FUNCTION MACROS
 * ***************************************************************************/

/*****************************************************************************
 *      GLOBAL DATA TYPES AND STRUCTURES
 * ***************************************************************************/
typedef enum
{
    // Use datasheet vectorTable to state Interrupts arrangment 
    // datasheet TM4C123GH6PM 
    // You can use 2 enums one for interrupts and one
    // Processor exceptions
    // So you can use interrupt Numbers instead of Vector number
    // Note interrupt vectors start at 16 vector numbers
    
    GPIO_PORT_A =0,
    GPIO_PORT_B ,
    GPIO_PORT_C ,
    GPIO_PORT_D ,
    GPIO_PORT_E ,
    
    UART0_0,
    UART_1,
    
    SSI0,
    I2C0,

    PWM_0_FAULT,
    PWM_0_GEN_0,
    PWM_0_GEN_1,
    PWM_0_GEN_2,

    QEI0,

    ADC_0_SEQUENCE_0,
    ADC_0_SEQUENCE_1,
    ADC_0_SEQUENCE_2,
    ADC_0_SEQUENCE_3,
    
    WATCHDOG_TIMERS_0_1,

    _16_32_BIT_TIMER_0A,
    _16_32_BIT_TIMER_0B,
    _16_32_BIT_TIMER_1A,
    _16_32_BIT_TIMER_1B,
    _16_32_BIT_TIMER_2A,
    _16_32_BIT_TIMER_2B,
    
    ANALOG_COMPARATOR_0,
    ANALOG_COMPARATOR_1,
    
    // 27 RESERVED
    
    SYSTEM_CONTROL = 28,
    
    FLASH__EEPROM_MEMORY_CTRL,

    GPIO_PORT_F,

    // 31-32 RESERVED

    UART2=33,

    SSI1,

    _16_32_BIT_TIMER_3A,
    _16_32_BIT_TIMER_BA,

    I2C1,

    QEI1,

    CAN0,
    CAN1,

    // 41-42 RESERVED

    HIBERNATION_MODULE=43,

    USB,

    PWM_GENERATOR_3,

    uDMA_SOFTWARE,
    uDMA_ERROR,

    ADC1_SEQUENCE_0,
    ADC1_SEQUENCE_1,
    ADC1_SEQUENCE_2,
    ADC1_SEQUENCE_3,

    // 52-56

    SSI2=57,
    SSI3,

    UART3,
    UART4,
    UART5,
    UART6,
    UART7,

    // 64-67 RESERVED

    I2C2=68,
    I2C3,

    _16_32_BIT_TIMER_4A,
    _16_32_BIT_TIMER_4B,

    // 72-91

    _16_32_BIT_TIMER_5A=92,
    _16_32_BIT_TIMER_5B,

    _32_64_BIT_TIMER_0A,
    _32_64_BIT_TIMER_0B,

    _32_64_BIT_TIMER_1A,
    _32_64_BIT_TIMER_1B,
    
    _32_64_BIT_TIMER_2A,
    _32_64_BIT_TIMER_2B,

    _32_64_BIT_TIMER_3A,
    _32_64_BIT_TIMER_3B,
    
    _32_64_BIT_TIMER_4A,
    _32_64_BIT_TIMER_4B,
    
    _32_64_BIT_TIMER_5A,
    _32_64_BIT_TIMER_5B,

    SYSTEM_EXCEPTION,

    // 107-133
    
    PWM_1_GEN_0=134,
    PWM_1_GEN_1,
    PWM_1_GEN_2,
    PWM_1_GEN_3,
    PWM_1_FAULT

}Nvic_IntTypes;

typedef struct 
{
    Nvic_IntTypes intNum;
    uint8 intPriGrp;
    uint8 intPriSubGrp;

}Nvic_CfgType;

#endif   /* INTCTRL_TYPES_H */

/****************************************************************************
 *      END OF FILE: IntCtrl_Types.h
 * **************************************************************************/
