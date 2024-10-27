#include "Sensor_PID.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include <stm32f4xx_hal_gpio.h>


void sensor_vaasippu_mattrum_PID()
{
    int16_t reading[8];
    int16_t weights[8] = {-7,-5,-3,-1,1,3,5,7};
    int32_t position = 0;
    int32_t total = 0;
    int16_t error;
    float pid_output;

    // Read sensor values
    for (int i = 0; i < 8; i++)
    {
        reading[i] = readADC(i);
        total += reading[i];
        position += reading[i] * weights[i];
    }

    if (total != 0)
    {
        int16_t line_position = position / total; // Calculate position error
        error = line_position;
    }
    else
    {
        // Line not detected, use previous error or set default
        error = previous_error;
    }

    // PID calculations
    integral += error;
    float derivative = error - previous_error;

    pid_output = Kp * error + Ki * integral + Kd * derivative;

    previous_error = error;

    // Implement control action using pid_output (e.g., adjust motor speeds)
    // For example:
    // setMotorSpeed(pid_output);

    // Debugging output
    printf("PID Output: %f\n", pid_output);
}