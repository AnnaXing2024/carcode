/*
 * akm.h
 *
 *  Created on: 2024Äê10ÔÂ26ÈÕ
 *      Author: 27384
 */

#ifndef AKM_H_
#define AKM_H_


#include <math.h>

#define EDS_OUT_LIMIT      30
#define EDS_IN_LIMIT       130

typedef enum{
    STOP,
    STRAIGHT,
    LONG_STRAIGHT,
    CURVE,
    SPEED_TURN,
    SPEED_CIRCLE,
    SPEED_RAMP_UP,
    SPEED_RAMP_DOWN,

    SPEED_ELEMENT_MAX
}element;

typedef struct{
     element current_element;
     int16 speed_array[SPEED_ELEMENT_MAX];

}speed_mode;

typedef struct{
        float out;
        float in;
}diff_speed_t;


extern diff_speed_t straight_diff_speed;
extern diff_speed_t curve_diff_speed;
extern diff_speed_t turn_diff_speed;
extern diff_speed_t circle_diff_speed;

extern speed_mode slow;

extern speed_mode *current_mode;

extern float speedL_set;
extern float speedR_set;

extern double currentL_set;
extern double currentR_set;

#endif /* AKM_H_ */
