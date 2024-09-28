#include "protocol.h"

MSG_TO_PC *buffer_serialization_to_pc_msg(const uint8_t *buffer);
uint8_t *bms_msg_serialization_to_buffer(const MSG_TO_BMS *msg);
