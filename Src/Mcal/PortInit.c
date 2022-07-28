/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   PortInit.c
 *          \brief
 *
 *          \details
 *
 *
 * ***************************************************************************/

/*****************************************************************************
 *      INCLUDES
 * **************************************************************************/

#include "Std_Types.h"
#include "Mcu_Hw.h"
#include "Common_Functions.h"
#include "PortInit.h"
#include "Dio.h"
/*****************************************************************************
 * LOCAL MACROS CONSTANT\FUNCTION
 * **************************************************************************/
#define PORT_NUMBER     6
#define PORT_INTERRUPTS 6
/****************************************************************************
 * LOCAL DATA
 * **************************************************************************/
static const uint32 Ports_Base_Addresses[PORT_NUMBER] = {
    GPIO_Port_A_AHB,
    GPIO_Port_B_AHB,
    GPIO_Port_C_AHB,
    GPIO_Port_D_AHB,
    GPIO_Port_E_AHB,
    GPIO_Port_F_AHB};
static portInterruptCallBack handlers[PORT_INTERRUPTS]={};
/*****************************************************************************
 * GLOABL DATA
 * ***************************************************************************/

/*****************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 * ***************************************************************************/

/*****************************************************************************
 * LOCAL FUNCTIONS
 * ***************************************************************************/

/*****************************************************************************
 * GLOABL FUNCTIONS
 * ***************************************************************************/

/*****************************************************************************
 * LOCAL MACROS CONSTANT\FUNCTION
 * **************************************************************************/
#define GPIOLOCK_UNLOCK_SEQ 0x4C4F434B
/****************************************************************************
 * \Syntax          : Std_ReturnType FunctionName (AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName     Parameter Description
 * \Parameter  (out):None
 * \Return value    : Std_ReturnType E_OK
 *                                   E_NOT_OK
 * *************************************************************************/

void enable_Port_AHB(Port_Number PortNo)
{
    SET_BIT(GET_HWREG(SYS_CTRL_BASE_ADDRESS, GPIO_HBCTL_OFFSET), PortNo);
}

void enable_Port_clock(Port_Number PortNo)
{
    SET_BIT(GET_HWREG(SYS_CTRL_BASE_ADDRESS, RCGCGPIO_OFFSET), PortNo);
}

void set_Port_Pin_Dir(Port_PinType Port_Pin, Port_PinDirectionType dir)
{
    Port_Number portindex = Port_Pin.portNum;
    Pin_Number pin = Port_Pin.pinNum;
    uint32 PortBase = Ports_Base_Addresses[portindex];

    if (dir == INPUT || dir == OUTPUT)
        if(dir == OUTPUT )
        SET_BIT(GET_HWREG(PortBase, GPIODIR_OFFSET), pin);
        else
        CLR_BIT(GET_HWREG(PortBase, GPIODIR_OFFSET), pin);

}

uint8 Check_Protected_Pin(Port_PinType Port_Pin)
{
    Port_Number port = Port_Pin.portNum;
    Pin_Number pin = Port_Pin.pinNum;
    uint8 protected;
    switch (port)
    {

    case PORTC:
        if (pin >= 0 && pin < 4)
        protected
        = 1;
        break;

    case PORTD:
        if (pin == 7)
        protected
        = 1;
        break;

    case PORTF:
        if (pin == 0)
        protected
        = 1;
        break;
    default:
        break;
    }
    return protected;
}

void set_Pin_Mode(Port_PinType Port_Pin, Port_PinModeType Pin_Mode)
{
    Port_Number port = Port_Pin.portNum;
    Pin_Number pin = Port_Pin.pinNum;
    uint32 PortBase = Ports_Base_Addresses[port];

    uint8 protected_pin = Check_Protected_Pin(Port_Pin);
    if (protected_pin)
    {
        if (GET_HWREG(PortBase, GPIOLOCK_OFFSET) == 1)
            GET_HWREG(PortBase, GPIOLOCK_OFFSET) |= GPIOLOCK_UNLOCK_SEQ;
        SET_BIT(GET_HWREG(PortBase, GPIOCR_OFFSET), pin);
    }

    if (Pin_Mode == DIO)
    {
        CLR_BIT(GET_HWREG(PortBase, GPIOAFSEL_OFFSET), pin);
        SET_BIT(GET_HWREG(PortBase, GPIODEN_OFFSET), pin);
    }
    else if (Pin_Mode == ANALOGUE)
    {
        CLR_BIT(GET_HWREG(PortBase, GPIOAFSEL_OFFSET), pin);
        CLR_BIT(GET_HWREG(PortBase, GPIODEN_OFFSET), pin);
        SET_BIT(GET_HWREG(PortBase, GPIOAMSEL_OFFSET), pin);
    }
    else
    {
        SET_BIT(GET_HWREG(PortBase, GPIOAFSEL_OFFSET), pin);
        SET_BIT(GET_HWREG(PortBase, GPIODEN_OFFSET), pin);
        GET_HWREG(PortBase, GPIOPCTL_OFFSET) |= (Pin_Mode << pin * 4);
    }
}

