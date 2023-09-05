/*
 * BUZZER_interface.h
 *
 *  Created on: Sep 4, 2023
 *      Author: one
 */

#ifndef HAL_BUZZER_BUZZER_INTERFACE_H_
#define HAL_BUZZER_BUZZER_INTERFACE_H_

/* Section : Macro Declarations */
#define SIREN_TIMER0		0
#define SIREN_TIMER1		1
#define SIREN_TIMER2		2
#define SIREN_TIMER		SIREN_TIMER0
#define F_CPU			8000000UL


/* Section : Data Type Declarations */
typedef enum{
	siren_off,
	siren_on
}enu_siren_state;

/* Section : Function Declarations */
void Siren_vInit();
void SIREN_vChangeSound(u16 Copy_u16Frequency);
void SIREN_vStop();



#endif /* HAL_BUZZER_BUZZER_INTERFACE_H_ */
