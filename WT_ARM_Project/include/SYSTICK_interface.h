/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : SYSTICK                                             */
/* Version : 1.0                                                 */
/* Date    : 11 Feb 2024                                         */
/*****************************************************************/
#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_


typedef enum{
	SYSTICK_INT_DISABLE,
	SYSTICK_INT_ENABLE
}tstrSYSTICK_IntState;

/*Clock Configuration*/
void SYSTICK_voidInit(void);

void SYSTICK_voidEnable(void);

void SYSTICK_voidDisable(void);

tenuErrorStatus SYSTICK_enuStart(uint32 u32LoadValueCpy);

tenuErrorStatus SYSTICK_enuDelayUs(uint32 u32DelayCpy);

tenuErrorStatus SYSTICK_enuDelayMs(uint32 u32DelayCpy);

uint8 SYSTICK_u8ReadFlag(void);

void SYSTICK_voidCtrlIntState(tstrSYSTICK_IntState enuStateCpy);

uint32 SYSTICK_u32GetElapsedTime(void);

tenuErrorStatus SYSTICK_enuSetInterval_single(uint32 u32LoadValue, pf pfCallBackFun);

tenuErrorStatus SYSTICK_enuSetInterval_periodic(uint32 u32LoadValue, pf pfCallBackFun);


#endif
