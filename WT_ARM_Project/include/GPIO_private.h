/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : GPIO                                                */
/* Version : 1.0                                                 */
/* Date    : 02 Feb 2024                                         */
/*****************************************************************/
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

#define GPIOA_BASE_ADDRESS (0x40020000)
#define GPIOB_BASE_ADDRESS (0x40020400)
#define GPIOC_BASE_ADDRESS (0x40020800)

typedef struct{
	uint32 MODER;
	uint32 OTYPER;
	uint32 OSPEEDR;
	uint32 PUPDR;
	uint32 IDR;
	uint32 ODR;
	uint32 BSRR;
	uint32 LCKR;
	uint32 AFRL;
	uint32 AFRH;
}tstrGPIO_registers;

#define GPIOA_REG ((volatile tstrGPIO_registers*)GPIOA_BASE_ADDRESS)
#define GPIOB_REG ((volatile tstrGPIO_registers*)GPIOB_BASE_ADDRESS)
#define GPIOC_REG ((volatile tstrGPIO_registers*)GPIOC_BASE_ADDRESS)

#endif
