# Zynq-7000-SPI-Interface

## Overview
This project focuses on implementing the Serial Peripheral Interface (SPI) on the Digilent Zybo Z7 development board. It includes exercises related to SPI loopback implementation and interfacing with the Xilinx/AMD Pmod OLED screen to explore embedded graphics programming concepts.

## Learning Objectives
* Gain practical experience with SPI in controller (master) and peripheral (slave) modes.
* Interface with an SPI device, specifically the Pmod OLED screen, to understand embedded graphics programming.
* Implement SPI loopback for data transfer testing.
* Develop applications utilizing the SPI protocol for graphical output on the OLED screen.

## Hardware Requirements
* Digilent Zybo Z7 development board.
* Xilinx/AMD Pmod OLED (revision A) module for graphical output.
* Input peripherals for user interaction (e.g., keyboard, buttons).
* Output peripherals for system feedback (e.g., terminal window, OLED display).

## Software Requirements
* Xilinx Vivado for hardware configuration.
* Xilinx SDK for software development.
* FreeRTOS library for real-time task management.
* Pmod OLED library for SPI interface.
* SPI loopback and OLED graphics source files.

## Project Structure
### Part 1: Implementing SPI Loopback
* Configure SPI loopback in both controller (master) and peripheral (slave) modes.
* Utilize FreeRTOS tasks for SPI communication and loopback testing.
* Explore the SPI block design in Vivado and analyze the connections between SPI interfaces.

### Part 2: SPI OLED Screen Interface
* Interface with the Pmod OLED screen using SPI for graphical output.
* Utilize optimized functions for drawing lines and shapes on the OLED display.
* Develop a custom application or game using input peripherals and OLED display interaction.

## How to Run
* Clone the repository to your local machine.
* Open the project in Xilinx Vivado and SDK.
* Configure the hardware design for Zybo Z7 and generate the bitstream.
* Create a new FreeRTOS application project in SDK.
* Include the provided source files for each part of the lab.
* Compile and build the project.
* Upload the generated executable to the Zybo Z7 board.
* Connect input peripherals (e.g., keyboard, buttons) to interact with the system.
* Connect the Pmod OLED screen to the SPI interface for graphical output.
* Power on the board and follow the on-screen instructions to test SPI loopback and OLED graphics features.
