#include "wifi.h"

#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "uart.h"

/* Select Demo */
#define RECEIVE_DEMO        /* Define RECEIVE demo */
//#define SEND_DEMO			/* Define SEND demo */

int8_t Response_Status;
volatile int8_t Counter = 0,
                pointer = 0;
uint32_t TimeOut = 0;
char RESPONSE_BUFFER[DEFAULT_BUFFER_SIZE];

void _readResponse(char *_Expected_Response) {
    uint8_t EXPECTED_RESPONSE_LENGTH = strlen(_Expected_Response);
    uint32_t TimeCount = 0;
    uint8_t ResponseBufferLength;
    char RECEIVED_CRLF_BUF[EXPECTED_RESPONSE_LENGTH];

    while (1) {
        if (TimeCount >= (DEFAULT_TIMEOUT + TimeOut)) {
            TimeOut = 0;
            Response_Status = Esp8266_RESPONSE_TIMEOUT;
            return;
        }

        if (Response_Status == Esp8266_RESPONSE_STARTING)
            Response_Status = Esp8266_RESPONSE_WAITING;

        ResponseBufferLength = strlen(RESPONSE_BUFFER);
        if (ResponseBufferLength) {
            _delay_ms(1);
            ++TimeCount;
            if (ResponseBufferLength == strlen(RESPONSE_BUFFER)) {
                for (uint8_t i = 0; i < ResponseBufferLength; ++i) {
                    memmove(RECEIVED_CRLF_BUF, RECEIVED_CRLF_BUF + 1, EXPECTED_RESPONSE_LENGTH - 1);
                    RECEIVED_CRLF_BUF[EXPECTED_RESPONSE_LENGTH - 1] = RESPONSE_BUFFER[i];
                    if (!strncmp(RECEIVED_CRLF_BUF, _Expected_Response, EXPECTED_RESPONSE_LENGTH)) {
                        TimeOut = 0;
                        Response_Status = Esp8266_RESPONSE_FINISHED;
                        return;
                    }
                }
            }
        }
        _delay_ms(1);
        ++TimeCount;
    }
}

void Esp8266_clear() {
    memset(RESPONSE_BUFFER, 0, DEFAULT_BUFFER_SIZE);
    Counter = 0;
    pointer = 0;
}

void _startReadResponse(char *_ExpectedResponse) {
    Response_Status = Esp8266_RESPONSE_STARTING;
    do
        _readResponse(_ExpectedResponse);
    while (Response_Status == Esp8266_RESPONSE_WAITING);
}

void _getResponseBody(char *Response, uint16_t ResponseLength) {
    uint16_t i = 12;
    char buffer[5];
    while (Response[i] != '\r')
        ++i;

    strncpy(buffer, Response + 12, (i - 12));
    ResponseLength = atoi(buffer);

    i += 2;
    uint16_t tmp = strlen(Response) - i;
    memcpy(Response, Response + i, tmp);

    if (!strncmp(Response + tmp - 6, "\r\nOK\r\n", 6))
        memset(Response + tmp - 6, 0, i + 6);
}

boolean _waitForExpectedResponse(char *ExpectedResponse) {
    _startReadResponse(ExpectedResponse);    /* First read response */
    return Response_Status != Esp8266_RESPONSE_TIMEOUT;
}

boolean _sendAtCommandAndExpectResponse(char *ATCommand, char *ExpectedResponse) {
    Esp8266_clear();
    Uart_sendString(ATCommand);        /* Send AT command to Esp8266 */
    Uart_sendString("\r\n");
    return _waitForExpectedResponse(ExpectedResponse);
}

boolean Esp8266_applicationMode(uint8_t Mode) {
    char _atCommand[14];
    memset(_atCommand, 0, 14);
    sprintf(_atCommand, "AT+CIPMODE=%d", Mode);
    _atCommand[13] = 0;
    return _sendAtCommandAndExpectResponse(_atCommand, "\r\nOK\r\n");
}

boolean Esp8266_connectionMode(uint8_t Mode) {
    char _atCommand[13];
    memset(_atCommand, 0, 13);
    sprintf(_atCommand, "AT+CIPMUX=%d", Mode);
    _atCommand[12] = 0;
    return _sendAtCommandAndExpectResponse(_atCommand, "\r\nOK\r\n");
}

boolean Esp8266_begin() {
    for (uint8_t i = 0; i < 5; ++i)
        if (_sendAtCommandAndExpectResponse("ATE0", "\r\nOK\r\n") ||
            _sendAtCommandAndExpectResponse("AT", "\r\nOK\r\n"))
            return True;
    return False;
}

boolean Esp8266_close() {
    return _sendAtCommandAndExpectResponse("AT+CIPCLOSE=1", "\r\nOK\r\n");
}

boolean Esp8266_wifiMode(uint8_t _mode) {
    char _atCommand[13];
    memset(_atCommand, 0, 13);
    sprintf(_atCommand, "AT+CWMODE=%d", _mode);
    _atCommand[12] = 0;
    return _sendAtCommandAndExpectResponse(_atCommand, "\r\nOK\r\n");
}

