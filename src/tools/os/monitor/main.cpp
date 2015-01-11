#include <stdio.h>
#include <signal.h>

#include <libserial/SerialPort.hpp>
#include <libreactor/Reactor.hpp>

#include "ArduinoCallback.hpp"

Reactor *reactor;

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
int main()
{
    // signal handler
    signal(SIGINT, signal_handler);

    // open all
    zmq::context_t zcontext(1);
    SerialPort arduino_port("/dev/ttyACM0");
    bool rc = arduino_port.open_port();

    if( !rc )
    {
        // init reactor and its callback
        ArduinoCallback arduino_cb(&arduino_port);
        
        reactor = new Reactor(&zcontext);
        reactor->register_event(&arduino_cb);

        // run
        reactor->run();

        // close all / delete
        arduino_port.close_port();
        delete reactor;
    }

    printf("Monitor correctly terminated...\n");

    // return
    return 0;
}
