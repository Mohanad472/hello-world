/*
 * SPI_config.h
 *
 *  Created on: Feb 25, 2024
 *      Author: Mohanad
 */

#ifndef MCAL_SPI_SPI_CONFIG_H_
#define MCAL_SPI_SPI_CONFIG_H_

#include "SPI_interface.h"
#include "../../LIB/Platform_Types.h"

struct S_IRQ_SRC
{
	uint8 TXE:1 ;
	uint8 RXNE:1 ;
	uint8 ERRI:1 ;
	uint8 Reserved:5 ;
};

typedef struct
{
	uint16        Device_Mode ;         //specifies the SPI operation mode @ref SPI_Device_Mode
	uint16        Communication_Mode ;  //specifies the SPI bidirectional mode state @ref SPI_Communication_Mode
	uint16        Frame_Format ;        //specifies LSB or MSB @ref SPI_Frame_Format
	uint16        Data_Size ;           //specifies Size of TX/RX Data 8/16 Bits @ref SPI_Data_Size
	uint16        CLK_Polarity ;        //specifies Clock Polarity (Low_Level when Idle or High_Level when idle )
	// this Parameter set based on @ref SPI_Clock_Polarity

	uint16        CLK_Phase ;           //specifies Clock Phase (Sampling at 1st or 2nd edge)according to CLKPolarity
	// this Parameter set based on @ref SPI_Clock_Phase

	uint16        NSS;                  //specifies whether the NSS signal managed by
	// Hardware (NSS Pin) or (Software SSI bit enable)
	// this Parameter set based on @ref SPI_NSS

	uint16        SPI_BAUDRATEPRESCALER ; /* Specifies the baud rate prescaler value which will be
											 used to configure the transmit and receive SCK Clock.
											 This Parameter can be a value of @ref SPI_BaudRatePrescaler
											 @note The Communication Clock derived form the master clock.
											 The slave clock dose not need to be set.*/
	/* Take care you have to Configure RCC to enter the correct clock to APB1 >> SPI2
											  or APB2 >> SPI1 .*/


	uint16        IRQ_Enable ;          // Specifies Interrupt Enable or Disable
	// This parameter must be set based on @ref SPI_IRQ_Enable_Define


	void (* P_IRQ_CallBack)(struct S_IRQ_SRC irq_src );  // Set C Function() which will be called once the IRQ Happen .

}SPI_Config_t;


//@ref SPI_Device_Mode
#define SPI_Device_Mode_SLAVE				(uint32)(0)	         //CR1 >> Bit 2 MSTR: Slave selection
#define SPI_Device_Mode_MASTER  			(uint32)(1<<2)         //CR1 >> Bit 2 MSTR: Master selection

//@ref SPI_Communication_Mode
#define SPI_DIRECTION_2LINES				(uint32)(0)	         //CR1 >> Bit 10 RXONLY: Full Duplex
#define SPI_DIRECTION_2LINES_RXONLY			(uint32)(1<<10)        //CR1 >> Bit 10 RXONLY: Receive only
#define SPI_DIRECTION_1LINES_TXONLY			(uint32)(1<<15 | 1<<14)//CR1 >> Bit 15 BIDIMODE: Bidirectional data mode enable
                                                                     //CR1 >> Bit 14 BIDIOE: Output disabled (receive-only mode)
#define SPI_DIRECTION_1LINES_RXONLY			(uint32)(1<<15)        //CR1 >> Bit 15 BIDIMODE: Bidirectional data mode enable
                                                                     //CR1 >> Bit 14 BIDIOE: Output enabled (transmit-only mode)

//@ref SPI_Frame_Format
#define SPI_Frame_Format_MSB_transmitted_first			(uint32)(0)   // MSB First
#define SPI_Frame_Format_LSB_transmitted_first			(uint32)(1<<7)//CR1 >> Bit 7 LSBFIRST: Frame format (LSB First)

//@ref SPI_Data_Size
#define SPI_Frame_Format_8B								(uint32)(0)
#define SPI_Frame_Format_16B							(uint32)(1<<11)//CR1 >> Bit 11 DFF: Data frame format

//@ref SPI_Clock_Polarity
#define	SPI_Clock_Polarity_LOW_when_Idle				(uint32)(0)    //CR1 >> Bit1 CPOL: CK to 0(Low_Level) when idle
#define	SPI_Clock_Polarity_HIGH_when_Idle				(uint32)(1<<1) //CR1 >> Bit1 CPOL: CK to 1(High_Level) when idle

//@ref SPI_Clock_Phase
#define	SPI_Clock_Phase_1EDGE_first_data_capture_edge	(uint32)(0)
#define	SPI_Clock_Phase_2EDGE_first_data_capture_edge	(uint32)(1<<0)//CR1 >> Bit 0 CPHA: Clock phase

//@ref SPI_NSS SPI Slave Select Management
//-----------------NSS--------------------
//Hardware
#define SPI_NSS_Hard_Slave  							(uint32)(0)   //CR1 >> Bit 9 SSM: Software slave management (Reset)
#define SPI_NSS_Hard_Master_SS_Output_Enable			(uint32)(1<<2)//CR2 >>Bit 2 SSOE: SS output enable
#define SPI_NSS_Hard_Master_SS_Output_Disable			~((uint32)(1<<2))	//CR2 >>Bit 2 SSOE: SS output enable

//NSS is Driven by SW (Master or Slave)
#define SPI_NSS_SW_NSSInternalSoft_Reset				(uint32)(1<<9)//CR1 >> Bit 9 SSM: Software slave management (Reset)
#define SPI_NSS_SW_NSSInternalSoft_Set					(uint32)(1<<9 | 1<<8)// for Slave & Master

//@ref SPI_BaudRatePrescaler
#define SPI_BaudRatePrescaler_2			(uint32)(0)
#define SPI_BaudRatePrescaler_4			(uint32)(0b001U << 3)
#define SPI_BaudRatePrescaler_8			(uint32)(0b010U << 3)
#define SPI_BaudRatePrescaler_16		(uint32)(0b011U << 3)
#define SPI_BaudRatePrescaler_32		(uint32)(0b100U << 3)
#define SPI_BaudRatePrescaler_64		(uint32)(0b101U << 3)
#define SPI_BaudRatePrescaler_128		(uint32)(0b110U << 3)
#define SPI_BaudRatePrescaler_256		(uint32)(0b111U << 3)

//@ref SPI_IRQ_Enable_Define
#define SPI_IRQ_Enable_NONE				(uint32)(0)
#define SPI_IRQ_Enable_TXEIE			(uint32)(1<<7)//CR2 >> Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE			(uint32)(1<<5)//CR2 >> Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE			(uint32)(1<<6)//CR2 >> Bit 5 ERRIE: Error interrupt enable

#endif /* MCAL_SPI_SPI_CONFIG_H_ */
