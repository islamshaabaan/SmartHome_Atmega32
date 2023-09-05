/*
 * EEPROM_program.c
 *
 *  Created on: Sep 1, 2023
 *      Author: one
 */


#define F_CPU 8000000UL
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MACROS.h"
#include <util/delay.h>

#include "../../MCAL/TWI/TWI_interface.h"
#include "../../MCAL/UART/UART_interface.h"
#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"
ErrorState EEPROM_ErrorStateSendDataByte1( u16 Copy_u16ByteAddress , u8 Copy_u8Data)
{
	ErrorState Local_ErrorState = STD_TYPES_OK ;
	u8 Local_u8I2cError = NoError ;
	//UART_voidSendStringSync_Tx((u8*)"loc0");

	/*Start Condition*/
	Local_u8I2cError = TWI_ErrorStatusSendStartCondition();
	//UART_voidSendStringSync_Tx((u8*)"loc00");

	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	//UART_voidSendStringSync_Tx((u8*)"loc1");
	/*
	 * Send SLA + W ACK
	 * 1010		-		0		- 		00        -  0/1
	 * unique 	-	HW Address		Byte Location -  R/W
	 * So : 0101 - 0 - 00 - 0 then Shift it by 1 in SendSlave Fun
	 * So : 1010 - 0 - 00 - 0
	 * So : (Copy_u16ByteAddress >> 8) = The Block.
	 * 01010000
	 * 00000000
	 * 00000001
	 * ----------
	 * 01010001
	 * 10100010
	 * */
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithWriteACK((u8)0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8));
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	//UART_voidSendStringSync_Tx((u8*)"loc2");

	/*Send Rest of byte address*/
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK((u8) (Copy_u16ByteAddress));
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	//UART_voidSendStringSync_Tx((u8*)"loc3");

	/*Send Data */
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK(Copy_u8Data );
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	//UART_voidSendStringSync_Tx((u8*)"loc4");

	/*Stop Condition*/
	TWI_voidSendStopCondition();

	_delay_ms(10);

	return Local_ErrorState ;
}
ErrorState EEPROM_ErrorStateReadDataByte1( u16 Copy_u16ByteAddress , u8* Copy_pu8Data)
{
	ErrorState Local_ErrorState = STD_TYPES_OK ;
	u8 Local_u8I2cError = NoError ;
	/*Start Condition */
	Local_u8I2cError = TWI_ErrorStatusSendStartCondition();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send SLA+W ACK*/
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithWriteACK(0x50 | (EEPROM_A2 << 2) |  (Copy_u16ByteAddress >> 8)	);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send Reset of byte address*/
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK((u8) Copy_u16ByteAddress);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*send repeated start*/
	Local_u8I2cError = TWI_ErrorStatusSendRepeatedStartConditionWithACK();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send SLA+R*/
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithReadACK(0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8));
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Read Data */
	TWI_ErrorStatusMasterReadDataByteWithACK(Copy_pu8Data);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Stop Conditon*/
	TWI_voidSendStopCondition();
	return Local_ErrorState ;
}
ErrorState EEPROM_ErrorStateSendDataByte	( u8 Copy_u8ByteAddress , u8 Copy_u8Data, enu_EEPROM_Blocks Block)
{
	ErrorState Local_ErrorState = STD_TYPES_OK ;
	u8 Local_u8I2cError = NoError ;
	/*Start Condition*/
	Local_u8I2cError = TWI_ErrorStatusSendStartCondition();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send SLA + W ACK
	 * 1010		-		0		- 		00        -  0/1
	 * unique 	-	HW Address		Byte Location -  R/W
	 * So : 0101 - 0 - 00 - 0 then Shift it by 1 in SendSlave Fun
	 * So : 1010 - 0 - 00 - 0
	 * So : (Copy_u16ByteAddress >> 8) = The Block.
	 * 01010000
	 * 00000000
	 * 00000001
	 * ----------
	 * 01010001
	 * 10100010
	 * */
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithWriteACK(0x50 | (EEPROM_A2 << 2) | (Block));
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send Rest of byte address*/
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK((u8) Copy_u8ByteAddress);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send Data */
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK(Copy_u8Data );
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Stop Condition*/
	TWI_voidSendStopCondition();

	_delay_ms(10);

	return Local_ErrorState ;
}
ErrorState EEPROM_ErrorStateReadDataByte( u8 Copy_u8ByteAddress , u8* Copy_pu8Data, enu_EEPROM_Blocks Block)
{
	ErrorState Local_ErrorState = STD_TYPES_OK ;
	u8 Local_u8I2cError = NoError ;
	/*Start Condition */
	Local_u8I2cError = TWI_ErrorStatusSendStartCondition();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send SLA+W ACK*/
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithWriteACK(0x50 | (EEPROM_A2 << 2) | (Block)	);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send Reset of byte address*/
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK((u8) Copy_u8ByteAddress);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*send repeated start*/
	Local_u8I2cError = TWI_ErrorStatusSendRepeatedStartConditionWithACK();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send SLA+R*/
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithReadACK(0x50 | (EEPROM_A2 << 2) | (Block));
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Read Data */
	TWI_ErrorStatusMasterReadDataByteWithACK(Copy_pu8Data);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Stop Conditon*/
	TWI_voidSendStopCondition();
	return Local_ErrorState ;
}
void EEPROM_vWriteString(u8 Copy_u8ByteAddress, u8 *Copy_u8String,enu_EEPROM_Blocks Block){
	u8 local_u8StringIndex=0;
	u8 local_u8Address = Copy_u8ByteAddress;
	while(Copy_u8String[local_u8StringIndex] != '\0'){
		EEPROM_ErrorStateSendDataByte(local_u8Address, Copy_u8String[local_u8StringIndex], Block);
		local_u8Address++;
		local_u8StringIndex++;
	}
	EEPROM_ErrorStateSendDataByte(local_u8Address, '\0',Block);
}

