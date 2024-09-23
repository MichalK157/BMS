
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
static Status *status;

uint8_t bms(void) {
  extern UART_HandleTypeDef huart1;
  bool is_charge = false;
  bool is_balancer_on = false;
  MSG_TO_PC *msg = (MSG_TO_PC *)malloc(sizeof(MSG_TO_PC));
  memset(msg, 0, sizeof(MSG_TO_PC));

  uint8_t stat = read_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT);
  if (stat != 0x80) {
    memset(status, 0, sizeof(Status));
    memset(msg, 0, sizeof(MSG_TO_PC));
    status->sys_status = stat;
    msg->id = MSG_ID_STATE;
    memcpy(&msg->status, status, sizeof(Status));
    HAL_UART_Transmit(&huart1, (uint8_t *)msg, sizeof(MSG_TO_PC), 100);
    write_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT, 0xBF);
    // to do detection type of error
    write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xC3);
  }
  battery->current = (read_register(BQ769200_ADDRESS, BQ769_REG_CC_HI) << 8) |
                     read_register(BQ769200_ADDRESS, BQ769_REG_CC_LO);
  if (battery->current > 0x0000) {
    is_charge = true;
  } else {
    is_charge = false;
  }

  if (is_charge && !is_balancer_on) {
    // balancer on
    is_balancer_on = true;
    write_register(address, BQ769_REG_CELLBAL_1, 0x1f); // for 5 cells
    // To Do : add to defines balancer cells depend of config
  } else if (!is_charge && is_balancer_on) {
    is_balancer_on = false;
    write_register(address, BQ769_REG_CELLBAL_1, 0x1f);
  }

  if (communication_is_enable()) {

    battery->voltage =
        (read_register(BQ769200_ADDRESS, BQ769_REG_BAT_HI) << 8) |
        read_register(BQ769200_ADDRESS, BQ769_REG_BAT_LO);

    battery->temperature.temperature[0] =
        0x3FFF & ((read_register(BQ769200_ADDRESS, BQ769_REG_TS1_HI) << 8) |
                  read_register(BQ769200_ADDRESS, BQ769_REG_TS1_LO));

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

    if (read_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL1) && 0x80) {
      battery->load = LOAD_detect;
    } else {
      battery->load = LOAD_not_detect;
      battery->current = 0;
    }
    memset(msg, 0, sizeof(MSG_TO_PC));
    msg->id = MSG_ID_BATTERY;
    memcpy(&msg->cells, battery, sizeof(Battery));
    HAL_UART_Transmit(&huart1, (uint8_t *)msg, sizeof(MSG_TO_PC), 100);
  }
  return 0;
}

void bms_init(void) {

  battery = malloc(sizeof(Battery));
  cells = malloc(sizeof(Cells));
  status = malloc(sizeof(Status));
  cells->noc = Number_of_Cells_5;
  battery->temperature.nt = Number_of_Thermistors_1;
  set_configuration(BQ769200_ADDRESS);

  startUart();
}
