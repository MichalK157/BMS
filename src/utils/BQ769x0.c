
#include "BQ769x0.h"
#include "stm32f0xx_hal.h"

static BQ769_Config* config;
extern I2C_HandleTypeDef hi2c1;

uint8_t read_register(uint8_t address, BQ769_Register reg)
{
	uint8_t value;
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t)address, (uint16_t)reg, 1, &value, sizeof(value), HAL_MAX_DELAY);
	return value;
}

void write_register(uint8_t address, BQ769_Register reg, uint8_t value)
{
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t)address, (uint16_t)reg, 1, &value, sizeof(value), HAL_MAX_DELAY);
}

void get_configuration(uint8_t address)
{
	config->sys_stat = read_register(address, BQ769_REG_SYS_STAT);
	// ...
}
