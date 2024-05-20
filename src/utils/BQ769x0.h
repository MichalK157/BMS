/*
 * BQ769x0.h
 *
 *  Created on: May 15, 2024
 *      Author: mkac
 */

#ifndef UTILS_BQ769X0_H_
#define UTILS_BQ769X0_H_
#include "stdint.h"

// Addresses of registers in the BQ769 circuit
#define BQ769_REG_SYS_STAT_ADDR     0x0000 // System Status Register
#define BQ769_REG_SYS_CTRL1_ADDR    0x0004 // System Control Register 1
#define BQ769_REG_SYS_CTRL2_ADDR    0x0005 // System Control Register 2
#define BQ769_REG_PROTECT1_ADDR     0x0006 // Protection Control Register 1
#define BQ769_REG_PROTECT2_ADDR     0x0007 // Protection Control Register 2
#define BQ769_REG_OV_TRIP_ADDR      0x0009 // Overvoltage Trip Threshold Register
#define BQ769_REG_UV_TRIP_ADDR      0x000A // Undervoltage Trip Threshold Register
#define BQ769_REG_CC_CFG_ADDR       0x000C // Coulomb Counter Configuration Register
#define BQ769_REG_VC1_HI_ADDR       0x000D // Voltage Cell 1 High Byte Register
#define BQ769_REG_VC1_LO_ADDR       0x000E // Voltage Cell 1 Low Byte Register
#define BQ769_REG_VC2_HI_ADDR       0x0010 // Voltage Cell 2 High Byte Register
#define BQ769_REG_VC2_LO_ADDR       0x0011 // Voltage Cell 2 Low Byte Register
#define BQ769_REG_VC3_HI_ADDR       0x0012 // Voltage Cell 3 High Byte Register
#define BQ769_REG_VC3_LO_ADDR       0x0013 // Voltage Cell 3 Low Byte Register
#define BQ769_REG_VC4_HI_ADDR       0x0014 // Voltage Cell 4 High Byte Register
#define BQ769_REG_VC4_LO_ADDR       0x0015 // Voltage Cell 4 Low Byte Register
#define BQ769_REG_VC5_HI_ADDR       0x0016 // Voltage Cell 5 High Byte Register
#define BQ769_REG_VC5_LO_ADDR       0x0017 // Voltage Cell 5 Low Byte Register
#define BQ769_REG_VC6_HI_ADDR       0x0018 // Voltage Cell 6 High Byte Register
#define BQ769_REG_VC6_LO_ADDR       0x0019 // Voltage Cell 6 Low Byte Register
#define BQ769_REG_VC7_HI_ADDR       0x001A // Voltage Cell 7 High Byte Register
#define BQ769_REG_VC7_LO_ADDR       0x001B // Voltage Cell 7 Low Byte Register
#define BQ769_REG_VC8_HI_ADDR       0x001C // Voltage Cell 8 High Byte Register
#define BQ769_REG_VC8_LO_ADDR       0x001D // Voltage Cell 8 Low Byte Register
#define BQ769_REG_VC9_HI_ADDR       0x001E // Voltage Cell 9 High Byte Register
#define BQ769_REG_VC9_LO_ADDR       0x001F // Voltage Cell 9 Low Byte Register
#define BQ769_REG_VC10_HI_ADDR      0x0020 // Voltage Cell 10 High Byte Register
#define BQ769_REG_VC10_LO_ADDR      0x0021 // Voltage Cell 10 Low Byte Register
#define BQ769_REG_VC11_HI_ADDR      0x0022 // Voltage Cell 11 High Byte Register
#define BQ769_REG_VC11_LO_ADDR      0x0023 // Voltage Cell 11 Low Byte Register
#define BQ769_REG_VC12_HI_ADDR      0x0024 // Voltage Cell 12 High Byte Register
#define BQ769_REG_VC12_LO_ADDR      0x0025 // Voltage Cell 12 Low Byte Register
#define BQ769_REG_VC13_HI_ADDR      0x0026 // Voltage Cell 13 High Byte Register
#define BQ769_REG_VC13_LO_ADDR      0x0027 // Voltage Cell 13 Low Byte Register
#define BQ769_REG_VC14_HI_ADDR      0x0028 // Voltage Cell 14 High Byte Register
#define BQ769_REG_VC14_LO_ADDR      0x0029 // Voltage Cell 14 Low Byte Register
#define BQ769_REG_VC15_HI_ADDR      0x002A // Voltage Cell 15 High Byte Register
#define BQ769_REG_VC15_LO_ADDR      0x002B // Voltage Cell 15 Low Byte Register
#define BQ769_REG_TS1_HI_ADDR       0x002C // Thermistor 1 High Byte Register
#define BQ769_REG_TS1_LO_ADDR       0x002D // Thermistor 1 Low Byte Register
#define BQ769_REG_TS2_HI_ADDR       0x002E // Thermistor 2 High Byte Register
#define BQ769_REG_TS2_LO_ADDR       0x002F // Thermistor 2 Low Byte Register
#define BQ769_REG_TS3_HI_ADDR       0x0030 // Thermistor 3 High Byte Register
#define BQ769_REG_TS3_LO_ADDR       0x0031 // Thermistor 3 Low Byte Register
#define BQ769_REG_CC_HI_ADDR        0x0032 // Coulomb Counter High Byte Register
#define BQ769_REG_CC_LO_ADDR        0x0033 // Coulomb Counter Low Byte Register
#define BQ769_REG_ADCGAIN1_ADDR     0x0050 // ADC Gain 1 Register
#define BQ769_REG_ADCOFFSET1_ADDR   0x0051 // ADC Offset 1 Register
#define BQ769_REG_ADCGAIN2_ADDR     0x0059 // ADC Gain 2 Register

