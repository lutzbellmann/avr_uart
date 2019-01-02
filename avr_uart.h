/*
 * avr_uart.h - Library for controlling the UART / USART on ATMEL AVRs
 * Original library	(0.1) 	by Dr. Lutz Bellmann
 *
 * Design the circuitery so that the RX Pin is used to receive data and TX for sending data
 * The AVR UART is compatible to the ESP8266 Serial interface
 * This library supports asynchronous data transfer (2-wire). Synchronous is seldomely used. 
 * Expand the library if you need.
 * You MUST define F_CPU properly 
*/

#ifndef avr_uart_h
#define avr_uart_h

// library interface description

class uart
{

public:
// constructor
	uart(uint16_t baud);
	uart(uint16_t baud, unsigned char framesize);
	uart(uint16_t baud, unsigned char framesize, unsigned char parity, unsigned char stopbits);

//	(*TODO: 9 bits not supported yet*)
//	(*TODO* synchronous datatransfer not supported yet)

	void rxenable(); // enable receive unit

	void txenable(); // enable transmitting unit

	unsigned char flushbuffer(); //returns 0 if flush ok, otherwise 1

	unsigned char getbyte(); // receive a byte

	void sendbyte(unsigned char byte); // send a byte

private:
	unsigned char dummy; // dummy for flushing read buffer

};

#endif



