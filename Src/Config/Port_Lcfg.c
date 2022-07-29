/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   Port_Lcfg.c
 *          \brief
 * 
 *          \details
 *
 * 
 * ***************************************************************************/

/*****************************************************************************
 *      INCLUDES
 * **************************************************************************/
#include "PortInit.h"

// #include "Std_Types.h"
// #include "Mcu_Hw.h"

/*****************************************************************************
 * LOCAL MACROS CONSTANT\FUNCTION
 * **************************************************************************/

/****************************************************************************
 * LOCAL DATA
 * **************************************************************************/

/*****************************************************************************
 * GLOABL DATA
 * ***************************************************************************/
uint32 OnNumber=1;
uint32 OffNumber=1;
uint32 mode=0;
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
void callback_PortF(Pin_Number pin)
{
    if(pin == 0)
    {
        if(mode ==0)
        {
            
        }
        else if (mode ==1)
        {
            OnNumber ++;
        }
        else if (mode == 2)
        {
            OffNumber ++;
        }
    }
    else if (pin == 4) 
    {
        mode ++;
        mode %=3;
    }
}



const Port_CfgType  Ports_init[CHANNELS_INITIALEZED_NUMBER]=
{   /*Port_PinType   , Level     DIR                MODE               Internal Attach    Current    */
    {{PORTF,PIN0},      LOW,   INPUT,              DIO,                  PULL_DOWN  ,        _2_mA , EDGE_LOW},
    {{PORTF,PIN4},      LOW,    INPUT,             DIO    ,              PULL_DOWN ,         _4_mA , EDGE_LOW},
    {{PORTF,PIN2},      LOW,    OUTPUT,            DIO    ,              PULL_DOWN ,         _2_mA , PORT_DISABLE},
    {{PORTF,PIN3},      LOW,    OUTPUT,            DIO    ,              PULL_DOWN ,         _2_mA , PORT_DISABLE}


};

const Port_Interrupts callBacks[PORT_INTERRUPTS_INITIALIZED]=
{
    {PORTF, &callback_PortF}
};


/****************************************************************************
 *      END OF FILE: Port_Lcfg.c
 * **************************************************************************/
 
