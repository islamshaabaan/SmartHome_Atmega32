/*
 * SERVO_interface.h
 *
 *  Created on: Aug 23, 2023
 *      Author: one
 */

#ifndef HAL_SERVO_MOTOR_SERVO_INTERFACE_H_
#define HAL_SERVO_MOTOR_SERVO_INTERFACE_H_

typedef struct{
	Timer * ptrTotimer;
	}Servo;

void SERVO_voidServoInit(Servo * ptrToservo);

void SERVO_voidSetAngle(Servo * ptrToServo, u16 COPY_u8ServoAngle);


#endif /* HAL_SERVO_MOTOR_SERVO_INTERFACE_H_ */
