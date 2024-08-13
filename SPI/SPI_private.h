/*
 * SPI_private.h
 *
 *  Created on: Feb 25, 2024
 *      Author: Mohanad
 */

#ifndef MCAL_SPI_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_PRIVATE_H_

#include "../../LIB/Platform_Types.h"

#define SPI1_BASE			0x40013000UL
#define SPI2_BASE			0x40003800UL

typedef struct
{
	volatile uint32	SPI_CR1;
	volatile uint32	SPI_CR2;
	volatile uint32	SPI_SR;
	volatile uint32	SPI_DR;
	volatile uint32	SPI_CRCPR;
	volatile uint32	SPI_RXCRCR;
	volatile uint32	SPI_TXCRCR;
	volatile uint32	SPI_I2SCFGR;
	volatile uint32	SPI_I2SPR;
}SPI_TypeDef;

#define SPI1		((SPI_TypeDef *)SPI1_BASE)
#define SPI2		((SPI_TypeDef *)SPI2_BASE)

#define SPI1_IRQ			35
#define SPI2_IRQ			36

#endif /* MCAL_SPI_SPI_PRIVATE_H_ */
