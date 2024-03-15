/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : NVIC                                                */
/* Version : 1.0                                                 */
/* Date    : 02 Feb 2024                                         */
/*****************************************************************/
#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

typedef enum{
    NVIC_POSITION_WWDG,
    NVIC_POSITION_EXTI16,
    NVIC_POSITION_EXTI21,
    NVIC_POSITION_EXTI22,
    NVIC_POSITION_FLASH,
    NVIC_POSITION_RCC,
    NVIC_POSITION_EXTI0,
    NVIC_POSITION_EXTI1,
    NVIC_POSITION_EXTI2,
    NVIC_POSITION_EXTI3,
    NVIC_POSITION_EXTI4,
    NVIC_POSITION_DMA1STR0,
    NVIC_POSITION_DMA1STR1,
    NVIC_POSITION_DMA1STR2,
    NVIC_POSITION_DMA1STR3,
    NVIC_POSITION_DMA1STR4,
    NVIC_POSITION_DMA1STR5,
    NVIC_POSITION_DMA1STR6,
    NVIC_POSITION_ADC,
    NVIC_POSITION_EXTI9_5 = 23,
    NVIC_POSITION_TIM1_BRK_TIM9,
    NVIC_POSITION_TIM1_UP_TIM10,
    NVIC_POSITION_TIM1_TRG_COM_TIM11,
    NVIC_POSITION_TIM1_CC,
    NVIC_POSITION_TIM2,
    NVIC_POSITION_TIM3,
    NVIC_POSITION_TIM4,
    NVIC_POSITION_I2C1_EV,
    NVIC_POSITION_I2C1_ER,
    NVIC_POSITION_I2C2_EV,
    NVIC_POSITION_I2C2_ER,
    NVIC_POSITION_SPI1,
    NVIC_POSITION_SPI2,
    NVIC_POSITION_USART1,
    NVIC_POSITION_USART2,
    NVIC_POSITION_EXTI15_10 = 40,
    NVIC_POSITION_EXTI17,
    NVIC_POSITION_EXTI18,
    NVIC_POSITION_DMA1STR7 = 47,
    NVIC_POSITION_SDIO = 49,
    NVIC_POSITION_TIM5,
    NVIC_POSITION_SPI3,
    NVIC_POSITION_DMA2STR0 = 56,
    NVIC_POSITION_DMA2STR1,
    NVIC_POSITION_DMA2STR2,
    NVIC_POSITION_DMA2STR3,
    NVIC_POSITION_DMA2STR4,
    NVIC_POSITION_OTG_FS = 67,
    NVIC_POSITION_DMA2STR5,
    NVIC_POSITION_DMA2STR6,
    NVIC_POSITION_DMA2STR7,
    NVIC_POSITION_USART6,
    NVIC_POSITION_I2C3_EV,
    NVIC_POSITION_I2C3_ER,
    NVIC_POSITION_FPU = 81,
    NVIC_POSITION_SPI4 = 84
}tenuNVIC_intPos;

typedef enum{
	Group16Sub0 = 3,
	Group8Sub2,
	Group4Sub4,
	Group2Sub8,
	Group0Sub16
}tenuNVIC_groups;

void NVIC_voidEnable(tenuNVIC_intPos enuPositionCpy);

void NVIC_voidDisable(tenuNVIC_intPos enuPositionCpy);

void NVIC_voidPendingSet(tenuNVIC_intPos enuPositionCpy);

void NVIC_voidPendingClear(tenuNVIC_intPos enuPositionCpy);

uint8 NVIC_u8ActiveRead(tenuNVIC_intPos enuPositionCpy);

void NVIC_voidSetInterruptGroupMode(tenuNVIC_groups enuGroupModeCpy);

void NVIC_voidSetInterruptPriority(tenuNVIC_intPos enuPositionCpy, uint8 u8GroupPriCpy, uint8 u8SubPriCpy);


#endif
