/*
  * EEPROM_interface.h
 *
 *  Created on: Sep 1, 2023
 *      Author: one
 */

#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_
/*	A9 - A8 - A7 - A6 - A5 - A4 - A3 - A2 - A1 - A0
 * 	512	 256 128   64   32	 16	  8		4	 2	 1
 * 00 = 0 = Block0 from 0   to 255
 * 10 = 2 = Block2 from 512 to 1023
 *
 * */
typedef enum{
	BLOCK0=0,
	BLOCK1=2,

}enu_EEPROM_Blocks;
ErrorState EEPROM_ErrorStateSendDataByte1	( u16 Copy_u16ByteAddress , u8 Copy_u8Data);
ErrorState  EEPROM_ErrorStateSendDataByte2	( u16 Copy_u16ByteAddress , u8 Copy_u8Data	);
ErrorState EEPROM_ErrorStateRecieveStreamDataByte(u16 Copy_u16ByteAddress	,u8* Copy_pu8Data, u8 Copy_u8NoBytes);
ErrorState EEPROM_ErrorStateReadDataByte1( u16 Copy_u16ByteAddress , u8* Copy_pu8Data);
ErrorState EEPROM_ErrorStateSendDataByte	( u8 Copy_u8ByteAddress , u8 Copy_u8Data, enu_EEPROM_Blocks Block	);

ErrorState EEPROM_ErrorStateReadDataByte	( u8 Copy_u8ByteAddress , u8* Copy_pu8Data, enu_EEPROM_Blocks Block	);
void EEPROM_vWriteString( u8 Copy_u8ByteAddress, u8 *Copy_u8String,  enu_EEPROM_Blocks Block);
void EEPROM_vReadString( u8 Copy_u8ByteAddress, u8 *Copy_u8String,  enu_EEPROM_Blocks Block);


#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
