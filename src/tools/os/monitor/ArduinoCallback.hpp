#ifndef ARDUINO_CALLBACK_HPP
#define ARDUINO_CALLBACK_HPP

#include <libserial/SerialPort.hpp>
#include <libreactor/ReactorCallback.hpp>

class ArduinoCallback : public ReactorCallback
{
public:
    ArduinoCallback(SerialPort *arduino_port);

    void cb();

private:
    SerialPort *_arduino_port;
};

#endif
