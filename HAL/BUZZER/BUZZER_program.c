/*
 * BUZZER_program.c
 *
 *  Created on: Sep 4, 2023
 *      Author: one
 */


#include "../../LIB/BIT_MACROS.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/GIE/GIE_interface.h"
#include "../../MCAL/TIMERS/TIMERS_interface.h"
#include "BUZZER_interface.h"
void __vector_11(void) __attribute__((signal));
static Timer CURRENT_BUZZER;
static enu_siren_state CURRENT_STATE;

void Siren_vInit(){
#if SIREN_TIMER == SIREN_TIMER0
	/* PWM0 implementation */
	CURRENT_BUZZER.timer_id = TIMER_COUNTER_0;
	CURRENT_BUZZER.timer_calling_mode = TIMER_POLLING;
	CURRENT_BUZZER.timer_mode = TIMER_FAST_PWM_MODE;
	CURRENT_BUZZER.timer_com_output_mode = PWM_OC0_CLEAR; // NonInverting
	CURRENT_BUZZER.timer_prescaller = TIMER_PRESCALER_64;

	DIO_voidSetupPinDirection(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);
	TIMER_voidTimerInit(&CURRENT_BUZZER);
	TIMER_voidEnableInterruptT0();
	GIE_voidEnable();
	CURRENT_STATE = siren_off;
#elif SIREN_TIMER == SIREN_TIMER1
	/* PWM1 implementation */

#elif SIREN_TIMER == SIREN_TIMER2
	/* PWM2 implementation */

#endif
}

void SIREN_vChangeSound(u16 Copy_u16Frequency){
	u8 prescaler = 1;
	if(siren_off == CURRENT_STATE){
		TIMER_voidStartTimer(&CURRENT_BUZZER);
		CURRENT_STATE = siren_on;
	}
#if SIREN_TIMER == SIREN_TIMER0
	u16 PreLoad = (F_CPU / (2 * Copy_u16Frequency * prescaler)) - 1;
	TIMER_voidTimerSetOCRValue(&CURRENT_BUZZER,PreLoad);

#elif SIREN_TIMER == SIREN_TIMER1
	/* PWM1 implementation */

#elif SIREN_TIMER == SIREN_TIMER2
	/* PWM2 implementation */

#endif
}

void SIREN_vStop(){
#if SIREN_TIMER == SIREN_TIMER0
	TIMER_voidStopTimer(&CURRENT_BUZZER);
	CURRENT_STATE = siren_off;
#elif SIREN_TIMER == SIREN_TIMER1
	/* PWM1 implementation */

#elif SIREN_TIMER == SIREN_TIMER2
	/* PWM2 implementation */

#endif
}

/* TIMER0 OVF ISR */
void __vector_11(void){
	static u8 state = 0;
	if(state == 0){
		DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,state);
		state = 1;
	}
	else{
		DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,state);
		state = 0;
	}

}
