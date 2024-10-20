
#ifndef IRQ_UART_IRQ_H_
#define IRQ_UART_IRQ_H_

#if STM32F031x6
#include "stm32f0xx_hal.h"

#elif STM32L432xx
#include "stm32l4xx_hal.h"
#endif

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);

#endif /* IRQ_UART_IRQ_H_ */
