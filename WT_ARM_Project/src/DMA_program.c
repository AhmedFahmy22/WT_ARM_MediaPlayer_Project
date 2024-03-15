/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : DMA                                                 */
/* Version : 1.0                                                 */
/* Date    : 10 Mar 2024                                         */
/*****************************************************************/
#include "STD_Types.h"
#include "BIT_Math.h"

#include "DMA_interface.h"
#include "DMA_private.h"
#include "DMA_config.h"

#define CR_EN     0
#define CR_TCIE   4
#define CR_PFCTRL 5
#define CR_DIR    6
#define CR_PINC   9
#define CR_MINC   10
#define CR_PSIZE  11
#define CR_CHSEL  25

pf apfDMA1StreamISR[8];
pf apfDMA2StreamISR[8];

/*************** DMA1 ***************/
void DMA1_voidConfig(tstrDMA_config strConfig)
{
    /*Disable DMA Stream ==> clear SxCR bit 0*/
    CLR_BIT(DMA1_REG->Sx[strConfig.u8StreamNum].CR,CR_EN);

    /*Channel Select ==> SxCR bits 25:27*/
    DMA1_REG->Sx[strConfig.u8StreamNum].CR &= ~(0b111<<CR_CHSEL);
    DMA1_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8ChannelNum<<CR_CHSEL);

    /*Peripheral Data Size ==> SxCR bits 11:12*/
    DMA1_REG->Sx[strConfig.u8StreamNum].CR &= ~(0b11<<CR_PSIZE);
    DMA1_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8PSize<<CR_PSIZE);

    /*Memory Increment Mode ==> SxCR bit 10*/
    CLR_BIT(DMA1_REG->Sx[strConfig.u8StreamNum].CR,CR_MINC);
    DMA1_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8MIncMode<<CR_MINC);

    /*Peripheral Increment Mode ==> SxCR bit 9*/
    CLR_BIT(DMA1_REG->Sx[strConfig.u8StreamNum].CR,CR_PINC);
    DMA1_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8PIncMode<<CR_PINC);

    /*Data Transfer Direction ==> SxCR bits 6:7*/
    DMA1_REG->Sx[strConfig.u8StreamNum].CR &= ~(0b11<<CR_DIR);
    DMA1_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8DataDirection<<CR_DIR);

    /*Peripheral Flow Control ==> SxCR bit 5*/
    CLR_BIT(DMA1_REG->Sx[strConfig.u8StreamNum].CR,CR_PFCTRL);
    DMA1_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8PFlowCtrl<<CR_PFCTRL);

    /*Transfer Complete Interrupt ==> SxCR bit 4*/
    CLR_BIT(DMA1_REG->Sx[strConfig.u8StreamNum].CR,CR_TCIE);
    DMA1_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8TransferInt<<CR_TCIE);

}

void DMA1_voidStartTransfer(uint8 u8StreamNumCpy, uint32* pu32PeriphAddressCpy, uint32* pu32MemoryAddressCpy, uint16 u16BlockSizeCpy)
{
    /*Disable DMA Stream ==> clear SxCR bit 0*/
    CLR_BIT(DMA1_REG->Sx[u8StreamNumCpy].CR,CR_EN);

    /*Block size ==> SxNDTR*/
    DMA1_REG->Sx[u8StreamNumCpy].NDTR = u16BlockSizeCpy;

    /*Peripheral Address ==> SxPAR*/
    DMA1_REG->Sx[u8StreamNumCpy].PAR = pu32PeriphAddressCpy;

    /*Memory Address ==> SxM0AR*/
    DMA1_REG->Sx[u8StreamNumCpy].M0AR = pu32MemoryAddressCpy;

    /*Enable DMA Stream ==> set SxCR bit 0*/
    SET_BIT(DMA1_REG->Sx[u8StreamNumCpy].CR,CR_EN);
}

void DMA1_voidEnable(uint8 u8StreamNumCpy)
{
    SET_BIT(DMA1_REG->Sx[u8StreamNumCpy].CR,CR_EN);
}

void DMA1_voidDisable(uint8 u8StreamNumCpy)
{
    CLR_BIT(DMA1_REG->Sx[u8StreamNumCpy].CR,CR_EN);
}

