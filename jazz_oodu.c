
#include "jazz_oodu.h"
#include "main.h"
#include "stm32f4xx_hal.h" 
#include <stm32f4xx_hal_gpio.h>



#define MOTOR_A_PWM_CHANNEL TIM_CHANNEL_1
#define MOTOR_B_PWM_CHANNEL TIM_CHANNEL_2


void motor_init() {
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();


    GPIO_InitTypeDef GPIO_InitStruct = {0};

    
    GPIO_InitStruct.Pin = GPIO_PIN_15 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    
    HAL_TIM_PWM_Start(&htim1, MOTOR_A_PWM_CHANNEL);
    HAL_TIM_PWM_Start(&htim1, MOTOR_B_PWM_CHANNEL);
}



void setMotorSpeed(float motor_A_speed, float motor_B_speed) {
    
    motor_A_speed = (motor_A_speed < -100.0f) ? -100.0f : (motor_A_speed > 100.0f ? 100.0f : motor_A_speed);
    motor_B_speed = (motor_B_speed < -100.0f) ? -100.0f : (motor_B_speed > 100.0f ? 100.0f : motor_B_speed);


    if (motor_A_speed > 0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
    } else if (motor_A_speed < 0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
    }

    
    uint32_t motor_A_duty_cycle = (uint32_t)(fabs(motor_A_speed) * TIM1->ARR / 100.0);
    __HAL_TIM_SET_COMPARE(&htim1, MOTOR_A_PWM_CHANNEL, motor_A_duty_cycle);

    
    if (motor_B_speed > 0) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    } else if (motor_B_speed < 0) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    }

    
    uint32_t motor_B_duty_cycle = (uint32_t)(fabs(motor_B_speed) * TIM1->ARR / 100.0);
    __HAL_TIM_SET_COMPARE(&htim1, MOTOR_B_PWM_CHANNEL, motor_B_duty_cycle);
}

void jazz_oodu(float motor_A_speed, float motor_B_speed) {
    setMotorSpeed(motor_A_speed, motor_B_speed);
}
