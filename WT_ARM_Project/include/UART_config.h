/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : UART                                                */
/* Version : 1.0                                                 */
/* Date    : 11 Feb 2024                                         */
/*****************************************************************/
#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define UART1_STATE UART_STATE_ENABLE

#define UART1_RECEIVER_STATE UART1_RECEIVER_STATE_ENABLE

#define UART1_TRANSMITTER_STATE UART1_TRANSMITTER_STATE_ENABLE

#define UART1_BAUDRATE UART1_BAUDRATE_230400

#define UART1_PARITY_STATE UART1_PARITY_STATE_DISABLE

#define UART1_STOP_BITS_MODE UART1_STOP_BITS_MODE_1

#define UART1_RECEIVE_INTERRUPT UART1_RECEIVE_INTERRUPT_ENABLE

#define UART1_TRANSMIT_INTERRUPT UART1_TRANSMIT_INTERRUPT_DISABLE

#define UART1_OVERSAMPLING_MODE UART1_OVERSAMPLING_MODE_8

#define UART1_WORD_LENGTH UART1_WORD_LENGTH_8

#define UART1_DMA_RECEIVER UART1_DMA_RECEIVER_ENABLE

#endif
