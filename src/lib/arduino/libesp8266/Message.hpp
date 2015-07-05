#ifndef LIB_ESP8266_MESSAGE
#define LIB_ESP8266_MESSAGE

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <Arduino.h>

//------------------------------------------------------------------------------
// enum, const
//------------------------------------------------------------------------------
enum LIB_ESP8266_MODE
{
    LIB_ESP8266_MODE_UDP,
    LIB_ESP8266_MODE_TCP
};

enum LIB_ESP8266_WIFI_MODE
{
    LIB_ESP8266_WIFI_MODE_STA = 1,
    LIB_ESP8266_WIFI_MODE_AP = 2,
    LIB_ESP8266_WIFI_MODE_BOTH = 3
};

enum LIB_ESP8266_CONNECTION_MODE
{
    LIB_ESP8266_CONNECTION_MODE_SINGLE = 0,
    LIB_ESP8266_CONNECTION_MODE_MULTIPLE = 1
};

//==============================================================================
//
// Classes
//
//==============================================================================
namespace libesp8266
{
    //--------------------------------------------------------------------------
    // Message
    //--------------------------------------------------------------------------
    class Message
    {
        public:
            Message() : _message("") {};
            virtual ~Message() {};

            String get() { return this->_message; };

        protected:
            String _message;
    };

    //--------------------------------------------------------------------------
    // MessageTest
    //--------------------------------------------------------------------------
    class MessageTest : public Message
    {
        public:
            MessageTest() { this->_message = "AT"; };
    };

    //--------------------------------------------------------------------------
    // MessageReset
    //--------------------------------------------------------------------------
    class MessageReset : public Message
    {
        public:
            MessageReset() { this->_message = "AT+RST"; };
    };

    //--------------------------------------------------------------------------
    // MessageOpenLink
    //--------------------------------------------------------------------------
    class MessageOpenLink : public Message
    {
        public:
            MessageOpenLink(LIB_ESP8266_MODE mode, String ip, int port)
            {
                _message = "AT+CIPSTART=";

                if (mode == LIB_ESP8266_MODE_TCP)
                   _message += "\"TCP\"";
                 else
                   _message += "\"UDP\"";

                 _message += ",\"" + ip + "\"," + port;
            };
    };

    //--------------------------------------------------------------------------
    // MessageSendData
    //--------------------------------------------------------------------------
    class MessageSendData : public Message
    {
        public:
            MessageSendData(String msg)
            {
                this->_part1 = "AT+CIPSEND=" + String(msg.length());
                this->_part2 = msg;
                this->_message = this->_part1 + this->_part2;
            };

            String get_part1() { return this->_part1; };

            String get_part2() { return this->_part2; };

        public:
            String _part1;
            String _part2;
    };

    //--------------------------------------------------------------------------
    // MessageCloseConnection
    //--------------------------------------------------------------------------
    class MessageCloseConnection : public Message
    {
        public:
            MessageCloseConnection() { this->_message = "AT+CIPCLOSE"; };
    };

    //--------------------------------------------------------------------------
    // MessageJoinAP
    //--------------------------------------------------------------------------
    class MessageJoinAP : public Message
    {
        public:
            MessageJoinAP(String essid, String password)
            {
                this->_message = "AT+CWJAP=\"" + essid + "\",\"" + password + "\"";
            };
    };

    //--------------------------------------------------------------------------
    // MessageWifiMode
    //--------------------------------------------------------------------------
    class MessageWifiMode : public Message
    {
        public:
            MessageWifiMode(LIB_ESP8266_WIFI_MODE mode)
            {
                this->_message = "AT+CWMODE=" + mode;
            };
    };

    //--------------------------------------------------------------------------
    // MessageConnectionMode
    //--------------------------------------------------------------------------
    class MessageConnectionMode : public Message
    {
        public:
            MessageConnectionMode(LIB_ESP8266_CONNECTION_MODE mode)
            {
                this->_message = "AT+CIPMUX=" + mode;
            };
    };

    //--------------------------------------------------------------------------
    // MessageGetIP
    //--------------------------------------------------------------------------
    class MessageGetIP : public Message
    {
        public:
            MessageGetIP() { this->_message = "AT+CIFSR"; };
    };
}

#endif
