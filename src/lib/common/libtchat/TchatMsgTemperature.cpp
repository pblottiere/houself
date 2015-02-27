#include <libtchat/TchatMsgTemperature.hpp>

//==============================================================================
//
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// set_temperature
//------------------------------------------------------------------------------
void TchatMsgTemperature::set_pin(uint8_t pin)
{
    _buffer.set_byte(TCHAT_POSITION_TEMPERATURE_PIN, pin);
}

//------------------------------------------------------------------------------
// get_pin
//------------------------------------------------------------------------------
uint8_t TchatMsgTemperature::get_pin()
{
    return (uint8_t) _buffer.get_byte(TCHAT_POSITION_TEMPERATURE_PIN);
}

//------------------------------------------------------------------------------
// get_temperature
//------------------------------------------------------------------------------
uint8_t TchatMsgTemperature::get_temperature()
{
    return _buffer.get_byte(TCHAT_POSITION_TEMPERATURE_STATUS);
}
