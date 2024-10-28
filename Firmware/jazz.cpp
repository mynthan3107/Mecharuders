#include "jazz.h"
#include "motor.h"
#include "ir_sensor.h"
#include "string"

using namespace std;

uint8_t rx[1];
uint8_t data1[] = "Hi\n";

void print(string msg);

void loop()
{
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    //  HAL_Delay(100);
    //float adj = line_ah_thedu();
    //jazz_oadu(60 + adj, 60 - adj);
    // HAL_UART_Transmit(&huart1, data, 3, 100);
    string hel = "Hello\n";
    print(hel);
    HAL_Delay(300);
}

void setup()
{
    motor_init();
    HAL_UART_Receive_IT(&huart1, rx, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static string rx_data;
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    HAL_UART_Receive_IT(&huart1, rx, 1);
    if (rx[0] == '\n')
        HAL_UART_Transmit(&huart1, data1, 3, 100);
    rx_data += rx[0];
}

void print(string msg)
{
    uint8_t n = msg.length();
    uint8_t msg_[100];
    for (int i = 0; i <n ; i++)
    {
        msg_[i] = msg[i];
    }
    HAL_UART_Transmit(&huart1, msg_, n, 100);
}