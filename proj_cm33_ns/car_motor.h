 
#ifndef CAR_MOTOR_H
#define CAR_MOTOR_H
#include <stdbool.h>
#include <stdint.h>
bool car_motor_init(void);
bool car_motor_stop(void);
/* Signed duty for each motor; zero stops it. Clamped to CAR_MAX_SPEED.
 * Applies configured polarity. Caller is responsible for a stop/timeout. */
bool car_motor_drive_all(int16_t m1, int16_t m2, int16_t m3, int16_t m4);
/* M1/M2 left, M3/M4 right, matching Freenove's turning example. */
bool car_motor_drive(int16_t left, int16_t right);
#endif
