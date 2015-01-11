#ifndef SERIAL_PORT_HPP
#define SERIAL_PORT_HPP

#include <stdint.h>
#include <string>

class SerialPort
{
public:
    SerialPort(const char* port);

    bool open_port();
    void close_port();

    //uint32_t write(const char *buffer);
    uint32_t read_data(uint8_t *buffer);

    int32_t get_fd();

private:
    const char* _port;
    uint32_t _fd;
};

#endif
