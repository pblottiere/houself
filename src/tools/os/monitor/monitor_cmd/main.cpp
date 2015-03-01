//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <iostream>
#include <zmq.hpp>

//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    // parse cli parameters
    std::string port("");
    uint32_t network = 0;
    int c;
    while ((c = getopt (argc, argv, "hp:")) != -1)
        switch (c)
        {
        case 'h':
            std::cout << "Usage: dominus_monitor_cmd:" << std::endl 
                      << "        -p device" << std::endl
                      << "        -n network" << std::endl;
            return 0;
        case 'p':
            port.append(optarg);
            break;
        case 'n':
            network = atoi(optarg);
            break;
        default:
            std::cout << "Unknwon option. See -help." << std::endl;
            return 1;
        }

    if( ((port.size() == 0) && (network == 0))
        || ((port.size() != 0) && (network == 0)) )
    {
        std::cout << "ERROR: see usage with --help." << std::endl;
        return 1;
    } 

    // init net port
    zmq::context_t context(1);
    std::string pub_adress = "tcp://127.0.0.1:" + std::to_string(network);
    zmq::context_t zcontext(1);
    zmq::socket_t pub(zcontext, ZMQ_PUB);
    pub.bind(pub_adress.c_str());    

    return 0;
}
