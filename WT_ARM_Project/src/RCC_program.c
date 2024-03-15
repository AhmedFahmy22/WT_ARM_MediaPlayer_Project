/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : RCC                                                 */
/* Version : 1.0                                                 */
/* Date    : 02 Feb 2024                                         */
/*****************************************************************/
#include "STD_Types.h"
#include "BIT_Math.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

void RCC_voidInit(void)
{
#if RCC_SYS_CLK == RCC_SYS_CLK_HSE
	/*bypass -> crystal oscillator(2 pins) or RC(1 pin)*/
	RCC_REG->CR &= ~(1<<RCC_HSEBYP);
	RCC_REG->CR |= 1<<RCC_HSEON;
	while(GET_BIT(RCC_REG->CR, RCC_HSERDY)==0);
	RCC_REG->CFGR &= SWITCH_MASK;
	RCC_REG->CFGR |= RCC_SYS_CLK_HSE;
#elif RCC_SYS_CLK == RCC_SYS_CLK_HSI
	RCC_REG->CR |= 1<<RCC_HSION;
	while(GET_BIT(RCC_REG->CR, RCC_HSIRDY)==0);
	RCC_REG->CFGR &= SWITCH_MASK;
	RCC_REG->CFGR |= RCC_SYS_CLK_HSI;
#endif
}
void RCC_voidEnable(BUS_t enuBusCpy, uint16 u16PeripheralCpy)
{
	switch(enuBusCpy)
	{
	case AHB1:
		RCC_REG->AHB1ENR |= 1<<u16PeripheralCpy;
		break;
	case AHB2:
		RCC_REG->AHB2ENR |= 1<<u16PeripheralCpy;
		break;
	case APB1:
		RCC_REG->APB1ENR |= 1<<u16PeripheralCpy;
		break;
	case APB2:
		RCC_REG->APB2ENR |= 1<<u16PeripheralCpy;
		break;
	}
}
void RCC_voidDisable(BUS_t enuBusCpy, uint16 u16PeripheralCpy)
{
	switch(enuBusCpy)
	{
	case AHB1:
		RCC_REG->AHB1ENR &= ~(1<<u16PeripheralCpy);
		break;
	case AHB2:
		RCC_REG->AHB2ENR &= ~(1<<u16PeripheralCpy);
		break;
	case APB1:
		RCC_REG->APB1ENR &= ~(1<<u16PeripheralCpy);
		break;
	case APB2:
		RCC_REG->APB2ENR &= ~(1<<u16PeripheralCpy);
		break;
	}
}
