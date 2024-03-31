# [PDM] Practice 4.2, Software debounce modularization

Practice related to the implementation of a modularized finite state machine to control bounces due to the mechanics of a push button.

## Author
Roberto Enrique Castro Beltran

## Description

The functions debounceFsmInit, debounceFsmUpdate, buttonPressed, buttonReleased are created to control the states of the FSM and its corresponding output, for this the machine is modeled with four possible states (BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RAISING)

This implementation is added as modules with header and implementation files
