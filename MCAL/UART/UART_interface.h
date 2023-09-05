/*
 * UART_interface.h
 *
 *  Created on: Aug 21, 2023
 *      Author: one
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

void UART_voidInit(void);

void UART_voidSendDataSync_Tx(u8 );

u8   UART_u8ReceiveDataSync_Rx(void);

void UART_voidSendStringSync_Tx(u8* );
void UART_voidReceiveStringSync_Rx(u8 * Copy_u8ReceiveData);
void UART_voidRXCompleteInterruptEnable(void);
void UART_voidUDREmptyInterruptEnable(void);
void UART_voidClearBuffer();

#endif /* MCAL_UART_UART_INTERFACE_H_ */
