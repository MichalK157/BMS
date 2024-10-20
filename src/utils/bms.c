
#include "bms.h"
#include "../proto/protocol.h"
#include "BQ769x0.h"
#include "com.h"
#include "main.h"
#include "stdlib.h"
#include "string.h"

#if STM32F031x6
#include "stm32f0xx_hal.h"

#elif STM32L432xx
#include "stm32l4xx_hal.h"
#endif

uint8_t bms(void)
{
    extern UART_HandleTypeDef huart1;
    MSG_TO_PC* msg = (MSG_TO_PC*)malloc(sizeof(MSG_TO_PC));
    while(1)
    {

        read_sys_status();
        read_current();
        read_voltage(communication_is_enable());
        read_load(communication_is_enable());
        read_cells(communication_is_enable());
        balancing_cells();

        if(communication_is_enable())
        {

            memset(msg, 0, sizeof(MSG_TO_PC));
            msg->id = MSG_ID_BATTERY;
            get_battery(&msg->battery);
            HAL_UART_Transmit(&huart1, (uint8_t*)msg, sizeof(MSG_TO_PC), 100);
        }
        HAL_Delay(1000);
    }
    return 0;
}

void bms_init(void)
{

    set_configuration(BQ769200_ADDRESS);
    init_battery();
    startUart();
}
