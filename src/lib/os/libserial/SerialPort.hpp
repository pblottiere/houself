#ifndef SERIAL_PORT_HPP
#define SERIAL_PORT_HPP

#include <stdint.h>
#include <string>

class SerialPort
{
public:
    bool open_port(const char *port);
    void close_port();

    //uint32_t write(const char *buffer);
    uint32_t read(char *buffer);

private:
    uint32_t _fd;
};

#endif
