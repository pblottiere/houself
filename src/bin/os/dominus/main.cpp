#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include <libreactor/Reactor.hpp>
#include <libserial/SerialPort.hpp>

#include "DominusCallback.hpp"

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
// print help
//------------------------------------------------------------------------------
void print_help()
{
  std::cout << "Usage: dominus :" << std::endl
	    << "        -p device" << std::endl
	    << "        -n network" << std::endl
	    << "        -d domoticz ip:port" << std::endl;
}



//------------------------------------------------------------------------------
// parse CLI
//------------------------------------------------------------------------------
const bool parse_cli(int argc, char **argv, std::string & port, 
		     std::string & network, std::string & domoticz_ip)
{
  int c;
  while ((c = getopt (argc, argv, "hp:d:")) != -1)
  {
    switch (c)
    {
    case 'p':
      port.append(optarg);
      break;
    case 'n':
      network.append(optarg);
      break;
    case 'd':
      domoticz_ip.append(optarg);
      break;
    default:
      print_help();
      break;
    }
  }

  if (domoticz_ip.size() == 0)
    domoticz_ip.append("localhost:8080");

  bool ok = ((port.size() == 0) ^ (network.size() == 0));

  if (!ok)
    std::cout << "ERROR: see usage with --help." << std::endl;
      
  return ok;
}




//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    // parse cli parameters
    std::string port("");
    std::string network("");
    std::string domoticz_ip("");
    if ( ! parse_cli(argc, argv, port, network, domoticz_ip) )
      return 1;  
  

    // signal handler
    signal(SIGINT, signal_handler);

    // open all
    zmq::context_t zcontext(1);
    SerialPort dominus_port(port.c_str());
    bool rc = dominus_port.open_port();

    if( !rc )
    {
        // init reactor and its callback
      DominusCallback dominus_cb(&dominus_port, domoticz_ip);
        
        reactor = new Reactor(&zcontext);
        reactor->register_event(&dominus_cb);

        // run
        reactor->run();

        // close all / delete
        dominus_port.close_port();
        delete reactor;
    }

    std::cout << "Dominus correctly terminated..." << std::endl;

    // return
    return 0;

ERR:
    return 1;
}
