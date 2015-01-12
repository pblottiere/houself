#ifndef TCHAT_BUFFER_HPP
#define TCHAT_BUFFER_HPP

#include <libtchat/TchatCommon.hpp>

class TchatBuffer
{
public:
    TchatBuffer();

    bool set_byte(size_t index, uint8_t byte);
    uint8_t get_byte(size_t index) const;
    
    bool add_byte(uint8_t byte);

    void clear();

private:
    uint32_t _index;
    uint8_t _buffer[TCHAT_MSG_SIZE];
};

#endif
