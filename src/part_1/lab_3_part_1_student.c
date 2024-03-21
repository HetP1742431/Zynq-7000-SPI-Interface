/******************************************************************************/
/* ECE - 315 	: WINTER 2021
 * Created on 	: 07 August, 2021
 *
 * Created by	: Shyama M. Gandhi, Mazen Elbaz
 * Modified by	: Shyama M. Gandhi, Winter 2023
 *
 * LAB 3: Implementation of SPI in Zynq-7000
 *------------------------------------------------------------------------------
 * This lab uses SPI in polled mode. The hardware diagram has a loop back connection hard coded where SPI0 - MASTER and SPI1 - SLAVE.
 * In this code SPI0 MASTER writes to SPI1 slave. The data received by SPI1 is transmitted back to the SPI0 master.
 * The driver function used to achieve this are provided by the Xilinx as xspips.h and xspipshw_h.
 * They are present in the provided initialization.h header file.
 *
 * There are two commands in the menu (options in the menu).
 * 1. Toggle loop back for UART manager task enable or disable (loop back mode)
 * 2. Toggle loop back for spi0-spi1 connection enable or disable (loop back mode)
 *
 * User enters the command in following ways:
 * For example, after you load the application on to the board, User may wish to execute the menu command 1. command is detected by using "command, enter". In this example it is <1> <ENTER>.
 *
 * Menu command 1:
 * Initially,
 * <1><ENTER> can be used to change the UART Manager task loop back from enable to disable mode. This can also be done using the <ENTER><%><ENTER>.
 * To change the UART Manager loop back from disable to enable mode, use <1><ENTER>.
 *
 * Menu command 2:
 * Initially,
 * <2><ENTER> enables the task two loop back. Which means there is no connection between SPI0 and SPI1.
 * You can enable the task 2 loop back (disable the SPI 1 - SPI 0 connection) using <2><ENTER> or <ENTER><%><ENTER>.
 * However, to enable the SPI 1 - SPI 0 connection, you must use <2><ENTER>.
 *
 * -----------------------------------------------
 *	When "uart_loopback=0", UART Manager Task loop back is disabled. So, nothing will appear as an output on the console.
 *	When "uart_loopback=1", UART Manager Task loop back is enabled. This will send the received characters to the terminal using the vUartManagerTask() itself.
 *
 *  When "spi_loopback=1", there is no SPI connection in effect. The data will be echoed back to the user using the loop back mode that uses FIFO2.
 *  When "spi_loopback=0", SPI connection is in effect. The data entered by the user will loop back from spi0 to spi1 and back to spi0. The data will be then displayed on the terminal using the FIFO2.
 * -----------------------------------------------
 *
 *	INITIALLY, when you run the application, the console will display the MENU and if you type anything from the console, nothing will be displayed.
 *	Type say, <1><ENTER> to enable the UART loopback inside the task1. Now type any text from the console and it will be echoed back.
 *
 */
/******************************************************************************/


/*****************************  FreeRTOS includes. ****************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
/***************************** Include Files *********************************/

#include "xparameters.h"	/* SDK generated parameters */
#include "xspips.h"			/* SPI device driver */
#include "xil_printf.h"
#include <ctype.h>

/********************** User defined Include Files **************************/
#include "initialization.h"

/************************** Constant Definitions *****************************/
#define CHAR_PERCENT			0x25	/* '%' character is used as termination sequence */
#define CHAR_CARRIAGE_RETURN	0x0D	/* '\r' character is used in the termination sequence */
#define DOLLAR 					0x24	// BELL character
#define TRANSFER_SIZE_IN_BYTES  1 		// 1 byte is transferred between SPI 0 and SPI 1 in the provided template every time
#define QUEUE_LENGTH			500
#define UART_DEVICE_ID_0		XPAR_XUARTPS_0_DEVICE_ID
#define SPI_0_DEVICE_ID			XPAR_XSPIPS_0_DEVICE_ID
#define SPI_1_DEVICE_ID			XPAR_XSPIPS_1_DEVICE_ID

/************************* Task Function definitions *************************/
static void vUartManagerTask( void *pvParameters );
static void vSpiMainTask( void *pvParameters );
static void vSpiSubTask( void *pvParameters );
static TaskHandle_t xTask_uart;
static TaskHandle_t xTask_spi0;
static TaskHandle_t xTask_spi1;

/************************* Queue Function definitions *************************/
static QueueHandle_t xQueue_FIFO1 = NULL;//queue between task1 and task2
static QueueHandle_t xQueue_FIFO2 = NULL;//queue between task1 and task2

