
#ifndef IRQ_UART_IRQ_H_
#define IRQ_UART_IRQ_H_

#include "stm32f0xx_hal.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* IRQ_UART_IRQ_H_ */
