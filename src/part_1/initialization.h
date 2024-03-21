/*
 * initialization.h
 *
 *  Created on	: Mar 14, 2021
 *  Modified by	: Shyama M. Gandhi, Winter 2023 (This file functions have been adopted from Xilinx driver files)
 *
 *  This file has been created using inbuilt driver functions for UART and SPI.
 *  The file also has a print_command_menu() function for displaying the menu on console.
 *  SPI 0 as MASTER, SPI 1 as SLAVE
 *
 */

#ifndef SRC_INITIALIZATION_H_
#define SRC_INITIALIZATION_H_

#include "xuartps.h"	/* UART device driver */
#include "xspips.h"		/* SPI device driver */

/******************* Other defined functions for UART and SPI ****************/
extern int intializeUART( u16 deviceId );
extern int initializeSPI( u16 spiMaster, u16 spiSlave );

extern void printMenu( void );

extern void spiMasterWrite( u8 *sendbuffer, int byteCount );
extern void spiSlaveRead( int byteCount );
extern void spiSlaveWrite( u8 *sendbuffer, int byteCount );
extern void spiMasterRead( int byteCount );


/***************** Macros (Inline Functions) Definitions *********************/

#define SpiPs_RecvByte(BaseAddress) \
		(u8)XSpiPs_In32((BaseAddress) + XSPIPS_RXD_OFFSET)

#define SpiPs_SendByte(BaseAddress, Data) \
		XSpiPs_Out32((BaseAddress) + XSPIPS_TXD_OFFSET, (Data))

/************************** Variable Definitions *****************************/

XUartPs Uart_PS;		/* Instance of the UART Device */
XUartPs_Config *Config;	/* The instance of the UART-PS Config */

u8 RxBuffer_Slave[1];
u8 *buffer_Rx_Master;
u8 RxBuffer_Master[1];

/*****************************************************************************/

#define configGENERATE_RUN_TIME_STATS 1
#define configUSE_STATS_FORMATTING_FUNCTIONS 1

#endif /* SRC_INITIALIZATION_H_ */
