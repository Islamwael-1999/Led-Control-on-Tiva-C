/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   FileName.c
 *          \brief
 *
 *          \details
 *
 *
 * ***************************************************************************/

/*****************************************************************************
 *      INCLUDES
 * **************************************************************************/
#include "pwm.h"
#include "IntCtrl.h"
#include "Timer.h"
#include "PortInit.h"
#include "Dio.h"

/*****************************************************************************
 * LOCAL MACROS CONSTANT\FUNCTION
 * **************************************************************************/

/****************************************************************************
 * LOCAL DATA
 * **************************************************************************/
uint8 OnOffFlag = 0;
uint32 _1_second_ticks = 0xF42400;
/*****************************************************************************
 * GLOABL DATA
 * ***************************************************************************/
extern uint32 OnNumber;
extern uint32 OffNumber;
extern uint32 mode;
extern uint32 timer_0_Flag;

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

void init_Configuartion()
{
    IntCrtl_Init();
    init_Port(Ports_init);
    Gpt_Init(TimerConfig);
}

void RunPwm()
{
    Dio_ChannelType channel = {DIO_PORTF, PIN_2};
    Dio_ChannelType Sw1 = {DIO_PORTF, PIN_0};
    Dio_ChannelType Sw2 = {PORTF, PIN4};
    uint8 val; 
    Dio_LevelType sw1 = Dio_ReadChannel(Sw1);
    if (sw1 == DIO_HIGH)
    {
        mode++;
        mode %= 3;
        Dio_WriteChannel(Sw1, DIO_LOW);
        if (mode != 0)
            Gpt_StopTimer(_16_32_BIT_TIMER_0A);
        else 
            timer_0_Flag =1;
    }
    if (mode == 0)
    {
        if (timer_0_Flag == 1)
        {
            if (OnOffFlag == 1)
            {
                OnOffFlag = 0;
                Dio_WriteChannel(channel, DIO_HIGH);
                // val = OnNumber;
                Gpt_StartTimer(_16_32_TIMER_0_A, OnNumber*_1_second_ticks);
            }
            else
            {
                OnOffFlag = 1;
                Dio_WriteChannel(channel, DIO_LOW);
                // val = OnNumber;
                Gpt_StartTimer(_16_32_TIMER_0_A, OffNumber*_1_second_ticks);
            }
            timer_0_Flag = 0;
        }
    }
    else if (mode == 1)
    {
        Dio_LevelType sw2 = Dio_ReadChannel(Sw2);
        if (sw2 == DIO_HIGH)
            OnNumber = (OnNumber + 1) % 50;
        Dio_WriteChannel(Sw2, DIO_LOW);
    }
    else if (mode == 2)
    {
        Dio_LevelType sw2 = Dio_ReadChannel(Sw2);
        if (sw2 == DIO_HIGH)
            OffNumber = (OffNumber + 1) % 50;
        Dio_WriteChannel(Sw2, DIO_LOW);
    }
}
/****************************************************************************
 *      END OF FILE: FileName.c
 * **************************************************************************/
