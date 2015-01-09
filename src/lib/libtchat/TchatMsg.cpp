#include <stddef.h>
#include <stdio.h>

#include <libtchat/TchatMsg.hpp>

//==============================================================================
//
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// format
//------------------------------------------------------------------------------
void TchatMsg::format()
{
    _buffer.set_byte(TCHAT_HEADER_POSITION, TCHAT_HEADER);
    _buffer.set_byte(TCHAT_FOOTER_POSITION, TCHAT_FOOTER);
}

//------------------------------------------------------------------------------
// set_buffer
//------------------------------------------------------------------------------
bool TchatMsg::set_buffer(const TchatBuffer &buffer)
{
    _buffer = buffer;

    return true;
}

//------------------------------------------------------------------------------
// get_buffer
//------------------------------------------------------------------------------
const TchatBuffer& TchatMsg::get_buffer() const
{
    return _buffer;
}

//------------------------------------------------------------------------------
// set_target
//------------------------------------------------------------------------------
void TchatMsg::set_target(TCHAT_TARGET target)
{
    uint8_t new_byte = get_type() | target;
    _buffer.set_byte(TCHAT_TARGET_POSITION, new_byte);
}

//------------------------------------------------------------------------------
// get_target
//------------------------------------------------------------------------------
TCHAT_TARGET TchatMsg::get_target()
{
    uint8_t byte_target = _buffer.get_byte(TCHAT_TARGET_POSITION)
        & TCHAT_HEADER_MASK_TARGET;

    return (TCHAT_TARGET) byte_target ;
}

//------------------------------------------------------------------------------
// set_type
//------------------------------------------------------------------------------
void TchatMsg::set_type(TCHAT_TYPE type)
{
    uint8_t new_byte = get_target() | type;
    _buffer.set_byte(TCHAT_TYPE_POSITION, new_byte);
}

//------------------------------------------------------------------------------
// get_type
//------------------------------------------------------------------------------
TCHAT_TYPE TchatMsg::get_type()
{
    uint8_t byte_type = _buffer.get_byte(TCHAT_TYPE_POSITION)  
        & TCHAT_HEADER_MASK_TYPE;

    return (TCHAT_TYPE) byte_type;
}
