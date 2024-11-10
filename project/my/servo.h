/*
 * servo.h
 *
 *  Created on: 2024Äê10ÔÂ23ÈÕ
 *      Author: 27384
 */

#ifndef SERVO_H_
#define SERVO_H_
#include "low_fliter.h"

extern float now_angle;
extern float set_angle;
extern filter_t servo_angle_filter;
extern int64 servo_offset;
void servo_init();
void servo_setangle();

#endif /* SERVO_H_ */
