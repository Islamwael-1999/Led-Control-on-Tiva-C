/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   Timer.h
 *          \brief
 *
 *          \details
 *
 *
 * ***************************************************************************/

/*****************************************************************************
 * File guard
/*****************************************************************************/

#ifndef TIMER_H
#define TIMER_H

/*****************************************************************************
 *      INCLUDES
 * ***************************************************************************/
#include "Std_Types.h"
#include "TimerTypes.h"
#include "Timer_Cfg.h"

/*****************************************************************************
 *      GLOBAL CONSTANT MACROS
 * ***************************************************************************/
extern const Gpt_ConfigType TimerConfig[NUMBER_OF_TIMERS_INIT];
/*****************************************************************************
 *      GLOBAL FUNCTION MACROS
 * ***************************************************************************/

/*****************************************************************************
 *      GLOBAL DATA TYPES AND STRUCTURES
 * ***************************************************************************/

/*****************************************************************************
 * Function Prototypes
 * ***************************************************************************/
void                Gpt_Init                   (const Gpt_ConfigType *ConfigPtr);
void                Gpt_DisableNotification    (Gpt_ChannelType channel);
void                Gpt_EnableNotification     (Gpt_ChannelType channel);
void                Gpt_StartTimer             (Gpt_ChannelType channel, Gpt_ValueType value);
void                Gpt_StopTimer              (Gpt_ChannelType channel);
void                Gpt_NotificationFn         (void);
Gpt_ValueType Gpt_GetRemainingTime             (Gpt_ChannelType channel);
Gpt_ValueType Gpt_GetTimeElapsed               (Gpt_ChannelType channel);

#endif /* TIMER_INIT_H */

/****************************************************************************
 *      END OF FILE: Timer.h
 * **************************************************************************/