/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : GPIO                                                */
/* Version : 1.0                                                 */
/* Date    : 02 Feb 2024                                         */
/*****************************************************************/
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

typedef enum {
    GPIO_PORTA,
    GPIO_PORTB,
    GPIO_PORTC
}tenuGPIO_portNum;

typedef enum {
    GPIO_PIN0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15
}tenuGPIO_pinNum;

typedef enum{
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALT_FUNCTION,
    GPIO_MODE_ANALOG
}tenuGPIO_pinMode;

typedef enum{
    GPIO_OUTPUT_TYPE_PUSH_PULL,
    GPIO_OUTPUT_TYPE_OPEN_DRAIN
}tenuGPIO_outputType;

typedef enum{
    GPIO_INPUT_TYPE_FLOAT,
    GPIO_INPUT_TYPE_PULL_UP,
    GPIO_INPUT_TYPE_PULL_DOWN
}tenuGPIO_inputType;

typedef enum{
    GPIO_LOW,
    GPIO_HIGH
}tenuGPIO_level;

typedef enum{
	AF_SYSTEM,
	AF_TIM1_2,
	AF_TIM3_4_5,
	AF_TIM9_10_11,
	AF_I2C1_2_3,
	AF_SPI1_2_3_4,
	AF_SPI3,
	AF_UART1_2,
	AF_UART6,
	AF_I2C2_3,
	AF_OTG_FS,
	AF_SDIO=12,
	AF_EVENTOUT=15
}tenuAltFun;

void GPIO_voidInit(void);

tenuErrorStatus GPIO_enuSetMode(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy, tenuGPIO_pinMode enuModeCpy);

tenuErrorStatus GPIO_enuSetOutputType(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy, tenuGPIO_outputType enuOutputTypeCpy);

tenuErrorStatus GPIO_enuSetInputType(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy, tenuGPIO_inputType enuInputTypeCpy);

tenuErrorStatus GPIO_enuWritePinValue(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy, tenuGPIO_level enuPinValueCpy);

tenuErrorStatus GPIO_enuTogglePinValue(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy);

tenuErrorStatus GPIO_enuReadPinValue(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy, uint8* pu8PinValue);

tenuErrorStatus GPIO_enuAlternateFunction(tenuAltFun enuAltFunCpy, tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy);

#endif
