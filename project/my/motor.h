/*
 * motor.h
 *
 *  Created on: 2024Äê10ÔÂ26ÈÕ
 *      Author: 27384
 */

#ifndef MOTOR_H_
#define MOTOR_H_

extern uint8 motor_flag;

extern int16 LMotor_Speed;
extern int16 RMotor_Speed;
extern float LMotor_TagSpeed;
extern float RMotor_TagSpeed;
extern int16 LMotor_Duty;
extern int16 LMotor_Duty_hubu ;
extern int16 RMotor_Duty;
extern int16 LDuty_set;
extern int16 RDuty_set;

void Motor_init();




#endif /* MOTOR_H_ */
