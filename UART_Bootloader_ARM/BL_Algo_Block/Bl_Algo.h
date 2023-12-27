#include "std_types.h"

/***************************************************************************
                           CONFIGURATIONS
****************************************************************************/
#define Start_Of_Rec 0x0001FE3A   //special code + ':'
#define RECORDS_PER_PAGE  64
#define DATABYTES_PER_RECORD 16

/***************************************************************************
                           BL_ALGO DEFINED TYPES
****************************************************************************/
typedef struct{
 uint8 Data_arr[RECORDS_PER_PAGE * DATABYTES_PER_RECORD];  //64 record inside each record there is 16 code bytes = 16*64
 uint16 Low_add_Part[RECORDS_PER_PAGE];
}Record_t;

/***************************************************************************  
                           FUNCTION PROTOTYPES                
****************************************************************************/
uint8 BLOCK_Parser(uint8* Record,uint16 Length_Rec, Record_t* struc,uint16* High_add_Part);
static uint8 Write_line_of_Data(uint8* Record, uint16 i_Record, uint8 counter, uint8 *Data_arr,uint8 cc);
uint8* Check_Sum(uint8* Record, uint16 Length_Rec);
static uint8 WriteEndOfFile(uint8 counter, uint8 *Data_arr);
uint8 Make_Byte(uint8 num1, uint8 num2);
//uint8 BL_RecParser(uint8* Record,uint16 Length_Rec, Record_t* struc,uint16* High_add_Part);