void set_Internal_Attach(Port_PinType Port_Pin, Port_PinInternalAttachType attachType)
{
    Port_Number portindex = Port_Pin.portNum;
    Pin_Number pin = Port_Pin.pinNum;
    uint32 PortBase = Ports_Base_Addresses[portindex];
    switch (attachType)
    {
    case PULL_UP:
        SET_BIT(GET_HWREG(PortBase, GPIOPUR_OFFSET), pin);
        break;
    case PULL_DOWN:
        SET_BIT(GET_HWREG(PortBase, GPIOPDR_OFFSET), pin);
        break;
    case OPEN_DRAIN:
        SET_BIT(GET_HWREG(PortBase, GPIOODR_OFFSET), pin);
        break;
    default:
        break;
    }
}

void set_current_output(Port_PinType Port_Pin, Port_PinOutputCurrentType currentType)
{
    Port_Number portindex = Port_Pin.portNum;
    Pin_Number pin = Port_Pin.pinNum;
    uint32 PortBase = Ports_Base_Addresses[portindex];
    switch (currentType)
    {
    case _2_mA:
        SET_BIT(GET_HWREG(PortBase, GPIODR2R_OFFSET), pin);
        break;
    case _4_mA:
        SET_BIT(GET_HWREG(PortBase, GPIODR4R_OFFSET), pin);
        break;
    case _8_mA:
        SET_BIT(GET_HWREG(PortBase, GPIODR8R_OFFSET), pin);
        break;
    default:
        break;
    }
}

void set_Interrupt_Type(Port_PinType Port_Pin,Port_PinInterruptType type)
{
    Port_Number portindex = Port_Pin.portNum;
    Pin_Number pin = Port_Pin.pinNum;
    uint32 PortBase = Ports_Base_Addresses[portindex];
    
    CLR_BIT(GET_HWREG(PortBase,GPIOIM_OFFSET),pin);

    switch (type)
    {
    case PORT_DISABLE:
        break;
    case LEVEL_LOW:
        SET_BIT(GET_HWREG(PortBase,GPIOIS_OFFSET),pin);
        CLR_BIT(GET_HWREG(PortBase,GPIOIEV_OFFSET),pin);
        SET_BIT(GET_HWREG(PortBase,GPIOIM_OFFSET),pin);

        break;
    case LEVEL_HIGH:
        SET_BIT(GET_HWREG(PortBase,GPIOIS_OFFSET),pin);
        SET_BIT(GET_HWREG(PortBase,GPIOIEV_OFFSET),pin);
        SET_BIT(GET_HWREG(PortBase,GPIOIM_OFFSET),pin);

        break;
    case EDGE_LOW:
        CLR_BIT(GET_HWREG(PortBase,GPIOIS_OFFSET),pin);
        CLR_BIT(GET_HWREG(PortBase,GPIOIBE_OFFSET),pin);
        CLR_BIT(GET_HWREG(PortBase,GPIOIEV_OFFSET),pin);
        SET_BIT(GET_HWREG(PortBase,GPIOICR_OFFSET),pin);
        SET_BIT(GET_HWREG(PortBase,GPIOIM_OFFSET),pin);

        break;
    case EGDE_HIGH:
        CLR_BIT(GET_HWREG(PortBase,GPIOIS_OFFSET),pin);
        CLR_BIT(GET_HWREG(PortBase,GPIOIBE_OFFSET),pin);
        SET_BIT(GET_HWREG(PortBase,GPIOIEV_OFFSET),pin);
        SET_BIT(GET_HWREG(PortBase,GPIOICR_OFFSET),pin);
        SET_BIT(GET_HWREG(PortBase,GPIOIM_OFFSET),pin);

        break;
    case BOTH:
        CLR_BIT(GET_HWREG(PortBase,GPIOIS_OFFSET),pin);
        SET_BIT(GET_HWREG(PortBase,GPIOIBE_OFFSET),pin);
        SET_BIT(GET_HWREG(PortBase,GPIOICR_OFFSET),pin);
        SET_BIT(GET_HWREG(PortBase,GPIOIM_OFFSET),pin);

        break;
    default:
        break;
    }

}

