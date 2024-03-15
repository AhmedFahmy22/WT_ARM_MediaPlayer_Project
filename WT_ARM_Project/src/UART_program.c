/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : UART                                                */
/* Version : 1.0                                                 */
/* Date    : 11 Feb 2024                                         */
/*****************************************************************/
#include "STD_Types.h"
#include "BIT_Math.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"

static uint16 UART_u16BRRValue(float32 f32DivValueCpy);


pf pfUART1ISRGlb = NULL_PTR;

void UART1_voidInit(void)
{
	/*Disable UART*/
	CLR_BIT(UART1_REG->CR1,CR1_UE);

	/*Word length*/
	UART1_REG->CR1 = (UART1_REG->CR1 & ~(1<<CR1_M)) | (UART1_WORD_LENGTH<<CR1_M);

	/*Baud Rate*/
	UART1_REG->BRR = UART_u16BRRValue(UART1_BAUDRATE);

	/*Parity*/
	UART1_REG->CR1 = (UART1_REG->CR1 & ~(1<<CR1_PCE)) | (UART1_PARITY_STATE<<CR1_PCE);

	/*Stop bits*/
	UART1_REG->CR2 = (UART1_REG->CR2 & ~(0b11<<CR2_STOP)) | (UART1_STOP_BITS_MODE<<CR2_STOP);

	/*Over Sampling mode*/
	UART1_REG->CR1 = (UART1_REG->CR1 & ~(1<<CR1_OVER8)) | (UART1_OVERSAMPLING_MODE<<CR1_OVER8);

	/*Receiver*/
	UART1_REG->CR1 = (UART1_REG->CR1 & ~(1<<CR1_RE)) | (UART1_RECEIVER_STATE<<CR1_RE);

	/*Transmitter*/
	UART1_REG->CR1 = (UART1_REG->CR1 & ~(1<<CR1_TE)) | (UART1_TRANSMITTER_STATE<<CR1_TE);

	/*DMA*/
	UART1_REG->CR3 = (UART1_REG->CR3 & ~(1<<CR3_DMAR)) | (UART1_DMA_RECEIVER<<CR3_DMAR);

	/*Interrupts*/
	UART1_REG->CR1 = (UART1_REG->CR1 & ~(1<<CR1_RXNEIE)) | (UART1_RECEIVE_INTERRUPT<<CR1_RXNEIE);
	UART1_REG->CR1 = (UART1_REG->CR1 & ~(1<<CR1_TXEIE)) | (UART1_TRANSMIT_INTERRUPT<<CR1_TXEIE);

	/*Enable UART*/
	UART1_REG->CR1 = (UART1_REG->CR1 & ~(1<<CR1_UE)) | (UART1_STATE<<CR1_UE);
}

void UART1_voidTransmitSynch(uint8 u8DataCpy)
{
	/*Send Data*/
	UART1_REG->DR = u8DataCpy;

    /*Transmit Flag*/
    while(GET_BIT(UART1_REG->SR, SR_TXE)==0);
}

uint8 UART1_u8ReceiveSynch(void)
{
    /*Receive Flag*/
	while(GET_BIT(UART1_REG->SR, SR_RXNE)==0);

	/*Read Data*/
	return ((uint8) UART1_REG->DR);
}

uint8 UART1_u8GetData(void)
{
	/*Read Data*/
	return ((uint8) UART1_REG->DR);
}

void UART1_voidReceiveIntEnable(void)
{
	SET_BIT(UART1_REG->CR1, CR1_RXNEIE);
}

void UART1_voidReceiveIntDisable(void)
{
	CLR_BIT(UART1_REG->CR1, CR1_RXNEIE);
}

void UART1_voidSetCallBack(pf pfUART1ISRCpy)
{
	pfUART1ISRGlb = pfUART1ISRCpy;
}

uint32* UART1_pu32DMAReceiveAddress(void)
{
	return &(UART1_REG->DR);
}

static uint16 UART_u16BRRValue(float32 f32DivValueCpy)
{
	uint16 u16RetValLoc = 0;
	float32 f32DivValLoc = 0;
#if UART1_OVERSAMPLING_MODE == UART1_OVERSAMPLING_MODE_16
	f32DivValueCpy /= 2.0;
	u16RetValLoc = (uint16)f32DivValueCpy;
	f32DivValLoc = (f32DivValueCpy - (float32) u16RetValLoc);
	f32DivValLoc *= 16.0;
#elif UART1_OVERSAMPLING_MODE == UART1_OVERSAMPLING_MODE_8
	u16RetValLoc = (uint16)f32DivValueCpy;
	f32DivValLoc = (f32DivValueCpy - (float32) u16RetValLoc);
	f32DivValLoc *= 8.0;
#endif
	u16RetValLoc = (u16RetValLoc<<4) | (((uint16)f32DivValLoc) & 0xF);
	return u16RetValLoc;
}

void USART1_IRQHandler(void)
{
	if(pfUART1ISRGlb!=NULL_PTR)
	{
		pfUART1ISRGlb();
	}
}