/************************* Function prototypes *************************/
void toggleUARTLoopback(void);
void toggleSpiMasterLoopback(void);
void checkTerminationSequence(void);
void checkCommand(void);

/************************* Global Variables *********************************/
int str_length; 				// length of number of bytes string
char rollingBuffer[3]={'\0', '\0', CHAR_CARRIAGE_RETURN}; // rolling buffer to detect termination sequence

BaseType_t spi_loopback = 0;	// GLOBAL variable to enable/disable loopback for spi main task
BaseType_t uart_loopback = 0;   // GLOBAL variable to enable/disable loopback for uart task

u32 flag = 0; 					// enables sending dummy char in SPI1-SPI0 mode

u8 command_flag = 1;			// determines the loopback mode
u8 sequence_flag = 0;			// helps detect the termination sequence
u8 uart_byte = 0;					// contains the last byte received through UART
u8 task1_receive_from_FIFO2;	// contains last data received when spi loopback was enabled
u8 task1_receive_from_FIFO2_spi_data; // contains data received by SPI1 and sent back using FIFO2

int message_counter=0;


int main(void)
{
	int status;

	xTaskCreate( vUartManagerTask
			   , (const char *) "UART TASK"
			   , configMINIMAL_STACK_SIZE*10
			   , NULL
			   , tskIDLE_PRIORITY+4
			   , &xTask_uart
			   );

	xTaskCreate( vSpiMainTask
			   , (const char *) "Main SPI TASK"
			   , configMINIMAL_STACK_SIZE*10
			   , NULL
			   , tskIDLE_PRIORITY+3
			   , &xTask_spi0
			   );

	xTaskCreate( vSpiSubTask
			   , (const char *) "Sub SPI TASK"
			   , configMINIMAL_STACK_SIZE*10
			   , NULL
			   , tskIDLE_PRIORITY+3
			   , &xTask_spi1
			   );


	xQueue_FIFO1 = xQueueCreate(QUEUE_LENGTH, sizeof(u8)); //connects vUartManagerTask -> vSpiMainTask
	xQueue_FIFO2 = xQueueCreate(QUEUE_LENGTH, sizeof(u8)); //connects vSpiMainTask -> vUartManagerTask


	/* Check the xQueue_FIFO1 and xQueue_FIFO2 if they were created. */
	configASSERT(xQueue_FIFO1);
	configASSERT(xQueue_FIFO2);

	//Initialization function for UART
	status = intializeUART(UART_DEVICE_ID_0);
	if (status != XST_SUCCESS) {
		xil_printf("UART Initialization Failed\r\n");
	}

	initializeSPI(SPI_0_DEVICE_ID, SPI_1_DEVICE_ID);

	vTaskStartScheduler();

	while(1);

	return 0;
}