void init_Port(const Port_CfgType *config)
{

    for (int i = 0; i < CHANNELS_INITIALEZED_NUMBER; i++)
    {
        Port_PinType Port_Pin = config[i].portPin;
        Port_PinLevelType initialLevel = config[i].portPinLevel;
        Port_PinDirectionType dir = config[i].portPinDir;
        Port_PinModeType mode = config[i].portPinMode;
        Port_PinInternalAttachType attachType = config[i].portPinInternalAttach;
        Port_PinOutputCurrentType OutCurrent = config[i].portPinCurrent;
        Port_PinInterruptType interrupt = config[i].portPinInterruptType;

        Port_Number portIndex = Port_Pin.portNum;
        Pin_Number pin = Port_Pin.pinNum;

        enable_Port_AHB(portIndex);
        enable_Port_clock(portIndex);

        set_Port_Pin_Dir(Port_Pin, dir);
        set_Pin_Mode(Port_Pin, mode);
        set_current_output(Port_Pin, OutCurrent);
        set_Internal_Attach(Port_Pin, attachType);
        set_Interrupt_Type(Port_Pin,interrupt);
        Dio_ChannelType channel = {portIndex ,pin};
        Dio_WriteChannel(channel, initialLevel);
    }

    for ( i=0 ;i<PORT_INTERRUPTS_INITIALIZED; i++)
    {
        Port_Number port = callBacks[i].port;
        portInterruptCallBack callback = callBacks[i].callback;
        handlers[port]= callback;
    }
}


void GPIOA_Handler()
{
portInterruptCallBack GPIOA_callBack= handlers[PORTA];
    uint32 PortBase = Ports_Base_Addresses[PORTA];
    uint8 rawInterrupt =GET_HWREG(PortBase,GPIORIS_OFFSET);
    Port_PinLevelType bitLevel=0;
    int i=0;
    for(i=0 ; i<8;i++)
      {
        bitLevel=GET_BIT(GET_HWREG(PortBase,GPIORIS_OFFSET),i);
        if(bitLevel)
        break;
      } 
    if(GPIOA_callBack != NULL)
        GPIOA_callBack(i);
}

void GPIOB_Handler()
{
portInterruptCallBack GPIOB_callBack= handlers[PORTB];
    uint32 PortBase = Ports_Base_Addresses[PORTB];
    uint8 rawInterrupt =GET_HWREG(PortBase,GPIORIS_OFFSET);
    Port_PinLevelType bitLevel=0;
    int i=0;
    for(i =0; i<8;i++)
      {
        bitLevel=GET_BIT(GET_HWREG(PortBase,GPIORIS_OFFSET),i);
        if(bitLevel)
        break;
      } 
    if(GPIOB_callBack != NULL)
    GPIOB_callBack(i);
    
}
void GPIOC_Handler()
{
    portInterruptCallBack GPIOC_callBack= handlers[PORTC];
    uint32 PortBase = Ports_Base_Addresses[PORTC];
    uint8 rawInterrupt =GET_HWREG(PortBase,GPIORIS_OFFSET);
    Port_PinLevelType bitLevel=0;
    int i=0;
    for( i =0; i<8;i++)
      {
        bitLevel=GET_BIT(GET_HWREG(PortBase,GPIORIS_OFFSET),i);
        if(bitLevel)
        break;
      } 
    if(GPIOC_callBack != NULL)
    GPIOC_callBack(i);

}
void GPIOD_Handler()
{
    portInterruptCallBack GPIOD_callBack= handlers[PORTD];
    uint32 PortBase = Ports_Base_Addresses[PORTD];
    uint8 rawInterrupt =GET_HWREG(PortBase,GPIORIS_OFFSET);
    Port_PinLevelType bitLevel=0;
    int i=0;
    for( i =0; i<8;i++)
      {
        bitLevel=GET_BIT(GET_HWREG(PortBase,GPIORIS_OFFSET),i);
        if(bitLevel)
        break;
      } 
    if(GPIOD_callBack != NULL)
    GPIOD_callBack(i);


}
void GPIOE_Handler()
{
    portInterruptCallBack GPIOE_callBack= handlers[PORTE];
    uint32 PortBase = Ports_Base_Addresses[PORTE];
    uint8 rawInterrupt =GET_HWREG(PortBase,GPIORIS_OFFSET);
    Port_PinLevelType bitLevel=0;
    int i=0;
    for(i =0; i<8;i++)
      {
        bitLevel=GET_BIT(GET_HWREG(PortBase,GPIORIS_OFFSET),i);
        if(bitLevel)
        break;
      } 
    if(GPIOE_callBack != NULL)
    GPIOE_callBack(i);

}
void GPIOF_Handler()
{
   portInterruptCallBack GPIOF_callBack= handlers[PORTF];
    uint32 PortBase = Ports_Base_Addresses[PORTF];
    uint8 rawInterrupt =GET_HWREG(PortBase,GPIORIS_OFFSET);
    Port_PinLevelType bitLevel=0;
    int i=0;
    for( i=0; i<8;i++)
      {
        bitLevel=GET_BIT(GET_HWREG(PortBase,GPIORIS_OFFSET),i);
        if(bitLevel)
        break;
      } 
    if(GPIOF_callBack != NULL)
    GPIOF_callBack(i);

}

/****************************************************************************
 *      END OF FILE: PortInit.c
 * **************************************************************************/
