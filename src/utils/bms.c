
#include "bms.h"
#include "main.h"
#include "stdlib.h"
#include "BQ769x0.h"
#include "../proto/protocol.h"

static Battery* battery;
static Cells* cells;
static Temperature* temperature;
static uint8_t load = 0;
static uint8_t charge = 0;

uint8_t bms(void)
{
	// INITIALISATION
	battery = malloc(sizeof(Battery));
	cells = malloc(sizeof(Cells));
	temperature = malloc(sizeof(Temperature));

	cells->noc = 5;
	temperature->not = 1;

	set_configuration(BQ769200_ADDRESS);
	//write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xc2);
	write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xc1);
	while(1)
	{
		battery->voltages = (read_register(BQ769200_ADDRESS, BQ769_REG_BAT_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_BAT_LO);
		battery->current = (read_register(BQ769200_ADDRESS, BQ769_REG_CC_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_CC_LO);
		for(uint8_t i = 0; i < MAX_CELLS_NUMBER; i++)
		{
			cells->voltage[i] = (read_register(BQ769200_ADDRESS, BQ769_REG_VC1_HI | i) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC1_LO | i);
		}
		for(uint8_t i = 0; i< MAX_THERMISTORS_NUMBER; i++)
		{
			temperature->temperature[i] = (read_register(BQ769200_ADDRESS, BQ769_REG_TS1_HI | i) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_TS1_LO| i);
		}
		
		if(read_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT) == 0x84)
		{
			write_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT, 0xBF);
			write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xc1);
		}

		/*
		if(read_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL1) & 0x80)
		{
			if(load == 0)
			{
				charge = 0;
				write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xc2);
			}
			load = 1;
			//write_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT, 0xBF);
		}
		else
		{
			if(charge == 0)
			{
				load = 0;
				write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xc1);
				write_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT, 0xBF);
			}
			charge = 1;
		}*/
		//read_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT);
		
		HAL_Delay(250);
	}
	return -1; // if something goes wrong
}
