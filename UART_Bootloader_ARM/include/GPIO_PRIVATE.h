/*********************************************************************************/
/* Author    : Ahmed Osama                                                       */
/* Version   : V01                                                               */
/* Date       : 12 August 2020                                                    */
/*********************************************************************************/
#ifndef GPIO_PRIVATE_h
#define GPIO_PRIVATE_h

/*GPIO on ABP2*/
#define GPIOA_BASE_ADSRESS       0x40010800
#define GPIOB_BASE_ADSRESS       0x40010C00
#define GPIOC_BASE_ADSRESS   	 0x40011000

/*Registers addresses for port A*/
#define GPIOA_CRL				 *((u32*)(GPIOA_BASE_ADSRESS+0x00))
#define GPIOA_CRH				 *((u32*)(GPIOA_BASE_ADSRESS+0x04))
#define GPIOA_IDR				 *((u32*)(GPIOA_BASE_ADSRESS+0x08))
#define GPIOA_ODR				 *((u32*)(GPIOA_BASE_ADSRESS+0x0C))
#define GPIOA_BSR				 *((u32*)(GPIOA_BASE_ADSRESS+0x10))
#define GPIOA_BRR				 *((u32*)(GPIOA_BASE_ADSRESS+0x14))
#define GPIOA_LCK				 *((u32*)(GPIOA_BASE_ADSRESS+0x18))
/*REGISTERS addresses FOR PORTB*/
#define GPIOB_CRL				 *((u32*)(GPIOB_BASE_ADSRESS+0x00))
#define GPIOB_CRH				 *((u32*)(GPIOB_BASE_ADSRESS+0x04))
#define GPIOB_IDR				 *((u32*)(GPIOB_BASE_ADSRESS+0x08))
#define GPIOB_ODR				 *((u32*)(GPIOB_BASE_ADSRESS+0x0C))
#define GPIOB_BSR				 *((u32*)(GPIOB_BASE_ADSRESS+0x10))
#define GPIOB_BRR				 *((u32*)(GPIOB_BASE_ADSRESS+0x14))
#define GPIOB_LCK				 *((u32*)(GPIOB_BASE_ADSRESS+0x18))
/*REGISTERS addresses FOR PORTC*/
#define GPIOC_CRL				 *((u32*)(GPIOC_BASE_ADSRESS+0x00))
#define GPIOC_CRH				 *((u32*)(GPIOC_BASE_ADSRESS+0x04))
#define GPIOC_IDR				 *((u32*)(GPIOC_BASE_ADSRESS+0x08))
#define GPIOC_ODR				 *((u32*)(GPIOC_BASE_ADSRESS+0x0C))
#define GPIOC_BSR				 *((u32*)(GPIOC_BASE_ADSRESS+0x10))
#define GPIOC_BRR				 *((u32*)(GPIOC_BASE_ADSRESS+0x14))
#define GPIOC_LCK				 *((u32*)(GPIOC_BASE_ADSRESS+0x18))





#endif
