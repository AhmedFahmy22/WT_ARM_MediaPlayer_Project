/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : SYSTICK                                             */
/* Version : 1.0                                                 */
/* Date    : 11 Feb 2024                                         */
/*****************************************************************/
#include "STD_Types.h"
#include "BIT_Math.h"

#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"
#include "SYSTICK_config.h"

static pf pfSysTickISRGlb = NULL_PTR;
static uint8 u8PeriodicModeGlb = 0;

void SYSTICK_voidInit(void)
{
	/*Clock*/
#if SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY8
	CLR_BIT(SYSTICK_REG->CTRL,CTRL_CLKSOURCE);
#elif SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY1
	SET_BIT(SYSTICK_REG->CTRL,CTRL_CLKSOURCE);
#endif

	/*Interrupt EN/DISABLE*/
#if SYSTICK_INTERRUPT == SYSTICK_INTERRUPT_DISABLE
	CLR_BIT(SYSTICK_REG->CTRL,CTRL_TICKINT);
#elif SYSTICK_INTERRUPT == SYSTICK_INTERRUPT_ENABLE
	SET_BIT(SYSTICK_REG->CTRL,CTRL_TICKINT);
#endif

	/*SysTick EN/DISABLE*/
#if SYSTICK_STATE == SYSTICK_STATE_DISABLE
	CLR_BIT(SYSTICK_REG->CTRL,CTRL_ENABLE);
#elif SYSTICK_STATE == SYSTICK_STATE_ENABLE
	SET_BIT(SYSTICK_REG->CTRL,CTRL_ENABLE);
#endif
}

void SYSTICK_voidEnable(void)
{
	SET_BIT(SYSTICK_REG->CTRL,CTRL_ENABLE);
}

void SYSTICK_voidDisable(void)
{
	CLR_BIT(SYSTICK_REG->CTRL,CTRL_ENABLE);
}

tenuErrorStatus SYSTICK_enuStart(uint32 u32LoadValueCpy)
{
    tenuErrorStatus enuErrorStatLoc = E_OK;
    if(u32LoadValueCpy>SYSTICK_LOAD_MAX_VALUE)
    {
        enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
    }
    else
    {
        SYSTICK_REG->LOAD = u32LoadValueCpy;
    	SYSTICK_REG->VAL = 0;
    }

    return enuErrorStatLoc;
}

tenuErrorStatus SYSTICK_enuDelayUs(uint32 u32DelayCpy)
{
    tenuErrorStatus enuErrorStatLoc = E_OK;

	SYSTICK_voidCtrlIntState(SYSTICK_INT_DISABLE);

#if SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY8
	enuErrorStatLoc = SYSTICK_enuStart(u32DelayCpy*2);
#elif SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY1
	enuErrorStatLoc = SYSTICK_enuStart(u32DelayCpy*16);
#endif

    if(enuErrorStatLoc==E_OK)
    {
        while(GET_BIT(SYSTICK_REG->CTRL,CTRL_COUNTFLAG)==0);
    }

	return enuErrorStatLoc;
}

tenuErrorStatus SYSTICK_enuDelayMs(uint32 u32DelayCpy)
{
    tenuErrorStatus enuErrorStatLoc = E_OK;

	SYSTICK_voidCtrlIntState(SYSTICK_INT_DISABLE);

#if SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY8
	enuErrorStatLoc = SYSTICK_enuStart(u32DelayCpy*2000);
#elif SYSTICK_CLK_SOURCE == SYSTICK_AHB_DIVBY1
	enuErrorStatLoc = SYSTICK_enuStart(u32DelayCpy*16000);
#endif

    if(enuErrorStatLoc==E_OK)
    {
        while(GET_BIT(SYSTICK_REG->CTRL,CTRL_COUNTFLAG)==0);
    }

	return enuErrorStatLoc;
}

uint8 SYSTICK_u8ReadFlag(void)
{
	return (GET_BIT(SYSTICK_REG->CTRL,CTRL_COUNTFLAG));
}

void SYSTICK_voidCtrlIntState(tstrSYSTICK_IntState enuStateCpy)
{
	SYSTICK_REG->CTRL = (SYSTICK_REG->CTRL & ~(1<<CTRL_TICKINT)) | (enuStateCpy<<CTRL_TICKINT);
}

uint32 SYSTICK_u32GetElapsedTime(void)
{
	return ((SYSTICK_REG->LOAD)-(SYSTICK_REG->VAL));
}

uint32 SYSTICK_u32GetRemainingTime(void)
{
	return (SYSTICK_REG->VAL);
}

tenuErrorStatus SYSTICK_enuSetInterval_single(uint32 u32LoadValue, pf pfCallBackFun)
{
    tenuErrorStatus enuErrorStatLoc = E_OK;

    if(pfCallBackFun==NULL_PTR)
    {
        enuErrorStatLoc = E_NOK_NULL_POINTER;
    }
    else
    {
        enuErrorStatLoc=SYSTICK_enuStart(u32LoadValue);
        if(enuErrorStatLoc==E_OK)
        {
            pfSysTickISRGlb = pfCallBackFun;
        	u8PeriodicModeGlb=SINGLE_MODE;
        }
    }

	return enuErrorStatLoc;
}

tenuErrorStatus SYSTICK_enuSetInterval_periodic(uint32 u32LoadValue, pf pfCallBackFun)
{
    tenuErrorStatus enuErrorStatLoc = E_OK;

    if(pfCallBackFun==NULL_PTR)
    {
        enuErrorStatLoc = E_NOK_NULL_POINTER;
    }
    else
    {
        enuErrorStatLoc=SYSTICK_enuStart(u32LoadValue);
        if(enuErrorStatLoc==E_OK)
        {
            pfSysTickISRGlb = pfCallBackFun;
        	u8PeriodicModeGlb=PERIODIC_MODE;
        }
    }

	return enuErrorStatLoc;
}

void SysTick_Handler(void)
{
	if(pfSysTickISRGlb!=NULL_PTR)
	{
		pfSysTickISRGlb();
		if(u8PeriodicModeGlb==SINGLE_MODE)
		{
			pfSysTickISRGlb = NULL_PTR;
		}
	}
	else
	{

	}
}
