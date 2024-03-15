/*
 * SPI_interface.h
 *
 *  Created on: Feb 4, 2024
 *      Author: Ahmed
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


void SPI1_voidInit(void);

void SPI1_voidTransmit(uint16 u16SendDataCpy);

uint16 SPI1_u16Transceive(uint16 u16SendDataCpy);

void SPI1_voidEnable(void);

#endif /* SPI_INTERFACE_H_ */
