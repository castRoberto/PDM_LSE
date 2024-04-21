# Temperature monitor application

This repository contains the source code of the temperature monitoring system, as a final practical work of the subjects "Microprocessor programming and communication protocols in embedded systems" of Specialization in embedded systems of the University of Buenos Aires.

[Demonstrative video](https://drive.google.com/file/d/1u7hXUIPquvdns73nV46hEVtTN0BkfMgu/view?usp=sharing)

## Author

Roberto Enrique Castro Beltran

## Description

This project consists of a layered system of collecting temperature data and displaying it on a graphic screen. The block diagram in Figure 1 shows the different components that make it up.

<img src="https://raw.githubusercontent.com/castRoberto/PDM_LSE/main/TempMonitorApp/doc/BlockDiagram.png">
Figure 1: Block Diagram of system.

### Peripherals
|Peripheral|Description|
|----------|---------|
|UART| Communication with nextion module|
|SPI| Communication with temperature module|
|GPIO| System start/stop button and indication LEDs|

As can be seen, the system has two inputs, a button that starts and stops the execution of the application at any time and a MAX6675 module that indicates the instantaneous temperature and the connection status of the transducer, which for this specific case is a thermocouple. type k.

As for the system outputs, it has a 3.2-inch NEXTION screen that communicates via UART protocol and three LEDs used to indicate system activity, the connection status of the thermocouple and a temperature alert when a predefined threshold is exceeded.

The business logic of this system is governed by the main finite state machine shown in Figure 2.

<img src="https://raw.githubusercontent.com/castRoberto/PDM_LSE/main/TempMonitorApp/doc/FiniteStatesMachine.png">
Figure 2: Main Finite State Machine of system.

## Software Architecture

The project was structured following a layered architecture. From the main system, only the functions to initialize the state machine and update it are called. Then, within the application layer there is all the business logic of the system, all that logic that must be coupled with the hardware, the ddt (data definition types) layer contains the data definitions common to all the software layers. , the libs layer contains all the libraries used by the different layers, the bsp (board support package) layer contains all the logic to interact with the hardware, different managers are implemented here, one for each peripheral, some of which require of a specific driver to function, for example, for the temperature module and the screen, both require certain logic that escapes the bsp, that is why the driver layer is used, all the functions to interact with it are implemented in it. external modules other than those already provided by the MCU. Finally, there is the hal layer (Hardware abstraction layer), this is provided by the chip manufacturer and contains all the low-level logic to interact with the chip. Figure 3 shows the layer relationships in detail

<img src="https://raw.githubusercontent.com/castRoberto/PDM_LSE/main/TempMonitorApp/doc/SoftwareArchitecture.png">
Figure 3: Software architecture

## Communication protocols

To demonstrate the correct operation of the communication protocols, figures 4 and 5 are added, which contain the activity diagrams on the SPI and UART ports respectively.

<img src="https://raw.githubusercontent.com/castRoberto/PDM_LSE/main/TempMonitorApp/doc/SPI.png">
Figura 4: SPI communication of the temperature module.

<img src="https://raw.githubusercontent.com/castRoberto/PDM_LSE/main/TempMonitorApp/doc/UART.png">
Figura 5: UART communication of nextion display.
