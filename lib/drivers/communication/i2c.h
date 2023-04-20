#pragma once

#define SCL_FREQ 100000UL


void I2c_init();
void I2c_start();
void I2c_write(uint8_t data);
uint8_t I2c_read(uint8_t ack_value);
void I2c_stop();