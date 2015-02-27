#ifndef TCHAT_MSG_LED_HPP
#define TCHAT_MSG_LED_HPP

#include <libtchat/TchatMsg.hpp>

class TchatMsgLed : public TchatMsg
{
public:
    void set_pin(uint32_t pin);
    uint32_t get_pin();

    void set_status(TCHAT_LED_STATUS status);
    TCHAT_LED_STATUS get_status();

private:  
};

#endif
