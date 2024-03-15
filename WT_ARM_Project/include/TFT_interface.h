/*
 * TFT_interface.h
 *
 *  Created on: Feb 5, 2024
 *      Author: Ahmed
 */

#ifndef TFT_INTERFACE_H_
#define TFT_INTERFACE_H_


void TFT_voidInit(void);

void TFT_voidSendCmd(uint8 u8CommandCpy);

void TFT_voidSendData(uint8 u8DataCpy);

void TFT_voidDisplayFrame(const uint16* pu16DataArrayCpy);


#endif /* TFT_INTERFACE_H_ */
