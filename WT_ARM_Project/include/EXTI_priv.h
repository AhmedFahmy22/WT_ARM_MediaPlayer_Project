/*
 * EXTI_priv.h
 *
 *  Created on: Jan 18, 2024
 *      Author: Ahmed
 */

#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_

#define SYSCFG_BASE_ADDRESS (0x40013800+0x08)

typedef struct{
	uint32 EXTICR[4];
}SysCfg_t;

#define SYSCF_REG ((volatile SysCfg_t*)SYSCFG_BASE_ADDRESS)

#define EXTI_BASE_ADDRESS (0x40013C00)

typedef struct{
	uint32 IMR;
	uint32 EMR;
	uint32 RTSR;
	uint32 FTSR;
	uint32 SWIER;
	uint32 PR;
}EXTI_t;

#define EXTI_REG ((volatile EXTI_t*)EXTI_BASE_ADDRESS)

#endif /* EXTI_PRIV_H_ */
