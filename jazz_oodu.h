
#ifndef JAZZ_OODU_H
#define JAZZ_OODU_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
//#include "adc.h"
//#include "usart.h"
//#include "gpio.h"
#include "stm32f4xx_hal_gpio.h"
#include "main.h"

void motor_init();
void jazz_oodu(float motor_A_speed, float motor_B_speed);

#endif 
