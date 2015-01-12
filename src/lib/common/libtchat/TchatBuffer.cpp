#include <stddef.h>
#include <stdio.h>

#include <libtchat/TchatMsg.hpp>
#include <libtchat/TchatBuffer.hpp>

//==============================================================================
//
// Cst/dst
//
//==============================================================================
//------------------------------------------------------------------------------
// Cst
//------------------------------------------------------------------------------
TchatBuffer::TchatBuffer() :
    _index(0)
{
    clear();
}

//==============================================================================
//
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// set_byte
//------------------------------------------------------------------------------
bool TchatBuffer::set_byte(size_t index, uint8_t byte)
{
    bool rc(false);

    if( (index >= 0) && (index < TCHAT_MSG_SIZE) )
    {
        _buffer[index] = byte;
        rc = true;
    }

    return rc;
}

//------------------------------------------------------------------------------
// get_byte
//------------------------------------------------------------------------------
uint8_t TchatBuffer::get_byte(size_t index) const
{
    uint8_t byte(0x00);

    if( (index >= 0) && (index < TCHAT_MSG_SIZE) )
        byte = _buffer[index];

    return byte;
}

//------------------------------------------------------------------------------
// add_byte
//------------------------------------------------------------------------------
bool TchatBuffer::add_byte(uint8_t byte)
{
    bool rc(false);
    
    // clear if necessary
    if ( (byte == TCHAT_HEADER)
         || ( (byte == TCHAT_FOOTER) && (_index != TCHAT_MSG_SIZE-1) )
         || (_index == TCHAT_MSG_SIZE))
        clear();
    
    // set byte
    if( ((_index == 0) && (byte == TCHAT_HEADER))
        || ( (_index == TCHAT_MSG_SIZE-1) && (byte == TCHAT_FOOTER)) 
        || ( (_index !=0) && (_index != TCHAT_MSG_SIZE-1)))
        set_byte(_index++, byte);

    // return value
    if ( (_index == TCHAT_MSG_SIZE) 
         && (_buffer[0] == TCHAT_HEADER)
         && (_buffer[TCHAT_MSG_SIZE-1] == TCHAT_FOOTER) )
        rc = true;

    return rc;
}

//------------------------------------------------------------------------------
// clear
//------------------------------------------------------------------------------
void TchatBuffer::clear()
{
    for(size_t j=0; j<TCHAT_MSG_SIZE; j++)
        _buffer[j] = 0x00;

    _index = 0;
}
