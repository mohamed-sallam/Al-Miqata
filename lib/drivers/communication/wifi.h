// /* In the name of Allah, the Most Gracious, the Most Merciful */

// /* Source: http://www.electronicwings.com */

// #include <avr/io.h>

// #include "../../../inc/types.h"

// #define DEFAULT_BUFFER_SIZE        200
// #define DEFAULT_TIMEOUT            10000

// /* Connection Mode */
// #define SINGLE              0
// #define MULTIPLE            1

// /* Application Mode */
// #define NORMAL              0
// #define TRANSPERANT         1

// /* Application Mode */
// #define STATION                          1
// #define ACCESS_POINT                     2
// #define BOTH_STATION_AND_ACCESS_POINT    3

// /* Define Required fields shown below */
// #define SSID                "AlMiqata"
// #define PASSWORD            "12root34"

// const char* SENSITIVE_DATA =  "[e]";
// const uint8_t SENSITIVE_DATA_LENGTH = strlen(SENSITIVE_DATA);

// enum Esp8266_RESPONSE_STATUS {
//     Esp8266_RESPONSE_WAITING,
//     Esp8266_RESPONSE_FINISHED,
//     Esp8266_RESPONSE_TIMEOUT,
//     Esp8266_RESPONSE_BUFFER_FULL,
//     Esp8266_RESPONSE_STARTING,
//     Esp8266_RESPONSE_ERROR
// };

// enum Esp8266_CONNECT_STATUS {
//     Esp8266_CONNECTED_TO_AP,
//     Esp8266_CREATED_TRANSMISSION,
//     Esp8266_TRANSMISSION_DISCONNECTED,
//     Esp8266_NOT_CONNECTED_TO_AP,
//     Esp8266_CONNECT_UNKNOWN_ERROR
// };

// enum Esp8266_JOIN_AP_STATUS {
//     Esp8266_WIFI_CONNECTED,
//     Esp8266_CONNECTION_TIMEOUT,
//     Esp8266_WRONG_PASSWORD,
//     Esp8266_NOT_FOUND_TARGET_AP,
//     Esp8266_CONNECTION_FAILED,
//     Esp8266_JOIN_UNKNOWN_ERROR
// };

// void Esp8266_clear();
// boolean Esp8266_applicationMode(uint8_t Mode);
// boolean Esp8266_connectionMode(uint8_t Mode);
// boolean Esp8266_begin();
// boolean Esp8266_close();
// boolean Esp8266_wifiMode(uint8_t _mode);
// boolean Esp8266_createAccessPoint(char *_SSID, char *_PASSWORD);
// uint8_t Esp8266_connected();
// uint8_t Esp8266_send(char *data);
// int16_t Esp8266_dataAvailable();
// uint8_t Esp8266_readByteData();
// uint8_t Esp8266_readData(char *_buffer);