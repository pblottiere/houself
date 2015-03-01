//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <unistd.h>
#include <signal.h>
#include <zmq.hpp>
#include <iostream>

#include <libserial/SerialPort.hpp>
#include <libreactor/Reactor.hpp>

#include "FromNetToSerialCB.hpp"

Reactor *reactor;

//==============================================================================
//
// Functions
//
//==============================================================================
//------------------------------------------------------------------------------
// signal_handler
//------------------------------------------------------------------------------
void signal_handler(int sig) {
    switch (sig) {
    case SIGINT:
        reactor->halt();
        break;
    default:
        fprintf(stderr, "Unexpected catched signal '%d'...\n", sig);
        abort();
    }
}

//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    // parse cli parameters
    std::string serial("");
    uint32_t net_to_serial(0);
    uint32_t serial_to_net(0);
    int c;
    while ((c = getopt (argc, argv, "hp:")) != -1)
    {
        switch (c)
        {
        case 'h':
            std::cout << "Usage: ./dominus_serial2net:" << std::endl
                      << "        -f serial to net port" << std::endl
                      << "        -h help" << std::endl
                      << "        -s serial port" << std::endl
                      << "        -t net to serial port" << std::endl;
            return 0;
        case 's':
            serial.append(optarg);
            break;
        case 't':
            net_to_serial = atoi(optarg);
            break;
        case 'f':
            serial_to_net = atoi(optarg);
            break;
        default:
            std::cout << "Unknwon option. See -help." << std::endl;
            return 1;
        }
    }
    
    if( (serial.size() == 0) || (net_to_serial == 0) || (serial_to_net == 0) )
    {
        std::cout << "ERROR: see usage with --help." << std::endl;
        return 1;
    }   

    // init serial port
    SerialPort serial_port(serial.c_str());
    serial_port.open_port();

    // init net port
    zmq::context_t context(1);
    std::string sub_adress = "tcp://127.0.0.1:" + std::to_string(net_to_serial);
    zmq::context_t zcontext(1);
    zmq::socket_t sub(zcontext, ZMQ_SUB);
    sub.connect(sub_adress.c_str());
    sub.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    // init callbacks and reactor
    FromNetToSerialCB to_serial_cb(&serial_port, &sub);

    reactor = new Reactor(&context);
    reactor->register_event(&to_serial_cb);

    // signal handler
    signal(SIGINT, signal_handler);

    // run
    reactor->run();

    // close all / delete
    serial_port.close_port();
    delete reactor;

    std::cout << "Serial2net correctly terminated..." << std::endl;

    return 0;
}
