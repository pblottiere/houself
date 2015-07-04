//------------------------------------------------------------------------------
// imports
//------------------------------------------------------------------------------
#include <libesp8266/ESP8266.hpp>
#include <libesp8266/Message.hpp>

using namespace libesp8266;

//==============================================================================
//
// Cst / Dst
//
//==============================================================================
//------------------------------------------------------------------------------
// Cst
//------------------------------------------------------------------------------
ESP8266::ESP8266() :
    _dbg_serial(NULL),
    _retry(10),
    _speed(9600)
{
}

//==============================================================================
//
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// set_dbg_serial
//------------------------------------------------------------------------------
void ESP8266::set_dbg_serial(SoftwareSerial &serial)
{
    _dbg_serial = &serial;
}

//------------------------------------------------------------------------------
// connect
//------------------------------------------------------------------------------
LIB_ESP8266_ERROR ESP8266::connect(const String &essid, const String &pass)
{
    LIB_ESP8266_ERROR err(LIB_ESP8266_ERROR_NO_ERROR);

    open_serial_port();

    err = check_esp8266_online();
    if (err == LIB_ESP8266_ERROR_NO_ERROR)
        err = get_ip(essid, pass);

    if (err == LIB_ESP8266_ERROR_NO_ERROR)
        log("Wifi ready.");

    return err;
}

//------------------------------------------------------------------------------
// send_http_request
//------------------------------------------------------------------------------
LIB_ESP8266_ERROR ESP8266::send_http_request(const String &ip, int32_t port,
                                             const String &msg)
{
    LIB_ESP8266_ERROR err(LIB_ESP8266_ERROR_NO_ERROR);

    // open TCP connection
    MessageOpenLink cmd(LIB_ESP8266_MODE_TCP, ip, port);
    Serial.println(cmd.get());

    if (Serial.find("Error"))
    {
        log("TCP connection failed.");
        return err;
    }
    else
        log("TCP connection successed.");

    // send the message
    String http_msg = "GET /" + msg + ";1 HTTP/1.0\r\n\r\n";
    MessageSendData send_data_cmd(http_msg);
    Serial.println(send_data_cmd.get_part1());

    if (Serial.find(">"))
    {
        Serial.print(send_data_cmd.get_part2());
        delay(2000);
    }
    else
    {
        // close the connection
        MessageCloseConnection close_cmd;
        Serial.println(close_cmd.get());
        log(close_cmd.get());
        log("Timeout");
        delay(1000);
    }

    return err;
}

//==============================================================================
//
// Private methods
//
//==============================================================================
//------------------------------------------------------------------------------
// log
//------------------------------------------------------------------------------
void ESP8266::log(const String &str)
{
    if (_dbg_serial != NULL)
        _dbg_serial->println(str);
}

//------------------------------------------------------------------------------
// open_serial_port
//------------------------------------------------------------------------------
void ESP8266::open_serial_port()
{
    log("Open serial port...");
    Serial.begin(_speed);
    Serial.setTimeout(5000);
}

//------------------------------------------------------------------------------
// check_esp8266_online
//------------------------------------------------------------------------------
LIB_ESP8266_ERROR ESP8266::check_esp8266_online()
{
    log("Check if ESP8266 is online...");

    // vars
    LIB_ESP8266_ERROR err(LIB_ESP8266_ERROR_OFFLINE);

    for (int i=0; i<_retry; i++)
    {
        // send a command
        MessageTest cmd;
        Serial.println(cmd.get());
        delay(3000);

        // check ack
        if (Serial.find("OK"))
        {
            log("OK");
            err = LIB_ESP8266_ERROR_NO_ERROR;
            break;
        }
    }

    // return
    return err;
}

//------------------------------------------------------------------------------
// get_ip
//------------------------------------------------------------------------------
LIB_ESP8266_ERROR ESP8266::get_ip(const String &essid, const String &pass)
{
    log("Get IP address...");

    LIB_ESP8266_ERROR err(LIB_ESP8266_ERROR_NOIP);

    // try to get an IP
    for (int i=0; i<_retry; i++)
    {
        MessageWifiMode mode_cmd(LIB_ESP8266_WIFI_MODE_BOTH);
        Serial.println(mode_cmd.get());

        MessageJoinAP join_ap_cmd(essid, pass);
        Serial.println(join_ap_cmd.get());
        delay(3000);

        if (Serial.find("OK"))
        {
            // single mode connection
            MessageConnectionMode conn_cmd(LIB_ESP8266_CONNECTION_MODE_SINGLE);
            Serial.println(conn_cmd.get());

            // the connection is done. Get the IP
            delay(2000);
            MessageGetIP ip_cmd;
            Serial.println(ip_cmd.get());

            // dbg msg
            log("OK");
            err = LIB_ESP8266_ERROR_NO_ERROR;
            break;
        }
    }

    return err;
}
