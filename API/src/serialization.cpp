#include "serialization.h"
#include <cstdint>
#include <cstring>
#include <stdlib.h>

#include <iostream>
#include <ostream>

template <class T> union MessageInterpreter {
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

MSG_TO_PC *buffer_serialization_to_pc_msg(const uint8_t *buffer) {
  MSG_TO_PC *msg = (MSG_TO_PC *)malloc(sizeof(MSG_TO_PC));
  msg->id = convert<MSG_ID>(buffer);
  buffer += sizeof(MSG_ID);
  switch (msg->id) {
  case MSG_ID_STATE: {
    msg->status.sys_status = convert<uint8_t>(buffer);
    buffer += sizeof(uint8_t);
    msg->status.cellbal_1 = convert<uint8_t>(buffer);
    buffer += sizeof(uint8_t);
    msg->status.cellbal_2 = convert<uint8_t>(buffer);
    buffer += sizeof(uint8_t);
    msg->status.cellbal_3 = convert<uint8_t>(buffer);
    buffer += sizeof(uint8_t);
    msg->status.sys_ctrl_1 = convert<uint8_t>(buffer);
    buffer += sizeof(uint8_t);
    msg->status.sys_ctrl_2 = convert<uint8_t>(buffer);
    buffer += sizeof(uint8_t);
    msg->status.protect1 = convert<uint8_t>(buffer);
    buffer += sizeof(uint8_t);
    msg->status.protect2 = convert<uint8_t>(buffer);
    buffer += sizeof(uint8_t);
    msg->status.protect3 = convert<uint8_t>(buffer);
    buffer += sizeof(uint8_t);
    break;
  }
  case MSG_ID_BATTERY: {
    msg->battery.voltage = convert<uint16_t>(buffer);
    buffer += sizeof(uint16_t);
    msg->battery.current = convert<uint16_t>(buffer);
    buffer += sizeof(uint16_t);
    msg->battery.temperature.nt = convert<Number_of_Thermistors>(buffer);
    buffer += sizeof(Number_of_Thermistors);
    break;
  }
  case MSG_ID_CELLS: {

    msg->cells.noc = convert<Number_of_Cells>(buffer);
    buffer += sizeof(Number_of_Cells);
    for (int i = 0; i < MAX_CELLS_NUMBER; i++) {
      msg->cells.voltage[i] = convert<uint16_t>(buffer);
      buffer += sizeof(uint16_t);
    }
    break;
  }
  case MSG_ID_PROTECTION: {
    msg->protection.uv = convert<Protection>(buffer);
    buffer += sizeof(Protection);
    msg->protection.ov = convert<Protection>(buffer);
    buffer += sizeof(Protection);
    msg->protection.scd = convert<Protection>(buffer);
    buffer += sizeof(Protection);
    msg->protection.ocd = convert<Protection>(buffer);
    buffer += sizeof(Protection);
    break;
  }

  default:
    free(msg);
    return NULL;
  }
  return msg;
}

uint8_t *pc_msg_serialization_to_buffer(const MSG_TO_PC *msg) {
  uint8_t *buffer = (uint8_t *)malloc(sizeof(MSG_TO_PC));

  memcpy(buffer, msg, sizeof(MSG_TO_PC));

  return buffer;
}

MSG_TO_BMS *buffer_serialization_to_bms_msg(const uint8_t *buffer) {
  MSG_TO_BMS *msg = (MSG_TO_BMS *)malloc(sizeof(MSG_TO_BMS));
  msg->id = convert<MSG_ID>(buffer);
  buffer += sizeof(MSG_ID) + SIZE_GAP;
  switch (msg->id) {
  case MSG_ID_GET:

    break;
  case MSG_ID_SET:

    break;
  case MSG_ID_COMMUNICATION:

    break;

  default:
    break;
  }
  return msg;
}

uint8_t *bms_msg_serialization_to_buffer(const MSG_TO_BMS *msg) {
  uint8_t *buffer = (uint8_t *)malloc(sizeof(MSG_TO_BMS));
  memset(buffer, 0, sizeof(MSG_TO_BMS));

  memcpy(buffer, &msg->id, sizeof(MSG_ID));
  buffer += sizeof(MSG_ID);

  switch (msg->id) {
  case MSG_ID_GET: {
    memcpy(buffer, &msg->get_msg.name, sizeof(Get_Msg_Name));
    buffer += sizeof(Get_Msg_Name);
    memcpy(buffer, &msg->get_msg.special, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    break;
  }
  case MSG_ID_SET: {
    memcpy(buffer, &msg->set_msg.name, sizeof(Set_Msg_Name));
    buffer += sizeof(Set_Msg_Name);
    memcpy(buffer, &msg->set_msg.reg_value, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    break;
  }
  case MSG_ID_COMMUNICATION: {
    memcpy(buffer, &msg->communication, sizeof(Communication));
    buffer += sizeof(Communication);
    break;
  }

  default: {
    buffer -= sizeof(MSG_ID);
    free(buffer);
    return NULL;
  }
  }
  return buffer;
}
