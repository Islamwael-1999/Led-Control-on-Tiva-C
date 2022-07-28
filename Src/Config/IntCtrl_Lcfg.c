/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   InCtrl_Lcfg.c
 *          \brief
 * 
 *          \details
 *
 * 
 * ***************************************************************************/

/*****************************************************************************
 *      INCLUDES
 * **************************************************************************/
#include "IntCtrl.h"
/*****************************************************************************
 * LOCAL MACROS CONSTANT\FUNCTION
 * **************************************************************************/

/****************************************************************************
 * LOCAL DATA
 * **************************************************************************/

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

const Nvic_CfgType  Nvic_Interrupts[ACTIVATED_INT_NUM]=
{   // Interupt Type/Number, Group Priority,  SubGroup Priority
    {   GPIO_PORT_F ,              1,                  0},
    {   _16_32_BIT_TIMER_0A,       2,                  0}
    
};
/****************************************************************************
 *      END OF FILE: InCtrl_Lcfg.c
 * **************************************************************************/
 