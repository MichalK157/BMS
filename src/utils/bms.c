
#include "bms.h"
#include "main.h"
#include "string.h"
#include "BQ769x0.h"
#include "../proto/protocol.h"


uint8_t bms(void)
{
	// INITIALISATION
	static Battery* battery;
	static Cells* cells;
	static Temperature* temperature;
	memset(battery,0, sizeof(Battery));
	memset(cells, 0, sizeof(Cells));
	memset(temperature, 0 ,sizeof(Temperature));

	cells->noc = MAX_CELLS_NUMBER;
	temperature->not = MAX_THERMISTORS_NUMBER;

	set_configuration(BQ769200_ADDRESS);
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
		
		read_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT);
		read_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL1);
		
		HAL_Delay(250);
	}
	return -1; // if something goes wrong
}
