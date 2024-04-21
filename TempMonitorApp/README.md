# Temperature monitor application

This repository contains the source code of the temperature monitoring system, as a final practical work of the subjects "Microprocessor programming and communication protocols in embedded systems" of Specialization in embedded systems of the University of Buenos Aires.

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
Figure 2: Main Finite State Machine of system


