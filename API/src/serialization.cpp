#include "serialization.h"
#include <cstdint>
#include <cstring>
#include <stdlib.h>

#include <iostream>
#include <ostream>

/*template <class T> union MessageInterpreter {
  T value;
  uint8_t tab[sizeof(T)];
};

template <class T> T convert(const uint8_t *buffer) {
  MessageInterpreter<T> message;

  for (int i = 0; i < sizeof(T); ++i) {
    message.tab[i] = buffer[i];
  }
  return message.value;
}
*/

MSG_TO_PC *buffer_serialization_to_pc_msg(const uint8_t *buffer) {
  MSG_TO_PC *msg = (MSG_TO_PC *)malloc(sizeof(MSG_TO_PC));
  memset(msg, 0, sizeof(MSG_TO_PC));
  memcpy(msg, buffer, sizeof(MSG_TO_PC));
  return msg;
}

uint8_t *bms_msg_serialization_to_buffer(const MSG_TO_BMS *msg) {
  uint8_t *buffer = (uint8_t *)malloc(sizeof(MSG_TO_BMS));
  memset(buffer, 0, sizeof(MSG_TO_BMS));
  memcpy(buffer, msg, sizeof(MSG_TO_BMS));
  return buffer;
}