static void vUartManagerTask( void *pvParameters ){
	u8 dummy = DOLLAR; 				// dummy char to send to the slave as a control character

	printMenu();

	while(1) {
		if(flag==1){ 						// flag is set to 1 when the user enters the end sequence on SPI1-SPI0 mode
			int loop_counter = str_length; 	// loop count for sending the dummy char
			for(int i = 0; i < loop_counter; i++){

				/*******************************************/
                // TODO 4: Implement the following sequence of operations:
                // 1. Send a "dummy" control character to FIFO1 to initiate communication.
				xQueueSendToBack(xQueue_FIFO1, &dummy, 0UL);
                // 2. Await incoming bytes from the SPIMain task via FIFO2 using xQueueReceive with portMAX_DELAY.
				xQueueReceive(xQueue_FIFO2, &task1_receive_from_FIFO2, portMAX_DELAY);
                // 3. Check if the UART transmitter (XUartPs) is ready to send data. If it's full, wait until there is space.
				while (XUartPs_IsTransmitFull(XPAR_XUARTPS_0_BASEADDR) == TRUE) {};
                // 4. Receive bytes until a null character ('\0') is received, use the UART write function
                //    to send the received byte to the UART. Refer to the XUartPs_WriteReg function with the appropriate parameters.
				XUartPs_WriteReg(XPAR_XUARTPS_0_BASEADDR, XUARTPS_FIFO_OFFSET, task1_receive_from_FIFO2);
				/*******************************************/
			}
			flag=0;
		} else {
			while (XUartPs_IsReceiveData(XPAR_XUARTPS_0_BASEADDR)){
				uart_byte = XUartPs_ReadReg(XPAR_XUARTPS_0_BASEADDR, XUARTPS_FIFO_OFFSET);

				if(uart_loopback == 1 && command_flag == 1){
					XUartPs_SendByte(XPAR_XUARTPS_0_BASEADDR, uart_byte);
					checkTerminationSequence();
				} else if(command_flag == 2){
					xQueueSendToBack(xQueue_FIFO1, &uart_byte, 0UL);

					if(spi_loopback == 1){
						xQueueReceive(xQueue_FIFO2, &task1_receive_from_FIFO2, portMAX_DELAY);
						while (XUartPs_IsTransmitFull(XPAR_XUARTPS_0_BASEADDR) == TRUE);
						XUartPs_WriteReg(XPAR_XUARTPS_0_BASEADDR, XUARTPS_FIFO_OFFSET, task1_receive_from_FIFO2);
						checkTerminationSequence();
					} else if(spi_loopback == 0){
                        /*******************************************/
                        // TODO 3: write the body for the case when "spi_master_loopback_en == 0"
                        // receive the data from FIFO2 into the variable "task1_receive_from_FIFO2_spi_data"
                        // If there is space in the UART transmitter, write the byte to the UART
						// receive data from FIFO2 into the variable "task1_receive_from_FIFO2_spi_data"
	                    /*******************************************/
						xQueueReceive(xQueue_FIFO2, &task1_receive_from_FIFO2_spi_data, portMAX_DELAY);
						while (XUartPs_IsTransmitFull(XPAR_XUARTPS_0_BASEADDR) == TRUE) {};
						XUartPs_WriteReg(XPAR_XUARTPS_0_BASEADDR, XUARTPS_FIFO_OFFSET, task1_receive_from_FIFO2_spi_data);
                    }
				}
				checkCommand();
			}
		}
	vTaskDelay(1);
	}
}


static void vSpiMainTask( void *pvParameters ){

	u8 received_from_FIFO1;
	u8 send_to_FIFO2;
	u32 received_bytes=0;
	u8 send_buffer[1];

	while(1){

		xQueueReceive( xQueue_FIFO1
					 , &received_from_FIFO1	//queue to receive the data from UART Manager task
					 , portMAX_DELAY
					 );

		if(command_flag == 2){

			if(spi_loopback == 1){
				xQueueSendToBack(xQueue_FIFO2, &received_from_FIFO1, 0UL); // byte is read from the FIFO1
			} else if (spi_loopback == 0){
                /*******************************************/
                // TODO 1: Implement the logic for handling SPI communication.
                // This process involves sending, yielding for SPI processing, reading back, and forwarding through FIFO2.
                // 1. Copy the received data from the FIFO1 into "send_buffer" variable. The "send_buffer" variable is declared for you.
				send_buffer[0] = received_from_FIFO1;
                // 2. Increment the received_bytes counter for each byte received.
				received_bytes++;
                // 3. Check if received_bytes matches TRANSFER_SIZE_IN_BYTES.
				if (received_bytes == TRANSFER_SIZE_IN_BYTES) {
                //    a. If true, transmit the collected bytes via SPI.
					spiMasterWrite(send_buffer, TRANSFER_SIZE_IN_BYTES);
                //    b. Yield the task to allow for SPI communication processing.
					taskYIELD();
					memset( (char *)&send_buffer,  0, sizeof(send_buffer) );
                //    c. Read the response back from SPI.
					spiMasterRead(TRANSFER_SIZE_IN_BYTES);
					send_to_FIFO2 = RxBuffer_Master[0];
                //    d. Send the received byte back through FIFO2.
					xQueueSendToBack(xQueue_FIFO2, &send_to_FIFO2, 0UL);
                //    e. Reset received_bytes counter to prepare for the next message.
					received_bytes = 0;
				}

                /*******************************************/
			}
		}
		vTaskDelay(1);
	}
}


