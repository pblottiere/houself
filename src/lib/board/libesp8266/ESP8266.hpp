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
enum LIB_ESP8266_SPEED
{
    LIB_ESP8266_SPEED_9600 = 9600,
    LIB_ESP8266_SPEED_115200 = 115200
};

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
            ESP8266(const LIB_ESP8266_SPEED speed = LIB_ESP8266_SPEED_9600,
                    const unsigned int retry = 10);

            LIB_ESP8266_ERROR connect(const String &essid, const String &pass);
            LIB_ESP8266_ERROR send_http_request(const String &ip, int32_t port,
                                                const String &msg);
            void reset();

            void set_dbg_serial(SoftwareSerial &serial);
            void unset_dbg_serial();

        private:
            // methods
            void log(const String &str, const bool ln = false);
            void log_status(const LIB_ESP8266_ERROR err);

            bool write(const String &str, const unsigned int delay_sec = 3000,
                       const String &ack = "OK");

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
