#include <libtchat/TchatMsgTempHum.hpp>

//==============================================================================
//
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// set_temp_hum
//------------------------------------------------------------------------------
void TchatMsgTempHum::set_pin(uint8_t pin)
{
    _buffer.set_byte(TCHAT_POSITION_TEMP_HUM_PIN, pin);
}

//------------------------------------------------------------------------------
// get_pin
//------------------------------------------------------------------------------
uint8_t TchatMsgTempHum::get_pin()
{
    return (uint8_t) _buffer.get_byte(TCHAT_POSITION_TEMP_HUM_PIN);
}

//------------------------------------------------------------------------------
// get_temperature
//------------------------------------------------------------------------------
uint8_t TchatMsgTempHum::get_temperature()
{
    return _buffer.get_byte(TCHAT_POSITION_TEMP_HUM_TEMPERATURE_VALUE);
}

//------------------------------------------------------------------------------
// get_humidity
//------------------------------------------------------------------------------
uint8_t TchatMsgTempHum::get_humidity()
{
    return _buffer.get_byte(TCHAT_POSITION_TEMP_HUM_HUMIDITY_VALUE);
}

//------------------------------------------------------------------------------
// set_temperature
//------------------------------------------------------------------------------
void TchatMsgTempHum::set_temperature(uint8_t temp)
{
    _buffer.set_byte(TCHAT_POSITION_TEMP_HUM_TEMPERATURE_VALUE, temp);
}

//------------------------------------------------------------------------------
// set_humidity
//------------------------------------------------------------------------------
void TchatMsgTempHum::set_humidity(uint8_t hum)
{
    _buffer.set_byte(TCHAT_POSITION_TEMP_HUM_HUMIDITY_VALUE, hum);
}
