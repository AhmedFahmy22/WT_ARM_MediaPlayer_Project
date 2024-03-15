/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : NVIC                                                */
/* Version : 1.0                                                 */
/* Date    : 02 Feb 2024                                         */
/*****************************************************************/
#include "STD_Types.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"

static tenuNVIC_groups enuGroupModeGlb;

void NVIC_voidEnable(tenuNVIC_intPos enuPositionCpy)
{
	NVIC_REG->ISER[enuPositionCpy/32] |= (1<<(enuPositionCpy%32));
}

void NVIC_voidDisable(tenuNVIC_intPos enuPositionCpy)
{
	NVIC_REG->ICER[enuPositionCpy/32] |= (1<<(enuPositionCpy%32));
}

void NVIC_voidPendingSet(tenuNVIC_intPos enuPositionCpy)
{
	NVIC_REG->ISPR[enuPositionCpy/32] |= (1<<(enuPositionCpy%32));
}

void NVIC_voidPendingClear(tenuNVIC_intPos enuPositionCpy)
{
	NVIC_REG->ICPR[enuPositionCpy/32] |= (1<<(enuPositionCpy%32));
}

uint8 NVIC_u8ActiveRead(tenuNVIC_intPos enuPositionCpy)
{
	uint8 u8ActiveValueLoc = 0;

	u8ActiveValueLoc = ((NVIC_REG->ICPR[enuPositionCpy/32])>>(enuPositionCpy%32))&1;

	return u8ActiveValueLoc;
}

void NVIC_voidSetInterruptGroupMode(tenuNVIC_groups enuGroupModeCpy)
{
	uint32 u32PortWriteLoc;
	enuGroupModeGlb = enuGroupModeCpy;
	u32PortWriteLoc =  NVIC_VECTKEY | (enuGroupModeCpy<<8);
	AIRCR = u32PortWriteLoc;
}

void NVIC_voidSetInterruptPriority(tenuNVIC_intPos enuPositionCpy, uint8 u8GroupPriCpy, uint8 u8SubPriCpy)
{
    switch(enuGroupModeGlb)
    {
    case Group16Sub0:
    	NVIC_REG->IPR[enuPositionCpy] = (u8GroupPriCpy<<4);
    	break;
    case Group8Sub2:
    	NVIC_REG->IPR[enuPositionCpy] = (u8GroupPriCpy<<5)|(u8SubPriCpy<<4);
    	break;
    case Group4Sub4:
    	NVIC_REG->IPR[enuPositionCpy] = (u8GroupPriCpy<<6)|(u8SubPriCpy<<4);
    	break;
    case Group2Sub8:
    	NVIC_REG->IPR[enuPositionCpy] = (u8GroupPriCpy<<7)|(u8SubPriCpy<<4);
    	break;
    case Group0Sub16:
    	NVIC_REG->IPR[enuPositionCpy] = (u8SubPriCpy<<4);
    	break;
    }
}
