/*
 * TWI_interface.h
 *
 *  Created on: Aug 30, 2023
 *      Author: one
 */

#ifndef MCAL_TWI_TWI_INTERFACE_H_
#define MCAL_TWI_TWI_INTERFACE_H_

typedef enum
{
	NoError,
	StartConditionError,
	RepeatedStartError,
	SlaveAddressWithWriteError,
	SlaveAddressWithReadError,
	MasterWriteByteWithACKError,
	MasterReadByteWithACKError,
	MasterReadByteWithNACKError
}TWI_ErrorStatus_t;
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef  u8 TWI_Address;
typedef  u8 TWI_BitRate;
typedef enum{
	twi_prescaler_1,
	twi_prescaler_4,
	twi_prescaler_16,
	twi_prescaler_64
}TWI_Prescaler;

typedef struct {
	TWI_Address twi_slave_address;
	TWI_BitRate twi_bit_rate;
	TWI_Prescaler twi_prescaler;
}TWI_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void 				TWI_voidInitMaster(u8 Copy_u8Address);
void 				TWI_voidInitSlave(u8 Copy_u8Address);
TWI_ErrorStatus_t 	TWI_ErrorStatusSendStartCondition(void);
TWI_ErrorStatus_t 	TWI_ErrorStatusSendRepeatedStartConditionWithACK(void);
TWI_ErrorStatus_t 	TWI_ErrorStatusSendSlaveAddressWithWriteACK(u8 Copy_u8SlaveAddress);
TWI_ErrorStatus_t 	TWI_ErrorStatusSendSlaveAddressWithReadACK(u8 Copy_u8SlaveAddress);
TWI_ErrorStatus_t 	TWI_ErrorStatusMasterWriteDataByteWithACK(u8 Copy_u8DataByte);
TWI_ErrorStatus_t 	TWI_ErrorStatusMasterReadDataByteWithACK(u8 * Copy_pu8ReceivedByte);
TWI_ErrorStatus_t 	TWI_ErrorStatusMasterReadDataByteWithNACK(u8 * Copy_pu8ReceivedByte);

void 				TWI_voidSendStopCondition(void);



#endif /* MCAL_TWI_TWI_INTERFACE_H_ */
