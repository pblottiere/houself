#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <algorithm>
#include <zmq.hpp>
#include <vector>
#include <libreactor/ReactorCallback.hpp>

class Reactor
{
public:
    Reactor(zmq::context_t *context);
    ~Reactor();

    void register_event(ReactorCallback *callback);
    void unregister_event(ReactorCallback *callback);

    void run();
    void halt();

private:
    void build_poll_items();

    std::vector<ReactorCallback*> _callbacks;
    zmq::context_t *_context;
    zmq::socket_t *_admin_pub;
    zmq::socket_t *_admin_sub;
    zmq_pollitem_t *_poll_items;
};

#endif
