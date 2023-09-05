/*************************************************************/
/*******   Author: Islam Shaaban *****************************/
/*******   SWC:         DIO      *****************************/
/*******   Date:    3/8/2023     *****************************/
/*******   Version:      1.00    *****************************/
/*************************************************************/

#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H



#define DIO_PORTA   0
#define DIO_PORTB   1
#define DIO_PORTC   2
#define DIO_PORTD   3

#define DIO_PIN0   0
#define DIO_PIN1   1
#define DIO_PIN2   2
#define DIO_PIN3   3
#define DIO_PIN4   4
#define DIO_PIN5   5
#define DIO_PIN6   6
#define DIO_PIN7   7

#define DIO_OUTPUT  1
#define DIO_INPUT   0

#define DIO_HIGH    1
#define DIO_LOW     0

/* SetPinDirection */
void DIO_voidSetupPinDirection (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Dirction);

void DIO_voidSetPinValue (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Value);

u8 DIO_u8GetPinValue (u8 Copy_u8PortID, u8 Copy_u8PinID);

void DIO_voidSetPortDirection    (u8 Copy_u8PortID , u8 Copy_u8Direction );

void DIO_voidSetPortValue    (u8 Copy_u8PortID , u8 Copy_u8Value );


u8 DIO_u8GetPortValue(u8 Copy_u8PortID);









#endif
