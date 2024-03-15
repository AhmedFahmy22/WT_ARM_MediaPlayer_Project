#include "STD_Types.h"
#include "BIT_Math.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"
#include "SPI_interface.h"
#include "DMA_interface.h"
#include "UART_interface.h"
#include "NVIC_interface.h"
#include "EXTI_int.h"

#include "R2RDAC_int.h"
#include "TFT_interface.h"


void APP_voidUART_ISR(void);
void APP_voidDMA_ISR(void);
void APP_voidSendImage(void);
void APP_voidSendAudio(void);
void APP_voidSendOK(void);
void APP_voidSendPause(void);
void APP_voidSendPlay(void);
void APP_voidSendStop(void);
void APP_voidSendNext(void);
void APP_voidSendPrev(void);



#define ARR_LENGTH 20480

uint16 au16ImageBufferGlb[ARR_LENGTH] = {0};

uint8 u8FlagGlb = 0;

uint8 au8AudioBufferGlb[2][256] = {0};
uint8 u8AudioCntrGlb = 0;
uint8 u8CurrentBuffer = 0;

int main(void)
{

	tstrDMA_config strDMA2Stream2_configLoc = {
			DMA_STREAM2,
			DMA_CHANNEL4,
			DMA_PSIZE_8,
			DMA_INCREMENT_INCREMENTED,
			DMA_INCREMENT_FIXED,
			DMA_DATA_DIRECTION_PERIPH_TO_MEM,
			DMA_FLOW_CTRL_DMA,
			DMA_INT_ENABLE
	};


	RCC_voidInit();
	RCC_voidEnable(AHB1,AHB1_GPIOA);
	RCC_voidEnable(AHB1,AHB1_GPIOB);
	RCC_voidEnable(APB2,APB2_SPI1);
	RCC_voidEnable(AHB1,AHB1_DMA2);
	RCC_voidEnable(APB2,APB2_USART1);
	RCC_voidEnable(APB2,APB2_SYSCFG);



	GPIO_voidInit();

	GPIO_enuAlternateFunction(AF_SPI1_2_3_4, GPIO_PORTA, GPIO_PIN4);
	GPIO_enuAlternateFunction(AF_SPI1_2_3_4, GPIO_PORTA, GPIO_PIN5);
	GPIO_enuAlternateFunction(AF_SPI1_2_3_4, GPIO_PORTA, GPIO_PIN6);
	GPIO_enuAlternateFunction(AF_SPI1_2_3_4, GPIO_PORTA, GPIO_PIN7);


	SYSTICK_voidInit();
	SYSTICK_voidEnable();
	SYSTICK_enuSetInterval_periodic(200, APP_voidSendAudio);
	//SYSTICK_voidCtrlIntState(SYSTICK_INT_ENABLE);

	GPIO_enuSetInputType(GPIO_PORTB, GPIO_PIN10, GPIO_INPUT_TYPE_PULL_UP);
	GPIO_enuSetInputType(GPIO_PORTB, GPIO_PIN12, GPIO_INPUT_TYPE_PULL_UP);
	GPIO_enuSetInputType(GPIO_PORTB, GPIO_PIN13, GPIO_INPUT_TYPE_PULL_UP);
	GPIO_enuSetInputType(GPIO_PORTB, GPIO_PIN14, GPIO_INPUT_TYPE_PULL_UP);
	GPIO_enuSetInputType(GPIO_PORTB, GPIO_PIN15, GPIO_INPUT_TYPE_PULL_UP);

	DMA2_voidConfig(strDMA2Stream2_configLoc);
	DMA2_voidSetCallBack(DMA_STREAM2, APP_voidDMA_ISR);

	EXTI_voidInerruptSetPort(EXTI_LineTen, EXTI_PortB);
	EXTI_voidInerruptSetPort(EXTI_LineTwelve, EXTI_PortB);
	EXTI_voidInerruptSetPort(EXTI_LineThirteen, EXTI_PortB);
	EXTI_voidInerruptSetPort(EXTI_LineFourteen, EXTI_PortB);
	EXTI_voidInerruptSetPort(EXTI_LineFifteen, EXTI_PortB);

	EXTI_voidInterruptTrigger(EXTI_LineTen, EXTI_Falling);
	EXTI_voidInterruptTrigger(EXTI_LineTwelve, EXTI_Falling);
	EXTI_voidInterruptTrigger(EXTI_LineThirteen, EXTI_Falling);
	EXTI_voidInterruptTrigger(EXTI_LineFourteen, EXTI_Falling);
	EXTI_voidInterruptTrigger(EXTI_LineFifteen, EXTI_Falling);

	EXTI_voidSetCallBack(EXTI_LineTen, APP_voidSendNext);
	EXTI_voidSetCallBack(EXTI_LineTwelve, APP_voidSendPrev);
	EXTI_voidSetCallBack(EXTI_LineThirteen, APP_voidSendPlay);
	EXTI_voidSetCallBack(EXTI_LineFourteen, APP_voidSendStop);
	EXTI_voidSetCallBack(EXTI_LineFifteen, APP_voidSendPause);

	EXTI_voidInterruptEnableDisable(EXTI_LineTen, EXTI_Enable);
	EXTI_voidInterruptEnableDisable(EXTI_LineTwelve, EXTI_Enable);
	EXTI_voidInterruptEnableDisable(EXTI_LineThirteen, EXTI_Enable);
	EXTI_voidInterruptEnableDisable(EXTI_LineFourteen, EXTI_Enable);
	EXTI_voidInterruptEnableDisable(EXTI_LineFifteen, EXTI_Enable);

	SPI1_voidInit();

	TFT_voidInit();

	GPIO_enuAlternateFunction(AF_UART1_2, UART1_RX_PORT, UART1_RX_PIN);
	GPIO_enuAlternateFunction(AF_UART1_2, UART1_TX_PORT, UART1_TX_PIN);

	UART1_voidInit();
	UART1_voidSetCallBack(APP_voidUART_ISR);

	NVIC_voidSetInterruptGroupMode(Group0Sub16);

	NVIC_voidSetInterruptPriority(NVIC_POSITION_USART1,0,0);
	NVIC_voidEnable(NVIC_POSITION_USART1);

	NVIC_voidSetInterruptPriority(NVIC_POSITION_DMA2STR2, 0, 1);
	NVIC_voidEnable(NVIC_POSITION_DMA2STR2);

	NVIC_voidSetInterruptPriority(NVIC_POSITION_EXTI15_10,0,2);
	NVIC_voidEnable(NVIC_POSITION_EXTI15_10);

	while(1)
	{

	}
	return 0;
}


