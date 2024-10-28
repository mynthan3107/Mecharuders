#include "motor.h"

#define MOTOR_A_PWM_CHANNEL TIM_CHANNEL_1
#define MOTOR_B_PWM_CHANNEL TIM_CHANNEL_2

void motor_init()
{
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
}

void setMotorSpeed(float motor_A_speed, float motor_B_speed)
{
    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    motor_A_speed = (motor_A_speed < -100.0f) ? -100.0f : (motor_A_speed > 100.0f ? 100.0f : motor_A_speed);
    motor_B_speed = (motor_B_speed < -100.0f) ? -100.0f : (motor_B_speed > 100.0f ? 100.0f : motor_B_speed);

    uint32_t motor_A_duty_cycle = (uint32_t)(fabs(motor_A_speed) * 1024 / 100.0);
    uint32_t motor_B_duty_cycle = (uint32_t)(fabs(motor_B_speed) * 1024 / 100.0);

    sConfigOC.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
    sConfigOC.Pulse = motor_A_duty_cycle;
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);

    if (motor_A_speed > 0)
    {
        sConfigOC.Pulse = motor_A_duty_cycle;
        HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
        sConfigOC.Pulse = 0;
        HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
    }
    else if (motor_A_speed < 0)
    {
        sConfigOC.Pulse = 0;
        HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
        sConfigOC.Pulse = motor_A_duty_cycle;
        HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
    }

    if (motor_B_speed > 0)
    {
        sConfigOC.Pulse = 0;
        HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
        sConfigOC.Pulse = motor_B_duty_cycle;
        HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
    }
    else if (motor_B_speed < 0)
    {
        sConfigOC.Pulse = motor_B_duty_cycle;
        HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
        sConfigOC.Pulse = 0;
        HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    }
}

void jazz_oadu(float motor_A_speed, float motor_B_speed)
{
    setMotorSpeed(motor_A_speed, motor_B_speed);
}
