/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   IntCtrl.c
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
#include "IntCtrl.h"
#include "Common_Functions.h"

/*****************************************************************************
 * LOCAL MACROS CONSTANT\FUNCTION
 * **************************************************************************/
#define INT_PRI_SYS_XXX   0x4
#define INT_PRI_SYS_XXY   0x5
#define INT_PRI_SYS_XYY   0x6
#define INT_PRI_SYS_YYY   0x7

#define APINT_VECTKEY       0x05FA
#define APINT_VECTKEY_OFFSET 16u
#define PRIGRP_FIELD_OFFSET  8u
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

/****************************************************************************
 * \Syntax          : void IntCrtl_Init (void)
 * \Description     : Initialize Nvic\SCB Module by parsing the Configuration
 *                      into Nvic\SCB registers
 * 
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : void    
 * \Parameter  (out): void
 * \Return value    : void
 * *************************************************************************/


void IntCrtl_Init (void)
{   
   
    uint8 intNum,GrpPri,SubGrpPri;
    uint8 PriRegNum,PriRegOffset,IntPriRegNum,IntPriBitOffset,PriGroupField;
    uint8 EnRegNum,EnRegOffset,IntEnBitOffset;
    uint8 counter;
    /*TODO Configure Grouping\SubGrouping System in APINT register in SCB */
    
    ENABLE_INT_F()
    ENABLE_INT_I()
    
    APINT->R|=APINT_VECTKEY<<APINT_VECTKEY_OFFSET|(NVIC_GROUPING_SYSTEM<<PRIGRP_FIELD_OFFSET);
   
    for (counter=0;counter<ACTIVATED_INT_NUM;counter++)
    {
        intNum = Nvic_Interrupts[counter].intNum;
        GrpPri = Nvic_Interrupts[counter].intPriGrp;
        SubGrpPri = Nvic_Interrupts[counter].intPriSubGrp;

        PriRegNum    = (uint8)(intNum/4);
        PriRegOffset = PriRegNum*4;
        IntPriRegNum = intNum%4;
        IntPriBitOffset = 5*(IntPriRegNum+1)+3*IntPriRegNum;

        /* Setting up grouping field */
			
        #if (NVIC_GROUPING_SYSTEM==INT_PRI_SYS_XXX)
            PriGroupField=GrpPri;
        #elif (NVIC_GROUPING_SYSTEM==INT_PRI_SYS_XXY)
            PriGroupField=(GrpPri<<1&0x6)|(SubGrpPri&0x1);
        #elif (NVIC_GROUPING_SYSTEM==INT_PRI_SYS_XYY)
            PriGroupField=(GrpPri<<2&0x4)|(SubGrpPri&0x3);            
        #elif(NVIC_GROUPING_SYSTEM==INT_PRI_SYS_YYY)
            PriGroupField=SubGrpPri;
        #else 
            #error
        #endif

        GET_HWREG(INT_PRIORITY_BASE_ADDRESS,PriRegOffset) |= PriGroupField << IntPriBitOffset;
    
        /*TODO : Enable\Disable based on user configurations in NVIC_ENx and SCB_Sys Registers*/
        EnRegNum = (uint8)(intNum/32);
        EnRegOffset = EnRegNum*4;
        IntEnBitOffset = intNum%32;

        GET_HWREG(INT_EN_BASE_ADDRESS,EnRegOffset) |= (1<<IntEnBitOffset);
    }

}

 
/****************************************************************************
 *      END OF FILE: IntCtrl.c
 * **************************************************************************/
 
