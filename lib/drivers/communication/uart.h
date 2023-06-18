#pragma once
#include <avr/io.h>

#define F_CPU 16000000UL
#define BAUDRATE 115200
#define BAUD_PRESCALE ((F_CPU/(BAUDRATE*16UL))-1)

void Uart_init();
void Uart_send(unsigned char data);
void Uart_sendString(char* string);
