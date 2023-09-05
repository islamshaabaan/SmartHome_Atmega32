/*
 * GIE_program.c
 *
 *  Created on: Aug 12, 2023
 *      Author: First
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MACROS.h"



#include "GIE_interface.h"


void GIE_voidEnable		(void)
{
	SET_BIT(SREG_REG , 7) ;
}
void GIE_voidDisable	(void)
{
	CLR_BIT(SREG_REG , 7) ;
}
