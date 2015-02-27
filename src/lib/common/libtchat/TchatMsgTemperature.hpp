#ifndef TCHAT_MSG_TEMPERATURE_HPP
#define TCHAT_MSG_TEMPERATURE_HPP

#include <libtchat/TchatMsg.hpp>

class TchatMsgTemperature : public TchatMsg
{
public:
    void set_pin(uint8_t pin);
    uint8_t get_pin();

    uint8_t get_temperature();

private:  
};

#endif
