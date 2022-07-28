/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   TimerTypes.h
 *          \brief
 *
 *          \details
 *
 *
 * ***************************************************************************/

/*****************************************************************************
 * File guard
/*****************************************************************************/

#ifndef TIMER_TYPES_H
#define TIMER_TYPES_H

/*****************************************************************************
 *      INCLUDES
 * ***************************************************************************/
#include "Std_Types.h"

/*****************************************************************************
 *      GLOBAL CONSTANT MACROS
 * ***************************************************************************/
#define GPT_PREDEF_TIMER_1US_16BIT      DISABLE
#define GPT_PREDEF_TIMER_1US_24BIT      DISABLE
#define GPT_PREDEF_TIMER_1US_32BIT      DISABLE
#define GPT_PREDEF_TIMER_100US_32BIT    DISABLE
/*****************************************************************************
 *      GLOBAL FUNCTION MACROS
 * ***************************************************************************/

/*****************************************************************************
 *      GLOBAL DATA TYPES AND STRUCTURES
 * ***************************************************************************/
typedef void (*GptNotification)(void);

typedef enum
{
    _16_32_TIMER_0_A,
    _16_32_TIMER_1_A,
    _16_32_TIMER_2_A,
    _16_32_TIMER_3_A,
    _16_32_TIMER_4_A,
    _16_32_TIMER_5_A,

    _32_64_TIMER_0_A,
    _32_64_TIMER_1_A,
    _32_64_TIMER_2_A,
    _32_64_TIMER_3_A,
    _32_64_TIMER_4_A,
    _32_64_TIMER_5_A,

} Gpt_ChannelType;

typedef uint32 Gpt_ValueType;

typedef enum {
    DISABLE,
    ENABLE
}Gpt_Predefined_Timers;

typedef enum
{
    GPT_MODE_NORMAL,
    GPT_MODE_SLEEP,
} Gpt_ModeType;

typedef enum
{
    
    GPT_CH_MODE_ONESHOT=1,
    GPT_CH_MODE_CONTINOUS
} Gpt_ChannelMode;

typedef struct
{
    Gpt_ChannelType GptChannelId;
    Gpt_ValueType GptChannelTickFrequency;
    Gpt_ValueType GptChannelTickValueMax;
    Gpt_ChannelMode channelMode;
    GptNotification callBackFunc;
} Gpt_ConfigType;

#endif /* TIMER_TYPES_H */

/****************************************************************************
 *      END OF FILE: TimerTypes.h
 * **************************************************************************/