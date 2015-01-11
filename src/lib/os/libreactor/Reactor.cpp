#include <libreactor/Reactor.hpp>

//==============================================================================
//
// Cst/Dst
//
//==============================================================================
//------------------------------------------------------------------------------
// cst
//------------------------------------------------------------------------------
Reactor::Reactor(zmq::context_t *context) :
    _context(context),
    _poll_items(nullptr)
{
    // init admin sockets
    _admin_pub = new zmq::socket_t(*_context, ZMQ_PUB);
    _admin_pub->bind("inproc://reactor_admin");

    _admin_sub = new zmq::socket_t(*_context, ZMQ_SUB);
    _admin_sub->connect("inproc://reactor_admin");
    _admin_sub->setsockopt(ZMQ_SUBSCRIBE, "", 0);
}

//------------------------------------------------------------------------------
// dst
//------------------------------------------------------------------------------
Reactor::~Reactor()
{
    if( _poll_items != nullptr)
        delete [] _poll_items;
    
    _admin_pub->close();
    _admin_sub->close();

    delete _admin_pub;
    delete _admin_sub;
}

//==============================================================================
//
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// register_event
//------------------------------------------------------------------------------
void Reactor::register_event(ReactorCallback *callback)
{
    _callbacks.push_back(callback);
}

//------------------------------------------------------------------------------
// unregister_event
//------------------------------------------------------------------------------
void Reactor::unregister_event(ReactorCallback *callback)
{
    for(size_t j=0; j<_callbacks.size(); j++)
        if(_callbacks[j] == callback)
        {
            _callbacks.erase(_callbacks.begin() + j);
            break;
        }
}

//------------------------------------------------------------------------------
// run
//------------------------------------------------------------------------------
void Reactor::run()
{
    build_poll_items();
    bool again(true);

    while(again)
    {
        int rc = zmq_poll (_poll_items, _callbacks.size()+1, -1);

        if ( (rc != -1) || ( (rc == -1) && (errno == EINTR) ) )
        {
            if (_poll_items[0].revents == ZMQ_POLLIN)
            {
                zmq::message_t zmsg;
                _admin_sub->recv(&zmsg);
                again = false;
                break;
            }
            
            for(size_t j=1; j<=_callbacks.size(); j++)
                if (_poll_items[j].revents == ZMQ_POLLIN)
                    _callbacks[j-1]->cb();
        }
        else
        {
            perror("Reactor::run:");
            again = false;
        }
    }
}

//------------------------------------------------------------------------------
// halt
//------------------------------------------------------------------------------
void Reactor::halt()
{
    zmq::message_t zmsg_empty;
    int rc = _admin_pub->send(zmsg_empty);
}

//==============================================================================
//
// Private methods
//
//==============================================================================
//------------------------------------------------------------------------------
// build_poll_items
//------------------------------------------------------------------------------
void Reactor::build_poll_items()
{
    if(_poll_items != nullptr)
        delete [] _poll_items;
    
    _poll_items = new zmq_pollitem_t[_callbacks.size() + 1];

    _poll_items[0].socket = *_admin_sub;
    _poll_items[0].events = ZMQ_POLLIN;

    for(size_t j=1; j<=_callbacks.size(); j++)
        _poll_items[j] = _callbacks[j-1]->get_poll_item();
}
