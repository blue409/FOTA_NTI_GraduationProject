#include "std_types.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "USART_interface.h"

#include "STK_interface.h"
#include "USART_interface.h"
#include "SCB_Interface.h"
#include <stdio.h>
#include <string.h>
#include "diag/Trace.h"
#include "FLITF.h"
#include "../include/LOGIC_BL.h"

extern u8 EndOfFile;
extern u8 NewRecordRecieved;
extern u32 Full_Address;
extern struct Record_t record;
extern Rec_type;

#define NO_APP 0xFFFFFFFF
#define APP_Valid 0xDDCCBBAA


volatile u8 u8BLWriteReq = 1;
u16 HighLowByteROMMarker[]={0xAABB,0xCCDD};

pf EntryPoint = NULL;
pf Global_pfNotification = NULL;

#define FLASH_SECTOR7_BASE_ADDRESS  0x08002000

static volatile uint_32t * ROM_Marker = (uint_32t *) (0x08001FF8);

void APP_voidStartApplication (void)
{
	//Set the user-defined vector table
	SetUserDefinedVectorTable();
	EntryPoint  = (*(pf *) (FLASH_SECTOR7_BASE_ADDRESS|4));
	//Calls the entry point of the application, which is a function that serves as the main entry point for the application.
	EntryPoint();

}

void main(void)
{
/******************************Initialization*******************************************/
	RCC_voidInitSysClock();
	/* FPEC clock enable*/
	RCC_voidEnableClock(RCC_AHB,4);
	/* Enable GPIOA Clock */
	RCC_voidEnableClock(RCC_APB2,2);
	/* Enable USART1 Clock */
	RCC_voidEnableClock(RCC_APB2, 14);
	/* initialize the UART1 Driver*/
	MUSART1_voidInit();
	/* Setting A9:TX pin as Output alternate function push pull w max speed 50 MHz */
	MGPIO_VoidSetPinDirection(GPIOA,GPIN9,OUTPUT_SPEED_50MHZ_AFPP);
	/* Setting A10:RX pin as input floating */
	MGPIO_VoidSetPinDirection(GPIOA,GPIN10,INPUT_FLOATING);
/******************************Initialization*******************************************/


	// Check if a new application is received
	switch(*ROM_Marker)
	{
	// Case when no application is currently stored in the device.
	case NO_APP:
		// The bootloader will enter this loop and wait for data to be sent from the host device.
		while(!(EndOfFile))
		{
			// Receive data from the host device using the UART protocol.
			MUSART1_u8Receive();
			 // If a new record is received and the record type is Data record, it indicates that this record is the new application firmware.
			if(NewRecordRecieved && (DataRecord==Rec_type))
			{
				// If a bootloader write request is set, the bootloader will erase the application area in the flash memory.
				if (u8BLWriteReq == 1)
				{
					FPEC_voidEraseAppArea();
					u8BLWriteReq = 0;
				}
				 // Write the new application firmware to the flash memory.
				Flash_ProgramWrite(  (u32*)Full_Address  ,  (u16*)record.Data  , record.Data_Size  );
				NewRecordRecieved=0;
			}

		}
		 // Set the ROM marker to APP_Valid, indicating that the new application firmware is valid and can be executed.
		Flash_ProgramWrite((u32*) ROM_Marker,(u16*)&HighLowByteROMMarker,4);
		// Trigger a soft reset to start executing the new application firmware.
		TriggerSoftReset();
		break;
	// Case when the bootloader has successfully received and stored a new application firmware.
	case APP_Valid:
		 	 // Jump to the new application firmware to start executing it.
			APP_voidStartApplication();
		break;
	// Default case for error handling.
	default:
		/*error handling*/
		break;
	}

}



