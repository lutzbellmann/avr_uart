/*
 * avr_uart.h - Library for controlling the UART / USART on ATMEL AVRs
 * Original library	(0.1) 	by Dr. Lutz Bellmann
 *
 * Design the circuitery so that the RX Pin is used to receive data and TX for sending data
 * The AVR UART is compatible to the ESP8266 Serial interface
 * This library supports asynchronous data transfer (2-wire). Synchronous is seldomely used. 
 * Expand the library if you need.
*/

#include "Arduino.h"
#include <avr/io.h>
#include "avr_uart.h"

uart::uart(uint16_t baud)
{
	#define UART_UBRR_CALC(BAUD_,FREQ_) ((FREQ_)/((BAUD_)*8L)-1)  //UBRR calculation makro with doublespeed according datasheet
	UCSRA |= (1<<U2X); // double speed cannot be bad
	UBRRH = (uint8_t)(UART_UBRR_CALC(baud,F_CPU))>>8;
	UBRRL = (uint8_t)(UART_UBRR_CALC(baud,F_CPU));
	UCSRC |= ((1<<UCSZ1)|(1<<UCSZ0)); // standard 8Bit frame
}

uart::uart(uint16_t baud, unsigned char framesize)
{
	#define UART_UBRR_CALC(BAUD_,FREQ_) ((FREQ_)/((BAUD_)*8L)-1)
        UCSRA |= (1<<U2X); // double speed cannot be bad
        UBRRH = (uint8_t)(UART_UBRR_CALC(baud,F_CPU))>>8;
        UBRRL = (uint8_t)(UART_UBRR_CALC(baud,F_CPU));
	switch(framesize)						// set respective bits for framesize (if 'framesize' is != 5-8 it is considered 5)
	{
		case(6): UCSRC |= (1<<UCSZ0); break;
		case(7): UCSRC |= (1<<UCSZ1); break;
		case(8): UCSRC |= ((1<<UCSZ1)|(1<<UCSZ0)); break;
		default: break;
	}
}

uart::uart(uint16_t baud, unsigned char framesize, unsigned char parity, unsigned char stopbits)
{
        #define UART_UBRR_CALC(BAUD_,FREQ_) ((FREQ_)/((BAUD_)*8L)-1)
        UCSRA |= (1<<U2X); // double speed cannot be bad
        UBRRH = (uint8_t)(UART_UBRR_CALC(baud,F_CPU))>>8;
        UBRRL = (uint8_t)(UART_UBRR_CALC(baud,F_CPU));
        switch(framesize)
        {
                case(6): UCSRC |= (1<<UCSZ0); break;
                case(7): UCSRC |= (1<<UCSZ1); break;
                case(8): UCSRC |= ((1<<UCSZ1)|(1<<UCSZ0)); break;
                default: break;
        }
	switch(parity)							// set parity check for received bytes; if 'parity' is neither 1nor2, it is considered no parity check 
	{
		case(1): UCSRC |= (1<<UPM0); break;			// even parity
		case(2): UCSRC |= ((1<<UPM0)|(1<<UPM1)); break;		// odd parity
		default: break;
	}
	switch(stopbits)						// set no of stopbits; 'stopbits' other than 2 default to 1
	{
		case(2): UCSRC |= (1<<USBS); break;
		default: break;
	}
}

//	(*TODO: 9 bits not supported yet*)
//	(*TODO* synchronous datatransfer not supported yet)
//      (*TODO* error handling to be included)
//	(*TODO* interrupt handling to be included, to avoid hanging in RX loop)

void uart::rxenable() // enable receive unit
{
	UCSRB |= (1<<RXEN);
}

void uart::txenable() // enable transmitting unit
{
	UCSRB |= (1<<TXEN);
}

unsigned char uart::flushbuffer() //returns 0 if flush ok, otherwise 1
{
	while (UCSRA & (1<<RXC))
	{
		dummy = UDR;  // reads until there is nothing more in the buffer
	}
}

unsigned char uart::getbyte() // receive a byte; TODO: probably interrupt handling is a much better solution
{
	while (!(UCSRA & (1<RXC))); // waits for data to appear in the buffer
	return UDR;
}

void uart::sendbyte(unsigned char byte) // send a byte
{
	while (!(1<<UCSRA) & (1<<UDRE));
	UDR = byte;
}
