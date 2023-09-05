/*
 * LED_program.c
 *
 *  Created on: Aug 3, 2023
 *      Author: Islam Shaaban
 */

#include "..\..\LIB\STD_TYPES.h"
#include "..\..\LIB\BIT_MACROS.h"

#include "..\..\MCAL\DIO\DIO_interface.h"

#include "LED_interface.h"

void LED_voidInit(LED_t * ptrLED){
	DIO_voidSetupPinDirection( ptrLED->Port,ptrLED->Pin,DIO_OUTPUT);

	switch( ptrLED -> ActiveState){
	case LED_ACTIVE_HIGH:
		DIO_voidSetPinValue(ptrLED->Port, ptrLED->Pin, DIO_LOW);
		break;
	case LED_ACTIVE_LOW:
		DIO_voidSetPinValue(ptrLED->Port, ptrLED->Pin, DIO_HIGH);
		break;

	}
}
void LED_voidON(LED_t * ptrLED){
	switch( ptrLED -> ActiveState){
	case LED_ACTIVE_HIGH:
		DIO_voidSetPinValue(ptrLED -> Port, ptrLED -> Pin, DIO_HIGH);
		break;
	case LED_ACTIVE_LOW:
		DIO_voidSetPinValue(ptrLED -> Port, ptrLED -> Pin, DIO_LOW);
		break;
	}

}
void LED_voidOFF(LED_t * ptrLED){
	switch( ptrLED -> ActiveState){
	case LED_ACTIVE_HIGH:
		DIO_voidSetPinValue(ptrLED -> Port, ptrLED -> Pin, DIO_LOW);
		break;
	case LED_ACTIVE_LOW:
		DIO_voidSetPinValue(ptrLED -> Port, ptrLED -> Pin, DIO_HIGH);
		break;


	}
}

