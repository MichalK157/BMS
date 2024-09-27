#pragma once

#include "stdint.h"

#ifdef __cplusplus
extern "C" {

#endif

#if BQ76920
#define MAX_CELLS_NUMBER 5
#define MAX_THERMISTORS_NUMBER 1
#elif BQ76930
#define MAX_CELLS_NUMBER 10
#define MAX_THERMISTORS_NUMBER 2
#elif BQ76940
#define MAX_CELLS_NUMBER 15
#define MAX_THERMISTORS_NUMBER 3
#endif

typedef enum {
  MSG_ID_BATTERY = 0x42415454,
  MSG_ID_GET = 0x47455420,
  MSG_ID_SET = 0x53455420,
  MSG_ID_COMMUNICATION = 0x434F4D4D

} MSG_ID;

// MSG to PC
typedef enum {

  Number_of_Cells_3 = 3,
  Number_of_Cells_4 = 4,
  Number_of_Cells_5 = 5,
  Number_of_Cells_6 = 6,
  Number_of_Cells_7 = 7,
  Number_of_Cells_8 = 8,
  Number_of_Cells_9 = 9,
  Number_of_Cells_10 = 10,
  Number_of_Cells_11 = 11,
  Number_of_Cells_12 = 12,
  Number_of_Cells_13 = 13,
  Number_of_Cells_14 = 14,
  Number_of_Cells_15 = 15
} Number_of_Cells;

typedef enum {
  Number_of_Thermistors_1 = 1,
  Number_of_Thermistors_2 = 2,
  Number_of_Thermistors_3 = 3
} Number_of_Thermistors;

typedef enum {
  Battery_Status_Discharge = 0x53446964,
  Battery_Status_Charge = 0x53436861,
  Battery_Status_Idle = 0x5349646C,
  Battery_Status_Error = 0x53457272,
} Battery_Status;
typedef struct _Cells {
  Number_of_Cells noc;
  uint16_t voltage[MAX_CELLS_NUMBER];
} Cells;

typedef struct _Temperature {
  Number_of_Thermistors nt;
  uint16_t temperature[MAX_THERMISTORS_NUMBER];
} Temperature;

typedef enum { LOAD_not_detect = 0x4C4F6E64, LOAD_detect = 0x4C4F4144 } LOAD;

typedef struct _Battery {
  Battery_Status battery_status;
  uint16_t voltage;
  int16_t current;
  Cells cells;
  Temperature temperature;
  LOAD load;
} Battery;

typedef struct _MSG_TO_PC {
  MSG_ID id;
  union {
    Battery battery;
  };
} MSG_TO_PC;

// MSG to BMS

typedef enum {
  Get_Msg_Name_Status = 0x474D4E53,
  Get_Msg_Name_Protection = 0x474D4E50,
  Get_Msg_Name_Register = 0x474D4E52
} Get_Msg_Name;

typedef struct _Get_Msg {
  Get_Msg_Name name;
  uint8_t special;
} Get_Msg;

typedef enum {
  Set_Msg_Name_sys_stat = 0x534D4E53,
  Set_Msg_Name_cc = 0x534D4E43,
  Set_Msg_Name_ctrl2 = 0x534d5555
} Set_Msg_Name;
typedef struct _Set_Msg {
  Set_Msg_Name name;
  uint8_t reg_value;
} Set_Msg;

typedef enum {
  Communication_Init = 0x43496E69,
  Communication_Stop = 0x4353746F
} Communication;
typedef struct _MSG_TO_BMS {
  MSG_ID id;
  union {
    Get_Msg get_msg;
    Set_Msg set_msg;
    Communication communication;
  };

} MSG_TO_BMS;

#ifdef __cplusplus
}
#endif
