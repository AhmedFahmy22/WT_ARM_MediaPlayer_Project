/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : SYSTICK                                             */
/* Version : 1.0                                                 */
/* Date    : 11 Feb 2024                                         */
/*****************************************************************/
#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_


#define SYSTICK_BASE_ADDRESS (0xE000E010)

typedef struct
{
	uint32 CTRL;
	uint32 LOAD;
	uint32 VAL;
	uint32 CALIB;
}SYSTICK_t;

#define SYSTICK_REG ((volatile SYSTICK_t*)SYSTICK_BASE_ADDRESS)

typedef enum{
	PERIODIC_MODE,
	SINGLE_MODE
}enuPeriodicMode;

#define CTRL_ENABLE 0
#define CTRL_TICKINT 1
#define CTRL_CLKSOURCE 2
#define CTRL_COUNTFLAG 16

#define SYSTICK_AHB_DIVBY8 0
#define SYSTICK_AHB_DIVBY1 1

#define SYSTICK_STATE_DISABLE 0
#define SYSTICK_STATE_ENABLE  1

#define SYSTICK_INTERRUPT_DISABLE 0
#define SYSTICK_INTERRUPT_ENABLE  1

#define SYSTICK_LOAD_MAX_VALUE 0xFFFFFF

#endif
