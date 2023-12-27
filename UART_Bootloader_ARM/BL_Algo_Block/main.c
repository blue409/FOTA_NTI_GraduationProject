#include "Bl_Algo.h"
#include <stdio.h>
/***************************************************************************  
                           FUNCTION PROTOTYPES                
****************************************************************************/
int ascii_to_hex(char c);
uint8 ArrayOfHex(uint8* final_hex,uint16 Lenght);
/***************************************************************************  
                            VARIABLES                
****************************************************************************/
//uint8 final_hex[1645]={0, 0, 1, 0xfe, 0x3a, 2, 0, 0, 4, 8, 0, 0xf2}; //small rec
uint8 final_hex[1645]={0, 0, 1, 0xfe, 0x3a, 0x10, 0, 0, 0, 0, 0x50, 0, 0x20, 0x21, 2, 0, 8, 0x27, 2, 0, 8, 0x2b, 2, 0, 8, 0xef}; //small rec
uint8 flag_not_complete = 0;
Record_t records_2 ;
uint16 High_address =0;
uint8* res = NULL_PTR;

int main(void)
{
 uint16 i;
 ArrayOfHex(final_hex,1643);   //1643 //38
 printf("\n ==============================ThE END================================");

 res = BLOCK_Parser(final_hex,1643,&records_2,&High_address);
 if(res != E_OK)
 {
  printf("\n ==========Early return===========");
  return 0;
 }
 printf("\n the High address part :%x ", High_address);
 for(uint8 k=1;k<64;k++)
 {
  printf("\n the Low address part :%x \t",records_2.Low_add_Part[k]);  //0
  for(i=16*k;i<(16*(k+1));i++)
   {
      printf("the data part : %x ", records_2.Data_arr[i]);
//    if((i % 16)==0){printf("\n ==============================================================");}
   }
 }
// for(uint8 i =16;i<1024;i++)
//  {
//   printf("the data part : %x ", records_2.Data_arr[i]);
//     if((i % 16)==0){printf("\n ==============================================================");}
//  }

////////////////////////////////////////CHECKSUM TEST/////////////////////////////////////////////////////////
//	res = Check_Sum(final_hex, 26);  //tests passed
//	if(res == E_OK)
//	{
//		printf("\n ==========success========");
//	}else
//	{
//		printf("\n ==========Failed========");
//	}
////////////////////////////////////////CHECKSUM TEST//////////////////////////////////////////////////////////
// ArrayOfHex(final_hex, 1643);   //1643
// res = Check_Sum(final_hex, 1643);
// printf(" ==============================\n");
// for(uint8 i=0;i<65;i++)
// {
//	 printf("OK %d \n",*(res + i));
// }


  return 0;
}

/***************************************************************************
                         USER FUNCTION DEFINITION
****************************************************************************/
/***************************************************************************
 * @Def   : Fills an array with hex numbers recieved from hex file
 * @Params:
 * uint8* : array to be filled with hex file
 * uint16 : controls the length of bytes we will fill the array with
****************************************************************************/
uint8 ArrayOfHex(uint8* final_hex,uint16 Lenght)   //donot handle GPIO.hex
{
  FILE *fp = fopen("stmexport","r");    ///fopen("GPIO.hex","r")  fopen("stmexport","r")
  
  if(fp == NULL)
  {
    return E_NOK;
  }
  uint8 sum,c1,c2;
  for(uint16 i=0;i<Lenght;i++)     //1643 prints the end of the record...correctly
  { 
    c1 = ascii_to_hex(fgetc(fp));
    c2 = ascii_to_hex(fgetc(fp));
    sum = c1<<4 | c2;
    final_hex[i] = sum;
//    printf("%x ",final_hex[i]);
  }
 // printf("\n ThE END ");

  return E_OK;
}

/***************************************************************************
 @Def   :  converts the char to hex num
 @Params:
 * uint8 : the char to be converted to hex num.
****************************************************************************/
int ascii_to_hex(char c)
{
        int num =  (int)c;
        if(num < 58 && num > 47)
        {
                return num - 48; 
        }
        if(num < 103 && num > 96)
        {
                return num - 87;
        }
        if(num < 71 && num > 64)
        {
          return num - 55;
        }
        
        return num;
}


/*
//  FILE *fp = fopen("stmexport","r");    ///fopen("GPIO.hex","r")
  
  // if(fp == NULL)
  // {
  //   return 0;
  // }
  // uint8 sum,c1,c2;
  // uint8 final_hex[1645]={0};  //elmafrod 1643
  // for(uint16 i=0;i<1643;i++)     //1643 prints the end of the record...correctly
  // { 
  //   c1 = ascii_to_hex(fgetc(fp));
  //   c2 = ascii_to_hex(fgetc(fp));
  //   sum = c1<<4 | c2;
  //   final_hex[i] = sum;
  //   printf("%x ",final_hex[i]);
  // }
  // printf("\n ThE END ");
*/


/**
 * FILE *fp = fopen("GPIO.hex","r");
  
  if(fp == NULL)
  {
    return 0;
  }
  uint8 sum,final_hex[1600],a[1600];
  for(uint8 i=0;i<25;i++)
  {
     if((fgets(final_hex, sizeof(final_hex), fp) != NULL))
     {
       // printf("%2x ",final_hex[i]);
      
        int b; // must use int with sscanf()
        sscanf(&final_hex[i], "%x", &b);
        a[i] = b;        
     }else{
      return 0;
     }
   printf("%x ",a[i]);   
  }
  printf("ThE END n");

  return 0; 
*/


/*
   if(i == 17)
   {
      for(uint8 j =0;j<27;j++)
      {
          c1= ascii_to_hex(fgetc(fp));
          c2=0;
         if(c1 == 58 || c1==10)
          {                               // call it in another func
           c2 =c1;
           c1=0;
         }else{
          c2 = ascii_to_hex(fgetc(fp));
         }
         sum = c1<<4 | c2;
         final_hex[i] = sum;
         i++;
      }
    }*/

