/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : GPIO                                                */
/* Version : 1.0                                                 */
/* Date    : 02 Feb 2024                                         */
/*****************************************************************/
#include "STD_Types.h"
#include "BIT_Math.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

static tenuErrorStatus GPIO_enuPinCheck(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy);

void GPIO_voidInit(void)
{
	uint8 u8CntrLoc = 0;
	tenuGPIO_pinMode aenuModeValuesLoc[29] = {GPIO_PIN_MODE_A0, GPIO_PIN_MODE_A1, GPIO_PIN_MODE_A2, GPIO_PIN_MODE_A3,
			GPIO_PIN_MODE_A4, GPIO_PIN_MODE_A5, GPIO_PIN_MODE_A6, GPIO_PIN_MODE_A7,
			GPIO_PIN_MODE_A8, GPIO_PIN_MODE_A9, GPIO_PIN_MODE_A10, GPIO_PIN_MODE_A11,
			GPIO_PIN_MODE_A12,
			GPIO_PIN_MODE_B0, GPIO_PIN_MODE_B1, GPIO_PIN_MODE_B5, GPIO_PIN_MODE_B6,
			GPIO_PIN_MODE_B7, GPIO_PIN_MODE_B8, GPIO_PIN_MODE_B9, GPIO_PIN_MODE_B10,
			GPIO_PIN_MODE_B11, GPIO_PIN_MODE_B12, GPIO_PIN_MODE_B13, GPIO_PIN_MODE_B14,
			GPIO_PIN_MODE_B15,
			GPIO_PIN_MODE_C13, GPIO_PIN_MODE_C14, GPIO_PIN_MODE_C15};

	for(u8CntrLoc=GPIO_PIN0 ; u8CntrLoc<=GPIO_PIN15; u8CntrLoc++)
	{
		if((u8CntrLoc == GPIO_PIN13) || (u8CntrLoc == GPIO_PIN14) || (u8CntrLoc == GPIO_PIN15))
		{
			/*nothing*/
		}
		else
		{
			GPIOA_REG->MODER = (GPIOA_REG->MODER & ~(3<<(u8CntrLoc*2))) | (aenuModeValuesLoc[u8CntrLoc]<<(u8CntrLoc*2));
		}

		if((u8CntrLoc == GPIO_PIN2) || (u8CntrLoc == GPIO_PIN3) || (u8CntrLoc == GPIO_PIN4))
		{
			/*nothing*/
		}
		else if(u8CntrLoc>4)
		{
			GPIOB_REG->MODER = (GPIOB_REG->MODER & ~(3<<(u8CntrLoc*2))) |aenuModeValuesLoc[u8CntrLoc+10]<<(u8CntrLoc*2);
		}
		else
		{
			GPIOB_REG->MODER = (GPIOB_REG->MODER & ~(3<<(u8CntrLoc*2))) |aenuModeValuesLoc[u8CntrLoc+13]<<(u8CntrLoc*2);
		}

		if(u8CntrLoc<13)
		{
			/*nothing*/
		}
		else
		{
			GPIOC_REG->MODER = (GPIOC_REG->MODER & ~(3<<(u8CntrLoc*2))) |aenuModeValuesLoc[u8CntrLoc+13]<<(u8CntrLoc*2);
		}

	}
}

tenuErrorStatus GPIO_enuSetMode(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy, tenuGPIO_pinMode enuModeCpy)
{
	tenuErrorStatus enuErrorStatLoc = E_OK;
	if(enuModeCpy>GPIO_MODE_ANALOG)
	{
		enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
	}
	else
	{
		enuErrorStatLoc = GPIO_enuPinCheck(enuPortNumCpy, enuPinNumCpy);
	}

	if(enuErrorStatLoc == E_OK)
	{
		switch(enuPortNumCpy)
		{
		case GPIO_PORTA:
			GPIOA_REG->MODER = (GPIOA_REG->MODER & ~(3<<(enuPinNumCpy*2))) |enuModeCpy<<(enuPinNumCpy*2);
			break;
		case GPIO_PORTB:
			GPIOB_REG->MODER = (GPIOB_REG->MODER & ~(3<<(enuPinNumCpy*2))) |enuModeCpy<<(enuPinNumCpy*2);
			break;
		case GPIO_PORTC:
			GPIOC_REG->MODER = (GPIOC_REG->MODER & ~(3<<(enuPinNumCpy*2))) |enuModeCpy<<(enuPinNumCpy*2);
			break;
		default:
			enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
			break;
		}
	}
	else
	{

	}

	return enuErrorStatLoc;
}

