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
ESP8266::ESP8266(const LIB_ESP8266_SPEED speed, const unsigned int retry) :
    _dbg_serial(NULL),
    _retry(retry),
    _speed(speed)
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
// unset_dbg_serial
//------------------------------------------------------------------------------
void ESP8266::unset_dbg_serial()
{
    _dbg_serial = NULL;
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

    return err;
}

//------------------------------------------------------------------------------
// send_http_request
//------------------------------------------------------------------------------
LIB_ESP8266_ERROR ESP8266::send_http_request(const String &ip, int32_t port,
                                             const String &msg)
{
    // log
    log("[ESP8266] send HTTP request");

    // init return value
    LIB_ESP8266_ERROR err(LIB_ESP8266_ERROR_UNKNOWN);

    for (int i=0; i<_retry; i++)
    {
        // log
        log(".");

        // open TCP connection
        MessageOpenLink cmd(LIB_ESP8266_MODE_TCP, ip, port);
        if ( write(cmd.get(), 3000, "Error"))
        {
            // send the message
            String http_msg = "GET /" + msg + ";1 HTTP/1.0\r\n\r\n";
            MessageSendData send_data_cmd(http_msg);

            if (! write(send_data_cmd.get_part1(), 3000, ">") )
            {
                write(send_data_cmd.get_part2());
                err = LIB_ESP8266_ERROR_NO_ERROR;
                break;
            }
            else
            {
                // close the connection
                MessageCloseConnection close_cmd;
                write(close_cmd.get());
            }
        }
    }

    // log
    log_status(err);

    return err;
}

//------------------------------------------------------------------------------
// reset
//------------------------------------------------------------------------------
void ESP8266::reset()
{
    log("[ESP8266] reset.");
    MessageReset rst;
    write(rst.get());
    log_status(LIB_ESP8266_ERROR_NO_ERROR);
}

//==============================================================================
//
// Private methods
//
//==============================================================================
//------------------------------------------------------------------------------
// log_status
//------------------------------------------------------------------------------
void ESP8266::log_status(const LIB_ESP8266_ERROR err)
{
    if (err == LIB_ESP8266_ERROR_NO_ERROR)
        log(" : OK", true);
    else
        log(" : FAIL", true);
}

//------------------------------------------------------------------------------
// log
//------------------------------------------------------------------------------
void ESP8266::log(const String &str, const bool ln)
{
    if (_dbg_serial != NULL)
        if (ln)
            _dbg_serial->println(str);
        else
            _dbg_serial->print(str);
}

//------------------------------------------------------------------------------
// write
//------------------------------------------------------------------------------
// @return False of no error, True otherwise.
bool ESP8266::write(const String &str, const unsigned int delay_sec,
                    const String &ack)
{
    // init return
    bool rc(true);

    // convert ack to char*
    char ack_ptr[sizeof(ack)];
    ack.toCharArray(ack_ptr, sizeof(ack_ptr));

    // write to serial port and wait
    Serial.println(str);
    delay(delay_sec);

    // search the acknowledgement
    if (Serial.find(ack_ptr))
        rc = false;

    return rc;
}

//------------------------------------------------------------------------------
// open_serial_port
//------------------------------------------------------------------------------
void ESP8266::open_serial_port()
{
    log("[ESP8266] open serial port.");
    Serial.begin(_speed);
    Serial.setTimeout(5000);
    log_status(LIB_ESP8266_ERROR_NO_ERROR);
}

//------------------------------------------------------------------------------
// check_esp8266_online
//------------------------------------------------------------------------------
LIB_ESP8266_ERROR ESP8266::check_esp8266_online()
{
    log("[ESP8266] test communication with ESP8266");

    // vars
    LIB_ESP8266_ERROR err(LIB_ESP8266_ERROR_OFFLINE);

    for (int i=0; i<_retry; i++)
    {
        // log
        log(".");

        // if no error
        MessageTest cmd;
        if (! write(cmd.get()))
        {
            err = LIB_ESP8266_ERROR_NO_ERROR;
            break;
        }
    }

    // log
    log_status(err);

    // return
    return err;
}

//------------------------------------------------------------------------------
// get_ip
//------------------------------------------------------------------------------
LIB_ESP8266_ERROR ESP8266::get_ip(const String &essid, const String &pass)
{
    log("[ESP8266] get IP address");

    LIB_ESP8266_ERROR err(LIB_ESP8266_ERROR_NOIP);

    // try to get an IP
    for (int i=0; i<_retry; i++)
    {
        // log msg
        log(".");

        // set wifi mode Station + Access Point
        MessageWifiMode mode_cmd(LIB_ESP8266_WIFI_MODE_BOTH);
        write(mode_cmd.get());

        // join access point
        MessageJoinAP join_ap_cmd(essid, pass);
        if ( ! write(join_ap_cmd.get()) )
        {
            // single mode connection
            MessageConnectionMode conn_cmd(LIB_ESP8266_CONNECTION_MODE_SINGLE);
            write(conn_cmd.get());

            // set err and break loop
            err = LIB_ESP8266_ERROR_NO_ERROR;
            break;
        }
    }

    // log message
    log_status(err);

    return err;
}
