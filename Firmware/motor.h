
#ifndef __MOTOR_H__
#define __MOTOR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

    void motor_init();
    void setMotorSpeed(float motor_A_speed, float motor_B_speed);
    void jazz_oadu(float motor_A_speed, float motor_B_speed);

#ifdef __cplusplus
}
#endif

#endif