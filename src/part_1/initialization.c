/*
 * initialization.c
 *
 *  Created on: Feb 24, 2023
 *  Author: Shyama Gandhi
 *  Modified by	: Shyama M. Gandhi, Winter 2023 (This file functions have been adopted from Xilinx driver files)
 *
 *  This file has been created using inbuilt driver functions for UART and SPI.
 *
 */


#include "initialization.h"

static XSpiPs spiInstMaster;
static XSpiPs spiInstSlave;

int intializeUART(u16 deviceId)
{
	int status;
	Config = XUartPs_LookupConfig(deviceId);
	if (Config == NULL) {
		return XST_FAILURE;
	}

	status = XUartPs_CfgInitialize(&Uart_PS, Config, Config->BaseAddress);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XUartPs_SetOperMode(&Uart_PS, XUARTPS_OPER_MODE_NORMAL);

	return XST_SUCCESS;
}

void printMenu( void )
{
	xil_printf("*****************Welcome to Lab_3 of ECE-315*****************\r\n");
	xil_printf("Select from the Command Menu to perform the desired operation.\r\n");
	xil_printf("Press <ENTER><menu command number><ENTER>\r\n\n");
	xil_printf("\n*** UART Loop-back OFF ***\r\n");
	xil_printf("\n*** SPI Loop-back OFF ***\r\n");
	xil_printf("\n\t1: Toggle UART Loop-back Mode\r\n");
	xil_printf("\n\t2: Toggle SPI Loop-back Mode\r\n");

}



int initializeSPI( u16 spiMaster, u16 spiSlave )
{
	int status;
	XSpiPs_Config *spiConfigMaster;
	XSpiPs_Config *spiConfigSlave;

	/*
	 * Initialize the SPI driver for SPI 0 so that it's ready to use
	 */
	spiConfigMaster = XSpiPs_LookupConfig(spiMaster);
	if (NULL == spiConfigMaster) {
		return XST_FAILURE;
	}

	status = XSpiPs_CfgInitialize( &spiInstMaster
								 , spiConfigMaster
								 , spiConfigMaster->BaseAddress
								 );

	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Initialize the SPI driver for SPI 1 so that it's ready to use
	 */

	spiConfigSlave = XSpiPs_LookupConfig(spiSlave);
	if (NULL == spiConfigSlave) {
		return XST_FAILURE;
	}

	status = XSpiPs_CfgInitialize( &spiInstSlave
								 , spiConfigSlave
								 , spiConfigSlave->BaseAddress
								 );
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	status = XSpiPs_SetOptions( &spiInstMaster, (XSPIPS_CR_CPHA_MASK) | (XSPIPS_MASTER_OPTION ) | (XSPIPS_CR_CPOL_MASK));
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	status = XSpiPs_SetOptions( &spiInstSlave, (XSPIPS_CR_CPHA_MASK) | (XSPIPS_CR_CPOL_MASK));
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;

}


spiMasterRead(int byteCount)
{
	int count=0;

//	RxBuffer_Master[count] = SpiPs_RecvByte(spiInstMaster.Config.BaseAddress);


	for(count = 0; count < byteCount; count++){
		RxBuffer_Master[count] = SpiPs_RecvByte(
				spiInstMaster.Config.BaseAddress);

	}
}

void spiMasterWrite(u8 *Sendbuffer, int byteCount)
{
	u32 statusReg;
	int transCount = 0;

	statusReg = XSpiPs_ReadReg(spiInstMaster.Config.BaseAddress,
				XSPIPS_SR_OFFSET);

	/*
	 * Fill the TXFIFO with as many bytes as it will take (or as
	 * many as we have to send).
	 */

	while (byteCount > 0 && transCount < XSPIPS_FIFO_DEPTH) {
		SpiPs_SendByte(spiInstMaster.Config.BaseAddress, *Sendbuffer);
		Sendbuffer++;
		++transCount;
		byteCount--;
	}

	/*
	 * Wait for the transfer to finish by polling Tx fifo status.
	 */
	do {
		statusReg = XSpiPs_ReadReg(spiInstMaster.Config.BaseAddress, XSPIPS_SR_OFFSET);
	} while ((statusReg & XSPIPS_IXR_TXOW_MASK) == 0);
}

void spiSlaveRead(int byteCount)
{
	int count;
	u32 statusReg;

	statusReg = XSpiPs_ReadReg(spiInstSlave.Config.BaseAddress,
					XSPIPS_SR_OFFSET);
	/*
	 * Polling the Rx Buffer for Data
	 */
	do{
		statusReg = XSpiPs_ReadReg( spiInstSlave.Config.BaseAddress,
									XSPIPS_SR_OFFSET);
	}while(!(statusReg & XSPIPS_IXR_RXNEMPTY_MASK));

	/*
	 * Reading the Rx Buffer
	 */
	for(count = 0; count < byteCount; count++){
		RxBuffer_Slave[count] = SpiPs_RecvByte(
				spiInstSlave.Config.BaseAddress);
	}

}

void spiSlaveWrite(u8 *Sendbuffer, int byteCount)
{
	int transCount = 0;
	u32 statusReg;

	statusReg = XSpiPs_ReadReg( spiInstSlave.Config.BaseAddress,
								XSPIPS_SR_OFFSET);

	while ((byteCount > 0) && (transCount < XSPIPS_FIFO_DEPTH)) {
		SpiPs_SendByte( spiInstSlave.Config.BaseAddress,
						*Sendbuffer);
		Sendbuffer++;
		++transCount;
		byteCount--;
	}

	/*
	 * Wait for the transfer to finish by polling Tx fifo status.
	 */
	do {
		statusReg = XSpiPs_ReadReg( spiInstSlave.Config.BaseAddress,
									XSPIPS_SR_OFFSET);
	} while ((statusReg & XSPIPS_IXR_TXOW_MASK) == 0);
}
