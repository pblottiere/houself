#ifndef TCHAT_MSG_TEMP_HUM_HPP
#define TCHAT_MSG_TEMP_HUM_HPP

#include <libtchat/TchatMsg.hpp>

class TchatMsgTempHum : public TchatMsg
{
public:
    void set_pin(uint8_t pin);
    uint8_t get_pin();

    void set_temperature(uint8_t temp);
    void set_humidity(uint8_t hum);
    uint8_t get_temperature();
    uint8_t get_humidity();

private:  
};

#endif
