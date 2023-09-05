/*
 * SERVO_program.c
 *
 *  Created on: Aug 23, 2023
 *      Author: one
 */



#include <stdlib.h>

#include "../../LIB/BIT_MACROS.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/TIMERS/TIMERS_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "SERVO_config.h"
#include "SERVO_interface.h"
#include "SERVO_private.h"
/*Explanation
 * we use Timer1 to generate PWM with 16 bit Reg.
 * Timer Freq = 8 / 8 = 1 MHZ.
 * Tick Time  = 1 Mirco Second.
 * Servo freq = 50 HZ ==> 1 / 50 = 20ms is the period
 * 20ms 			>>>> 	? Ticks
 * 1 micro second 	>>>>> 	1 Tick
 * ? = 20 000 Ticks as a top = Input capture reg.
 * */


void SERVO_voidServoInit(Servo * ptrToServo){
	DIO_voidSetupPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);
	Timer * ptrToTimer = (Timer *) malloc(sizeof(Timer));
	ptrToServo-> ptrTotimer = ptrToTimer;
	ptrToTimer -> timer_id = TIMER_COUNTER_1;
	ptrToTimer -> timer_mode =  TIMER_1_FAST_PWM_TOP_ICR1_MODE;
	ptrToTimer -> timer_calling_mode = TIMER_POLLING;
	ptrToTimer -> timer_prescaller = TIMER_PRESCALER_8;
	ptrToTimer -> timer_com_output_mode = PWM_OC0_CLEAR;
	TIMER_voidTimer1SetICRValue(ptrToTimer, 20000); // define the counter top value
	TIMER_voidTimerInit(ptrToTimer);
	TIMER_voidStartTimer(ptrToTimer);
}

void SERVO_voidSetAngle(Servo * ptrToServo, u16 COPY_u8ServoAngle){
/* we have from 1ms to 2 ms for get a high pulse.
 * so we need 1000 >>>> 2000, so we have a 1000 step range.
 * so we need to get each 1 step = x degree
 *  1000/180 = 5.556
 *  and add the 1000 as it's the reference.
 */
	u32 LOCAL_u32OCRValue = ((COPY_u8ServoAngle*(5.556))+1000);
	TIMER_voidTimerSetOCRValue((ptrToServo->ptrTotimer), LOCAL_u32OCRValue);
}
