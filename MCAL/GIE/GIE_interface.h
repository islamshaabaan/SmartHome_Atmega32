/*
 * GIE_interface.h
 *
 *  Created on: Aug 12, 2023
 *      Author: First
 */

#ifndef MCAL_GIE_GIE_INTERFACE_H_
#define MCAL_GIE_GIE_INTERFACE_H_

#define SREG_REG		*(	(	volatile u8*	)	0x5F	)

void GIE_voidEnable		(void);
void GIE_voidDisable	(void);

#endif /* MCAL_GIE_GIE_INTERFACE_H_ */
