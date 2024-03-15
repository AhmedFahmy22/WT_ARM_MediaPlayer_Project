/*
 * SPI_program.c
 *
 *  Created on: Feb 4, 2024
 *      Author: Ahmed
 */

#include "STD_Types.h"
#include "BIT_Math.h"

#include "SYSTICK_interface.h"

#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"

#define CR1_DFF 	 11
#define CR1_LSBFIRST 7
#define CR1_SPE 	 6
#define CR1_BR 		 3
#define CR1_MSTR 	 2
#define CR1_CPOL 	 1
#define CR1_CPHA 	 0

#define SR_BSY  7
#define SR_TXE  1
#define SR_RXNE 0

void SPI1_voidInit(void)
{
	/*Disable SPI*/
	CLR_BIT(SPI1_REG->CR1, CR1_SPE);
#if SPI1_MODE == SPI1_MODE_MASTER
	/*Data format*/
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(1<<CR1_DFF)) | (SPI1_DATA_LENGTH<<CR1_DFF);

	/*msb / lsb*/
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(1<<CR1_LSBFIRST)) | (SPI1_FRAME_FORMAT<<CR1_LSBFIRST);

	/*baud rate*/
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(0b111<<CR1_BR)) | (SPI1_CLK_BAUDRATE<<CR1_BR);

	/*master/slave*/
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(1<<CR1_MSTR)) | (SPI1_MODE<<CR1_MSTR);

	/*Polarity, Phase*/
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(1<<CR1_CPOL)) | (SPI1_CLK_POLARITY<<CR1_CPOL);
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(1<<CR1_CPHA)) | (SPI1_CLK_PHASE<<CR1_CPHA);

	SET_BIT(SPI1_REG->CR1 , 8);
	SET_BIT(SPI1_REG->CR1 , 9);
#elif SPI1_MODE == SPI1_MODE_SLAVE
	/*Data format*/
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(1<<CR1_DFF)) | (SPI1_DATA_LENGTH<<CR1_DFF);
	/*Polarity, Phase*/
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(1<<CR1_CPOL)) | (SPI1_CLK_POLARITY<<CR1_CPOL);
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(1<<CR1_CPHA)) | (SPI1_CLK_PHASE<<CR1_CPHA);
	/*master/slave*/
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(1<<CR1_MSTR)) | (SPI1_MODE<<CR1_MSTR);
	/*msb / lsb*/
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(1<<CR1_LSBFIRST)) | (SPI1_FRAME_FORMAT<<CR1_LSBFIRST);
#endif
	/*SPI Enable*/
	SPI1_REG->CR1 = (SPI1_REG->CR1 & ~(1<<CR1_SPE)) | (1<<CR1_SPE);
}

void SPI1_voidTransmit(uint16 u16SendDataCpy)
{
	uint16 u16RBufferLoc = 0;
	u16RBufferLoc = SPI1_REG->DR;
	SPI1_REG->DR = u16SendDataCpy;
	while(GET_BIT(SPI1_REG->SR, SR_TXE)==0);
}

uint16 SPI1_u16Transceive(uint16 u16SendDataCpy)
{
	uint16 u16ReceiveDataLoc = 0;
	while(GET_BIT(SPI1_REG->SR, SR_TXE)==0);
	SPI1_REG->DR = u16SendDataCpy;
	while(GET_BIT(SPI1_REG->SR, SR_RXNE)==0);
	u16ReceiveDataLoc = (uint16)SPI1_REG->DR;
	return u16ReceiveDataLoc;
}

void SPI1_voidEnable(void)
{
	SPI1_REG->CR1 |= (1<<6) ;
}
