#include "uart.h"

#include <string.h>

#define BAUD_RATE 115200
#define BAUD_PRESCALE ((F_CPU / (BAUD_RATE * 16UL)) - 1)

void Uart_init()
{
    // Set baud rate
    UBRR0H = (BAUD_PRESCALE >> 8);
    UBRR0L = BAUD_PRESCALE;

    // Enable transmitter and receiver
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Set frame format: 8 data bits, 1 stop bit, no parity
    UCSR0C = (0 << USBS0) | (3 << UCSZ00);
}

void Uart_send(unsigned char data)
{
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));

    // Put data into buffer, sends the data
    UDR0 = data;
}

void Uart_sendString(char* string)
{
    size_t string_size = strlen(string);
    for (size_t i = 0; i < string_size; ++i)
        Uart_send(string[i]);
}