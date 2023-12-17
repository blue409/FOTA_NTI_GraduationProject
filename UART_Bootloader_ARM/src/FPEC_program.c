#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"


void FPEC_voidEraseAppArea(void)
{
	u8 i;
	
	for (i=7;i<64;i++)
	{
		FPEC_voidFlashPageErase(i);
	}
}

void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber)
{
	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,0) == 1);

	/* Check if FPEC is locked or not */
	if ( GET_BIT(FPEC->CR,7) == 1)
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}
	
	/* Page Erase Operation */
	SET_BIT(FPEC->CR,1);

	/* Write Page address */
	FPEC->AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000 ;

	/* Start operation */
	SET_BIT(FPEC->CR,6);

	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,0) == 1);

	/* EOP */
	SET_BIT(FPEC->SR,5);
	CLR_BIT(FPEC->CR,1);
}

void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u16 Copy_u8Length)
{
	u16 i;
	volatile u16 Temp;
	while (GET_BIT(FPEC->SR,0) == 1);
	SET_BIT(FPEC->CR,0);				/* Write Flash Programming */
	for (i = 0; i< Copy_u8Length; i++)
	{
		/* Half word operation */
		Temp = Copy_u16Data[i];
		Copy_u16Data[i]=(((0x00FF)&Copy_u16Data[i])<<8);
	    Temp=((Temp>>8)&(0x00FF));
	    Copy_u16Data[i]=Copy_u16Data[i]|((u16)Temp);

		*((volatile u16*)Copy_u32Address) = Copy_u16Data[i];
		//*((volatile u16*)Copy_u32Address) = Temp;
		Copy_u32Address += 2 ;
	}
	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,0) == 1);
	/* EOP */
	SET_BIT(FPEC->SR,5);
	CLR_BIT(FPEC->CR,0);
}
