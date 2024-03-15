/*****************************************************************/
/* Author  : Ahmed                                               */
/* Layer   : MCAL                                                */
/* SWC     : DMA                                                 */
/* Version : 1.0                                                 */
/* Date    : 10 Mar 2024                                         */
/*****************************************************************/
#ifndef DMA_PRIVATE_H_
#define DMA_PRIVATE_H_

#define DMA1_BASE_ADDRESS (0x40026000)
#define DMA2_BASE_ADDRESS (0x40026400)

typedef struct{
    uint32 CR;
    uint32 NDTR;
    uint32 PAR;
    uint32 M0AR;
    uint32 M1AR;
    uint32 FCR;
}DMA_Sx_t;

typedef struct{
    uint32 LISR;
    uint32 HISR;
    uint32 LIFCR;
    uint32 HIFCR;
    DMA_Sx_t Sx[8];
}DMA_t;

#define DMA1_REG ((volatile DMA_t*)DMA1_BASE_ADDRESS)
#define DMA2_REG ((volatile DMA_t*)DMA2_BASE_ADDRESS)

#endif
