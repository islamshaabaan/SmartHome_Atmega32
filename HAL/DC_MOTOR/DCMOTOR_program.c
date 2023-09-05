/*
 * DCMOTOR_program.c
 *
 *  Created on: Aug 11, 2023
 *      Author: Islam Shaaban
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MACROS.h"
#define F_CPU 8000000UL
#include <util/delay.h>
/*MCAL*/
#include "../../MCAL/DIO/DIO_interface.h"

#include "DCMOTOR_interface.h"

void DCMOTOR_voidInit(){
	DIO_voidSetupPinDirection(DCMOTOR_PORT,DCMOTOR_HB_PIN0,DIO_OUTPUT );
	DIO_voidSetupPinDirection(DCMOTOR_PORT,DCMOTOR_HB_PIN1,DIO_OUTPUT );
}


void DCMOTOR_voidCWRotate(){
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN0,DIO_HIGH );
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN1,DIO_LOW );

}
void DCMOTOR_voidCCWRotate(){
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN0,DIO_LOW );
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN1,DIO_HIGH );

}
void DCMOTOR_voidStop(){
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN0,DIO_LOW );
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN1,DIO_LOW );

}

/*
// H-bridge
	DIO_voidSetupPinDirection(DIO_PORTD,DIO_PIN0,DIO_OUTPUT );
	DIO_voidSetupPinDirection(DIO_PORTD,DIO_PIN1,DIO_OUTPUT );
	while(1){
		DIO_voidSetPinValue(DIO_PORTD,DIO_PIN0,DIO_HIGH );
		DIO_voidSetPinValue(DIO_PORTD,DIO_PIN1,DIO_LOW );
		_delay_ms(1000);
		DIO_voidSetPinValue(DIO_PORTD,DIO_PIN0,DIO_LOW );
		DIO_voidSetPinValue(DIO_PORTD,DIO_PIN1,DIO_HIGH );
		_delay_ms(1000);



	}*/

/*
//Relay with motors

DIO_voidSetupPinDirection(DIO_PORTA,DIO_PIN0,DIO_OUTPUT );
DIO_voidSetupPinDirection(DIO_PORTA,DIO_PIN1,DIO_OUTPUT );
DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,DIO_LOW );
DIO_voidSetPinValue(DIO_PORTA,DIO_PIN1,DIO_LOW );
while(1){
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,DIO_HIGH );
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN1,DIO_LOW );
		_delay_ms(3000);
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,DIO_LOW );
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN1,DIO_LOW );
		_delay_ms(2000);
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,DIO_LOW );
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN1	,DIO_HIGH );
		_delay_ms(3000);


}

*/

/*
// Switch only, or switch[DIPSW_8 with Opto coupler [PC817]
	DIO_voidSetupPinDirection(DIO_PORTD,DIO_PIN0,DIO_OUTPUT );

	// input and pull up
	DIO_voidSetupPinDirection(DIO_PORTD,DIO_PIN1,DIO_INPUT );
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN1,DIO_HIGH );
	u8 Local_GetPressed;
	while(1){
		Local_GetPressed = DIO_u8GetPinValue(DIO_PORTD,DIO_PIN1);
		// for debouncing

		_delay_ms(10);
		if(Local_GetPressed==0){

			DIO_voidSetPinValue(DIO_PORTD,DIO_PIN0,DIO_LOW );

		}else{
			DIO_voidSetPinValue(DIO_PORTD,DIO_PIN0,DIO_HIGH );
		}

	}


	return 1;
 */
