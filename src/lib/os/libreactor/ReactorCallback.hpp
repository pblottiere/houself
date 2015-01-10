#ifndef REACTOR_CALLBACK_HPP
#define REACTOR_CALLBACK_HPP

class ReactorCallback
{
public:
    ReactorCallback(zmq_pollitem_t item);
    ReactorCallback(int32_t fd);

    zmq_pollitem_t get_poll_item();
    virtual void run() = 0;

private:  
    zmq_pollitem_t _item;
};

#endif
