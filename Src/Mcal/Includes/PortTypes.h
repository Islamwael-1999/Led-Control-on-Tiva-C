/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   FileName.h
 *          \brief
 *
 *          \details
 *
 *
 * ***************************************************************************/

/*****************************************************************************
 * File guard
/*****************************************************************************/

#ifndef PORT_TYPES_H
#define PORT_TYPES_H

/*****************************************************************************
 *      INCLUDES
 * ***************************************************************************/

/*****************************************************************************
 *      GLOBAL CONSTANT MACROS
 * ***************************************************************************/

/*****************************************************************************
 *      GLOBAL FUNCTION MACROS
 * ***************************************************************************/

/*****************************************************************************
 *      GLOBAL DATA TYPES AND STRUCTURES
 * ***************************************************************************/

typedef enum{
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF
}Port_Number;

typedef enum {

    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7

}Pin_Number;

typedef void (* portInterruptCallBack)(Pin_Number pin);


typedef struct 
{
    Port_Number portNum;
    Pin_Number pinNum;

}Port_PinType;

typedef enum
{
    INPUT,
    OUTPUT,
    Ignore
} Port_PinDirectionType;

typedef enum
{   DIO=0,
    GPIOPCTL_BIT_FIELD_ENCODING_1,
    GPIOPCTL_BIT_FIELD_ENCODING_2,
    GPIOPCTL_BIT_FIELD_ENCODING_3,
    GPIOPCTL_BIT_FIELD_ENCODING_4,
    GPIOPCTL_BIT_FIELD_ENCODING_5,
    GPIOPCTL_BIT_FIELD_ENCODING_6,
    GPIOPCTL_BIT_FIELD_ENCODING_7,
    GPIOPCTL_BIT_FIELD_ENCODING_8,
    GPIOPCTL_BIT_FIELD_ENCODING_9,
    GPIOPCTL_BIT_FIELD_ENCODING_10,
    GPIOPCTL_BIT_FIELD_ENCODING_11,
    GPIOPCTL_BIT_FIELD_ENCODING_12,
    GPIOPCTL_BIT_FIELD_ENCODING_13,
    GPIOPCTL_BIT_FIELD_ENCODING_14,
    GPIOPCTL_BIT_FIELD_ENCODING_15,
    ANALOGUE

} Port_PinModeType;
typedef enum
{
    PULL_UP,
    PULL_DOWN,
    OPEN_DRAIN
} Port_PinInternalAttachType;

typedef enum
{
    None,
    _2_mA,
    _4_mA,
    _8_mA

} Port_PinOutputCurrentType;

typedef enum{
    LOW,
    HIGH
}Port_PinLevelType;

typedef enum
{
    PORT_DISABLE,
    LEVEL_LOW,
    LEVEL_HIGH,
    EDGE_LOW,
    EGDE_HIGH,
    BOTH
}Port_PinInterruptType;

typedef struct
{
    Port_PinType portPin;
    Port_PinLevelType portPinLevel;
    Port_PinDirectionType portPinDir;
    Port_PinModeType portPinMode;
    Port_PinInternalAttachType portPinInternalAttach;
    Port_PinOutputCurrentType portPinCurrent;
    Port_PinInterruptType portPinInterruptType;

} Port_CfgType;

typedef struct 
{
    Port_Number port;
    portInterruptCallBack callback;
}Port_Interrupts;

#endif /* HEADER_NAME_H */

/****************************************************************************
 *      END OF FILE: FileName.h
 * **************************************************************************/