//I2C address

#define BQ7692000_ADDRESS 0x08
#define BQ7692001_ADDRESS 0x08
#define BQ7692002_ADDRESS 0x08
#define BQ7692003_ADDRESS 0x08
#define BQ7692006_ADDRESS 0x18
#define BQ7693000_ADDRESS 0x08
#define BQ7693001_ADDRESS 0x08
#define BQ7693002_ADDRESS 0x08
#define BQ7693003_ADDRESS 0x08
#define BQ7693006_ADDRESS 0x18
#define BQ7693007_ADDRESS 0x18
#define BQ7694000_ADDRESS 0x08
#define BQ7694001_ADDRESS 0x08
#define BQ7694002_ADDRESS 0x08
#define BQ7694003_ADDRESS 0x08
#define BQ7694006_ADDRESS 0x18


// Data types for I2C communication
typedef enum {
    BQ769_REG_SYS_STAT = BQ769_REG_SYS_STAT_ADDR,
    BQ769_REG_SYS_CTRL1 = BQ769_REG_SYS_CTRL1_ADDR,
    BQ769_REG_SYS_CTRL2 = BQ769_REG_SYS_CTRL2_ADDR,
    BQ769_REG_PROTECT1 = BQ769_REG_PROTECT1_ADDR,
    BQ769_REG_PROTECT2 = BQ769_REG_PROTECT2_ADDR,
    BQ769_REG_OV_TRIP = BQ769_REG_OV_TRIP_ADDR,
    BQ769_REG_UV_TRIP = BQ769_REG_UV_TRIP_ADDR,
    BQ769_REG_CC_CFG = BQ769_REG_CC_CFG_ADDR,
    BQ769_REG_VC1_HI = BQ769_REG_VC1_HI_ADDR,
    BQ769_REG_VC1_LO = BQ769_REG_VC1_LO_ADDR,
    BQ769_REG_VC2_HI = BQ769_REG_VC2_HI_ADDR,
    BQ769_REG_VC2_LO = BQ769_REG_VC2_LO_ADDR,
    BQ769_REG_VC3_HI = BQ769_REG_VC3_HI_ADDR,
    BQ769_REG_VC3_LO = BQ769_REG_VC3_LO_ADDR,
    BQ769_REG_VC4_HI = BQ769_REG_VC4_HI_ADDR,
    BQ769_REG_VC4_LO = BQ769_REG_VC4_LO_ADDR,
    BQ769_REG_VC5_HI = BQ769_REG_VC5_HI_ADDR,
    BQ769_REG_VC5_LO = BQ769_REG_VC5_LO_ADDR,
    BQ769_REG_VC6_HI = BQ769_REG_VC6_HI_ADDR,
    BQ769_REG_VC6_LO = BQ769_REG_VC6_LO_ADDR,
    BQ769_REG_VC7_HI = BQ769_REG_VC7_HI_ADDR,
    BQ769_REG_VC7_LO = BQ769_REG_VC7_LO_ADDR,
    BQ769_REG_VC8_HI = BQ769_REG_VC8_HI_ADDR,
    BQ769_REG_VC8_LO = BQ769_REG_VC8_LO_ADDR,
    BQ769_REG_VC9_HI = BQ769_REG_VC9_HI_ADDR,
    BQ769_REG_VC9_LO = BQ769_REG_VC9_LO_ADDR,
    BQ769_REG_VC10_HI = BQ769_REG_VC10_HI_ADDR,
    BQ769_REG_VC10_LO = BQ769_REG_VC10_LO_ADDR,
    BQ769_REG_VC11_HI = BQ769_REG_VC11_HI_ADDR,
    BQ769_REG_VC11_LO = BQ769_REG_VC11_LO_ADDR,
    BQ769_REG_VC12_HI = BQ769_REG_VC12_HI_ADDR,
    BQ769_REG_VC12_LO = BQ769_REG_VC12_LO_ADDR,
    BQ769_REG_VC13_HI = BQ769_REG_VC13_HI_ADDR,
    BQ769_REG_VC13_LO = BQ769_REG_VC13_LO_ADDR,
    BQ769_REG_VC14_HI = BQ769_REG_VC14_HI_ADDR,
    BQ769_REG_VC14_LO = BQ769_REG_VC14_LO_ADDR,
    BQ769_REG_VC15_HI = BQ769_REG_VC15_HI_ADDR,
    BQ769_REG_VC15_LO = BQ769_REG_VC15_LO_ADDR,
    BQ769_REG_TS1_HI = BQ769_REG_TS1_HI_ADDR,
    BQ769_REG_TS1_LO = BQ769_REG_TS1_LO_ADDR,
    BQ769_REG_TS2_HI = BQ769_REG_TS2_HI_ADDR,
    BQ769_REG_TS2_LO = BQ769_REG_TS2_LO_ADDR,
    BQ769_REG_TS3_HI = BQ769_REG_TS3_HI_ADDR,
    BQ769_REG_TS3_LO = BQ769_REG_TS3_LO_ADDR,
    BQ769_REG_CC_HI = BQ769_REG_CC_HI_ADDR,
    BQ769_REG_CC_LO = BQ769_REG_CC_LO_ADDR,
    BQ769_REG_ADCGAIN1 = BQ769_REG_ADCGAIN1_ADDR,
    BQ769_REG_ADCOFFSET1 = BQ769_REG_ADCOFFSET1_ADDR,
    BQ769_REG_ADCGAIN2 = BQ769_REG_ADCGAIN2_ADDR,
} BQ769_Register;


