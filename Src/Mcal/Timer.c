/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   Timer.c
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
#include "Timer.h"
#include "Common_Functions.h"
/*****************************************************************************
 * LOCAL MACROS CONSTANT\FUNCTION
 * **************************************************************************/
/****************************************************************************
 * LOCAL DATA
 * **************************************************************************/
GptNotification callBack[TimerBaseAddressesNumber]={};

static TimerBaseAddresses[TimerBaseAddressesNumber]=
{
    _16_32_BIT_TIMER_0_BASE_ADDRESS,
    _16_32_BIT_TIMER_1_BASE_ADDRESS,
    _16_32_BIT_TIMER_2_BASE_ADDRESS,
    _16_32_BIT_TIMER_3_BASE_ADDRESS,
    _16_32_BIT_TIMER_4_BASE_ADDRESS,
    _16_32_BIT_TIMER_5_BASE_ADDRESS,

    _32_64_BIT_TIMER_0_BASE_ADDRESS,
    _32_64_BIT_TIMER_1_BASE_ADDRESS,
    _32_64_BIT_TIMER_2_BASE_ADDRESS,
    _32_64_BIT_TIMER_3_BASE_ADDRESS,
    _32_64_BIT_TIMER_4_BASE_ADDRESS,
    _32_64_BIT_TIMER_5_BASE_ADDRESS,

};
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
void    Gpt_StopTimer              (Gpt_ChannelType channel)
{
    uint32 TimerBaseAddress = TimerBaseAddresses[channel];
    CLR_BIT(GET_HWREG(TimerBaseAddress,GPTMCTL_OFFSET),0);
    SET_BIT(GET_HWREG(TimerBaseAddress,GPTMICR_OFFSET),0);

}

void    Gpt_StartTimer              (Gpt_ChannelType channel, Gpt_ValueType value)
{
    uint32 TimerBaseAddress = TimerBaseAddresses[channel];
    
    GET_HWREG(TimerBaseAddress, GPTMTAILR_OFFSET)=value;
    SET_BIT(GET_HWREG(TimerBaseAddress,GPTMICR_OFFSET),0);
    SET_BIT(GET_HWREG(TimerBaseAddress,GPTMCTL_OFFSET),0);

}

void    Gpt_DisableNotification    (Gpt_ChannelType channel)
{
    uint32 TimerBaseAddress = TimerBaseAddresses[channel];

    CLR_BIT(GET_HWREG(TimerBaseAddress,GPTMIMR_OFFSET),0);
}
void    Gpt_EnableNotification     (Gpt_ChannelType channel)
{
    uint32 TimerBaseAddress = TimerBaseAddresses[channel];
    
    SET_BIT(GET_HWREG(TimerBaseAddress,GPTMICR_OFFSET),0);
    SET_BIT(GET_HWREG(TimerBaseAddress,GPTMIMR_OFFSET),0);
}

Gpt_ValueType Gpt_GetRemainingTime             (Gpt_ChannelType channel)
{
    uint32 baseAddress = TimerBaseAddresses[channel];
    return GET_HWREG(baseAddress,GPTMTAILR_OFFSET) - GET_HWREG(baseAddress,GPTMTAV_OFFSET);
}
Gpt_ValueType Gpt_GetTimeElapsed               (Gpt_ChannelType channel)
{
    uint32 baseAddress = TimerBaseAddresses[channel];
    return GET_HWREG(baseAddress,GPTMTAV_OFFSET);

}

void    Gpt_Init                   (const Gpt_ConfigType *ConfigPtr)
{   
    

    for(int i =0 ; i<NUMBER_OF_TIMERS_INIT ; i++)
    {
        Gpt_ChannelType channel = ConfigPtr[i].GptChannelId;;
        Gpt_ValueType tickFreq = ConfigPtr[i].GptChannelTickFrequency;
        Gpt_ValueType tickMaxValue = ConfigPtr[i].GptChannelTickValueMax ;
        Gpt_ChannelMode mode = ConfigPtr[i].channelMode;
        GptNotification handlerFunc = ConfigPtr[i].callBackFunc;
        SET_BIT(GET_HWREG(SYS_CTRL_BASE_ADDRESS,RCGCTIMER_OFFSET),channel%6);

        if(handlerFunc != NULL)
        {
            Gpt_EnableNotification(channel);

            callBack[channel] = handlerFunc;
        }
        uint32 TimerBaseAddress = TimerBaseAddresses[channel];

        Gpt_StopTimer(channel);
        GET_HWREG(TimerBaseAddress,GPTMCFG_OFFSET)=0x0;
        GET_HWREG(TimerBaseAddress,GPTMTAMR_OFFSET)|=mode;
        CLR_BIT (GET_HWREG(TimerBaseAddress,GPTMTAMR_OFFSET),4);  // direction countdown
        Gpt_StartTimer(_16_32_TIMER_0_A,tickFreq);
    }
    
  /*TODO STOP TIMER*/

  
 
  /*TODO LOAD INITIAL VALUE FOR TIMER IN GPTMTAILR*/
  /*TODO LOAD INITIAL VALUE FOR TIMER IN GPTMTBILR*/
}

void TIMER0A_Handler(void)
{       
    GptNotification TimerA0_Callback= callBack[_16_32_TIMER_0_A];
    if(TimerA0_Callback != NULL)
    TimerA0_Callback();

}

/****************************************************************************
 *      END OF FILE: Timer.c
 * **************************************************************************/
 
