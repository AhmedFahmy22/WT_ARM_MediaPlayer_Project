/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : DMA                                                 */
/* Version : 1.0                                                 */
/* Date    : 10 Mar 2024                                         */
/*****************************************************************/
#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

/************ Config ***********/
#define DMA_STREAM0 0
#define DMA_STREAM1 1
#define DMA_STREAM2 2
#define DMA_STREAM3 3
#define DMA_STREAM4 4
#define DMA_STREAM5 5
#define DMA_STREAM6 6
#define DMA_STREAM7 7

#define DMA_CHANNEL0 0
#define DMA_CHANNEL1 1
#define DMA_CHANNEL2 2
#define DMA_CHANNEL3 3
#define DMA_CHANNEL4 4
#define DMA_CHANNEL5 5
#define DMA_CHANNEL6 6
#define DMA_CHANNEL7 7

#define DMA_PSIZE_8  0
#define DMA_PSIZE_16 1
#define DMA_PSIZE_32 2

#define DMA_INCREMENT_FIXED       0
#define DMA_INCREMENT_INCREMENTED 1

#define DMA_DATA_DIRECTION_PERIPH_TO_MEM 0
#define DMA_DATA_DIRECTION_MEM_TO_PERIPH 1
#define DMA_DATA_DIRECTION_MEM_TO_MEM    2

#define DMA_FLOW_CTRL_DMA    0
#define DMA_FLOW_CTRL_PERIPH 1

#define DMA_INT_DISABLE 0
#define DMA_INT_ENABLE  1

/************ DMA1 ************/
/*Stream 0*/
#define DMA1_STREAM0_CHANNEL0_SPI3_RX     0
#define DMA1_STREAM0_CHANNEL1_I2C1_RX     4
#define DMA1_STREAM0_CHANNEL2_TIM4_CH1    6
#define DMA1_STREAM0_CHANNEL3_I2S3_EXT_RX 3
#define DMA1_STREAM0_CHANNEL6_TIM5_CH3    6
#define DMA1_STREAM0_CHANNEL6_TIM5_UP     6
/*Stream 1*/
#define DMA1_STREAM1_CHANNEL1_I2C3_RX     1
#define DMA1_STREAM1_CHANNEL3_TIM2_CH3    3
#define DMA1_STREAM1_CHANNEL3_TIM2_UP     3
#define DMA1_STREAM1_CHANNEL6_TIM5_CH4    6
#define DMA1_STREAM1_CHANNEL6_TIM5_TRIG   6
/*Stream 2*/
#define DMA1_STREAM2_CHANNEL0_SPI3_RX     0
#define DMA1_STREAM2_CHANNEL2_I2S3_EXT_RX 2
#define DMA1_STREAM2_CHANNEL3_I2C3_RX     3
#define DMA1_STREAM2_CHANNEL5_TIM3_CH4    5
#define DMA1_STREAM2_CHANNEL5_TIM3_UP     5
#define DMA1_STREAM2_CHANNEL6_TIM5_CH1    6
#define DMA1_STREAM2_CHANNEL7_I2C2_RX     7
/*Stream 3*/
#define DMA1_STREAM3_CHANNEL0_SPI2_RX     0
#define DMA1_STREAM3_CHANNEL2_TIM4_CH2    2
#define DMA1_STREAM3_CHANNEL3_I2S2_EXT_RX 3
#define DMA1_STREAM3_CHANNEL5_TIM3_CH1    5
#define DMA1_STREAM3_CHANNEL5_TIM3_TRIG   5
#define DMA1_STREAM3_CHANNEL6_TIM5_CH2    6
/*Stream 4*/
#define DMA1_STREAM4_CHANNEL0_SPI2_TX     0
#define DMA1_STREAM4_CHANNEL2_I2S2_EXT_TX 2
#define DMA1_STREAM4_CHANNEL3_I2C3_TX     3
#define DMA1_STREAM4_CHANNEL5_SPI4_TX     5
#define DMA1_STREAM4_CHANNEL6_TIM1_CH4    6
#define DMA1_STREAM4_CHANNEL6_TIM1_TRIG   6
#define DMA1_STREAM4_CHANNEL6_TIM1_COM    6
/*Stream 5*/
#define DMA1_STREAM5_CHANNEL0_SPI3_TX     0
#define DMA1_STREAM5_CHANNEL1_I2C1_RX     1
#define DMA1_STREAM5_CHANNEL2_I2S3_EXT_TX 2
#define DMA1_STREAM5_CHANNEL3_TIM2_CH1    3
#define DMA1_STREAM5_CHANNEL4_USART2_RX   4
#define DMA1_STREAM5_CHANNEL5_TIM3_CH2    5
#define DMA1_STREAM5_CHANNEL6_I2C3_TX     6
/*Stream 6*/
#define DMA1_STREAM6_CHANNEL1_I2C1_TX     1
#define DMA1_STREAM6_CHANNEL2_TIM4_UP     2
#define DMA1_STREAM6_CHANNEL3_TIM2_CH2    3
#define DMA1_STREAM6_CHANNEL3_TIM2_CH4    3
#define DMA1_STREAM6_CHANNEL4_USART2_TX   4
#define DMA1_STREAM6_CHANNEL6_TIM5_UP     6
/*Stream 7*/
#define DMA1_STREAM7_CHANNEL0_SPI3_TX     0
#define DMA1_STREAM7_CHANNEL1_I2C1_TX     1
#define DMA1_STREAM7_CHANNEL2_TIM4_CH3    2
#define DMA1_STREAM7_CHANNEL3_TIM2_UP     3
#define DMA1_STREAM7_CHANNEL3_TIM2_CH4    3
#define DMA1_STREAM7_CHANNEL5_TIM3_CH3    5
#define DMA1_STREAM7_CHANNEL7_I2C2_TX     7

