/*
 * SPI_private.h
 *
 *  Created on: Feb 4, 2024
 *      Author: Ahmed
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#define SPI1_BASE_ADDRESS (0x40013000)

typedef struct{
	uint32 CR1;
	uint32 Reserved1;
	uint32 SR;
	uint32 DR;
	uint32 CRCPR;
	uint32 RXCRCR;
	uint32 TXCRCR;
	uint32 I2SCFGR;
	uint32 I2SPR;
}tstrSPI_registers;

#define SPI1_REG ((volatile tstrSPI_registers *) SPI1_BASE_ADDRESS)

#endif /* SPI_PRIVATE_H_ */
