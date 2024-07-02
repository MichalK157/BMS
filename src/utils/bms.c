
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
static Temperature *temperature;

uint8_t bms(void) {
  extern UART_HandleTypeDef huart1;

  // INITIALISATION
  battery = malloc(sizeof(Battery));
  cells = malloc(sizeof(Cells));
  temperature = malloc(sizeof(Temperature));
  MSG_TO_PC *msg = (MSG_TO_PC *)malloc(sizeof(MSG_TO_PC));

  cells->noc = Number_of_Cells_5;
  temperature->nt = Number_of_Thermistors_1;
  startUart();
  set_configuration(BQ769200_ADDRESS);
  write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xc3);
  // write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xc1);
  while (1) {
    if (communication_is_enable()) {
      battery->voltage =
          (read_register(BQ769200_ADDRESS, BQ769_REG_BAT_HI) << 8) |
          read_register(BQ769200_ADDRESS, BQ769_REG_BAT_LO);
      battery->current =
          (read_register(BQ769200_ADDRESS, BQ769_REG_CC_HI) << 8) |
          read_register(BQ769200_ADDRESS, BQ769_REG_CC_LO);

      /*
       for (uint8_t i = 0; i < MAX_CELLS_NUMBER; i++) {
        cells->voltage[i] =
            0x3FFF &
            ((read_register(BQ769200_ADDRESS, BQ769_REG_VC1_HI | i) << 8) |
             read_register(BQ769200_ADDRESS, BQ769_REG_VC1_LO | i));
        HAL_Delay(2);
      }
      */
      // h = read_register(BQ769200_ADDRESS, BQ769_REG_VC1_HI);
      // l = read_register(BQ769200_ADDRESS, BQ769_REG_VC1_LO );
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

      temperature->temperature[0] =
          0x3FFF & ((read_register(BQ769200_ADDRESS, BQ769_REG_TS1_HI) << 8) |
                    read_register(BQ769200_ADDRESS, BQ769_REG_TS1_LO));
      HAL_Delay(2);

      if (read_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT) == 0x84) {
        write_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT, 0xBF);
        // write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xc1);
      }

      msg->id = MSG_ID_CELLS;
      memcpy(&msg->cells, cells, sizeof(Cells));

      HAL_UART_Transmit(&huart1, (uint8_t *)msg, sizeof(MSG_TO_PC), 100);
      /*
      if(read_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL1) & 0x80)
      {
              if(load == 0)
              {
                      charge = 0;
                      write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2,
      0xc2);
              }
              load = 1;
              //write_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT, 0xBF);
      }
      else
      {
              if(charge == 0)
              {
                      load = 0;
                      write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2,
      0xc1); write_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT, 0xBF);
              }
              charge = 1;
      }*/
      // read_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT);
    }
    HAL_Delay(1000);
  }
  return -1; // if something goes wrong
}
