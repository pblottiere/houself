#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <zmq.hpp>
#include <vector>
#include <libreactor/ReactorCallback.hpp>

class Reactor
{
public:
    Reactor();

    void register_event(ReactorCallback *callback);
    void unregister_event(ReactorCallback *callback);
    void run();

private:  
    void build_poll_items();

    std::vector<ReactorCallback*> _callbacks;
    zmq_pollitem_t *_poll_items;
};

#endif
