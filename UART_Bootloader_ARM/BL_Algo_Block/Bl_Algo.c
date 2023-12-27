#include "Bl_Algo.h"
#include <stdio.h>

/***************************************************************************
 *Params :
   uint8*     : Raw array of records of 1 page
   uint16     : size of array
   Record_t*  : pointer to a struct of type Record_t (To be filled with data)
   uint16*    : pointer to uint16 var (To be filled with High add of hex file)
 *return     :  E_OK or  E_NOK
   uint8      : Localestate (E_OK or  E_NOK)
***************************************************************************/
uint8 BLOCK_Parser(uint8* Record,uint16 Length_Rec, Record_t* struc,uint16* High_add_Part)
{   uint8 LocaleState = E_OK;
    uint8 counter =0;          // counter for last place used in add array in struc  ..static
    uint8 cc ;                 //data byte(char) count in one record
	uint8 rec_type ;           //type of data bytes in record
	uint32 current_bytes = 0;
//   if(current_bytes != NULL_PTR){
    for(uint16 i=0;i<Length_Rec-3;i++)  //to prevent accessing wrong place
	{
      current_bytes = (Record[i]<<24) | (Record[i+1]<<16) |(Record[i+2]<< 8)|Record[i+3];
      if(current_bytes == Start_Of_Rec)
	  {
        struc->Low_add_Part[counter]= 0;	
		cc = 0;
		rec_type = 0;
		cc = Record[i+4];
		rec_type= Record[i+7];
		switch(rec_type)
		{
		  case 0:	//Data Bytes
              struc->Low_add_Part[counter]  = Record[i+6];
		      struc->Low_add_Part[counter] |= (Record[i+5])<<8;		  
              Write_line_of_Data(Record,i,counter,struc->Data_arr,cc);//case data
		      break;
		  case 1:  //EOF....8 of # indicating End of File 
              WriteEndOfFile(counter,struc->Data_arr);
              break ;
		  case 4:  //High Add Part
		     *High_add_Part= Record[i+9];
             *High_add_Part |= Record[i+8]<<8;
              break ;	           			 
		}
        counter++;
      }//all start of line operations....if
   	}//for

  return LocaleState;
}
/***************************************************************************
 * Params :
 * uint8* : array of records bytes
 * uint16 : iterator i inside parser func.
 * uint8  : counter indicates start place to be filled in Data arr
 * uint8* : data array
 * uint8  : charc. count in the current record
***************************************************************************/
static uint8 Write_line_of_Data(uint8* Record, uint16 i_Record, uint8 counter, uint8 *Data_arr,uint8 cc)
{  
   uint8 LocaleState = E_OK;
   for(uint8 k=0;k<cc;k++)
   {	
     Data_arr[(counter*16)+k] = Record[i_Record+8+k];
   }
   return LocaleState;
}

/***************************************************************************
 *Params :
   uint8*     : Raw array of records of 1 page
   uint16     : size of array
 *return     :
   uint8*      : array of states of checksum for each record to help make decision if error was found
***************************************************************************/
uint8* Check_Sum(uint8* Record, uint16 Length_Rec)
{   uint8 LocaleState[64] = {E_OK};
	uint32 sum = 0;
	uint8 CS = 0;
	uint8 cc  ;
	uint8 index=0;
	uint8 Low_Byte = 0;
    uint32 current_bytes = 0;
    uint8 LocaleState_indx=0;
	for(uint16 i=0;i<Length_Rec-3;i++)
	{
		current_bytes = (Record[i]<<24) | (Record[i+1]<<16) |(Record[i+2]<< 8)|Record[i+3];
		if (current_bytes == Start_Of_Rec)
		{
			sum = 0;
			cc = Record[i+4];
			if(cc == 0x10)
			{
				index=24;
			}else if(cc == 0x02)
			{
				index=10;
			}else if(cc == 0x08)
			{
				index=16;
			}
			else
			{
				printf("NOT Handeled");
			}
			CS = Record[i+index];
		    for(uint8 k=4;k<index;k++) //for adding all the bytes in the record
		    {
			  sum += Record[i+k];
		    }
			Low_Byte = (uint8)(sum & 0x00ff);  //Taking least byte
			Low_Byte = (~Low_Byte) + 1;       //complementing it then add 1
			if (Low_Byte == CS)
			{
//				LocaleState = E_OK;
				LocaleState[LocaleState_indx]=E_OK;
				printf(" OK %d \n",LocaleState_indx);
			}
			else
			{
//				LocaleState = E_NOK;
				LocaleState[LocaleState_indx]=E_NOK;
				printf(" NOK %d \n",LocaleState_indx);
				//resend the whole hex file again loop on returned state array if E_Nok found take decision
			}

			LocaleState_indx++;
		}

	}
	return &LocaleState;
}

/***************************************************************************
 *Params :
   uint8     : first char(num1)
   uint8     : second char(num2)
 *return     :
   uint8     : num1 & num2 as 1 byte
***************************************************************************/

uint8 Make_Byte(uint8 num1, uint8 num2)
{
	return (num1<<4 | num2);
}

static uint8 WriteEndOfFile(uint8 counter, uint8 *Data_arr)
{
	uint8 LocaleState = E_OK;
    for(uint8 k=0;k<8;k++)
	{
	  Data_arr[(counter*16)+k] = '#';
	}
	return LocaleState;
}

/*
uint8 BL_RecParser(uint8* Record,uint16 Length_Rec, Record_t* struc,uint16* High_add_Part)
{
	    uint8 LocaleState = E_OK;
		static uint8 counter =0;   // counter for last place used in add array in struc
	    uint8 cc  ;                //data byte(char) count in one record
		uint8 rec_type ;         //type of data bytes in record
		uint32 current_bytes = 0;
	    struc->Low_add_Part[0]= 0;
	    struc->Low_add_Part[1]= 0;
	    struc->Low_add_Part[2]= 0;
	    struc->Low_add_Part[3]= 0;
		cc = 0;
		rec_type = 0;
		cc = Record[0];
		rec_type= Record[3];
		switch(rec_type)
		{
		  case 0:	//Data Bytes
			  struc->Low_add_Part[0]  = Record[2];
			  struc->Low_add_Part[1] |= (Record[1])<<8;
			  for(uint8 i=0;i<16;i++)
			  {
				  struc->Data_arr[i]= Record[i+4];
			  }
			  break;
		  case 1:  //EOF....8 of # indicating End of File
				WriteEndOfFile(counter,struc->Data_arr);
				break ;
		  case 4:  //High Add Part
			 *High_add_Part= Record[5];
			 *High_add_Part |= Record[4]<<8;
				break ;
		}

	  return LocaleState;
}
*/
