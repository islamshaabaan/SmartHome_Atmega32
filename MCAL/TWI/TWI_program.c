/*
 * TWI_program.c
 *
 *  Created on: Aug 30, 2023
 *      Author: one
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MACROS.h"

#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_config.h"

/*******************************************************************************
 *                     		 Functions Definitions                             *
 *******************************************************************************/

/*Set Master Address to 0 if master will not be addressed*/
void TWI_voidInitMaster(u8 Copy_u8Address)
{
	/*Enable Acknowledge Bit*/
	SET_BIT(TWCR, TWCR_TWEA);

	/*SCL Freq = CPU_Freq / 16 + 2(TWBR) * 4 ^ TWPS*/
	/*Set SCL frequency to 100KHz, with 8MHz system frequency*/
	/* 1- Set TWBR = 2*/
	TWBR = 32;
	/* 2- Clear The Prescaler bit (TWPS0 - TWPS1)
	 * Option:
	 * TWPS1   TWPS0  - Prescaler
	 *   0       0          1
	 *   0		 1			4
	 *   1		 0			16
	 *	 1		 1			64
	 *   */
	CLR_BIT(TWSR, TWSR_TWPS0);
	CLR_BIT(TWSR, TWSR_TWPS1);

	/*Check if the master node will be addressed or not*/
	if(Copy_u8Address == 0)
	{
		/*Do Nothing*/
	}
	else
	{
		/*Set The Required Address to The Master*/
		TWAR = (Copy_u8Address << 1);
	}

	/*Enable TWI*/
	SET_BIT(TWCR, TWCR_TWEN);
}

void TWI_voidInitSlave(u8 Copy_u8Address)
{
	/*Set The Required Address to The Slave*/
	TWAR = (Copy_u8Address << 1);

	/*Enable Acknowledge Bit*/
	SET_BIT(TWCR, TWCR_TWEA);

	/*Enable TWI*/
	SET_BIT(TWCR, TWCR_TWEN);
}

TWI_ErrorStatus_t TWI_ErrorStatusSendStartCondition(void)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;
	//	TWCR |= (1 << TWCR_TWINT) | (1 << TWCR_TWSTA) | (1 << TWCR_TWEN);
	/*Send Start Condition Bit*/
	SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear The TWINT Flag*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while( GET_BIT(TWCR, TWCR_TWINT) == 0);

	/*check if start condition sent successfully from status register*/
	if( ( TWSR & STATUS_BIT_MASK ) == START_ACK ){
		/* Do nothing */
	}
	else{
		Local_ErrorStatus = StartConditionError;
	}
	return Local_ErrorStatus;
}


TWI_ErrorStatus_t TWI_ErrorStatusSendRepeatedStartConditionWithACK(void)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;
	TWCR |= (1 << TWCR_TWINT) | (1 << TWCR_TWSTA) | (1 << TWCR_TWEN);
	/*Send Start Condition Bit*/
	//SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear The TWINT Flag*/
	//SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while( GET_BIT(TWCR, TWCR_TWINT) == 0);

	/*Check For The Condition Status Code*/
	if( ( TWSR & STATUS_BIT_MASK ) == REP_START_ACK ){
		/* Do nothing */
	}
	else{
		Local_ErrorStatus = RepeatedStartError;
	}
	return Local_ErrorStatus;
}


TWI_ErrorStatus_t TWI_ErrorStatusSendSlaveAddressWithWriteACK(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;
//	u8 Local_u8TWCRValue = 0;

	/*Set 7 bits slave address to the bus,
	 *Set bit[0] = 0 to write.*/
	TWDR  = ( Copy_u8SlaveAddress << 1 ) & 0xFE;

	/*Clear The Start Condition Bit*/
	CLR_BIT(TWCR, TWCR_TWSTA);

	/*Clear The TWINT Flag*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while( GET_BIT(TWCR, TWCR_TWINT) == 0);

	/*Check For The Condition Status Code*/
	if( ( TWSR & STATUS_BIT_MASK ) == SLAVE_ADD_AND_WR_ACK ){
		/* Do nothing */
	}
	else{
		Local_ErrorStatus = SlaveAddressWithWriteError;
	}
	return Local_ErrorStatus;
}


TWI_ErrorStatus_t TWI_ErrorStatusSendSlaveAddressWithReadACK(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;

	/*Set 7 bits slave address to the bus,
	 *Set bit[0] = 1 to read*/
	TWDR  = ( Copy_u8SlaveAddress << 1 ) | 1;

	/*Clear The Start Condition Bit*/
	CLR_BIT(TWCR, TWCR_TWSTA);

	/*Clear The TWINT Flag*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while( GET_BIT(TWCR, TWCR_TWINT) == 0);

	/*Check For The Condition Status Code*/
	if( ( TWSR & STATUS_BIT_MASK ) == SLAVE_ADD_AND_RD_ACK ){
		/* Do nothing */
	}
	else{
		Local_ErrorStatus = SlaveAddressWithReadError;
	}

	return Local_ErrorStatus;
}


TWI_ErrorStatus_t TWI_ErrorStatusMasterWriteDataByteWithACK(u8 Copy_u8DataByte)
{

	TWI_ErrorStatus_t Local_ErrorStatus = NoError;

	/*Set The Data To The TWDR Register*/
	TWDR =  Copy_u8DataByte ;

	/*Clear The TWINT Flag*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while( GET_BIT(TWCR, TWCR_TWINT) == 0);

	/*Check For The Condition Status Code*/
	if( ( TWSR & STATUS_BIT_MASK ) == MSTR_WR_BYTE_ACK ){
		/* Do nothing */
	}
	else{
		Local_ErrorStatus = MasterWriteByteWithACKError;
	}
	return Local_ErrorStatus;
}


TWI_ErrorStatus_t TWI_ErrorStatusMasterReadDataByteWithACK(u8 * Copy_pu8ReceivedByte)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;

	/*Clear The TWINT Flag, To Make The Slave To Send its Data*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while( GET_BIT(TWCR, TWCR_TWINT) == 0);

	/*Check For The Condition Status Code*/
	if( ( TWSR & STATUS_BIT_MASK ) == MSTR_RD_BYTE_WITH_ACK ){
		* Copy_pu8ReceivedByte = TWDR ;
	}
	else{
		Local_ErrorStatus = MasterReadByteWithACKError;
	}
	return Local_ErrorStatus;
}
TWI_ErrorStatus_t 	TWI_ErrorStatusMasterReadDataByteWithNACK(u8 * Copy_pu8ReceivedByte){
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;

	/*Clear The TWINT Flag, To Make The Slave To Send its Data*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*Disable Ack Bit*/
	CLR_BIT(TWCR, TWCR_TWEA);

	/*wait until the operation finishes and the flag is raised again*/
	while( GET_BIT(TWCR, TWCR_TWINT) == 0);

	/*Check For The Condition Status Code*/
	if( ( TWSR & STATUS_BIT_MASK ) == MSTR_RD_BYTE_WITH_NACK ){
		* Copy_pu8ReceivedByte = TWDR ;
	}
	else{
		Local_ErrorStatus = MasterReadByteWithNACKError;
	}
	return Local_ErrorStatus;

}
void TWI_voidSendStopCondition(void)
{
	/*Send a stop condition on the bus*/
	SET_BIT(TWCR, TWCR_TWSTO);

	/*Clear The TWINT Flag*/
	SET_BIT(TWCR, TWCR_TWINT);

}

