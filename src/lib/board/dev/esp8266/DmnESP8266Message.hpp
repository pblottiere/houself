/**
 * @file DmnESP8266Message.hpp
 * @author Paul Blottiere
 * @date 30/06/2016
 */

#pragma once

#include <dominus/board/core/DmnCore.hpp>

// ----------------------------------------------------------------------------
// enum, const
// ----------------------------------------------------------------------------
enum ESP8266_FIRMWARE
{
  ESP8266_FIRMWARE_1,
  ESP8266_FIRMWARE_2
};

enum ESP8266_MODE
{
  ESP8266_MODE_UDP,
  ESP8266_MODE_TCP
};

enum ESP8266_WIFI_MODE
{
  ESP8266_WIFI_MODE_STA = 1,
  ESP8266_WIFI_MODE_AP = 2,
  ESP8266_WIFI_MODE_BOTH = 3
};

enum ESP8266_CONNECTION_MODE
{
  ESP8266_CONNECTION_MODE_SINGLE = 0,
  ESP8266_CONNECTION_MODE_MULTIPLE = 1
};

// ============================================================================
//
// Classes
//
// ============================================================================
// ----------------------------------------------------------------------------
// Message
// ----------------------------------------------------------------------------
class Message
{
  public:
    Message( ESP8266_FIRMWARE f = ESP8266_FIRMWARE_1 )
      : _message(""), _ack("") {};
    virtual ~Message() {};

    String data() const { return this->_message; };
    String ack() const { return this->_ack; };

  protected:
    ESP8266_FIRMWARE _firmware;
    String _message;
    String _ack;
};

// ----------------------------------------------------------------------------
// MessageTest
// ----------------------------------------------------------------------------
class MessageTest : public Message
{
  public:
    MessageTest( ESP8266_FIRMWARE f = ESP8266_FIRMWARE_1 )
      : Message( f )
    {
      this->_message = "AT";
      this->_ack = "OK";
    };
};

// ----------------------------------------------------------------------------
// MessageReset
// ----------------------------------------------------------------------------
class MessageReset : public Message
{
  public:
    MessageReset( ESP8266_FIRMWARE f = ESP8266_FIRMWARE_1 )
      : Message( f )
    {
      this->_message = "AT+RST";
    };
};

// ----------------------------------------------------------------------------
// MessageOpenLink
// ----------------------------------------------------------------------------
class MessageOpenLink : public Message
{
  public:
    MessageOpenLink( ESP8266_MODE mode, String ip, int port,
       ESP8266_FIRMWARE f = ESP8266_FIRMWARE_1 )
      : Message( f )
    {
      _message = "AT+CIPSTART=";

      if (mode == ESP8266_MODE_TCP)
        _message += "\"TCP\"";
      else
        _message += "\"UDP\"";

       _message += ",\"" + ip + "\"," + port;

       _ack = "Error"; // we are waiting to not receive it!
    };
};

// ----------------------------------------------------------------------------
// MessageSendData
// ----------------------------------------------------------------------------
class MessageSendData : public Message
{
  public:
    MessageSendData( String msg, ESP8266_FIRMWARE f = ESP8266_FIRMWARE_1 )
      : Message( f )
    {
      this->_part1 = "AT+CIPSEND=";
      this->_part1 += msg.length();
      this->_part2 = msg;
      this->_message = this->_part1 + this->_part2;

      this->_ack = ">";
    };

    String get_part1() { return this->_part1; };

    String get_part2() { return this->_part2; };

  public:
    String _part1;
    String _part2;
};

// ----------------------------------------------------------------------------
// MessageCloseConnection
// ----------------------------------------------------------------------------
class MessageCloseConnection : public Message
{
  public:
    MessageCloseConnection( ESP8266_FIRMWARE f = ESP8266_FIRMWARE_1 )
      : Message( f )
    {
      this->_message = "AT+CIPCLOSE";
    };
};

// ----------------------------------------------------------------------------
// MessageJoinAP
// ----------------------------------------------------------------------------
class MessageJoinAP : public Message
{
  public:
    MessageJoinAP( String essid, String password,
        ESP8266_FIRMWARE f = ESP8266_FIRMWARE_1 )
      : Message( f )
    {
      this->_message = "AT+CWJAP=\"" + essid + "\",\"" + password + "\"";
      this->_ack = "OK";
    };
};

// ----------------------------------------------------------------------------
// MessageWifiMode
// ----------------------------------------------------------------------------
class MessageWifiMode : public Message
{
  public:
    MessageWifiMode( ESP8266_WIFI_MODE mode,
        ESP8266_FIRMWARE f = ESP8266_FIRMWARE_1 )
      : Message( f )
    {
      this->_message = "AT+CWMODE=";
      this->_message += mode;
      this->_ack = "OK";
    };
};

// ----------------------------------------------------------------------------
// MessageConnectionMode
// ----------------------------------------------------------------------------
class MessageConnectionMode : public Message
{
  public:
    MessageConnectionMode( ESP8266_CONNECTION_MODE mode,
        ESP8266_FIRMWARE f = ESP8266_FIRMWARE_1 )
      : Message( f )
    {
      this->_message = "AT+CIPMUX=";
      this->_message += mode;
    };
};

// ----------------------------------------------------------------------------
// MessageGetIP
// ----------------------------------------------------------------------------
class MessageGetIP : public Message
{
  public:
    MessageGetIP( ESP8266_FIRMWARE f = ESP8266_FIRMWARE_1 )
      : Message( f )
    {
      this->_message = "AT+CIFSR";
    };
};
