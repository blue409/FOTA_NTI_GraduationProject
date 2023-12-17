
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"
#include "GPIO_interface.h"
#include "LOGIC_BL.h"

#include <stdio.h>
#include <string.h>

u8 LocalArray[1665];//1000 bytes of data & 409 bytes for the rest of the record & 256 extra to replace the ':'
u8 NewRecordRecieved=0;
u8 BeginingOfRecord=0;
u8 EndOfFile=0;
void MUSART1_voidInit(void)
{
	/*	baud rate = 115200		*/
	USART1 -> BRR = 0x045;

	SET_BIT((USART1-> CR[0]), 3);			/* Enabling Transmitter */
	SET_BIT((USART1-> CR[0]), 2);			/* Enabling Receiver */
	SET_BIT((USART1-> CR[0]), 13);			/* Enabling USART */
	
	USART1 -> SR = 0;						/* Clearing status register */
}

void MUSART1_voidTransmit(u8 arr[])
{
	u8 i = 0;
	while(arr[i] != '\0'){
		USART1 -> DR = arr[i];
		while((GET_BIT((USART1 -> SR), 6)) == 0);
		i++;
	}
	
}

void MUSART1_u8Receive(void)
{
	static u16 LocalArrayIndex=0;
	u8 Loc_u8ReceivedData = 0;
	while((GET_BIT((USART1 -> SR), 5)) == 0);
	Loc_u8ReceivedData = USART1 -> DR;

	if(BeginingOfRecord)
	{
		LocalArray[LocalArrayIndex]=Loc_u8ReceivedData;
		//trace_printf("Add:%p    val:%x\n", &GlobalArray[GlobalArrayIndex],GlobalArray[GlobalArrayIndex]);
		LocalArrayIndex++;
	}
	else
	{
		LocalArray[LocalArrayIndex]=Loc_u8ReceivedData;
		LocalArrayIndex++;
	}


	if( GET_BIT((USART1 -> SR), 2) || GET_BIT((USART1 -> SR), 3) || GET_BIT((USART1 -> SR), 1) )
	{

		trace_printf("UART Data Corrupted ! ");
	}

	//end of record
	if(LocalArray[LocalArrayIndex-1]==0xfd)
	{
		if(LocalArray[LocalArrayIndex-2]==0x1)
		{
			if(LocalArray[LocalArrayIndex-3]==0x0)
			{
				if(LocalArray[LocalArrayIndex-4]==0x0 )
				{
					if(LocalArray[LocalArrayIndex-5]==0x0)
					{
						NewRecordRecieved=1;
						Parser(LocalArray);
						print_Data();
						//trace_printf("  val:%d\n",GlobalArrayIndex-5);
						LocalArrayIndex=0;
						MUSART1_voidTransmit("C");
						BeginingOfRecord=0;
					}
				}
			}
		}
	}


	//begin of record
	if(LocalArray[LocalArrayIndex-1]==0xfe)
	{
		if(LocalArray[LocalArrayIndex-2]==0x1)
		{
			if(LocalArray[LocalArrayIndex-3]==0x0)
			{
				if(LocalArray[LocalArrayIndex-4]==0x0 )
				{
					if(LocalArray[LocalArrayIndex-5]==0x0)
					{
						memset(LocalArray,0,sizeof(LocalArray));
						BeginingOfRecord=1;
						MUSART1_voidTransmit("Z");
						LocalArrayIndex=0;
					}
				}
			}
		}
	}





	//end of file
	else if(LocalArray[LocalArrayIndex-1]==0xFF)
	{
		if(LocalArray[LocalArrayIndex-2]==0x01)
		{
			if(LocalArray[LocalArrayIndex-3]==0x00)
			{
				if(LocalArray[LocalArrayIndex-4]==0x00 )
				{
					if(LocalArray[LocalArrayIndex-5]==0x00)
					{
						EndOfFile=1;
						LocalArrayIndex=0;
						MUSART1_voidTransmit("D");
						MGPIO_VoidSetPinValue(GPIOA,GPIN0,GPIO_HIGH);
					}
				}
			}
		}
	}

		MUSART1_voidTransmit("K");

}





















