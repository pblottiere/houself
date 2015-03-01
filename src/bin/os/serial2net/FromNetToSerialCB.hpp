#ifndef FROM_NET_TO_SERIAL_CB
#define FROM_NET_TO_SERIAL_CB

#include <libserial/SerialPort.hpp>
#include <libreactor/ReactorCallback.hpp>

class FromNetToSerialCB : public ReactorCallback
{
public:
    FromNetToSerialCB(SerialPort *port, zmq::socket_t *socket);

    void cb();

private:
    SerialPort *_serial;
    zmq::socket_t *_socket;
};

#endif
