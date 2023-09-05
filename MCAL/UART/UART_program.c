/*
 * UART_program.c
 *
 *  Created on: Aug 21, 2023
 *      Author: one
 */

#include "../../LIB/BIT_MACROS.h"
#include "../../LIB/STD_TYPES.h"

#include "UART_config.h"
#include "UART_private.h"
#include "UART_interface.h"

#include <avr/interrupt.h>

void UART_voidInit(void){
	//BIT2 : UCSZ0 always = 0,
	//BIT3 : TXEX  , BIT4: RXEN
	//BIT5 : UDRIE , BIT6 : TXCIE , BIT7 : RXCIE
	UART_UCSRB_REG = 0b00011000;


	//config uscrc, MUST BE ONE TO WRITE IN UCSRC
	u8 Local_u8TempUCSRC = 0b10000000;
	// Asyn
	CLR_BIT(Local_u8TempUCSRC,6); // UMSEL
	// disable parity
	CLR_BIT(Local_u8TempUCSRC,5); // UPM1
	CLR_BIT(Local_u8TempUCSRC,4); // UPM0
	// 1 STOP BIT
	CLR_BIT(Local_u8TempUCSRC,3); // USBS
	// 8 BIT MODE , UCS2->>0, UCS1,0 --> 1
	SET_BIT(Local_u8TempUCSRC,1); // UCSZ0
	SET_BIT(Local_u8TempUCSRC,2); // UCSZ1

	//CPOL -->> leading edge (raising) ONLY FOR SYNCH
	CLR_BIT(Local_u8TempUCSRC,0);

	UART_UCSRC_REG = Local_u8TempUCSRC;

	//baud rate >> ex 959 = 0000-0011-1011-1111
	/*	copy_u32BaudRate = 9600
	 * UART_BAUD_RATE = (((F_CPU / (copy_u32BaudRate * 16UL))) - 1);
	 * */
	UART_UBRRL_REG = (u8) UART_BAUD_RATE; // 1011-1111
	UART_UBRRH_REG = (u8) (UART_BAUD_RATE >> 8 ); // 0000-0011

}

void UART_voidSendDataSync_Tx(u8 Copy_u8Data){

	// check if buffer is empty UDRE
	while(GET_BIT(UART_UCSRA_REG,5)==0);

	// SEND DATA and the flag will cleared automatically after sending
	UART_UDR_REG = Copy_u8Data;
}

u8 UART_u8ReceiveDataSync_Rx(){
	/* Waiting till RxC flag raise  RXC*/
	while(GET_BIT(UART_UCSRA_REG , 7) == 0);

	/* Return the received Byte */
	return UART_UDR_REG;
}
void UART_voidSendStringSync_Tx(u8 * Pu8Data)
{
	u8 u8LoopCtr=0;
	while(Pu8Data[u8LoopCtr]!='\0')//fakt l gomla dy *(Pu8DAta+u8loopctr) da nzakr pointer aw c ya man b2a
	{
		//transmit
		UART_voidSendDataSync_Tx(Pu8Data[u8LoopCtr]);
		u8LoopCtr++;

	}
}
void UART_voidReceiveStringSync_Rx(u8 * Copy_u8ReceiveData){
	u8 counter =0;
	volatile u8 recChar;
	recChar =  UART_u8ReceiveDataSync_Rx();
	if(Copy_u8ReceiveData != NULL_ADDRESS){
		while(recChar !=13){
			UART_voidSendDataSync_Tx(recChar);
			//read data
			Copy_u8ReceiveData[counter]= recChar;
			counter ++ ;
			recChar =  UART_u8ReceiveDataSync_Rx();

		}
	}
}


void UART_voidRXCompleteInterruptEnable(void)
{
	SET_BIT(UART_UCSRB_REG,7);
}
void UART_voidUDREmptyInterruptEnable(void)
{
	SET_BIT(UART_UCSRB_REG,5);
}
void UART_voidClearBuffer(){
	u8 temp;
	temp = UART_UDR_REG;
	CLR_BIT(UART_UCSRA_REG, 7);
}


/**GLOBAL POINTER TO FUNCTION**/
static void (*Gpfunc1)(void)=NULL_ADDRESS;
static void (*Gpfunc2)(void)=NULL_ADDRESS;
/********CALL BACK FUNCTION*****/
void UART_VidSetCallBackForRxComplete(void (*Lpfunc)(void))
{
	Gpfunc1=Lpfunc;
}
void UART_VidSetCallBackForUDREmpty(void (*Lpfunc)(void))
{
	Gpfunc2=Lpfunc;
}

/*************ISR FOR UART**********/
ISR(__vector_13)
{
	if(Gpfunc1 != NULL_ADDRESS)
	{
		Gpfunc1();
	}
}

ISR(__vector_14)
{
	if(Gpfunc2 != NULL_ADDRESS)
	{
		Gpfunc2();
	}
}
// Assignment
/* 0- Time out 50ms
 * 1- Send and Receive Data Asynch.
 * 3- Send string function Asynch.
 */