void APP_voidUART_ISR(void)
{
	if(u8FlagGlb==0)
	{
		DMA2_voidStartTransfer(DMA_STREAM2, UART1_pu32DMAReceiveAddress(), au16ImageBufferGlb, ARR_LENGTH*2);
	}
	else
	{
		DMA2_voidStartTransfer(DMA_STREAM2, UART1_pu32DMAReceiveAddress(), au8AudioBufferGlb, 256);
		SYSTICK_voidCtrlIntState(SYSTICK_INT_ENABLE);
		SYSTICK_enuStart(200);
	}
	UART1_voidReceiveIntDisable();

}

void APP_voidDMA_ISR(void)
{
	u8FlagGlb=1;

	UART1_voidReceiveIntEnable();
}

void APP_voidSendAudio(void)
{
	R2RDAC_voidWriteChar(au8AudioBufferGlb[u8CurrentBuffer][u8AudioCntrGlb++]);
	if(u8AudioCntrGlb==0)
	{
		u8CurrentBuffer = !u8CurrentBuffer;
		APP_voidSendOK();
	}
}

void APP_voidSendImage(void)
{
	TFT_voidDisplayFrame(au16ImageBufferGlb);
}

void APP_voidSendOK(void)
{
	UART1_voidTransmitSynch('O');
}

void APP_voidSendPause(void)
{
	SYSTICK_voidDisable();
	UART1_voidTransmitSynch('A');
}

void APP_voidSendPlay(void)
{
	//SYSTICK_voidEnable();
	TFT_voidDisplayFrame(au16ImageBufferGlb);
	UART1_voidTransmitSynch('B');
}

void APP_voidSendStop(void)
{
	SYSTICK_voidDisable();
	DMA2_voidStartTransfer(DMA_STREAM2, UART1_pu32DMAReceiveAddress(), au16ImageBufferGlb, ARR_LENGTH);
	UART1_voidTransmitSynch('C');
}

void APP_voidSendNext(void)
{
	DMA2_voidStartTransfer(DMA_STREAM2, UART1_pu32DMAReceiveAddress(), au16ImageBufferGlb, ARR_LENGTH);
	UART1_voidTransmitSynch('D');
}

void APP_voidSendPrev(void)
{
	DMA2_voidStartTransfer(DMA_STREAM2, UART1_pu32DMAReceiveAddress(), au16ImageBufferGlb, ARR_LENGTH);
	UART1_voidTransmitSynch('E');
}

