
#include "com.h"
#include "stdlib.h"
#include "string.h"

#if STM32F031x6
#include "stm32f0xx_hal.h"

#elif STM32L432xx
#include "stm32l4xx_hal.h"
#endif

uint8_t rxdata[128];

static CMD* cmd;
volatile bool communication;

// to do : remove convert use projecting
void* convert(uint8_t* buffer, size_t size);
void add_cmd(const MSG_TO_BMS* msg);

void startUart(void)
{
    extern UART_HandleTypeDef huart1;
    memset(rxdata, 0, sizeof(MSG_TO_BMS));

    cmd = (CMD*)malloc(sizeof(cmd));
    memset(cmd, 0, sizeof(CMD));
    cmd->empty = true;
    cmd->number_of_cmd = 0;

    communication = false;

    HAL_UART_Receive_IT(&huart1, rxdata, sizeof(MSG_TO_BMS));
}

void serialized_msg(uint8_t* data)
{
    MSG_TO_BMS* msg = (MSG_TO_BMS*)malloc(sizeof(MSG_TO_BMS));
    memcpy(msg, data, sizeof(MSG_TO_BMS));
    // msg->id = *((MSG_ID *)convert(data, sizeof(MSG_ID)));
    // data += sizeof(MSG_ID);
    switch(msg->id)
    {
        case MSG_ID_COMMUNICATION:
        {
            // msg->communication =*((Communication *)convert(data,
            // sizeof(Communication)));
            if(msg->communication == Communication_Init)
            {
                communication = true;
            }
            else
            {
                communication = false;
            }
            break;
        }
        case MSG_ID_GET:
        {
            add_cmd(msg);
            break;
        }
        case MSG_ID_SET:
        {
            add_cmd(msg);
            break;
        }
        default:
        {
            msg = NULL;
            break;
        }
    }

    if(msg == NULL)
    {
        free(msg);
        return;
    }

    free(msg);
}

uint8_t get_cmd_counter()
{
    return cmd->number_of_cmd;
}

MSG_TO_BMS* get_cmd()
{
    if(!cmd->empty)
    {
        return NULL;
    }

    MSG_TO_BMS* msg = (MSG_TO_BMS*)malloc(sizeof(MSG_TO_BMS));
    memcpy(msg, &cmd->msg[0], sizeof(MSG_TO_BMS));

    for(int i = 0; i < cmd->number_of_cmd - 1; i++)
    {
        memset(&cmd->msg[i], 0, sizeof(MSG_TO_BMS));
        memcpy(&cmd->msg[i], &cmd->msg[i + 1], sizeof(MSG_TO_BMS));
    }
    cmd->number_of_cmd--;

    if(cmd->number_of_cmd == 0)
    {
        cmd->empty = true;
    }
    return msg;
}

bool cmd_is_empty()
{
    return cmd->empty;
}

/*void *convert(uint8_t *buffer, size_t size) {
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
*/
void add_cmd(const MSG_TO_BMS* msg)
{
    // copy msg to cmd list
    if(cmd->number_of_cmd < MAX_CMD_COUNT)
    {
        cmd->number_of_cmd++;
        memcpy(&cmd->msg[cmd->number_of_cmd], msg, sizeof(MSG_TO_BMS));
        if(cmd->empty != true)
        {
            cmd->empty = true;
        }
    }
}

bool communication_is_enable(void)
{
    return communication;
}
