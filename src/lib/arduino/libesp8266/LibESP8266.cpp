//------------------------------------------------------------------------------
// imports
//------------------------------------------------------------------------------
#include <libesp8266/LibESP8266.hpp>

//==============================================================================
//
// Cst / Dst
//
//==============================================================================
//------------------------------------------------------------------------------
// Cst
//------------------------------------------------------------------------------
LibESP8266::LibESP8266() :
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
void LibESP8266::set_dbg_serial(SoftwareSerial &serial)
{
    _dbg_serial = &serial;
}

//------------------------------------------------------------------------------
// connect
//------------------------------------------------------------------------------
LIB_ESP8266_ERROR LibESP8266::connect(const String &essid, const String &pass)
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
// send_tcp_msg
//------------------------------------------------------------------------------
LIB_ESP8266_ERROR LibESP8266::send_tcp_msg(const String &ip, int32_t port,
                                           const String &msg)
{
    LIB_ESP8266_ERROR err(LIB_ESP8266_ERROR_NO_ERROR);

    // open TCP connection
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += ip;
    cmd += "\",";
    cmd += port;
    Serial.println(cmd);
    if (Serial.find("Error"))
    {
        log("TCP connection failed.");
        return err;
    }
    else
        log("TCP connection successed.");

    log(cmd);

    // send the message
    Serial.print("AT+CIPSEND=");
    Serial.println(msg.length());
    if (Serial.find(">"))
    {
        Serial.print(msg);
        delay(2000);

        log("OK");
        // while (Serial.available())
        // {
        //     char c = Serial.read();
        //     _dbg_serial->write(c);
        //     if (c == '\r') _dbg_serial->print('\n');
        // }
    }
    else
    {
        // close the connection
        Serial.println("AT+CIPCLOSE");
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
void LibESP8266::log(const String &str)
{
    if (_dbg_serial != NULL)
        _dbg_serial->println(str);
}

//------------------------------------------------------------------------------
// open_serial_port
//------------------------------------------------------------------------------
void LibESP8266::open_serial_port()
{
    log("Open serial port...");
    Serial.begin(_speed);
    Serial.setTimeout(5000);
}

//------------------------------------------------------------------------------
// check_esp8266_online
//------------------------------------------------------------------------------
LIB_ESP8266_ERROR LibESP8266::check_esp8266_online()
{
    log("Check if ESP8266 is online...");

    // vars
    LIB_ESP8266_ERROR err(LIB_ESP8266_ERROR_OFFLINE);

    for (int i=0; i<_retry; i++)
    {
        // send a command
        Serial.println("AT");
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
LIB_ESP8266_ERROR LibESP8266::get_ip(const String &essid, const String &pass)
{
    log("Get IP address...");

    LIB_ESP8266_ERROR err(LIB_ESP8266_ERROR_NOIP);

    // build command
    String cmd = "AT+CWJAP=\"";
    cmd += essid;
    cmd += "\",\"";
    cmd += pass;
    cmd += "\"";

    // try to get an IP
    for (int i=0; i<_retry; i++)
    {
        Serial.println("AT+CWMODE=1");
        Serial.println(cmd);
        delay(3000);
        if (Serial.find("OK"))
        {
            // single mode connection
            Serial.println("AT+CIPMUX=0");

            // the connection is done. Get the IP
            delay(2000);
            Serial.println("AT+CIFSR");
            //while (Serial.available())
            //_dbg_serial->write(Serial.read());

            // dbg msg
            log("OK");
            err = LIB_ESP8266_ERROR_NO_ERROR;
            break;
        }
    }

    return err;
}