static void vSpiSubTask( void *pvParameters ){
	u8 termination_flag=0;
	u8 temp_store;
	int spi_rx_bytes = 0;
	char buffer[150];
	int message_counter = 0;

	while(1){
        if(spi_loopback==0 && command_flag==2){
			/*******************************************/
			// TODO 2: Implement the logic for handling and monitoring SPI communication in this task.
			// This involves reading from SPI, monitoring for a specific sequence, and responding with a summary message.
			// 1. Detect the termination sequence (\r%\r) and set the termination_flag to 3 upon successful detection.
			// 2. Continuously track:
			//    a. The number of characters received over SPI.
			//    b. The number of complete messages received so far.
			// 3. Utilize SpiSlave read and write functions from the driver file for SPI communication.
			//    - Use "RxBuffer_Slave" for reading data from the SPI slave node.
			// 4. Store the message string "\nNumber of bytes received over SPI:%d\nTotal messages received: %d\n" in "buffer".
			// 5. Before detecting the termination sequence, ensure bytes are consistently sent back to the SPI master.
			// 6. Upon receiving the termination sequence:
			//    a. Construct the message string with the total number of bytes and messages received.
			//    b. Loop through the message string and send it back to the SPI master using the appropriate SpiSlave write function.
			/*******************************************/
        	spiSlaveRead(TRANSFER_SIZE_IN_BYTES);
        	temp_store = RxBuffer_Slave[0];
        	spi_rx_bytes = (temp_store == CHAR_CARRIAGE_RETURN || temp_store == CHAR_PERCENT || temp_store == DOLLAR) ? spi_rx_bytes : spi_rx_bytes + 1;

        	if (termination_flag == 3) {
        		message_counter++;
        		flag = 1;

        		memset( buffer, 0, sizeof(buffer) );


        		str_length = sprintf(buffer, "The number of characters received over SPI:%d\nTotal messages received: %d\n", spi_rx_bytes, message_counter);


        		for(int i = 0; i < str_length; i++) {
        			temp_store = (u8)buffer[i];
        			spiSlaveWrite(&temp_store, TRANSFER_SIZE_IN_BYTES);
        			spiSlaveRead(TRANSFER_SIZE_IN_BYTES);
        		}

        		spi_rx_bytes = 0;
        		termination_flag = 0;

        	} else {
        		if(temp_store == CHAR_CARRIAGE_RETURN && termination_flag==2){
        			termination_flag +=1;
        		} else if(temp_store == CHAR_PERCENT && termination_flag==1){
        			termination_flag +=1;
        		} else if(temp_store == CHAR_CARRIAGE_RETURN && termination_flag==0) {
        			termination_flag +=1;
        		} else {
        			termination_flag=0;
        		}
        		spiSlaveWrite(&temp_store, TRANSFER_SIZE_IN_BYTES);
        	}
        	vTaskDelay(1);
        }

	}
}

///////////////////////////////////////////////////////////////////////////
// FUNCTION DEFINITIONS
///////////////////////////////////////////////////////////////////////////

/**
 * This functions checks if the user input is the termination sequence \r%\r
 * When the termination sequence is detected, sequence_flag would be 3
 * Returns: None
 */
void checkTerminationSequence(void){

	if(uart_byte == CHAR_CARRIAGE_RETURN && sequence_flag==2){
		sequence_flag += 1;
	}
	else if(uart_byte == CHAR_PERCENT && sequence_flag==1){
		sequence_flag += 1;
	} else if(uart_byte == CHAR_CARRIAGE_RETURN && sequence_flag==0){
		sequence_flag += 1;
	} else {
		sequence_flag = 0;
	}

	if (sequence_flag == 3){
		command_flag = 1;
		sequence_flag = 0;
		spi_loopback = 0;
		uart_loopback = 0;
		xil_printf("\n*** Text entry ended using termination sequence ***\r\n");
	}
}

/**
 * This functions checks if the user input is a valid command or not. A valid command would be ENTER <COMMAND> ENTER.
 * <COMMAND> can only be 1 or 2
 * For a valid command, the command_flag would be 1 or 2
 * Returns: None
 */
void checkCommand(void)
{
	rollingBuffer[0] = rollingBuffer[1];
	rollingBuffer[1] = rollingBuffer[2];
	rollingBuffer[2] = uart_byte;

	if (rollingBuffer[2] == CHAR_CARRIAGE_RETURN && rollingBuffer[0] == rollingBuffer[2]) {
		if (rollingBuffer[1] == '1') {
			uart_loopback = !uart_loopback;
			command_flag = 1;
			if(uart_loopback==1){
				xil_printf("\n*** UART Loop-back ON ***\r\n");
			} else {
				xil_printf("\n*** UART Loop-back OFF ***\r\n");
			}
		} else if (rollingBuffer[1] == '2') {
			command_flag = 2;
			spi_loopback = !spi_loopback;
			if(spi_loopback==1){
				xil_printf("\n*** SPI Loop-back ON ***\r\n");
			} else {
				xil_printf("\n*** SPI Loop-back OFF ***\r\n");
			}
		}
	}
}
