/*
 * EXTI_int.h
 *
 *  Created on: Jan 18, 2024
 *      Author: Ahmed
 */

#ifndef EXTI_INT_H_
#define EXTI_INT_H_


#ifndef MEXTI_INT_H
#define MEXTI_INT_H

typedef enum{
	EXTI_Disable,
	EXTI_Enable
}EXTI_ENDis;

typedef enum{
	EXTI_Rising,
	EXTI_Falling,
	EXTI_OnChange
}EXTI_Trigger;

typedef enum{
	EXTI_LineZero=0,
	EXTI_LineOne,
	EXTI_LineTwo,
	EXTI_LineThree,
	EXTI_LineFour,
	EXTI_LineFive,
	EXTI_LineSix,
	EXTI_LineSeven,
	EXTI_LineEight,
	EXTI_LineNine,
	EXTI_LineTen,
	EXTI_LineEleven,
	EXTI_LineTwelve,
	EXTI_LineThirteen,
	EXTI_LineFourteen,
	EXTI_LineFifteen

}EXTI_Line;

typedef enum{
EXTI_PortA=0,
EXTI_PortB,
EXTI_PortC,
EXTI_PortD,
EXTI_PortE,
EXTI_PortH=7,

}EXTI_Port;

void EXTI_voidInerruptSetPort(EXTI_Line enuLineCpy,EXTI_Port enuPortCpy);
void EXTI_voidInterruptEnableDisable(EXTI_Line enuLineCpy , EXTI_ENDis enuENDisCpy);
void EXTI_voidInterruptTrigger(EXTI_Line enuLineCpy,EXTI_Trigger enuTriggerCpy);
void EXTI_voidSetCallBack(EXTI_Line enuLineCpy, pf pfIsrCpy);

#endif


#endif /* EXTI_INT_H_ */
