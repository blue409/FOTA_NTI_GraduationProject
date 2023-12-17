 /*********************************************************************************/
/* Author    : Ahmed Osama                                                       */
/* Version   : V01                                                               */
/* Date      : 12 August 2020                                                    */
/*********************************************************************************/
#ifndef GPIO_INTERFACE_h
#define GPIO_INTERFACE_h

#define GPIOA	0
#define GPIOB	1
#define GPIOC	2

#define GPIN0	0
#define GPIN1	1
#define GPIN2	2
#define GPIN3	3
#define GPIN4	4
#define GPIN5	5
#define GPIN6	6
#define GPIN7	7
#define GPIN8	8
#define GPIN9	9
#define GPIN10	10
#define GPIN11	11
#define GPIN12	12
#define GPIN13	13
#define GPIN14	14
#define GPIN15	15

#define GPIO_HIGH 1
#define GPIO_LOW 0

#define INPUT_Analoge       0b0000
#define INPUT_FLOATING      0b0100
#define INPUT_PULL_UP_DOWEN 0b1000


#define OUTPUT_SPEED_10MHZ_PP   0b0001
#define OUTPUT_SPEED_10MHZ_OD   0b0101
#define OUTPUT_SPEED_10MHZ_AFPP 0b1001
#define OUTPUT_SPEED_10MHZ_AFOD 0b1101

#define OUTPUT_SPEED_2MHZ_PP   0b0010
#define OUTPUT_SPEED_2MHZ_OD   0b0110
#define OUTPUT_SPEED_2MHZ_AFPP 0b1010
#define OUTPUT_SPEED_2MHZ_AFOD 0b1110


#define OUTPUT_SPEED_50MHZ_PP   0b0011
#define OUTPUT_SPEED_50MHZ_OD   0b0111
#define OUTPUT_SPEED_50MHZ_AFPP 0b1011
#define OUTPUT_SPEED_50MHZ_AFOD 0b1111




void MGPIO_VoidSetPinDirection(u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Mode);

void MGPIO_VoidSetPinValue(u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Value);

u8 MGPIO_u8GetPinValue(u8 copy_u8PORT , u8 copy_u8PIN);


#endif

