
#ifndef LOGIB_BL_H_INCLUDED
#define LOGIB_BL_H_INCLUDED
#include "std_types.h"

#define CAN_FINISHED_TRANSMISSION_FLAG 1
#define DataRecord	0x00
struct Record_t {
 u16 Low_Add;
 u8 Data[16];  //64 record inside each record there is 16 code bytes
 u8 Data_Size;
 u8 Check_Sum;
 u32 Full_Add;
};

typedef enum {ES_NOK, ES_OK}ErrorStatus;

void Parser(u8* Record);
u8 Check_Sum(u8* Record);
u8 GET_RECORD_TYPE(u8* Record);
u16 GET_Address(u8* Record);
u8 GET_Data_Bit_Size(u8* Record);
u8 GET_Checksum(u8* Record, u8 size_);
void print_Data(void);
#endif // LOGIB_BL_H_INCLUDED
