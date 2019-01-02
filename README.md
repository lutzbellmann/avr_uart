# avr_uart
Library for simple but configurable UART usage with Atmels AVR, primarily under Arduino IDE

# installation
Create a directory named avr_uart in /libraries directory of your sketch directory in Arduino IDE and clone all files to this directory. Restart Arduino IDE. Under Sketch, you should be able to include the avr_uart library.

# usage
I may, or may not include an example later.
In your Sketch, use:
uart MYUART(<baudrate>[, <framesize][, <parity>, <stopbits>];
  to declare the constructor.
Refer to avr_uart.h for possible commands.
  
# restrictions
The Library is currently only tested with the Attiny 4313, but should work with all Atmel AVR with ONE UART (f.e. Atmega 8).
For testing I used the ATTinyCore 1.2.2 from Spence Konde.

# future work
too much to mention, just a start