tenuErrorStatus GPIO_enuSetOutputType(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy, tenuGPIO_outputType enuOutputTypeCpy)
{
	tenuErrorStatus enuErrorStatLoc = E_OK;

	if(enuOutputTypeCpy>GPIO_OUTPUT_TYPE_OPEN_DRAIN)
	{
		enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
	}
	else
	{
		enuErrorStatLoc = GPIO_enuPinCheck(enuPortNumCpy, enuPinNumCpy);
	}

	if(enuErrorStatLoc == E_OK)
	{
		switch(enuPortNumCpy)
		{
		case GPIO_PORTA:
			GPIOA_REG->OTYPER = (GPIOA_REG->OTYPER & ~(3<<(enuPinNumCpy*2))) |enuOutputTypeCpy<<(enuPinNumCpy*2);
			break;
		case GPIO_PORTB:
			GPIOB_REG->OTYPER = (GPIOB_REG->OTYPER & ~(3<<(enuPinNumCpy*2))) |enuOutputTypeCpy<<(enuPinNumCpy*2);
			break;
		case GPIO_PORTC:
			GPIOC_REG->OTYPER = (GPIOC_REG->OTYPER & ~(3<<(enuPinNumCpy*2))) |enuOutputTypeCpy<<(enuPinNumCpy*2);
			break;
		default:
			enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
			break;
		}
	}

	return enuErrorStatLoc;
}

tenuErrorStatus GPIO_enuSetInputType(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy, tenuGPIO_inputType enuInputTypeCpy)
{
	tenuErrorStatus enuErrorStatLoc = E_OK;

	if(enuInputTypeCpy>GPIO_INPUT_TYPE_PULL_DOWN)
	{
		enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
	}
	else
	{
		enuErrorStatLoc = GPIO_enuPinCheck(enuPortNumCpy, enuPinNumCpy);
	}

	if(enuErrorStatLoc == E_OK)
	{
		switch(enuPortNumCpy)
		{
		case GPIO_PORTA:
			GPIOA_REG->PUPDR = (GPIOA_REG->PUPDR & ~(3<<(enuPinNumCpy*2))) |enuInputTypeCpy<<(enuPinNumCpy*2);
			break;
		case GPIO_PORTB:
			GPIOB_REG->PUPDR = (GPIOB_REG->PUPDR & ~(3<<(enuPinNumCpy*2))) |enuInputTypeCpy<<(enuPinNumCpy*2);
			break;
		case GPIO_PORTC:
			GPIOC_REG->PUPDR = (GPIOC_REG->PUPDR & ~(3<<(enuPinNumCpy*2))) |enuInputTypeCpy<<(enuPinNumCpy*2);
			break;
		default:
			enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
			break;
		}
	}

	return enuErrorStatLoc;
}

tenuErrorStatus GPIO_enuWritePinValue(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy, tenuGPIO_level enuPinValueCpy)
{
	tenuErrorStatus enuErrorStatLoc = E_OK;

	if(enuPinValueCpy>GPIO_HIGH)
	{
		enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
	}
	else
	{
		enuErrorStatLoc = GPIO_enuPinCheck(enuPortNumCpy, enuPinNumCpy);
	}

	if(enuErrorStatLoc == E_OK)
	{
		switch(enuPortNumCpy)
		{
		case GPIO_PORTA:
			GPIOA_REG->ODR = (GPIOA_REG->ODR & ~(1<<(enuPinNumCpy))) |enuPinValueCpy<<(enuPinNumCpy);
			break;
		case GPIO_PORTB:
			GPIOB_REG->ODR = (GPIOB_REG->ODR & ~(1<<(enuPinNumCpy))) |enuPinValueCpy<<(enuPinNumCpy);
			break;
		case GPIO_PORTC:
			GPIOC_REG->ODR = (GPIOC_REG->ODR & ~(1<<(enuPinNumCpy))) |enuPinValueCpy<<(enuPinNumCpy);
			break;
		default:
			enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
			break;
		}
	}

	return enuErrorStatLoc;
}

tenuErrorStatus GPIO_enuTogglePinValue(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy)
{
	tenuErrorStatus enuErrorStatLoc = E_OK;

	enuErrorStatLoc = GPIO_enuPinCheck(enuPortNumCpy, enuPinNumCpy);

	if(enuErrorStatLoc == E_OK)
	{
		switch(enuPortNumCpy)
		{
		case GPIO_PORTA:
			GPIOA_REG->ODR = (GPIOA_REG->ODR) ^ (1<<enuPinNumCpy);
			break;
		case GPIO_PORTB:
			GPIOB_REG->ODR = (GPIOB_REG->ODR) ^ (1<<enuPinNumCpy);
			break;
		case GPIO_PORTC:
			GPIOC_REG->ODR = (GPIOC_REG->ODR) ^ (1<<enuPinNumCpy);
			break;
		default:
			enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
			break;
		}
	}

	return enuErrorStatLoc;
}