void DMA1_voidSetCallBack(uint8 u8StreamNumCpy, pf pfISRCpy)
{
    apfDMA1StreamISR[u8StreamNumCpy] = pfISRCpy;
}

/*************** DMA2 ***************/
void DMA2_voidConfig(tstrDMA_config strConfig)
{
    /*Disable DMA Stream ==> clear SxCR bit 0*/
    CLR_BIT(DMA2_REG->Sx[strConfig.u8StreamNum].CR,CR_EN);

    /*Channel Select ==> SxCR bits 25:27*/
    DMA2_REG->Sx[strConfig.u8StreamNum].CR &= ~(0b111<<CR_CHSEL);
    DMA2_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8ChannelNum<<CR_CHSEL);

    /*Peripheral Data Size ==> SxCR bits 11:12*/
    DMA2_REG->Sx[strConfig.u8StreamNum].CR &= ~(0b11<<CR_PSIZE);
    DMA2_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8PSize<<CR_PSIZE);

    /*Memory Increment Mode ==> SxCR bit 10*/
    CLR_BIT(DMA2_REG->Sx[strConfig.u8StreamNum].CR,CR_MINC);
    DMA2_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8MIncMode<<CR_MINC);

    /*Peripheral Increment Mode ==> SxCR bit 9*/
    CLR_BIT(DMA2_REG->Sx[strConfig.u8StreamNum].CR,CR_PINC);
    DMA2_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8PIncMode<<CR_PINC);

    /*Data Transfer Direction ==> SxCR bits 6:7*/
    DMA2_REG->Sx[strConfig.u8StreamNum].CR &= ~(0b11<<CR_DIR);
    DMA2_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8DataDirection<<CR_DIR);

    /*Peripheral Flow Control ==> SxCR bit 5*/
    CLR_BIT(DMA2_REG->Sx[strConfig.u8StreamNum].CR,CR_PFCTRL);
    DMA2_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8PFlowCtrl<<CR_PFCTRL);

    /*Transfer Complete Interrupt ==> SxCR bit 4*/
    CLR_BIT(DMA2_REG->Sx[strConfig.u8StreamNum].CR,CR_TCIE);
    DMA2_REG->Sx[strConfig.u8StreamNum].CR |= (strConfig.u8TransferInt<<CR_TCIE);

}

void DMA2_voidStartTransfer(uint8 u8StreamNumCpy, uint32* pu32PeriphAddressCpy, uint32* pu32MemoryAddressCpy, uint16 u16BlockSizeCpy)
{
    /*Disable DMA Stream ==> clear SxCR bit 0*/
    CLR_BIT(DMA2_REG->Sx[u8StreamNumCpy].CR,CR_EN);

    /*Block size ==> SxNDTR*/
    DMA2_REG->Sx[u8StreamNumCpy].NDTR = (uint32)u16BlockSizeCpy;
    uint32* pu32NDTRLoc = &(DMA2_REG->Sx[u8StreamNumCpy].NDTR);

    /*Peripheral Address ==> SxPAR*/
    DMA2_REG->Sx[u8StreamNumCpy].PAR = pu32PeriphAddressCpy;

    /*Memory Address ==> SxM0AR*/
    DMA2_REG->Sx[u8StreamNumCpy].M0AR = pu32MemoryAddressCpy;

    /*Enable DMA Stream ==> set SxCR bit 0*/
    SET_BIT(DMA2_REG->Sx[u8StreamNumCpy].CR,CR_EN);
}

void DMA2_voidEnable(uint8 u8StreamNumCpy)
{
    SET_BIT(DMA2_REG->Sx[u8StreamNumCpy].CR,CR_EN);
}

void DMA2_voidDisable(uint8 u8StreamNumCpy)
{
    CLR_BIT(DMA2_REG->Sx[u8StreamNumCpy].CR,CR_EN);
}

void DMA2_voidSetCallBack(uint8 u8StreamNumCpy, pf pfISRCpy)
{
    apfDMA2StreamISR[u8StreamNumCpy] = pfISRCpy;
}

/************ IRQ Handlers************/

