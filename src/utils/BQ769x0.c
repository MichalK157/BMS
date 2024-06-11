
#include "BQ769x0.h"
#include "stm32f0xx_hal.h"
#include "main.h"

static BQ769_Config* config;
extern I2C_HandleTypeDef hi2c1;

uint8_t read_register(uint8_t address, BQ769_Register reg)
{
	uint8_t value = 0;
	uint8_t regg = reg;
	HAL_I2C_Master_Transmit(&hi2c1, (address <<1), &regg, sizeof(uint8_t), HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, (address <<1), &value, sizeof(uint8_t), HAL_MAX_DELAY);
	return value;
}

void write_register(uint8_t address, BQ769_Register reg, uint8_t value)
{
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(address << 1), (uint16_t)reg, 1, &value, sizeof(value), HAL_MAX_DELAY);
}

void set_configuration(uint8_t address)
{
	HAL_GPIO_WritePin(ALERT_GPIO_Port, ALERT_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);
	write_register(address, BQ769_REG_SYS_STAT, 0xBF);
	HAL_Delay(1);
	write_register(address, BQ769_REG_CELLBAL_1, CB1 | CB2 | CB3 | CB5);
	HAL_Delay(1);
	write_register(address, BQ769_REG_SYS_CTRL1, 0x18); // 0x19 0x1A shutdown sequence
	HAL_Delay(1);
	write_register(address, BQ769_REG_SYS_CTRL2, 0xC0);
	HAL_Delay(1);
	write_register(address, BQ769_REG_PROTECT_1, 0x9d);
	HAL_Delay(1);
	write_register(address, BQ769_REG_PROTECT_2, 0x5f);
	HAL_Delay(1);
	write_register(address, BQ769_REG_PROTECT_3, 0xb0);
	HAL_Delay(1);
	write_register(address, BQ769_REG_OV_TRIP, 0xDC); //AC
	HAL_Delay(1);
	write_register(address, BQ769_REG_UV_TRIP, 0x97);
	HAL_Delay(1);
	write_register(address, BQ769_REG_CC_CFG, 0X19);
	HAL_Delay(10);
}

void get_configuration(uint8_t address)
{
	uint8_t sys_stat = read_register(address, BQ769_REG_SYS_STAT);
	HAL_Delay(1);
	uint8_t cellbal_1 = read_register(address, BQ769_REG_CELLBAL_1);
	HAL_Delay(1);
	uint8_t cellbal_2 = read_register(address, BQ769_REG_CELLBAL_2);
	HAL_Delay(1);
	uint8_t cellbal_3 = read_register(address, BQ769_REG_CELLBAL_3);
	HAL_Delay(1);
	uint8_t sys_ctrl1 = read_register(address, BQ769_REG_SYS_CTRL1);
	HAL_Delay(3);
	uint8_t sys_ctrl2 = read_register(address, BQ769_REG_SYS_CTRL2);
	HAL_Delay(3);
	uint8_t protect1 = read_register(address, BQ769_REG_PROTECT_1);
	HAL_Delay(3);
	uint8_t protect2 = read_register(address, BQ769_REG_PROTECT_2);
	HAL_Delay(3);
	uint8_t protect3 = read_register(address, BQ769_REG_PROTECT_3);
	HAL_Delay(3);
	uint8_t ov_trip = read_register(address, BQ769_REG_OV_TRIP);
	HAL_Delay(3);
	uint8_t uv_trip = read_register(address, BQ769_REG_UV_TRIP);
	HAL_Delay(3);
	uint8_t cc_cfg = read_register(address, BQ769_REG_CC_CFG);

}
