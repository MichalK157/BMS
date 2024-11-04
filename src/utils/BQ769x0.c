
#include "BQ769x0.h"
#include "main.h"
#include "stdlib.h"
#include "string.h"

#if STM32F031x6
#include "stm32f0xx_hal.h"

#elif STM32L432xx
#include "stm32l4xx_hal.h"
#endif

static BQ769_Config* config;
static Battery* battery;
static uint8_t* cbals;
uint16_t cell_min_v;
uint8_t valltowri;

static void set_battery_status(Battery_Status);
static uint8_t read_register(uint8_t address, BQ769_Register register);
static void write_register(uint8_t address, BQ769_Register register, uint8_t value);

uint8_t read_register(uint8_t address, BQ769_Register reg)
{
    extern I2C_HandleTypeDef hi2c1;
    uint8_t value = 0;
    uint8_t regg = reg;
    HAL_I2C_Master_Transmit(&hi2c1, (address << 1), &regg, sizeof(uint8_t), HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, (address << 1), &value, sizeof(uint8_t), HAL_MAX_DELAY);
    return value;
}

void write_register(uint8_t address, BQ769_Register reg, uint8_t value)
{
    extern I2C_HandleTypeDef hi2c1;
    HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(address << 1), (uint16_t)reg, 1, &value, sizeof(value), 100);
}

void set_configuration(uint8_t address)
{
    HAL_GPIO_WritePin(ALTER_GPIO_Port, ALTER_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    write_register(address, BQ769_REG_SYS_STAT, 0xBF);
    HAL_Delay(1);
    write_register(address, BQ769_REG_CELLBAL_1,
                   0x00); // 0x00 off, 0x13 3 cells, 0x17 4 cells, 0x1f 5calls
    HAL_Delay(1);
    write_register(address, BQ769_REG_SYS_CTRL1,
                   0x18); // 0x19 0x1A shutdown sequence
    HAL_Delay(1);
    write_register(address, BQ769_REG_SYS_CTRL2,
                   0xC3); // 0xc0 off 0xc1 load 0xc2 charge
    HAL_Delay(1);
    write_register(address, BQ769_REG_PROTECT_1, 0x94);
    HAL_Delay(1);
    write_register(address, BQ769_REG_PROTECT_2, 0x5f);
    HAL_Delay(1);
    write_register(address, BQ769_REG_PROTECT_3, 0x50);
    HAL_Delay(1);
    write_register(address, BQ769_REG_OV_TRIP, 0xAF); // AC
    HAL_Delay(1);
    write_register(address, BQ769_REG_UV_TRIP, 0xEA);
    HAL_Delay(1);
    write_register(address, BQ769_REG_CC_CFG, 0X19);
    HAL_Delay(10);
}

void get_configuration(uint8_t address)
{
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
    config->protect1 = read_register(address, BQ769_REG_PROTECT_1);
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

void init_battery()
{
    battery = (Battery*)malloc(sizeof(Battery));
    memset(battery, 0, sizeof(Battery));
    battery->battery_status = Battery_Status_Idle;
    battery->temperature.nt = MAX_THERMISTORS_NUMBER;

#if C3
    battery->cells.noc = Number_of_Cells_3;
    cbals = (uint8_t*)malloc(sizeof(uint8_t) * 3);
    cbals[0] = CB1;
    cbals[1] = CB2;
    cbals[2] = CB5;

#elif C4
    battery->cells.noc = Number_of_Cells_4;
    cbals = (uint8_t*)malloc(sizeof(uint8_t) * 4);
    cbals[0] = CB1;
    cbals[1] = CB2;
    cbals[2] = CB3;
    cbals[3] = CB5;

#elif C5
    battery->cells.noc = Number_of_Cells_5;
    cbals = (uint8_t*)malloc(sizeof(uint8_t) * 5);
    cbals[0] = CB1;
    cbals[1] = CB2;
    cbals[2] = CB3;
    cbals[3] = CB4;
    cbals[4] = CB5;

#endif // to do add from 6 to 15 cells
}

void get_battery(Battery* _battery)
{
    memcpy(_battery, battery, sizeof(Battery));
}

// To DO  !!!!
void read_sys_status()
{
    uint8_t stat = read_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT);

    if(stat != 0x80)
    {
        write_register(BQ769200_ADDRESS, BQ769_REG_SYS_STAT, 0xBF);
        // to do detection type of error
        write_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL2, 0xC3);
    }
}

void read_cells(bool communication)
{
    if(battery->battery_status != Battery_Status_Charge)
    {
        if(!communication)
        {
            return;
        }
    }

#if C3
    battery->cells.voltage[0] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC1_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC1_LO);
    battery->cells.voltage[1] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC2_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC2_LO);
    battery->cells.voltage[2] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC5_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC5_LO);
#elif C4
    battery->cells.voltage[0] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC1_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC1_LO);
    battery->cells.voltage[1] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC2_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC2_LO);
    battery->cells.voltage[2] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC3_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC3_LO);
    battery->cells.voltage[3] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC5_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC5_LO);
#elif C5
    battery->cells.voltage[0] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC1_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC1_LO);
    battery->cells.voltage[1] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC2_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC2_LO);
    battery->cells.voltage[2] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC3_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC3_LO);
    battery->cells.voltage[3] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC4_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC4_LO);
    battery->cells.voltage[4] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_VC5_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_VC5_LO);