/**** DMA1 ****/
void DMA1_Stream0_IRQHandler(void)
{
    if(apfDMA1StreamISR[0]!=NULL_PTR)
    {
        apfDMA1StreamISR[0]();
    }
    SET_BIT(DMA1_REG->LIFCR,5);
}

void DMA1_Stream1_IRQHandler(void)
{
    if(apfDMA1StreamISR[1]!=NULL_PTR)
    {
        apfDMA1StreamISR[1]();
    }
    SET_BIT(DMA1_REG->LIFCR,11);
}

void DMA1_Stream2_IRQHandler(void)
{
    if(apfDMA1StreamISR[2]!=NULL_PTR)
    {
        apfDMA1StreamISR[2]();
    }
    SET_BIT(DMA1_REG->LIFCR,21);
}

void DMA1_Stream3_IRQHandler(void)
{
    if(apfDMA1StreamISR[3]!=NULL_PTR)
    {
        apfDMA1StreamISR[3]();
    }
    SET_BIT(DMA1_REG->LIFCR,27);
}

void DMA1_Stream4_IRQHandler(void)
{
    if(apfDMA1StreamISR[4]!=NULL_PTR)
    {
        apfDMA1StreamISR[4]();
    }
    SET_BIT(DMA1_REG->HIFCR,5);
}

void DMA1_Stream5_IRQHandler(void)
{
    if(apfDMA1StreamISR[5]!=NULL_PTR)
    {
        apfDMA1StreamISR[5]();
    }
    SET_BIT(DMA1_REG->HIFCR,11);
}

void DMA1_Stream6_IRQHandler(void)
{
    if(apfDMA1StreamISR[6]!=NULL_PTR)
    {
        apfDMA1StreamISR[6]();
    }
    SET_BIT(DMA1_REG->HIFCR,21);
}

void DMA1_Stream7_IRQHandler(void)
{
    if(apfDMA1StreamISR[7]!=NULL_PTR)
    {
        apfDMA1StreamISR[7]();
    }
    SET_BIT(DMA1_REG->HIFCR,27);
}

/**** DMA1 ****/
void DMA2_Stream0_IRQHandler(void)
{
    if(apfDMA2StreamISR[0]!=NULL_PTR)
    {
        apfDMA2StreamISR[0]();
    }
    SET_BIT(DMA2_REG->LIFCR,5);
}

void DMA2_Stream1_IRQHandler(void)
{
    if(apfDMA2StreamISR[1]!=NULL_PTR)
    {
        apfDMA2StreamISR[1]();
    }
    SET_BIT(DMA2_REG->LIFCR,11);
}

void DMA2_Stream2_IRQHandler(void)
{
    if(apfDMA2StreamISR[2]!=NULL_PTR)
    {
        apfDMA2StreamISR[2]();
    }
    SET_BIT(DMA2_REG->LIFCR,21);
}

void DMA2_Stream3_IRQHandler(void)
{
    if(apfDMA2StreamISR[3]!=NULL_PTR)
    {
        apfDMA2StreamISR[3]();
    }
    SET_BIT(DMA2_REG->LIFCR,27);
}

void DMA2_Stream4_IRQHandler(void)
{
    if(apfDMA2StreamISR[4]!=NULL_PTR)
    {
        apfDMA2StreamISR[4]();
    }
    SET_BIT(DMA2_REG->HIFCR,5);
}

void DMA2_Stream5_IRQHandler(void)
{
    if(apfDMA2StreamISR[5]!=NULL_PTR)
    {
        apfDMA2StreamISR[5]();
    }
    SET_BIT(DMA2_REG->HIFCR,11);
}

void DMA2_Stream6_IRQHandler(void)
{
    if(apfDMA2StreamISR[6]!=NULL_PTR)
    {
        apfDMA2StreamISR[6]();
    }
    SET_BIT(DMA2_REG->HIFCR,21);
}

void DMA2_Stream7_IRQHandler(void)
{
    if(apfDMA2StreamISR[7]!=NULL_PTR)
    {
        apfDMA2StreamISR[7]();
    }
    SET_BIT(DMA2_REG->HIFCR,27);
}