tenuErrorStatus GPIO_enuReadPinValue(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy, uint8* pu8PinValue)
{
	tenuErrorStatus enuErrorStatLoc = E_OK;
	if(pu8PinValue == NULL_PTR)
	{
		enuErrorStatLoc = E_NOK_NULL_POINTER;
	}
	else
	{
		enuErrorStatLoc = GPIO_enuPinCheck(enuPortNumCpy, enuPinNumCpy);
	}

	if(enuErrorStatLoc == E_OK)
	{
		switch(enuPortNumCpy)
		{
		case GPIO_PORTA:
			*pu8PinValue = (GPIOA_REG->IDR>>enuPinNumCpy) & 1;
			break;
		case GPIO_PORTB:
			*pu8PinValue = (GPIOB_REG->IDR>>enuPinNumCpy) & 1;
			break;
		case GPIO_PORTC:
			*pu8PinValue = (GPIOC_REG->IDR>>enuPinNumCpy) & 1;
			break;
		default:
			enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
			break;
		}
	}

	return enuErrorStatLoc;
}

tenuErrorStatus GPIO_enuAlternateFunction(tenuAltFun enuAltFunCpy, tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy)
{
	tenuErrorStatus enuErrorStatLoc = E_OK;
	if((enuAltFunCpy>AF_EVENTOUT) || (enuAltFunCpy==11) || (enuAltFunCpy==13) || (enuAltFunCpy==14))
	{
		enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
	}
	else
	{
		enuErrorStatLoc = GPIO_enuSetMode(enuPortNumCpy, enuPinNumCpy, GPIO_MODE_ALT_FUNCTION);
	}

	if(enuErrorStatLoc == E_OK)
	{
		if(enuPinNumCpy>GPIO_PIN7)
		{
			enuPinNumCpy -= 8;
			switch(enuPortNumCpy)
			{
			case GPIO_PORTA:
				GPIOA_REG->AFRH = (GPIOA_REG->AFRH & ~(0b1111<<(enuPinNumCpy*4))) |enuAltFunCpy<<(enuPinNumCpy*4);
				break;
			case GPIO_PORTB:
				GPIOB_REG->AFRH = (GPIOB_REG->AFRH & ~(0b1111<<(enuPinNumCpy*4))) |enuAltFunCpy<<(enuPinNumCpy*4);
				break;
			case GPIO_PORTC:
				GPIOC_REG->AFRH = (GPIOC_REG->AFRH & ~(0b1111<<(enuPinNumCpy*4))) |enuAltFunCpy<<(enuPinNumCpy*4);
				break;
			default:
				break;
			}
		}
		else
		{
			switch(enuPortNumCpy)
			{
			case GPIO_PORTA:
				GPIOA_REG->AFRL = (GPIOA_REG->AFRL & ~(0b1111<<(enuPinNumCpy*4))) |enuAltFunCpy<<(enuPinNumCpy*4);
				break;
			case GPIO_PORTB:
				GPIOB_REG->AFRL = (GPIOB_REG->AFRL & ~(0b1111<<(enuPinNumCpy*4))) |enuAltFunCpy<<(enuPinNumCpy*4);
				break;
			case GPIO_PORTC:
				GPIOC_REG->AFRL = (GPIOC_REG->AFRL & ~(0b1111<<(enuPinNumCpy*4))) |enuAltFunCpy<<(enuPinNumCpy*4);
				break;
			default:
				break;
			}
		}
	}

	return enuErrorStatLoc;
}

static tenuErrorStatus GPIO_enuPinCheck(tenuGPIO_portNum enuPortNumCpy, tenuGPIO_pinNum enuPinNumCpy)
{
	tenuErrorStatus enuErrorStatLoc = E_OK;
	if(enuPinNumCpy>GPIO_PIN15)
	{
		enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
	}
	else if((enuPortNumCpy==GPIO_PORTA)&&(enuPinNumCpy>GPIO_PIN12))
	{
		enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
	}
	else if((enuPortNumCpy==GPIO_PORTB)&&((enuPinNumCpy==GPIO_PIN2)||(enuPinNumCpy==GPIO_PIN3)||(enuPinNumCpy==GPIO_PIN4)))
	{
		enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
	}
	else if((enuPortNumCpy==GPIO_PORTC)&&(enuPinNumCpy<GPIO_PIN13))
	{
		enuErrorStatLoc = E_NOK_PARAMETER_OUT_OF_RANGE;
	}
	else
	{
		enuErrorStatLoc = E_OK;
	}

	return enuErrorStatLoc;
}
