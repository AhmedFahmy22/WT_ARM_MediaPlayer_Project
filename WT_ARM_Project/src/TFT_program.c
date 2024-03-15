/*
 * TFT_porgram.c
 *
 *  Created on: Feb 5, 2024
 *      Author: Ahmed
 */

#include "STD_Types.h"
#include "BIT_Math.h"

#include "GPIO_interface.h"
#include "SPI_interface.h"
#include "SYSTICK_interface.h"

#include "TFT_interface.h"
#include "TFT_config.h"
#include "TFT_private.h"


#define TFT_RESET_PORT GPIO_PORTA
#define TFT_RESET_PIN  GPIO_PIN0

#define TFT_CONTROL_PORT GPIO_PORTA
#define TFT_CONTROL_PIN  GPIO_PIN1

#define TFT_COMM_SLEEPOUT  0x11
#define TFT_COMM_COLORMODE 0x3A
#define TFT_COMM_DISPLAYON 0x29
#define TFT_COMM_XLIMIT	   0x2A
#define TFT_COMM_YLIMIT	   0x2B
#define TFT_COMM_RAMWRITE  0x2C


#define TFT_COLORMODE_565 0x05

#define TFT_IMAGE_SIZE 20480

void TFT_voidInit(void)
{
	GPIO_enuSetMode(TFT_RESET_PORT, TFT_RESET_PIN, GPIO_MODE_OUTPUT);
	GPIO_enuSetMode(TFT_CONTROL_PORT, TFT_CONTROL_PIN, GPIO_MODE_OUTPUT);

	/* Reset */
	GPIO_enuWritePinValue(TFT_RESET_PORT, TFT_RESET_PIN, GPIO_HIGH);
	SYSTICK_enuDelayUs(100);
	GPIO_enuWritePinValue(TFT_RESET_PORT, TFT_RESET_PIN, GPIO_LOW);
	SYSTICK_enuDelayUs(100);
	GPIO_enuWritePinValue(TFT_RESET_PORT, TFT_RESET_PIN, GPIO_HIGH);
	SYSTICK_enuDelayUs(100);
	GPIO_enuWritePinValue(TFT_RESET_PORT, TFT_RESET_PIN, GPIO_LOW);
	SYSTICK_enuDelayUs(100);
	GPIO_enuWritePinValue(TFT_RESET_PORT, TFT_RESET_PIN, GPIO_HIGH);
	SYSTICK_enuDelayMs(120);


	/* Sleep Out */
	TFT_voidSendCmd(TFT_COMM_SLEEPOUT);
	SYSTICK_enuDelayMs(10);

	/* Color Mode */
	TFT_voidSendCmd(TFT_COMM_COLORMODE);
	TFT_voidSendData(TFT_COLORMODE_565);

	/* Display On */
	TFT_voidSendCmd(TFT_COMM_DISPLAYON);
}

void TFT_voidSendCmd(uint8 u8CommandCpy)
{
	GPIO_enuWritePinValue(TFT_CONTROL_PORT, TFT_CONTROL_PIN, GPIO_LOW);
	SPI1_u16Transceive(u8CommandCpy);
}

void TFT_voidSendData(uint8 u8DataCpy)
{
	GPIO_enuWritePinValue(TFT_CONTROL_PORT, TFT_CONTROL_PIN, GPIO_HIGH);
	SPI1_u16Transceive(u8DataCpy);
}

void TFT_voidDisplayFrame(const uint16* pu16FrameArrayCpy)
{
	uint16 u16CntrLoc = 0;

	/* X-axis */
	TFT_voidSendCmd(TFT_COMM_XLIMIT);
	TFT_voidSendData(0);
	TFT_voidSendData(0);
	TFT_voidSendData(0);
	TFT_voidSendData(127);

	/* Y-axis */
	TFT_voidSendCmd(TFT_COMM_YLIMIT);
	TFT_voidSendData(0);
	TFT_voidSendData(0);
	TFT_voidSendData(0);
	TFT_voidSendData(159);

	/* Write on RAM*/
	TFT_voidSendCmd(TFT_COMM_RAMWRITE);

	/* Display Data */
	for(u16CntrLoc=0; u16CntrLoc<TFT_IMAGE_SIZE; u16CntrLoc++)
	{
		TFT_voidSendData((uint8)(pu16FrameArrayCpy[u16CntrLoc]>>8));
		TFT_voidSendData((uint8) pu16FrameArrayCpy[u16CntrLoc]);
	}
}
