
#include "uart_irq.h"
#include "../proto/protocol.h"
#include "../utils/com.h"
#include "string.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  extern uint8_t rxdata[128];

  serialized_msg(rxdata);
  memset(rxdata, 0, sizeof(MSG_TO_BMS));
  HAL_UART_Receive_IT(huart, rxdata, sizeof(MSG_TO_BMS));
}
