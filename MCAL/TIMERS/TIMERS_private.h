/*
 * TIMERS_private.h
 *
 *  Created on: Aug 22, 2023
 *      Author: one
 */

#ifndef MCAL_TIMERS_TIMERS_PRIVATE_H_
#define MCAL_TIMERS_TIMERS_PRIVATE_H_

/************************************************************************/
/* TIMERS                                                                     */
/************************************************************************/

//Timer/Counter Interrupt Mask Register
#define TIMSK_REG *((volatile u8*)0x59)

typedef enum{
	//timer 0 overflow interrupt
	TOIE0_BIT,
	//timer 0 ctc interrupt enable
	OCIE0_BIT,
	//Timer/Counter1, Overflow Interrupt Enable
	TOIE1_BIT,
	//Timer/Counter1, Output Compare B Match Interrupt Enable
	OCIE1B_BIT,
	//Timer/Counter1, Output Compare A Match Interrupt Enable
	OCIE1A_BIT,
	//Timer/Counter1, Input Capture Interrupt Enable
	TICIE1_BIT,
	//timer 2 overflow interrupt
	TOIE2_BIT,
	//timer 2 ctc interrupt enable
	OCIE2_BIT
}TIMSK_REG_BITS;



//Timer/Counter Interrupt Flag Register
#define TIFR_REG *((volatile u8*)0x58)

typedef enum{
	//overflow FLAG
	TOV0_BIT,
	//ctc interrupt FLAG
	OCF0_BIT,
	//TIMER 1 overflow FLAG
	TOV1_BIT,
	//Timer/Counter1, Output Compare B Match Flag
	OCF1B_BIT,
	//Timer/Counter1, Output Compare A Match Flag
	OCF1A_BIT,
	//Timer/Counter1, Input Capture Flag
	ICF1_BIT,
	//TIMER 2 overflow interrupt
	TOV2_BIT,
	//TIMER 2 ctc interrupt enable
	OCF2_BIT,

}TIFR_REG_BITS;



/************************************************************************/
/* timer 0                                                                      */
/************************************************************************/


//Timer/Counter 0 Control Register
#define TCCR0_REG *(( volatile u8 *) 0x53)

typedef enum{
	//Clock selector
	CS00_BIT,
	CS01_BIT,
	CS02_BIT,
	//Waveform Generation Mode
	WGM01_BIT,
	//compare output mode
	COM00_BIT,
	COM01_BIT,
	//Waveform Generation Mode
	WGM00_BIT,
	//Force Output Compare
	FOC0_BIT
}TCCR0_REG_BITS;

//Timer/Counter 0 Register
#define TCNT0_REG *((volatile u8*)0x52)

//Output Compare Register
#define OCR0_REG *((volatile u8*)0x5C)

/************************************************************************/
/* timer 1                                                                     */
/************************************************************************/

//Timer/Counter1 Control Register A
#define  TCCR1A_REG *((volatile u8 *) 0x4F)

typedef enum{
	//Waveform Generation Mode
	WGM10_BIT,
	WGM11_BIT,
	//Force Output Compare for Compare unit B
	FOC1B_BIT,
	//Force Output Compare for Compare unit A
	FOC1A_BIT,
	//Compare Output Mode for Compare unit B
	COM1B0_BIT,
	COM1B1_BIT,
	//Compare Output Mode for Compare unit A
	COM1A0_BIT,
	COM1A1_BIT
	}TCCR1A_REG_BITS;


//Timer/Counter1 Control Register B
#define TCCR1B_REG *((volatile u8 *)0x4E)

typedef enum{
	//Clock Select prescaler
	CS10_BIT,
	CS11_BIT,
	CS12_BIT,
	//Waveform Generation Mode
	WGM12_BIT,
	WGM13_BIT,
	RESERVED,
	//Input Capture Edge Select
	ICES1_BIT,
	ICNC1_BIT,
	}TCCR1B_REG_BITS;

//TIMER/CONTER1
#define TCNT1H_REG *((volatile u8 *) 0X4D)
#define TCNT1L_REG *((volatile u8 *) 0X4C)

//Output Compare Register 1 A
#define OCR1AH_REG *((volatile u8 *)0x4B)
#define OCR1AL_REG *((volatile u8 *)0x4A)
#define OCR1A_REG 	*((volatile u16 *)0x4A)


//Output Compare Register 1
#define OCR1BH_REG *((volatile u8 *)0x49)
#define OCR1BL_REG *((volatile u8 *)0x48)

//Input Capture Register 1
#define ICR1H_REG *((volatile u8 *)0x47)
#define ICR1L_REG *((volatile u8 *)0x46)




#endif /* MCAL_TIMERS_TIMERS_PRIVATE_H_ */
