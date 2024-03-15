/*
 * EXTI_prog.c
 *
 *  Created on: Jan 18, 2024
 *      Author: Ahmed
 */
#include "BIT_Math.h"
#include "STD_Types.h"

#include "EXTI_int.h"
#include "EXTI_cfg.h"
#include "EXTI_priv.h"

pf apfExtiISRGlb[16];

void EXTI_voidInerruptSetPort(EXTI_Line enuLineCpy,EXTI_Port enuPortCpy)
{
	SYSCF_REG->EXTICR[enuLineCpy/4]  = ((SYSCF_REG->EXTICR[enuLineCpy/4])&(~(0x0F<<(4*(enuLineCpy%4)))))|(enuPortCpy<<(4*(enuLineCpy%4)));
}

void EXTI_voidInterruptEnableDisable(EXTI_Line enuLineCpy , EXTI_ENDis enuENDisCpy)
{
	switch(enuENDisCpy)
	{
	case EXTI_Disable:
		CLR_BIT(EXTI_REG->IMR, enuLineCpy);
		break;
	case EXTI_Enable:
		SET_BIT(EXTI_REG->IMR, enuLineCpy);
		break;
	default:
		break;
	}
}

void EXTI_voidInterruptTrigger(EXTI_Line enuLineCpy,EXTI_Trigger enuTriggerCpy)
{
	switch(enuTriggerCpy)
	{
	case EXTI_Rising:
		CLR_BIT(EXTI_REG->FTSR,enuLineCpy);
		SET_BIT(EXTI_REG->RTSR,enuLineCpy);
		break;
	case EXTI_Falling:
		SET_BIT(EXTI_REG->FTSR,enuLineCpy);
		CLR_BIT(EXTI_REG->RTSR,enuLineCpy);
		break;
	case EXTI_OnChange:
		SET_BIT(EXTI_REG->FTSR,enuLineCpy);
		SET_BIT(EXTI_REG->RTSR,enuLineCpy);
		break;
	default:
		break;
	}
}

void EXTI_voidSetCallBack(EXTI_Line enuLineCpy, pf pfIsrCpy)
{
	apfExtiISRGlb[enuLineCpy] = pfIsrCpy;
}

void EXTI0_IRQHandler(void)
{
	if(apfExtiISRGlb[0]!=NULL_PTR)
	{
		apfExtiISRGlb[0]();
	}
	EXTI_REG->PR |= 1;
}

void EXTI1_IRQHandler(void)
{
	if(apfExtiISRGlb[1]!=NULL_PTR)
	{
		apfExtiISRGlb[1]();
	}
	EXTI_REG->PR |= 1<<1;
}

void EXTI15_10_IRQHandler(void)
{
    uint8 u8CntrLoc = 0;

    for(u8CntrLoc = 10; u8CntrLoc<16; u8CntrLoc++)
    {
        if(GET_BIT(EXTI_REG->PR,u8CntrLoc)==1)
        {
            if(apfExtiISRGlb[u8CntrLoc]!=NULL_PTR)
        	{
        		apfExtiISRGlb[u8CntrLoc]();
        	}
        	EXTI_REG->PR |= 1<<u8CntrLoc;
        }
    }
}

/*Task*/
/*2 buttons EXTI--> 1st: 8Leds On, 2nd: turn off all leds*/
/*Tomorrow 11:59pm*/
