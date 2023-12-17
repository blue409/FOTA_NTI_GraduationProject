#ifndef   STD_TYPES_H_
#define   STD_TYPES_H_


typedef unsigned char      u8;
typedef signed char        int8 ;



typedef unsigned short int   u16;
typedef unsigned long  int   u32;

typedef signed char        s8 ;
typedef signed short int   s16;
typedef signed long  int   s32;

typedef unsigned char uint_8t;

typedef unsigned short int uint_16t;

typedef unsigned long int uint_32t;

typedef unsigned long long uint_64t;

typedef signed char int_8t;

typedef signed short int int_16t;

typedef signed long int int_32t;

#define OK 		0
/**
 * @def     OK
 * @brief   used in Checking Error
 */
#define NOK  	1
/**
 * @def     BUSY
 * @brief   used in Check Status
 */
#define BUSY	2
/**
 * @def     OK
 * @brief   used in Checking
 */
#define ON 		1
/**
 * @def     OFF
 * @brief   used in Checking
 */
#define OFF  	0
/**
 * @def     NULL
 */

typedef void (* pf) (void);


#define NULL (void *)0




#endif