typedef enum {
    CELL_1 = 0,
    CELL_2 = 1,
    CELL_3 = 2,
    CELL_4 = 3,
    CELL_5 = 4,
    CELL_6 = 5,
    CELL_7 = 6,
    CELL_8 = 7,
    CELL_9 = 8,
    CELL_10 = 9,
    CELL_11 = 10,
    CELL_12 = 11,
    CELL_13 = 12,
    CELL_14 = 13,
    CELL_15 = 14,
	CELL_MAX = 15
} Cell_Index;

typedef enum {
    TEMP_SENSOR_1 = 0,
    TEMP_SENSOR_2 = 1,
    TEMP_SENSOR_3 = 2,
	TEMP_SENSOR_MAX = 3
} Temp_Sensor_Index;


typedef struct {
    uint8_t sys_stat;
    uint8_t sys_ctrl1;
    uint8_t sys_ctrl2;
    uint8_t protect1;
    uint8_t protect2;
    uint8_t ov_trip;
    uint8_t uv_trip;
    uint8_t cc_cfg;
    uint16_t vc[CELL_MAX]; // Voltage Cell [1-15]
    uint16_t ts[TEMP_SENSOR_MAX];  // Thermistor [1-3]
    uint16_t cc;
    uint8_t adcgain1;
    uint8_t adcoffset1;
    uint8_t adcgain2;
} BQ769_Config;

typedef struct {
    uint16_t voltage;
} BQ769_Voltage;

typedef struct {
    uint16_t current;
} BQ769_Current;

typedef struct {
    uint16_t temperature;
} BQ769_Temperature;

typedef struct {
    uint8_t address;
    int bus_fd; // File descriptor for the I2C bus
    // Add other necessary fields
} BQ769_Device;

uint8_t read_register(uint8_t address, BQ769_Register register);
void write_register(uint8_t address, BQ769_Register register, uint8_t value);
void get_configuration(uint8_t address);

#endif /* UTILS_BQ769X0_H_ */
