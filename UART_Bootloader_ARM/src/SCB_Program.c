
#include "std_types.h"
#include "SCB_Interface.h"
#include "SCB_Private.h"
#include "SCB_Config.h"

#define VECTOR_TABLE_BASE_ADDRESS	0x08000000


void SetUserDefinedVectorTable(void)
{
	SCB_VTOR = VECTOR_TABLE_BASE_ADDRESS|VECTOR_TABLE_OFFSET;
}


void TriggerSoftReset(void)
{
	SCB_AIRCR = (0x05FA0000 | (1 << 2));
}


