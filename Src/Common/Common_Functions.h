/*****************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------*/
/**         \file   Common_Functions.h
 *          \brief  This header file contains basic functions such as bit operations   
 *               
 *          \details
 *
 * 
 * ***************************************************************************/

/*****************************************************************************
 * File guard 
/*****************************************************************************/


#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

/*****************************************************************************
 *      INCLUDES
 * ***************************************************************************/

/*****************************************************************************
 *      GLOBAL CONSTANT MACROS
 * ***************************************************************************/

/*****************************************************************************
 *      GLOBAL FUNCTION MACROS
 * ***************************************************************************/

#define SET_BIT(VAR,BITNO) (VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO) (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO) (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 0x01)

#define GET_HWREG(BASE_ADDR,REG_OFFSET)     *((volatile uint32*)(BASE_ADDR+REG_OFFSET))
/*****************************************************************************
 *      GLOBAL DATA TYPES AND STRUCTURES
 * ***************************************************************************/

 
#endif   /* HEADER_NAME_H */

/****************************************************************************
 *      END OF FILE: FileName.h
 * **************************************************************************/