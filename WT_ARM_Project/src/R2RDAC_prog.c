/*
 * R2RDAC_prog.c
 *
 *  Created on: Jan 23, 2024
 *      Author: Ahmed
 */

#include "STD_Types.h"
#include "BIT_Math.h"

#include "GPIO_interface.h"
#include "SYSTICK_interface.h"

#include "R2RDAC_int.h"
#include "R2RDAC_cfg.h"

void R2RDAC_voidInit(void)
{
	uint8 u8CntrLoc = 0;

	SYSTICK_voidInit();

	for(u8CntrLoc=0;u8CntrLoc<8;u8CntrLoc++)
	{
		GPIO_enuSetMode(GPIO_PORTA, u8CntrLoc, GPIO_MODE_OUTPUT);
		GPIO_enuWritePinValue(GPIO_PORTA, u8CntrLoc, 0);
	}
}

void R2RDAC_voidWriteChar(const uint8 u8DataCpy)
{
	GPIO_enuWritePinValue(GPIO_PORTB, GPIO_PIN0, GET_BIT(u8DataCpy,0));
	GPIO_enuWritePinValue(GPIO_PORTB, GPIO_PIN1, GET_BIT(u8DataCpy,1));
	GPIO_enuWritePinValue(GPIO_PORTA, GPIO_PIN2, GET_BIT(u8DataCpy,2));
	GPIO_enuWritePinValue(GPIO_PORTA, GPIO_PIN3, GET_BIT(u8DataCpy,3));
	GPIO_enuWritePinValue(GPIO_PORTB, GPIO_PIN5, GET_BIT(u8DataCpy,4));
	GPIO_enuWritePinValue(GPIO_PORTB, GPIO_PIN6, GET_BIT(u8DataCpy,5));
	GPIO_enuWritePinValue(GPIO_PORTB, GPIO_PIN7, GET_BIT(u8DataCpy,6));
	GPIO_enuWritePinValue(GPIO_PORTB, GPIO_PIN8, GET_BIT(u8DataCpy,7));

}

void R2RDAC_voidSetData(const uint8* au8DataCpy, uint32 u32ArrLengthCpy)
{
	uint32 u32ArrCntrLoc = 0;

	for(u32ArrCntrLoc=0;u32ArrCntrLoc<u32ArrLengthCpy;u32ArrCntrLoc++)
	{
		R2RDAC_voidWriteChar(au8DataCpy[u32ArrCntrLoc]);
		SYSTICK_enuDelayUs(125);
	}
}
