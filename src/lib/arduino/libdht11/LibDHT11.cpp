#include <Arduino.h>
#include <libdht11/LibDHT11.hpp>

//==============================================================================
//
// Cst / Dst
//
//==============================================================================
//------------------------------------------------------------------------------
// Cst
//------------------------------------------------------------------------------
LibDHT11::LibDHT11(uint8_t pin) : 
    _pin(pin),
    _pin_bitmask(digitalPinToBitMask(_pin)),
    _pin_port(digitalPinToPort(_pin)),
    _register_ddr(portModeRegister(_pin_port)),
    _register_out(portOutputRegister(_pin_port)),
    _register_in(portInputRegister(_pin_port))
{    
}

//==============================================================================
//
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// get_data
//------------------------------------------------------------------------------
LIB_DHT11_ERROR LibDHT11::get_data(uint8_t &temperature, uint8_t &humidity)
{
    woke_up();
    LIB_DHT11_ERROR err = wait_reaction();

    if (err == LIB_DHT11_ERROR_NO_ERROR)
    {
        err = read_data();
        
        if (err == LIB_DHT11_ERROR_NO_ERROR)
        {
            humidity = _buffer[0];
            temperature = _buffer[2];
        }
    }    
}

//==============================================================================
//
// Private methods
//
//==============================================================================
//------------------------------------------------------------------------------
// woke_up
//------------------------------------------------------------------------------
void LibDHT11::woke_up()
{
    *_register_ddr |= _pin_bitmask;  // OUTPUT
    *_register_out &= ~_pin_bitmask; // LOW
    delay(18);                       // Wait to woke up sensor
    *_register_out |= _pin_bitmask;  // HIGH
    delayMicroseconds(40);           // Wait to woke up sensor 
}

//------------------------------------------------------------------------------
// wait_reaction
//------------------------------------------------------------------------------
LIB_DHT11_ERROR LibDHT11::wait_reaction()
{
    *_register_ddr &= ~_pin_bitmask; // INPUT
    
    uint32_t timeout = 0;
    while(!(*_register_in & _pin_bitmask)) // wait a LOW state
        if (++timeout == 10000)
            return LIB_DHT11_ERROR_TIMEOUT;
    
    timeout = 0;
    while(*_register_in & _pin_bitmask) // wait a HIGH state
        if (++timeout == 10000)
            return LIB_DHT11_ERROR_TIMEOUT;

    return LIB_DHT11_ERROR_NO_ERROR;
}

//------------------------------------------------------------------------------
// read_data
//------------------------------------------------------------------------------
LIB_DHT11_ERROR LibDHT11::read_data()
{
    uint32_t timeout = 0;
    uint32_t index = 0;
    uint32_t counter = 7;

    // read 40 bits of data
    for (byte i = 0; i < 40; ++i) 
    {
        // wait a LOW state
        timeout = 0;
        while(!(*_register_in & _pin_bitmask))
            if (++timeout == 10000)
                return LIB_DHT11_ERROR_TIMEOUT;
 
        // store current time
        unsigned long t = micros();
 
        // wait a HIGH state
        timeout = 0;
        while(*_register_in & _pin_bitmask)
            if (++timeout == 10000)
                return LIB_DHT11_ERROR_TIMEOUT;
 
        // /\* Si le delta Temps est supérieur à 40µS c'est un "1", sinon c'est un "0" *\/
        if ((micros() - t) > 40)
            _buffer[index] |= (1 << counter); // "1"
 
        // stop
        if (counter-- == 0) 
        {
            counter = 7; // next byte
            ++index;
        }
    }

    // checksum
    if (_buffer[4] != (_buffer[0] + _buffer[2]))
        return LIB_DHT11_ERROR_CHECKSUM; 
    else
        return LIB_DHT11_ERROR_NO_ERROR; 
}

