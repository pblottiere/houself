#ifndef REACTOR_CALLBACK_HPP
#define REACTOR_CALLBACK_HPP

#include <algorithm>
#include <zmq.hpp>
#include <stdint.h>

class ReactorCallback
{
public:
    ReactorCallback(zmq::socket_t *socket);
    ReactorCallback(int32_t fd);

    zmq_pollitem_t get_poll_item();

    virtual void cb() = 0;

private:
    zmq_pollitem_t _item;
};

#endif