#endif // to do add from 6 to 15 cells
}

void read_current()
{
    battery->current =
        (read_register(BQ769200_ADDRESS, BQ769_REG_CC_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_CC_LO);

    if(battery->current > 10)
    {
        if(battery->battery_status != Battery_Status_Charge)
        {
            set_battery_status(Battery_Status_Charge);
        }
    }
    else if(battery->current < -10)
    {
        if(battery->battery_status != Battery_Status_Discharge)
        {
            set_battery_status(Battery_Status_Discharge);
        }
    }
    else
    {
        if(battery->battery_status != Battery_Status_Idle)
        {
            set_battery_status(Battery_Status_Idle);
        }
    }
}

void read_voltage()
{
    battery->voltage =
        (read_register(BQ769200_ADDRESS, BQ769_REG_BAT_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_BAT_LO);
}

void set_battery_status(Battery_Status status)
{
    battery->battery_status = status;
    if(battery->battery_status != Battery_Status_Charge)
    {
#if BQ76920
        write_register(BQ769200_ADDRESS, BQ769_REG_CELLBAL_1, 0x00);
#elif BQ76930
        write_register(BQ7693000_ADDRESS, BQ769_REG_CELLBAL_1, 0x00);
        write_register(BQ7693000_ADDRESS, BQ769_REG_CELLBAL_2, 0x00);
#elif BQ76940
        write_register(BQ7694000_ADDRESS, BQ769_REG_CELLBAL_1, 0x00);
        write_register(BQ7694000_ADDRESS, BQ769_REG_CELLBAL_2, 0x00);
        write_register(BQ7694000_ADDRESS, BQ769_REG_CELLBAL_3, 0x00);
#endif
    }
}

void read_load(bool communication)
{
    if(!communication)
    {
        return;
    }
    if(read_register(BQ769200_ADDRESS, BQ769_REG_SYS_CTRL1) && 0x80)
    {
        battery->load = LOAD_detect;
    }
    else
    {
        battery->load = LOAD_not_detect;
        battery->current = 0;
    }
}

void read_temperature()
{

    battery->temperature.temperature[0] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_TS1_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_TS1_LO);
#if BQ76930
    battery->temperature.temperature[1] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_TS2_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_TS2_LO);
#elif BQ76940
    battery->temperature.temperature[1] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_TS2_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_TS2_LO);
    battery->temperature.temperature[2] =
        (read_register(BQ769200_ADDRESS, BQ769_REG_TS3_HI) << 8) | read_register(BQ769200_ADDRESS, BQ769_REG_TS3_LO);
#endif
}

void balancing_cells()
{
    if(battery->battery_status != Battery_Status_Charge)
    {
        return;
    }
    uint8_t cbals_value = 0;
    uint16_t c_bal = 0;
    uint16_t min_cell = battery->cells.voltage[0];
    for(uint8_t i = 1; i < battery->cells.noc; i++)
    {
        if(min_cell > battery->cells.voltage[i])
        {
            min_cell = battery->cells.voltage[i];
        }
    }
    cell_min_v = min_cell;
    /*
    check iterator if cell value is more then 95,5mV and it will be 250 ADC
    */
    for(uint8_t i = 0; i < battery->cells.noc; i++)
    {
        if((battery->cells.voltage[i] - min_cell) > 120)
        {
            // enable balancer on that cell
            c_bal += (1 << i);
        }
    }
    if(c_bal == 0)
    {
#if BQ76920
        write_register(BQ769200_ADDRESS, BQ769_REG_CELLBAL_1, 0x00);
#elif BQ76930
        write_register(BQ7693000_ADDRESS, BQ769_REG_CELLBAL_1, 0x00);
        write_register(BQ7693000_ADDRESS, BQ769_REG_CELLBAL_2, 0x00);
#elif BQ76940
        write_register(BQ7694000_ADDRESS, BQ769_REG_CELLBAL_1, 0x00);
        write_register(BQ7694000_ADDRESS, BQ769_REG_CELLBAL_2, 0x00);
        write_register(BQ7694000_ADDRESS, BQ769_REG_CELLBAL_3, 0x00);
#endif
        return;
    }

#if BQ76920
    for(uint8_t i = 0; i < battery->cells.noc; i++)
    {
        if(c_bal & (1 << i))
        {
            cbals_value |= cbals[i];
        }
    }
    valltowri = cbals_value;
    write_register(BQ769200_ADDRESS, BQ769_REG_CELLBAL_1, cbals_value);
#elif BQ76930

    write_register(BQ7693000_ADDRESS, BQ769_REG_CELLBAL_1, 0x00);
    write_register(BQ7693000_ADDRESS, BQ769_REG_CELLBAL_2, 0x00);
// To DO
#elif BQ76940
    write_register(BQ7694000_ADDRESS, BQ769_REG_CELLBAL_1, 0x00);
    write_register(BQ7694000_ADDRESS, BQ769_REG_CELLBAL_2, 0x00);
    write_register(BQ7694000_ADDRESS, BQ769_REG_CELLBAL_3, 0x00);
// To DO
#endif
    return;
}