boolean Esp8266_createAccessPoint(char *_SSID, char *_PASSWORD) {
    char _atCommand[60];
    memset(_atCommand, 0, 60);
    sprintf(_atCommand, "AT+CWSAP=\"%s\",\"%s\",0,3,1", _SSID, _PASSWORD);
    _atCommand[59] = 0;
    return _sendAtCommandAndExpectResponse(_atCommand, "\r\nOK\r\n");
}

uint8_t Esp8266_connected() {
    _sendAtCommandAndExpectResponse("AT+CIPSTATUS", "\r\nOK\r\n");
    return (strstr(RESPONSE_BUFFER, "STATUS:2")) ?
           Esp8266_CONNECTED_TO_AP :
           (strstr(RESPONSE_BUFFER, "STATUS:3")) ?
           Esp8266_CREATED_TRANSMISSION :
           (strstr(RESPONSE_BUFFER, "STATUS:4")) ?
           Esp8266_TRANSMISSION_DISCONNECTED :
           (strstr(RESPONSE_BUFFER, "STATUS:5")) ?
           Esp8266_NOT_CONNECTED_TO_AP :
           Esp8266_CONNECT_UNKNOWN_ERROR;
}

uint8_t Esp8266_send(char *data) {
    char _atCommand[16];
    memset(_atCommand, 0, 16);
    sprintf(_atCommand, "AT+CIPSEND=%d", (strlen(data) + 2));
    _atCommand[15] = 0;
    _sendAtCommandAndExpectResponse(_atCommand, "\r\nOK\r\n>");
    return (_sendAtCommandAndExpectResponse(data, "\r\nSEND OK\r\n")) ?
           Esp8266_RESPONSE_FINISHED :
           ((Response_Status == Esp8266_RESPONSE_TIMEOUT) ?
            Esp8266_RESPONSE_TIMEOUT :
            Esp8266_RESPONSE_ERROR);
}

int16_t Esp8266_dataAvailable() {
    return Counter - pointer;
}

uint8_t Esp8266_readByteData() {
    return (pointer < Counter) ?
           RESPONSE_BUFFER[pointer++] :
           (Esp8266_clear(), 0);
}

uint8_t _sensitive_data_equality_pointer = 0;
uint8_t Esp8266_readData(char *_buffer) {
    _sensitive_data_equality_pointer = 0;
    uint8_t len = 0;
    _delay_ms(100);
    while (Esp8266_dataAvailable() > 0)
        _buffer[len++] = Esp8266_readByteData();
    return len;
}

ISR (USART_RX_vect) {
    if (_sensitive_data_equality_pointer != SENSITIVE_DATA_LENGTH) {
        uint8_t oldsrg = SREG;
        cli();
        RESPONSE_BUFFER[Counter++] = UDR0;
        if (URD0 == SENSITIVE_DATA[_sensitive_data_equality_pointer])
            ++_sensitive_data_equality_pointer;
        else
            _sensitive_data_equality_pointer = 0;
        if (Counter == DEFAULT_BUFFER_SIZE)
            Counter = pointer = 0;
        SREG = oldsrg;
    }
}
//
//int main(void) {
//    char _buffer[150];
//    uint8_t Connect_Status;
//#ifdef SEND_DEMO
//    uint8_t Sample = 0;
//#endif
//
//    Uart_init();
//    sei();
//
//    while (!Esp8266_begin());
//    Esp8266_wifiMode(BOTH_STATION_AND_ACCESS_POINT);/* 3 = Both (AP and STA) */
//    Esp8266_connectionMode(SINGLE);        /* 0 = Single; 1 = Multi */
//    Esp8266_applicationMode(NORMAL);    /* 0 = Normal Mode; 1 = Transperant Mode */
//    if (Esp8266_connected() == Esp8266_NOT_CONNECTED_TO_AP)
//        Esp8266_joinAccessPoint(SSID, PASSWORD);
//    while (1) {
//        Connect_Status = Esp8266_connected();
//        if (Connect_Status == Esp8266_NOT_CONNECTED_TO_AP)
//            Esp8266_joinAccessPoint(SSID, PASSWORD);
//
//#ifdef SEND_DEMO
//        memset(_buffer, 0, 150);
//        sprintf(_buffer, "GET /update?api_key=%s&field1=%d", API_WRITE_KEY, Sample++);
//        Esp8266_send(_buffer);
//        _delay_ms(15000);	/* Thingspeak server delay */
//#endif
//
//#ifdef RECEIVE_DEMO
//        memset(_buffer, 0, 150);
//        sprintf(_buffer, "GET /channels/%s/feeds/last.txt", CHANNEL_ID);
//        Esp8266_send(_buffer);
//        _readData(_buffer);
//        _delay_ms(600);
//#endif
//    }
//}