void EEPROM_vReadString(u8 Copy_u8ByteAddress, u8 *Copy_u8String, enu_EEPROM_Blocks Block){
	u8 local_u8StringIndex=0;
	u8 local_u8Address = Copy_u8ByteAddress;
	u8 local_temp;
	do{
		EEPROM_ErrorStateReadDataByte(local_u8Address, &local_temp, Block);
		if(local_temp == 0xFF){
			break;
		}
		else{ /* Do Nothing */ }
		Copy_u8String[local_u8StringIndex] = local_temp;
		local_u8StringIndex++;
		local_u8Address++;
	}while(local_temp != '\0');
}

ErrorState EEPROM_ErrorStateRecieveStreamDataByte(u16 Copy_u16ByteAddress	,u8* Copy_pu8Data, u8 Copy_u8NoBytes)
{
	u8 Local_u8ByteNo=0;
	ErrorState Local_ErrorState = STD_TYPES_OK ;
	u8 Local_u8I2cError = NoError ;
	/*Start Condition */
	Local_u8I2cError = TWI_ErrorStatusSendStartCondition();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Send SLA+W ACK*/
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithWriteACK(0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8)	);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Send Reset of byte address*/
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK((u8) Copy_u16ByteAddress);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*send repeated start*/
	Local_u8I2cError = TWI_ErrorStatusSendRepeatedStartConditionWithACK();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Send SLA+R*/
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithReadACK(0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8));
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Read Data */
	while(Local_u8ByteNo<Copy_u8NoBytes)
		//while(Copy_pu8Data[Local_u8ByteNo-1]!='\r')
	{

		TWI_ErrorStatusMasterReadDataByteWithACK(& Copy_pu8Data[Local_u8ByteNo] );
		if(( Copy_pu8Data[Local_u8ByteNo]==255))
		{
			break;
		}
		Local_u8ByteNo++;
		//if(Local_u8I2cError != NoError)
		//		{
		//			Local_ErrorState = Local_u8I2cError ;
		//		}
	}
	/*Stop Conditon*/
	//TWI_voidSendStopCondition();
	_delay_ms(10);
	return Local_ErrorState ;
}

ErrorState  EEPROM_ErrorStateSendDataByte2	( u16 Copy_u16ByteAddress , u8 Copy_u8Data	)
{
	ErrorState Local_ErrorState = STD_TYPES_OK ;
	u8 Local_u8I2cError = NoError ;
	/*Start Condition*/

	Local_u8I2cError = TWI_ErrorStatusSendStartCondition();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send SLA + W ACK*/
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithWriteACK(0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8)	);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send Rest of byte address*/
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK((u8) Copy_u16ByteAddress);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Send Data */

	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK(Copy_u8Data );
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = STD_TYPES_NOK ;
	}
	/*Stop Condition*/
	TWI_voidSendStopCondition();

	_delay_ms(10);

	return Local_ErrorState ;
}

ErrorState EEPROM_ErrorStateRecieveDataByte	( u16 Copy_u16ByteAddress	,u8* Copy_pu8Data)
{

	ErrorState Local_ErrorState = STD_TYPES_OK ;
	u8 Local_u8I2cError = NoError ;
	/*Start Condition */
	//	UART_voidSendDataSync('M');
	Local_u8I2cError = TWI_ErrorStatusSendStartCondition();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Send SLA+W ACK*/
	//UART_voidSendDataSync('L');
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithWriteACK(0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8)	);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Send Reset of byte address*/
	//UART_voidSendDataSync('w');
	Local_u8I2cError = TWI_ErrorStatusMasterWriteDataByteWithACK((u8) Copy_u16ByteAddress);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*send repeated start*/
	//UART_voidSendDataSync('V');
	Local_u8I2cError = TWI_ErrorStatusSendRepeatedStartConditionWithACK();
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Send SLA+R*/
	//UART_voidSendDataSync('X');
	Local_u8I2cError = TWI_ErrorStatusSendSlaveAddressWithReadACK(0x50 | (EEPROM_A2 << 2) | (Copy_u16ByteAddress >> 8));
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	/*Read Data */
	//UART_voidSendDataSync('Y');
	TWI_ErrorStatusMasterReadDataByteWithACK(Copy_pu8Data);
	if(Local_u8I2cError != NoError)
	{
		Local_ErrorState = Local_u8I2cError ;
	}
	//UART_voidSendDataSync('T');
	/*Stop Conditon*/
	//TWI_voidSendStopCondition();
	//TWI_ErrorStatusSendStartConditionWithACK();
	//_delay_ms(10);
	//UART_voidSendDataSync('P');

	return Local_ErrorState ;
}


