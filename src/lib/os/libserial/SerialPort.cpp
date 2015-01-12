#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include <libserial/SerialPort.hpp>

//==============================================================================
//
// Cst / Dst
//
//==============================================================================
//------------------------------------------------------------------------------
// cst
//------------------------------------------------------------------------------
SerialPort::SerialPort(const char *port) :
    _port(port)
{    
}

//==============================================================================
//
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// open
//------------------------------------------------------------------------------
bool SerialPort::open_port()
{
    bool rc(false);

    // open file descriptor
    _fd = open(_port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (_fd != -1)
    {
        fcntl(_fd, F_SETFL, 0);
    }
    else
    {
        perror("Serial::open_port: ");
        rc = true;
    }

    // configure
    struct termios options;

    tcgetattr(_fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    options.c_cflag |= (CLOCAL | CREAD);

    tcsetattr(_fd, TCSANOW, &options);
    tcsetattr(_fd, TCSAFLUSH, &options);

    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~CRTSCTS; 

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    options.c_iflag &= ~(IXON | IXOFF | IXANY);

    // flush data
    tcflush(_fd, TCIOFLUSH);

    return rc;
}

//------------------------------------------------------------------------------
// close
//------------------------------------------------------------------------------
void SerialPort::close_port()
{
    close(_fd);
}

//------------------------------------------------------------------------------
// read
//------------------------------------------------------------------------------
uint32_t SerialPort::read_data(uint8_t *buffer)
{
    return read(_fd, buffer, sizeof(buffer));
}

//------------------------------------------------------------------------------
// get_fd
//------------------------------------------------------------------------------
int32_t SerialPort::get_fd()
{
    return _fd;
}
