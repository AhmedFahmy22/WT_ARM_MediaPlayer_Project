/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : NVIC                                                */
/* Version : 1.0                                                 */
/* Date    : 02 Feb 2024                                         */
/*****************************************************************/
#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_


#define NVIC_BASE_ADDRESS (0xE000E100)

#define AIRCR (*((volatile uint32*)0xE000ED0C))

typedef struct{
	uint32 ISER[8];
	uint32 Reserved0[24];
	uint32 ICER[8];
	uint32 Reserved1[24];
	uint32 ISPR[8];
	uint32 Reserved2[24];
	uint32 ICPR[8];
	uint32 Reserved3[24];
	uint32 IABR[8];
	uint32 Reserved4[24];
	uint8 IPR[240];
	uint32 Reserved5[580];
}tstrNVIC_registers;

#define NVIC_REG ((volatile tstrNVIC_registers*)NVIC_BASE_ADDRESS)

#define NVIC_VECTKEY 0x05FA0000

#endif
