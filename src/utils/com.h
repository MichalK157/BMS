/*
 * com.h
 *
 *  Created on: Jun 20, 2024
 *      Author: mkac
 */

#ifndef UTILS_COM_H_
#define UTILS_COM_H_

#include "../proto/protocol.h"
#include "stdbool.h"
#include "stdint.h"

#define MAX_CMD_COUNT 5

typedef struct _CMD {
  bool empty;
  uint8_t number_of_cmd;
  MSG_TO_BMS msg[MAX_CMD_COUNT];
} CMD;

void startUart(void);
void serialized_msg(uint8_t *data);
uint8_t get_cmd_counter();
bool cmd_is_empty();
MSG_TO_BMS *get_cmd();
bool communication_is_enable(void);

#endif /* UTILS_COM_H_ */
