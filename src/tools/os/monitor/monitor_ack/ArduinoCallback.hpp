#ifndef ARDUINO_CALLBACK_HPP
#define ARDUINO_CALLBACK_HPP

#include <libtchat/TchatBuffer.hpp>
#include <libtchat/TchatMsg.hpp>
#include <libserial/SerialPort.hpp>
#include <libreactor/ReactorCallback.hpp>

class ArduinoCallback : public ReactorCallback
{
public:
    ArduinoCallback(SerialPort *arduino_port);

    void cb();

private:
    std::string get_date(); 

    void recv_ack_led(TchatMsg *msg);
    void recv_ack_servo(TchatMsg *msg);

    TchatBuffer _tchat_buffer;
    SerialPort *_arduino_port;
};

#endif
