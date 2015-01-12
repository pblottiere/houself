#include <stdio.h>
#include <iostream>
#include <libtchat/TchatMsg.hpp>
#include <libtchat/TchatMsgLed.hpp>
#include <libtchat/TchatMsgServo.hpp>
#include "ArduinoCallback.hpp"

//==============================================================================
//
// Cst / Dst
//
//==============================================================================
//------------------------------------------------------------------------------
// cst
//------------------------------------------------------------------------------
ArduinoCallback::ArduinoCallback(SerialPort *arduino_port) :
    _arduino_port(arduino_port),
    ReactorCallback(arduino_port->get_fd())
{
}

//==============================================================================
//
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// cb
//------------------------------------------------------------------------------
void ArduinoCallback::cb()
{
    uint8_t buffer[256];
    uint32_t bytes =_arduino_port->read_data(buffer);

    bool rc(false);
    TchatMsg msg;

    for(size_t j=0; j<bytes; j++)
    {
        bool rc = _tchat_buffer.add_byte(buffer[j]);
        if(rc)
        {
            msg.set_buffer(_tchat_buffer);

            if(msg.get_type() == TCHAT_TYPE_ACK)
            {
                switch(msg.get_target())
                {
                case TCHAT_TARGET_LED:
                {
                    recv_ack_led(&msg);
                    break;
                }
                case TCHAT_TARGET_SERVO:
                {
                    recv_ack_servo(&msg);
                    break;
                }
                default:
                    perror("Target unknown");
                }
            }
        }
    }
}

//==============================================================================
//
// Private methods
//
//==============================================================================
//------------------------------------------------------------------------------
// get_date
//------------------------------------------------------------------------------
std::string ArduinoCallback::get_date()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "\033[1;37m[%X]\033[0m", &tstruct);

    return buf;
}

//------------------------------------------------------------------------------
// recv_ack_led
//------------------------------------------------------------------------------
void ArduinoCallback::recv_ack_led(TchatMsg *msg)
{
    std::cout << get_date() << " LED" << std::endl;
    TchatMsgLed *led = (TchatMsgLed*) msg;
}

//------------------------------------------------------------------------------
// recv_ack_servo
//------------------------------------------------------------------------------
void ArduinoCallback::recv_ack_servo(TchatMsg *msg)
{
    std::cout << get_date() << " SERVO" << std::endl;
    TchatMsgServo *servo = (TchatMsgServo*) msg;
}
