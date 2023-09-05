/*
 * TIMERS_program.c
 *
 *  Created on: Aug 22, 2023
 *      Author: one
 */



#include "../../LIB/BIT_MACROS.h"
#include "../../LIB/STD_TYPES.h"

#include "TIMERS_config.h"
#include "TIMERS_interface.h"
#include "TIMERS_private.h"



void TIMER_voidTimerInit(Timer * ptrToTimer){
	switch(ptrToTimer->timer_id)
	{
	case TIMER_COUNTER_0:
		switch (ptrToTimer->timer_mode)
		{
		case TIMER_NORMAL_MODE:
			CLR_BIT(TCCR0_REG,WGM00_BIT);
			CLR_BIT(TCCR0_REG,WGM01_BIT);
			break;
		case TIMER_PWM_PHASE_CORRECT_MODE:
			SET_BIT(TCCR0_REG,WGM00_BIT);
			CLR_BIT(TCCR0_REG,WGM01_BIT);
			switch(ptrToTimer->timer_com_output_mode)
			{
			case PWM_OC0_CLEAR:
				SET_BIT(TCCR0_REG,COM01_BIT);
				CLR_BIT(TCCR0_REG,COM00_BIT);
				break;
			case PWM_OC0_SET:
				SET_BIT(TCCR0_REG,COM01_BIT);
				SET_BIT(TCCR0_REG,COM00_BIT);
				break;
			default:
				break;
			}
			break;
		case TIMER_CTC_MODE:
			CLR_BIT(TCCR0_REG,WGM00_BIT);
			SET_BIT(TCCR0_REG,WGM01_BIT);
			break;
		case TIMER_FAST_PWM_MODE:
			SET_BIT(TCCR0_REG,WGM00_BIT);
			SET_BIT(TCCR0_REG,WGM01_BIT);
			switch(ptrToTimer->timer_com_output_mode){
			case PWM_OC0_CLEAR:
				SET_BIT(TCCR0_REG,COM01_BIT);
				CLR_BIT(TCCR0_REG,COM00_BIT);
				break;
			case PWM_OC0_SET:
				SET_BIT(TCCR0_REG,COM01_BIT);
				SET_BIT(TCCR0_REG,COM00_BIT);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		switch (ptrToTimer->timer_calling_mode)
		{
		case TIMER_POLLING:
			CLR_BIT(TIMSK_REG,TOIE0_BIT);
			CLR_BIT(TIMSK_REG,OCIE0_BIT);
			break;
		case TIMER_INTERRUPT:
			switch (ptrToTimer->timer_mode)
			{
			case TIMER_NORMAL_MODE:
				SET_BIT(TIMSK_REG,TOIE0_BIT);
				break;
			case TIMER_CTC_MODE:
				SET_BIT(TIMSK_REG,OCIE0_BIT);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
		case TIMER_COUNTER_1:
			switch (ptrToTimer -> timer_mode)
			{
			case TIMER_1_NORMAL_MODE:
				CLR_BIT(TCCR1A_REG,WGM10_BIT);
				CLR_BIT(TCCR1A_REG,WGM11_BIT);
				CLR_BIT(TCCR1B_REG,WGM12_BIT);
				CLR_BIT(TCCR1B_REG,WGM13_BIT);
				break;
			case TIMER_1_FAST_PWM_TOP_ICR1_MODE:{
				CLR_BIT(TCCR1A_REG,WGM10_BIT);
				SET_BIT(TCCR1A_REG,WGM11_BIT);
				SET_BIT(TCCR1B_REG,WGM12_BIT);
				SET_BIT(TCCR1B_REG,WGM13_BIT);
				switch(ptrToTimer->timer_com_output_mode){
				case PWM_OC0_CLEAR:
					CLR_BIT(TCCR1A_REG,COM1A0_BIT);
					SET_BIT(TCCR1A_REG,COM1A1_BIT);
					break;
				case PWM_OC0_SET:
					SET_BIT(TCCR1A_REG,COM01_BIT);
					SET_BIT(TCCR1A_REG,COM00_BIT);
					break;
				default:
					break;
				}
				break;
			}
			default:
				break;
			}
			switch (ptrToTimer->timer_calling_mode){
			case TIMER_POLLING:
				CLR_BIT(TIMSK_REG,TOIE1_BIT);
				CLR_BIT(TIMSK_REG,OCIE1B_BIT);
				CLR_BIT(TIMSK_REG,OCIE1A_BIT);
				CLR_BIT(TIMSK_REG,TICIE1_BIT);
				break;
			case TIMER_INTERRUPT:
				switch (ptrToTimer->timer_mode){
				case TIMER_1_INPUT_CAPTURE_INTERRUPT:
					SET_BIT(TIMSK_REG,TICIE1_BIT);
					break;
				case TIMER_1_OUTPUT_COMPARE_A_MATCH_INTERRUPT:
					SET_BIT(TIMSK_REG,OCIE1A_BIT);
					break;
				case TIMER_1_OUTPUT_COMPARE_B_MATCH_INTERRUPT:
					SET_BIT(TIMSK_REG,OCIE1B_BIT);
					break;
				case TIMER_1_OVERFLOW_INTERRUPT:
					SET_BIT(TIMSK_REG,TOIE1_BIT);
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
	}
}

void TIMER_voidEnableInterruptT0(){
	TIMSK_REG = (1<<TOIE0_BIT);
}
void TIMER_voidStartTimer(Timer * ptrToTimer){
	switch (ptrToTimer -> timer_id)
	{
	case TIMER_COUNTER_0:{
		//clear old prescaler
		TCCR0_REG &= ~(0x7<<0);
		//set new prescaler
		TCCR0_REG |= ((ptrToTimer->timer_prescaller) & 0x7);
		break;
	}
	case TIMER_COUNTER_1:{
		TCCR1B_REG &= ~(0x7<<0);
		//set new prescaler
		TCCR1B_REG |= ((ptrToTimer->timer_prescaller) & 0x7);
		break;
	}
	default:
		break;
	}
}

void Timer_voidHoldTimer(Timer * ptrToTimer){
	//clear old prescaler
	switch (ptrToTimer -> timer_id)
	{
	case TIMER_COUNTER_0:{
		TCCR0_REG &= ~(0x7  <<0);
		break;
	}
	case TIMER_COUNTER_1:{
		TCCR1B_REG &= ~(0x7<<0);
		break;
	}
	default:
		break;
	}
}

void TIMER_voidStopTimer(Timer * ptrToTimer){

	switch (ptrToTimer -> timer_id)
	{
	case TIMER_COUNTER_0:{
		//clear all timer data
		TCCR0_REG = 0x00;
		TCNT0_REG = 0x00;
		OCR0_REG  = 0x00;
		break;
	}
	case TIMER_COUNTER_1:{
		TCCR1A_REG = 0;
		TCCR1B_REG = 0;
		TCNT1H_REG = 0;
		TCNT1L_REG = 0;
		OCR1AH_REG = 0;
		OCR1AL_REG = 0;
		OCR1BH_REG = 0;
		OCR1BL_REG = 0;
		ICR1H_REG = 0;
		ICR1L_REG = 0;
		break;
	}
	default:
		break;
	}

}


void TIMER_voidTimerSetPreloadValue(Timer * ptrToTimer,u32 COPY_u32PreloadValue){
	switch (ptrToTimer -> timer_id){
	case TIMER_COUNTER_0:{
		TCNT0_REG = COPY_u32PreloadValue & 0xff;
		break;
	}
	case TIMER_COUNTER_1:{
		TCNT1H_REG = COPY_u32PreloadValue >> 8;
		TCNT1L_REG = COPY_u32PreloadValue & 0xff;
		break;
	}
	default:
		break;
	}
}

void TIMER_voidTimerSetOCRValue(Timer * ptrToTimer,u32 COPY_u32PreloadValue){
	switch (ptrToTimer -> timer_id){
	case TIMER_COUNTER_0:{
		OCR0_REG = COPY_u32PreloadValue & 0xff;
		break;
	}
	case TIMER_COUNTER_1:{
		OCR1AH_REG = COPY_u32PreloadValue >> 8;
		OCR1AL_REG = COPY_u32PreloadValue & 0xff;
		//OCR1A_REG = COPY_u32PreloadValue;
		break;
	}
	default:
		break;
	}

}

void TIMER_voidTimer1SetICRValue(Timer * ptrToTimer,u32 COPY_u32PreloadValue){
	switch (ptrToTimer -> timer_id){
	case TIMER_COUNTER_1:{
		ICR1H_REG = COPY_u32PreloadValue >> 8;
		ICR1L_REG = COPY_u32PreloadValue & 0xff;
		break;
	}
	default:
		break;
	}

}

// void Timer_voidReadTimer0(Timer_0 * ptrToTimer0, u8 * COPY_ptrTimerValue){
// 	switch (ptrToTimer0->timer_mode){
// 		case (TIMER_NORMAL_MODE):
// 		*COPY_ptrTimerValue = TCNT0_REG;
// 		break;
// 		case (TIMER_CTC_MODE):
// 		*COPY_ptrTimerValue = OCR0_REG;
// 		break;
// 		case (TIMER_FAST_PWM_MODE):
// 		*COPY_ptrTimerValue = OCR0_REG;
// 		break;
// 		case (TIMER_PWM_PHASE_CORRECT_MODE):
// 		*COPY_ptrTimerValue = OCR0_REG;
// 		break;
// 		default:
// 		break;
// 	}
// }
