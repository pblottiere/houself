#ifndef TCHAT_MSG_HPP
#define TCHAT_MSG_HPP

#include <stdint.h>

#include <libtchat/TchatBuffer.hpp>

class TchatMsg
{
public:
    bool set_buffer(const TchatBuffer &buffer);
    const TchatBuffer& get_buffer() const;

    void set_target(TCHAT_TARGET target);
    TCHAT_TARGET get_target();

    void set_type(TCHAT_TYPE type);
    TCHAT_TYPE get_type();

    void format();

private:
    TchatBuffer _buffer;
};

#endif

