/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   DIO.c
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
#include "Dio.h"
#include "Common_Functions.h"

/*****************************************************************************
 * LOCAL MACROS CONSTANT\FUNCTION
 * **************************************************************************/
#define PORT_NUMBER 6
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

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    uint32 PortBase = Ports_Base_Addresses[PortId];
    uint32 gpioOffsetMask = GPIODATA_OFFSET + ((0xFF) << 2);
    Dio_PortLevelType portLevel = GET_HWREG(PortBase, gpioOffsetMask);
    return portLevel;
}

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

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
    uint32 portBase = Ports_Base_Addresses[PortId];
    uint32 gpioOffsetMask = GPIODATA_OFFSET + ((0xFF) << 2);
    GET_HWREG(portBase, gpioOffsetMask) = Level;
}

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

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    uint8 portIndex = (uint8)ChannelId.port ;
    uint32 portBase = Ports_Base_Addresses[portIndex];

    uint8 pinOffset = (uint8)ChannelId.pin;
    uint8 totalShift =pinOffset +2;

    uint32 gpioOffsetMask =  GPIODATA_OFFSET + (0xFF)<<2 ;
    Dio_LevelType level = (GET_HWREG(portBase, gpioOffsetMask) & (1<< pinOffset))>>pinOffset;

    return level;
}

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

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    uint8 portIndex = (uint8)ChannelId.port ;
    uint32 portBase = Ports_Base_Addresses[portIndex];

    uint8 pinOffset = (uint8)ChannelId.pin;
    uint8 totalShift =pinOffset +2;
    uint32 gpioOffsetMask = GPIODATA_OFFSET + (0xFF)<<2 ;
    uint8 value =   Level << pinOffset;
    GET_HWREG(portBase, gpioOffsetMask) = value;
}

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    Dio_LevelType currentLevel = Dio_ReadChannel(ChannelId);
    if (currentLevel)
    currentLevel = 0;
    else 
    currentLevel = 1;
    Dio_WriteChannel(ChannelId,currentLevel);
    return currentLevel;
}

/****************************************************************************
 *      END OF FILE: FileName.c
 * **************************************************************************/
