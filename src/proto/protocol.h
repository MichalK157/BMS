#pragma once

#define MAX_CELLS_NUMBER = 15
typedef enum
{
    MSG_ID_STATE = 0x53544154,
    MSG_ID_BATTERY = 0x42415454
} MSG_ID;

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

typedef struct _Battery
{
    Number_of_Cells noc;
    uint16_t current;
    uint16_t voltages[MAX_CELLS_NUMBER];
} Battery;