/************ DMA2 ************/
/*Stream 0*/
#define DMA2_STREAM0_CHANNEL0_ADC1      0
#define DMA2_STREAM0_CHANNEL3_SPI1_RX   3
#define DMA2_STREAM0_CHANNEL4_SPI4_RX   4
#define DMA2_STREAM0_CHANNEL6_TIM1_TRIG 6
/*Stream 1*/
#define DMA2_STREAM1_CHANNEL4_SPI4_TX   4
#define DMA2_STREAM1_CHANNEL5_USART6_RX 5
#define DMA2_STREAM1_CHANNEL6_TIM1_CH1  6
/*Stream 2*/
#define DMA2_STREAM2_CHANNEL3_SPI1_RX   3
#define DMA2_STREAM2_CHANNEL4_USART1_RX 4
#define DMA2_STREAM2_CHANNEL5_USART6_RX 5
#define DMA2_STREAM2_CHANNEL6_TIM1_CH2  6
/*Stream 3*/
#define DMA2_STREAM3_CHANNEL3_SPI1_TX   3
#define DMA2_STREAM3_CHANNEL4_SDIO      4
#define DMA2_STREAM3_CHANNEL5_SPI4_RX   5
#define DMA2_STREAM3_CHANNEL6_TIM1_CH1  6
/*Stream 4*/
#define DMA2_STREAM4_CHANNEL0_ADC1      0
#define DMA2_STREAM4_CHANNEL5_SPI4_TX   5
#define DMA2_STREAM4_CHANNEL6_TIM1_CH4  6
#define DMA2_STREAM4_CHANNEL6_TIM1_TRIG 6
#define DMA2_STREAM4_CHANNEL6_TIM1_COM  6
/*Stream 5*/
#define DMA2_STREAM5_CHANNEL4_SPI1_TX   4
#define DMA2_STREAM5_CHANNEL5_USART1_RX 5
#define DMA2_STREAM5_CHANNEL6_TIM1_UP   6
/*Stream 6*/
#define DMA2_STREAM6_CHANNEL0_TIM1_CH1  0
#define DMA2_STREAM6_CHANNEL0_TIM1_CH2  0
#define DMA2_STREAM6_CHANNEL0_TIM1_CH3  0
#define DMA2_STREAM6_CHANNEL4_SDIO      4
#define DMA2_STREAM6_CHANNEL5_USART6_TX 5
#define DMA2_STREAM6_CHANNEL6_TIM1_CH3  6
/*Stream 7*/
#define DMA2_STREAM7_CHANNEL4_USART1_TX 4
#define DMA2_STREAM7_CHANNEL5_USART6_TX 5

typedef struct {
    uint8 u8StreamNum:      3;
    uint8 u8ChannelNum:     3;
    uint8 u8PSize:          2;
    uint8 u8MIncMode:       1;
    uint8 u8PIncMode:       1;
    uint8 u8DataDirection:  2;
    uint8 u8PFlowCtrl:      1;
    uint8 u8TransferInt:    1;
}tstrDMA_config;

void DMA1_voidConfig(tstrDMA_config strConfig);

void DMA1_voidStartTransfer(uint8 u8StreamNumCpy, uint32* pu32PeriphAddressCpy, uint32* pu32MemoryAddressCpy, uint16 u16BlockSizeCpy);

void DMA1_voidEnable(uint8 u8StreamNumCpy);

void DMA1_voidDisable(uint8 u8StreamNumCpy);

void DMA1_voidSetCallBack(uint8 u8StreamNumCpy, pf pfISRCpy);

void DMA2_voidConfig(tstrDMA_config strConfig);

void DMA2_voidStartTransfer(uint8 u8StreamNumCpy, uint32* pu32PeriphAddressCpy, uint32* pu32MemoryAddressCpy, uint16 u16BlockSizeCpy);

void DMA2_voidEnable(uint8 u8StreamNumCpy);

void DMA2_voidDisable(uint8 u8StreamNumCpy);

void DMA2_voidSetCallBack(uint8 u8StreamNumCpy, pf pfISRCpy);

#endif
