/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : UART                                                */
/* Version : 1.0                                                 */
/* Date    : 11 Feb 2024                                         */
/*****************************************************************/
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#define UART1_RX_PORT GPIO_PORTA
#define UART1_RX_PIN  GPIO_PIN10

#define UART1_TX_PORT GPIO_PORTA
#define UART1_TX_PIN  GPIO_PIN9

void UART1_voidInit(void);

void UART1_voidTransmitSynch(uint8 u8DataCpy);

uint8 UART1_u8ReceiveSynch(void);

uint8 UART1_u8GetData(void);

void UART1_voidReceiveIntEnable(void);

void UART1_voidReceiveIntDisable(void);

void UART1_voidSetCallBack(pf pfUART1ISRCpy);

uint32* UART1_pu32DMAReceiveAddress(void);

#endif
