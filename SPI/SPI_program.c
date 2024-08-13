/*
 * SPI_program.c
 *
 *  Created on: Feb 25, 2024
 *      Author: Mohanad
 */

#include "SPI_interface.h"

#define SPI1_INDEX		0
#define SPI2_INDEX		1

#define SPI_SR_TXE				((uint8)(0x02)) // Transmit Buffer is empty
#define SPI_SR_RXNE				((uint8)(0x01)) // Receive Buffer is not empty

/**================================================================
 * @Fn			 -MCAL_SPI_Init
 * @brief 		 -Initialize SPI according to the specified parameters in SPI_Config
 * @param [in]   -SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @param [in]   -PinConfig : pointer to SPI_Config Structure that Contains
 * 						      the configuration information for All SPI.
 * @retval		 -none
 * Note			 -Support for SPI Full Duplex Master/Slave & NSS HW/SW
 * 				 -In Case of Master you have to Configure pin and drive it.
 */

void MCAL_SPI_Init(SPI_TypeDef *SPIx,SPI_Config_t *SPI_Config)
{
	//Safety for registers
	uint16 tmpreg_CR1 = 0;
	uint16 tmpreg_CR2 = 0;

	if(SPIx == SPI1)
	{
		MRCC_u8EnablePeripheralClock(RCC_APB2, RCC_APB2_SPI1_EN);
	}
	else if(SPIx == SPI2)
	{
		MRCC_u8EnablePeripheralClock(RCC_APB1, RCC_APB1_SPI2_EN);
	}

	// Enable SPI CR1 bit6 SPE
	tmpreg_CR1 = (0x1U<<6);

	// Master or slave
	tmpreg_CR1 |= SPI_Config->Device_Mode;

	// Communication mode
	tmpreg_CR1 |= SPI_Config->Communication_Mode;

	// Frame format
	tmpreg_CR1 |= SPI_Config->Frame_Format;

	// Data size
	tmpreg_CR1 |= SPI_Config->Data_Size;

	// Clock polarity
	tmpreg_CR1 |= SPI_Config->CLK_Polarity;

	// Clock phase
	tmpreg_CR1 |= SPI_Config->CLK_Phase;

	// NSS
	if(SPI_Config->NSS == SPI_NSS_Hard_Master_SS_Output_Enable)
	{
		tmpreg_CR2 |= SPI_Config->NSS;
	}
	else if(SPI_Config->NSS == SPI_NSS_Hard_Master_SS_Output_Disable)
	{
		tmpreg_CR2 &= SPI_Config->NSS;
	}
	else
	{
		tmpreg_CR2 |= SPI_Config->NSS;
	}

	// Baudrate
	tmpreg_CR1 |= SPI_Config->SPI_BAUDRATEPRESCALER;

	SPIx->SPI_CR1 = tmpreg_CR1;
	SPIx->SPI_CR2 = tmpreg_CR2;
}

void MCAL_SPI_DeInit(SPI_TypeDef *SPIx)
{
	if(SPIx == SPI1)
	{
		MRCC_u8DisablePeripheralClock(RCC_APB2, RCC_APB2_SPI1_EN);
	}
	else if(SPIx == SPI2)
	{
		MRCC_u8DisablePeripheralClock(RCC_APB1, RCC_APB1_SPI2_EN);
	}
}

void MCAL_SPI_SendData(SPI_TypeDef *SPIx,uint16 *pTxBuffer ,enum PollingMechanism PollingEn)
{
	// todo receive only
	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_TXE));

	SPIx->SPI_DR = *pTxBuffer;
}

void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx,uint16 *pTxBuffer ,enum PollingMechanism PollingEn )
{
	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_RXNE)) ;

	*pTxBuffer = SPIx->SPI_DR ;
}

void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx,uint16 *pTxBuffer ,enum PollingMechanism PollingEn )
{

	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_TXE)) ;

	SPIx->SPI_DR = *pTxBuffer ;


	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_RXNE)) ;

	*pTxBuffer = SPIx->SPI_DR ;
}


