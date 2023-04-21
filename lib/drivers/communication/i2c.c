#include "i2c.h"


void I2c_init() 
{
    PORTC |= 0b01100000;
    TWSR = 0x00;                                             /* Set prescaler to 1 */
    TWBR = (((F_CPU / SCL_FREQ) - 16) >> 1);                 /* Set bit rate */
    TWCR = (1 << TWEN);                                      /* Enable I2C */
}

void I2c_start() 
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);        /* Send start condition */
    while (!(TWCR & (1 << TWINT)));                          /* Wait for start condition to be sent */
}

void I2c_write(uint8_t data) 
{
    TWDR = data;                                             /* Load data into data register */
    TWCR = (1 << TWINT) | (1 << TWEN);                       /* Send data */
    while (!(TWCR & (1 << TWINT)));                          /* Wait for data to be sent */
}

uint8_t I2c_read(uint8_t ack_value) 
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (ack_value << TWEA); /* Enable I2C and ACK */
    while (!(TWCR & (1 << TWINT)));                          /* Wait for data to be received */
    return TWDR;                                             /* Return received data */
}

void I2c_stop() 
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);        /* Send stop condition */
    while ((TWCR & (1 << TWSTO)));                           /* Wait for stop condition to be sent */
}