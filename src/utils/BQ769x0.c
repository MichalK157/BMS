
#include "BQ769x0.h"
#include "main.h"
#include "stm32f0xx_hal.h"
#include "stdlib.h"

static BQ769_Config *config;
extern I2C_HandleTypeDef hi2c1;

uint8_t read_register(uint8_t address, BQ769_Register reg) {
  uint8_t value = 0;
  uint8_t regg = reg;
  HAL_I2C_Master_Transmit(&hi2c1, (address << 1), &regg, sizeof(uint8_t),
                          HAL_MAX_DELAY);
  HAL_I2C_Master_Receive(&hi2c1, (address << 1), &value, sizeof(uint8_t),
                         HAL_MAX_DELAY);
  return value;
}

void write_register(uint8_t address, BQ769_Register reg, uint8_t value) {
  HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(address << 1), (uint16_t)reg, 1, &value,
                    sizeof(value), 100);
}

void set_configuration(uint8_t address) {
  HAL_GPIO_WritePin(ALERT_GPIO_Port, ALERT_Pin, GPIO_PIN_RESET);
  HAL_Delay(5);
  write_register(address, BQ769_REG_SYS_STAT, 0xBF);
  HAL_Delay(1);
  write_register(address, BQ769_REG_CELLBAL_1, 0x00); //0x00 off, 0x13 3 cells, 0x17 4 cells, 0x1f 5calls
  HAL_Delay(1);
  write_register(address, BQ769_REG_SYS_CTRL1,0x18); // 0x19 0x1A shutdown sequence
  HAL_Delay(1);
  write_register(address, BQ769_REG_SYS_CTRL2, 0xC0); //0xc0 off 0xc1 load 0xc2 charge
  HAL_Delay(1);
  write_register(address, BQ769_REG_PROTECT_1, 0x9d);
  HAL_Delay(1);
  write_register(address, BQ769_REG_PROTECT_2, 0x59);
  HAL_Delay(1);
  write_register(address, BQ769_REG_PROTECT_3, 0xb0);
  HAL_Delay(1);
  write_register(address, BQ769_REG_OV_TRIP, 0xDC); // AC
  HAL_Delay(1);
  write_register(address, BQ769_REG_UV_TRIP, 0x97);
  HAL_Delay(1);
  write_register(address, BQ769_REG_CC_CFG, 0X19);
  HAL_Delay(10);
}

void get_configuration(uint8_t address) {
	config = (BQ769_Config*)malloc(sizeof(BQ769_Config));
	config->sys_stat = read_register(address, BQ769_REG_SYS_STAT);
	HAL_Delay(1);
	config->cellbal_1 = read_register(address, BQ769_REG_CELLBAL_1);
	HAL_Delay(1);
	config->cellbal_2 = read_register(address, BQ769_REG_CELLBAL_2);
	HAL_Delay(1);
	config->cellbal_3 = read_register(address, BQ769_REG_CELLBAL_3);
	HAL_Delay(1);
	config->sys_ctrl1 = read_register(address, BQ769_REG_SYS_CTRL1);
	HAL_Delay(3);
	config->sys_ctrl2 = read_register(address, BQ769_REG_SYS_CTRL2);
	HAL_Delay(3);
	config->protect1= read_register(address, BQ769_REG_PROTECT_1);
	HAL_Delay(3);
	config->protect2 = read_register(address, BQ769_REG_PROTECT_2);
	HAL_Delay(3);
	config->protect3 = read_register(address, BQ769_REG_PROTECT_3);
	HAL_Delay(3);
	config->ov_trip = read_register(address, BQ769_REG_OV_TRIP);
	HAL_Delay(3);
	config->uv_trip = read_register(address, BQ769_REG_UV_TRIP);
	HAL_Delay(3);
	config->cc_cfg = read_register(address, BQ769_REG_CC_CFG);
}
