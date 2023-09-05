/*
 * LED_interface.h
 *
 *  Created on: Aug 3, 2023
 *      Author: Islam Shaaban
 */

#ifndef HAL_LED_INTERFACE_H_
#define HAL_LED_INTERFACE_H_

#define LED_ACTIVE_HIGH		1
#define LED_ACTIVE_LOW		0
typedef struct{
	u8 Port;
	u8 Pin;
	u8 ActiveState;
}LED_t;

void LED_voidInit(LED_t * Copy_ptrLED);
void LED_voidON(LED_t * Copy_ptrLED);
void LED_voidOFF(LED_t * Copy_ptrLED);

#endif /* HAL_LED_INTERFACE_H_ */
