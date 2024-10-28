#include "ir_sensor.h"

uint16_t readADC(uint8_t pin)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    uint16_t adc_val = 0;
    if (pin == 7)
        pin = -1;
    pin = pin + 1;

    pin = 7 - pin;

    if (pin >= 0 && pin <= 7)
    {
        switch (pin)
        {
        case 0:
            sConfig.Channel = ADC_CHANNEL_0;
            break;
        case 1:
            sConfig.Channel = ADC_CHANNEL_1;
            break;
        case 2:
            sConfig.Channel = ADC_CHANNEL_2;
            break;
        case 3:
            sConfig.Channel = ADC_CHANNEL_3;
            break;
        case 4:
            sConfig.Channel = ADC_CHANNEL_4;
            break;
        case 5:
            sConfig.Channel = ADC_CHANNEL_5;
            break;
        case 6:
            sConfig.Channel = ADC_CHANNEL_6;
            break;
        case 7:
            sConfig.Channel = ADC_CHANNEL_7;
            break;
        default:
            return 0;
        }

        sConfig.Rank = 1;
        sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;

        if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
        {
            Error_Handler();
        }

        HAL_ADC_Start(&hadc1);

        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
        {
            adc_val = HAL_ADC_GetValue(&hadc1);
        }

        HAL_ADC_Stop(&hadc1);
    }

    return adc_val;
}

// Read sensor values

float line_ah_thedu()
{
    int16_t reading[8];
    int16_t weights[8] = {-7, -5, -3, -1, 1, 3, 5, 7};
    int32_t position = 0;
    int32_t total = 0;
    float error;
    static int16_t previous_error;
    static int16_t integral;
    float pid_output;

    for (int i = 0; i < 8; i++)
    {
        reading[i] = 4096 - readADC(i);
        total += reading[i];
        position += reading[i] * weights[i];
    }

    if (total < 100)
        total = 100;

    error = (float)position / total; // Calculate position error

    integral = integral + error;
    integral = (integral < -20.0f) ? -20.0f : (integral > 20.0f ? 20.0f : integral);
    float derivative = error - previous_error;

    pid_output = 7 * error + 0.1 * integral + 5 * derivative;

    previous_error = error;

    // Implement control action using pid_output (e.g., adjust motor speeds)
    // For example:
    // setMotorSpeed(pid_output);

    // Debugging output
    // printf("PID Output: %d\n", (int)(error*100));
    // for (int a = 0; a < 8; a++)
    // {
    //     reading[a] = 4096-readADC(a);
    //     printf("%d\t", reading[a]);
    // }
    // printf("\n");
    return pid_output;
}