
#include "bms.h"
#include "../proto/protocol.h"
#include "BQ769x0.h"
#include "com.h"
#include "main.h"
#include "stdlib.h"
#include "stm32f0xx_hal.h"
#include "string.h"

static Battery *battery;
static Cells *cells;


uint8_t bms(void) {
  extern UART_HandleTypeDef huart1;

  // INITIALISATION
  battery = malloc(sizeof(Battery));
  cells = malloc(sizeof(Cells));
  MSG_TO_PC *msg = (MSG_TO_PC *)malloc(sizeof(MSG_TO_PC));
  memset(msg, 0, sizeof(MSG_TO_PC));
  cells->noc = Number_of_Cells_5;
  battery->temperature.nt = Number_of_Thermistors_1;
  startUart();
  set_configuration(BQ769200_ADDRESS);
  // write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xc3);
  //  write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xc1);
  while (1) {

    if (read_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT) == 0x84) {
      // write_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT, 0xBF);
      //  write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xc1);
    }

    if (communication_is_enable()) {
      battery->voltage =
          (read_register(BQ769200_ADDRESS, BQ769_REG_BAT_HI) << 8) |
          read_register(BQ769200_ADDRESS, BQ769_REG_BAT_LO);
      battery->current =
          (read_register(BQ769200_ADDRESS, BQ769_REG_CC_HI) << 8) |
          read_register(BQ769200_ADDRESS, BQ769_REG_CC_LO);

      cells->voltage[0] =
          0x3FFF & ((read_register(BQ769200_ADDRESS, BQ769_REG_VC1_HI) << 8) |
                    read_register(BQ769200_ADDRESS, BQ769_REG_VC1_LO));

      cells->voltage[1] =
          0x3FFF & ((read_register(BQ769200_ADDRESS, BQ769_REG_VC2_HI) << 8) |
                    read_register(BQ769200_ADDRESS, BQ769_REG_VC2_LO));

      cells->voltage[2] =
          0x3FFF & ((read_register(BQ769200_ADDRESS, BQ769_REG_VC3_HI) << 8) |
                    read_register(BQ769200_ADDRESS, BQ769_REG_VC3_LO));

      cells->voltage[3] =
          0x3FFF & ((read_register(BQ769200_ADDRESS, BQ769_REG_VC4_HI) << 8) |
                    read_register(BQ769200_ADDRESS, BQ769_REG_VC4_LO));

      cells->voltage[4] =
          0x3FFF & ((read_register(BQ769200_ADDRESS, BQ769_REG_VC5_HI) << 8) |
                    read_register(BQ769200_ADDRESS, BQ769_REG_VC5_LO));

      memset(msg, 0, sizeof(MSG_TO_PC));
      msg->id = MSG_ID_CELLS;
      memcpy(&msg->cells, cells, sizeof(Cells));
      HAL_UART_Transmit(&huart1, (uint8_t *)msg, sizeof(MSG_TO_PC), 100);
      HAL_Delay(100);

      battery->voltage =
          ((read_register(BQ769200_ADDRESS, BQ769_REG_BAT_HI) << 8) |
           read_register(BQ769200_ADDRESS, BQ769_REG_BAT_LO));
      if (read_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL1) & 0x80) {
        battery->load = LOAD_detect;
        battery->current =
            ((read_register(BQ769200_ADDRESS, BQ769_REG_CC_HI) << 8) |
             read_register(BQ769200_ADDRESS, BQ769_REG_CC_LO));
      } else {
        battery->load = LOAD_not_detect;
        battery->current = 0;
      }
      battery->temperature.temperature[0] =
          0x3FFF & ((read_register(BQ769200_ADDRESS, BQ769_REG_TS1_HI) << 8) |
                    read_register(BQ769200_ADDRESS, BQ769_REG_TS1_LO));

      memset(msg, 0, sizeof(MSG_TO_PC));
      msg->id = MSG_ID_BATTERY;
      memcpy(&msg->cells, battery, sizeof(Battery));
      HAL_UART_Transmit(&huart1, (uint8_t *)msg, sizeof(MSG_TO_PC), 100);
    }
    HAL_Delay(900);
  }
  return -1; // if something goes wrong
}
