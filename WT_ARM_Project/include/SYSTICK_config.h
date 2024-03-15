/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : SYSTICK                                             */
/* Version : 1.0                                                 */
/* Date    : 11 Feb 2024                                         */
/*****************************************************************/
#ifndef SYSTICK_CONFIG_H_
#define SYSTICK_CONFIG_H_

/*Options
SYSTICK_AHB_DIVBY1
SYSTICK_AHB_DIVBY8
*/
#define SYSTICK_CLK_SOURCE  SYSTICK_AHB_DIVBY8

/*Options
SYSTICK_STATE_DISABLE
SYSTICK_STATE_ENABLE
*/
#define SYSTICK_STATE SYSTICK_INTERRUPT_ENABLE

/*Options
SYSTICK_INTERRUPT_DISABLE
SYSTICK_INTERRUPT_ENABLE
*/
#define SYSTICK_INTERRUPT SYSTICK_INTERRUPT_DISABLE

#endif
