
#include "com.h"
#include "stdlib.h"
#include "stm32f0xx_hal.h"
#include "string.h"

uint8_t rxdata[128];

static CMD *cmd;

void *convert(uint8_t *buffer, size_t size);
void add_cmd(const MSG_TO_BMS *msg);

void startUart(void) {
  extern UART_HandleTypeDef huart1;
  memset(rxdata, 0, sizeof(MSG_TO_BMS));

  cmd = (CMD *)malloc(sizeof(cmd));
  memset(cmd, 0, sizeof(CMD));
  cmd->empty = true;
  cmd->number_of_cmd = 0;

  HAL_UART_Receive_IT(&huart1, rxdata, sizeof(MSG_TO_BMS));
}

void serialized_msg(uint8_t *data) {
  MSG_TO_BMS *msg = (MSG_TO_BMS *)malloc(sizeof(MSG_TO_BMS));
  msg->id = *((MSG_ID *)convert(data, sizeof(MSG_ID)));
  data += sizeof(MSG_ID);
  switch (msg->id) {
  case MSG_ID_COMMUNICATION: {
    msg->communication =
        *((Communication *)convert(data, sizeof(Communication)));
    break;
  }
  case MSG_ID_GET: {
    msg->get_msg.name = *((Get_Msg_Name *)convert(data, sizeof(Get_Msg_Name)));
    data += sizeof(Get_Msg_Name);
    msg->get_msg.special = *((uint8_t *)convert(data, sizeof(uint8_t)));
    break;
  }
  case MSG_ID_SET: {
    msg->set_msg.name = *((Set_Msg_Name *)convert(data, sizeof(Set_Msg_Name)));
    data += sizeof(Set_Msg_Name);
    msg->set_msg.reg_value = *((uint8_t *)convert(data, sizeof(uint8_t)));
    break;
  }
  default: {
    msg = NULL;
    break;
  }
  }
  if (msg == NULL) {
    free(msg);
    return;
  }

  add_cmd(msg);
  free(msg);
}

uint8_t get_cmd_counter() { return cmd->number_of_cmd; }

MSG_TO_BMS *get_cmd() {
  MSG_TO_BMS *msg = (MSG_TO_BMS *)malloc(sizeof(MSG_TO_BMS));
  return msg;
}

bool cmd_is_empty() { return cmd->empty; }

void *convert(uint8_t *buffer, size_t size) {
  uint8_t *value = malloc(size);

  if (value == NULL) {
    // error
    return NULL;
  }
  for (int i = 0; i < size; i++) {
    value[i] = buffer[i];
  }
  return (void *)value;
}

void add_cmd(const MSG_TO_BMS *msg) {
  // copy msg to cmd list
  if (cmd->number_of_cmd < MAX_CMD_COUNT) {
    cmd->number_of_cmd++;
    memcpy(&cmd->msg[cmd->number_of_cmd], msg, sizeof(MSG_TO_BMS));
    if (cmd->empty != true) {
      cmd->empty = true;
    }
  }
}
