#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <iostream>

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
// clear_console
//------------------------------------------------------------------------------
void clear_console()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    for(size_t j=0; j<w.ws_row; j++)
        printf("\n");
}

//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    // parse cli parameters
    std::string port("");
    std::string network("");
    int c;
    while ((c = getopt (argc, argv, "hp:")) != -1)
        switch (c)
        {
        case 'h':
            std::cout << "Usage: ./monitor -p device -n network" << std::endl;
            return 0;
        case 'p':
            port.append(optarg);
            break;
        case 'n':
            network.append(optarg);
            break;
        default:
            std::cout << "Unknwon option. See --help." << std::endl;
            return 1;
        }

    if( ((port.size() == 0) && (network.size() == 0))
        || ((port.size() != 0) && (network.size() != 0)) )
    {
        std::cout << "ERROR: see usage with --help." << std::endl;
        return 1;
    }    

    // clear console before anything
    clear_console();

    // signal handler
    signal(SIGINT, signal_handler);

    // open all
    zmq::context_t zcontext(1);
    SerialPort arduino_port(port.c_str());
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

    std::cout << "Monitor correctly terminated..." << std::endl;

    // return
    return 0;

ERR:
    return 1;
}
