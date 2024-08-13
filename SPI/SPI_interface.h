/*
 * SPI_interface.h
 *
 *  Created on: Feb 25, 2024
 *      Author: Mohanad
 */

#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

#include "SPI_config.h"
#include "SPI_private.h"
#include "../../MCAL/RCC/RCC_Interface.h"
#include "../../LIB/Platform_Types.h"

enum PollingMechanism
{
	PollingEnable ,
	PollingDisable
};

/*
 * ===============================================
 * APIs Supported by "MCAL SPI DRIVER"
 * ===============================================
 */
void MCAL_SPI_Init(SPI_TypeDef *SPIx,SPI_Config_t *SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx);

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx);

void MCAL_SPI_SendData(SPI_TypeDef *SPIx,uint16 *pTxBuffer ,enum PollingMechanism PollingEn );

void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx,uint16 *pTxBuffer ,enum PollingMechanism PollingEn );

void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx,uint16 *pTxBuffer ,enum PollingMechanism PollingEn );

#endif /* MCAL_SPI_SPI_INTERFACE_H_ */
