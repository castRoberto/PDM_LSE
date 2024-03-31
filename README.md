# Author
Roberto Enrique Castro Beltran

# [PDM] Practice 2, Non-blocking delays.

## Description

In this practice, functions are implemented to manage non-blocking delays, as well as an example managing multiple LEDs with different oscillation periods.


# [PDM] Practice 3, Modularization

Practice related to the modularization of functions that control non-blocking delays.

## Description

A package called API is created that contains the header and implementation files for the API_delay module. Calls are redirected to this new module. The concept of encapsulation is also used by limiting the scope with the static modifier of a new function called isTimeOut.


# [PDM] Practice 4.1, Software debounce

Practice related to the implementation of a finite state machine to control bounces due to the mechanics of a push button.

## Descriptio

The functions debounceFsmInit, debounceFsmUpdate, buttonPressed, buttonReleased are created to control the states of the FSM and its corresponding output, for this the machine is modeled with four possible states (BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RAISING)


# [PDM] Practice 4.2, Software debounce modularization

Practice related to the implementation of a modularized finite state machine to control bounces due to the mechanics of a push button.

## Description

The functions debounceFsmInit, debounceFsmUpdate, buttonPressed, buttonReleased are created to control the states of the FSM and its corresponding output, for this the machine is modeled with four possible states (BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RAISING)

This implementation is added as modules with header and implementation files


# [PDM] Practice 5, UART module

Practice related to the implementation of a module that wraps the main functions of the STMicroelectronics HAL for the management of the UART module by polling method.

## Description

The initialization, reception and sending of information functions are encapsulated through the UART bus of the NUCLEO board
