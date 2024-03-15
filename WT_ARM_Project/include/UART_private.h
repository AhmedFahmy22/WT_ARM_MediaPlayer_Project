/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : UART                                                */
/* Version : 1.0                                                 */
/* Date    : 11 Feb 2024                                         */
/*****************************************************************/
#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UART1_BASE_ADDRESS (0x40011000)

typedef struct {
	uint32 SR;
	uint32 DR;
	uint32 BRR;
	uint32 CR1;
	uint32 CR2;
	uint32 CR3;
	uint32 GTPR;
}UART_t;

#define UART1_REG ((volatile UART_t*) UART1_BASE_ADDRESS)

#define UART1_OVERSAMPLING_MODE_16 0
#define UART1_OVERSAMPLING_MODE_8 1

#define UART_STATE_DISABLE 0
#define UART_STATE_ENABLE  1

#define UART1_WORD_LENGTH_8 0
#define UART1_WORD_LENGTH_9 1

#define UART1_PARITY_STATE_DISABLE 0
#define UART1_PARITY_STATE_ENABLE  1

#define UART1_TRANSMIT_INTERRUPT_DISABLE 0
#define UART1_TRANSMIT_INTERRUPT_ENABLE  1

#define UART1_RECEIVE_INTERRUPT_DISABLE 0
#define UART1_RECEIVE_INTERRUPT_ENABLE  1

#define UART1_RECEIVER_STATE_DISABLE 0
#define UART1_RECEIVER_STATE_ENABLE  1

#define UART1_STOP_BITS_MODE_1   0
#define UART1_STOP_BITS_MODE_0_5 1
#define UART1_STOP_BITS_MODE_2   2
#define UART1_STOP_BITS_MODE_1_5 3

#define UART1_TRANSMITTER_STATE_DISABLE 0
#define UART1_TRANSMITTER_STATE_ENABLE  1

#define UART1_BAUDRATE_2400   833.375
#define UART1_BAUDRATE_9600   208.375
#define UART1_BAUDRATE_19200  104.125
#define UART1_BAUDRATE_57600  34.750
#define UART1_BAUDRATE_115200 17.375
#define UART1_BAUDRATE_230400 8.625
#define UART1_BAUDRATE_460800 4.375
#define UART1_BAUDRATE_896000 2.250
#define UART1_BAUDRATE_921600 2.125

#define UART1_BAUDRATE_80000  31.25

#define UART1_DMA_RECEIVER_DISABLE 0
#define UART1_DMA_RECEIVER_ENABLE  1

#define CR1_OVER8  15
#define CR1_UE     13
#define CR1_M      12
#define CR1_PCE    10
#define CR1_TXEIE  7
#define CR1_RXNEIE 5
#define CR1_TE     3
#define CR1_RE     2

#define CR2_STOP   12

#define SR_TXE  7
#define SR_RXNE 5

#define CR3_DMAR 6

#endif
