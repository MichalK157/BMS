#pragma once

#include "stdint.h"

#ifdef __cplusplus
extern "C" {

#endif

#if BQ76920
#define MAX_CELLS_NUMBER 5
#define MAX_THERMISTORS_NUMBER 1
#define CELL_PADDING 6
#elif BQ76930
#define MAX_CELLS_NUMBER 10
#define MAX_THERMISTORS_NUMBER 2
#define CELL_PADDING 4
#elif BQ76940
#define MAX_CELLS_NUMBER 15
#define MAX_THERMISTORS_NUMBER 3
#define CELL_PADDING 2
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
  Number_of_Cells noc;                    // 4 byte
  unsigned char reserved[4];              // 4 byte
  uint16_t voltage[MAX_CELLS_NUMBER];     // 10/20/30 byte
  unsigned char reserved_2[CELL_PADDING]; // 6/4/2 byte
} Cells;                                  // 24/32/40 byte

typedef struct _Temperature {
  Number_of_Thermistors nt;                                 // 4byte
  unsigned char reserved[4];                                // 4byte
  uint16_t temperature[MAX_THERMISTORS_NUMBER];             // 2/4/6 byte
  unsigned char reserved_2[8 - 2 * MAX_THERMISTORS_NUMBER]; // 6/4/2 byte
} Temperature;                                              // 16 byte

typedef enum { LOAD_not_detect = 0x4C4F6E64, LOAD_detect = 0x4C4F4144 } LOAD;

typedef struct _Battery {
  Battery_Status battery_status; // 4 byte
  LOAD load;                     // 4 byte
  uint16_t voltage;              // 2 byte
  int16_t current;               // 2 byte
  unsigned char reserved[4];     // 4 byte
  Cells cells;                   // 24 byte
  Temperature temperature;       // 16 byte

} Battery; // 56

typedef struct _MSG_TO_PC {
  MSG_ID id;                 // 4 byte
  unsigned char reserved[4]; // 4 byte
  union {
    Battery battery; // 56
  };
} MSG_TO_PC; // 64

// MSG to BMS

typedef enum {
  Get_Msg_Name_Status = 0x474D4E53,
  Get_Msg_Name_Protection = 0x474D4E50,
  Get_Msg_Name_Register = 0x474D4E52
} Get_Msg_Name;

typedef struct _Get_Msg {
  Get_Msg_Name name;         // 4 byte
  uint8_t special;           // 1 byte
  unsigned char reserved[3]; // 3 byte
} Get_Msg;

typedef enum {
  Set_Msg_Name_sys_stat = 0x534D4E53,
  Set_Msg_Name_cc = 0x534D4E43,
  Set_Msg_Name_ctrl2 = 0x534d5555
} Set_Msg_Name;
typedef struct _Set_Msg {
  Set_Msg_Name name;         // 4 byte
  uint8_t reg_value;         // 1 byte
  unsigned char reserved[3]; // 3 byte
} Set_Msg;

typedef enum {
  Communication_Init = 0x43496E69,
  Communication_Stop = 0x4353746F
} Communication;
typedef struct _MSG_TO_BMS {
  MSG_ID id;                 // 4 byte
  unsigned char reserved[4]; // 4 byte
  union {
    Get_Msg get_msg;             // 8 byte
    Set_Msg set_msg;             // 8 byte
    Communication communication; // 4 byte
  };

} MSG_TO_BMS; // 16 byte

#ifdef __cplusplus
}
#endif
