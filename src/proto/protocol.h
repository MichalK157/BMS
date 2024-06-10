#pragma once

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

typedef enum
{
    MSG_ID_STATE = 0x53544154,
    MSG_ID_BATTERY = 0x42415454,
    MSG_ID_CELLS = 0x43454C4C,
    MSG_ID_PROTECTION = 0x50524F54,
    MSG_ID_CMD = 0x434D445F,
    MSG_ID_GET = 0x47455420,
    MSG_ID_SET = 0x53455420

} MSG_ID;

// MSG to PC
typedef enum 
{
   
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

typedef enum
{
    Number_of_Thermistors_1 = 1,
    Number_of_Thermistors_2 = 2,
    Number_of_Thermistors_3 = 3
} Number_of_Thermistors;

typedef enum
{
    State_Discharge = 1,
    State_Charge = 2,
    State_Idle = 3,
    State_Error = 4,
} State;
typedef struct _Battery
{
    State State;
    uint16_t voltages;
    uint16_t current;
} Battery;

typedef struct _Cells
{
    Number_of_Cells noc;
    uint16_t voltage[MAX_CELLS_NUMBER];
} Cells;


typedef struct _Temperature
{
    Number_of_Thermistors not;
    uint16_t temperature[MAX_THERMISTORS_NUMBER];
} Temperature;

typedef enum
{
    LOAD_not_detect = 0,
    LOAD_detect = 1
} LOAD;

typedef struct _BMS
{
    Battery battery;
    Temperature temperature;
    uint16_t current;
    LOAD load;
} BMS;

typedef struct _Status
{
    uint8_t sys_status;
    uint8_t cellbal_1;
    uint8_t cellbal_2;
    uint8_t cellbal_3;
    uint8_t sys_ctrl_1;
    uint8_t sys_ctrl_2;
    uint8_t protect1;
    uint8_t protect2;
    uint8_t protect3;
} Status;

typedef enum
{
    Protection_not_activated = 0,
    Protection_activated = 1
} Protection;


typedef struct _Protection_Activation
{
    Protection uv;
    Protection ov;
    Protection scd;
    Protection ocd;
} Protection_Activation;


typedef struct _MSG_TO_PC
{
    MSG_ID id;
    union
    {
        BMS bms;
        Status status;
        Protection_Activation protection;
    } data;
} MSG_TO_PC;

// MSG to BMS

typedef enum
{
    Get_Msg_Name_Status = 1,
    Get_Msg_Name_Protection = 2,
    Get_Msg_Name_Register = 3
} Get_Msg_Name;

typedef struct _Get_Msg
{
    Get_Msg_Name name;
    uint8_t special;
} Get_Msg;

typedef enum
{
    Set_Msg_Name_sys_stat,
    Set_Msg_Name_cc
}Set_Msg_Name;
typedef struct _Set_Msg
{
    Set_Msg_Name name;
    uint8_t reg_value;
} Set_Msg;

typedef struct _MSG_TO_BMS
{
    MSG_ID id;
    union
    {
        Get_Msg get_msg;
        Set_Msg set_msg;
    } data;
    
} MSG_TO_BMS;
