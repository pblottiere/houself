#ifndef LIB_ESP8266
#define LIB_ESP8266

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <stdint.h>
#include <SoftwareSerial/SoftwareSerial.h>
#include <Arduino.h>

//------------------------------------------------------------------------------
// enum, const
//------------------------------------------------------------------------------
enum LIB_ESP8266_ERROR
{
    LIB_ESP8266_ERROR_UNKNOWN,
    LIB_ESP8266_ERROR_NO_ERROR,
    LIB_ESP8266_ERROR_OFFLINE,
    LIB_ESP8266_ERROR_NOIP,
    LIB_ESP8266_ERROR_TIMEOUT
};

//------------------------------------------------------------------------------
// Class LibESP8266
//------------------------------------------------------------------------------
namespace libesp8266
{
    class ESP8266
    {
        public:
            ESP8266();

            LIB_ESP8266_ERROR connect(const String &essid, const String &pass);
            void set_dbg_serial(SoftwareSerial &serial);
            LIB_ESP8266_ERROR send_tcp_msg(const String &ip, int32_t port,
                    const String &msg);

        private:
            // methods
            void log(const String &str);
            void open_serial_port();
            LIB_ESP8266_ERROR check_esp8266_online();
            LIB_ESP8266_ERROR get_ip(const String &essid, const String &pass);

            // attr
            SoftwareSerial *_dbg_serial;
            int32_t _retry;
            int32_t _speed;
    };
}

#endif
