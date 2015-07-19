#include <Arduino.h>
#include <libdht11/DHT11.hpp>

using namespace libdht11;

//==============================================================================
//
// Cst / Dst
//
//==============================================================================
//------------------------------------------------------------------------------
// Cst
//------------------------------------------------------------------------------
DHT11::DHT11(uint8_t pin) :
    _pin(pin)
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
LIB_DHT11_ERROR DHT11::get_data(uint8_t &temperature, uint8_t &humidity)
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

    return err;
}

//==============================================================================
//
// Private methods
//
//==============================================================================
//------------------------------------------------------------------------------
// woke_up
//------------------------------------------------------------------------------
void DHT11::woke_up()
{
    pinMode(this->_pin, OUTPUT);
    digitalWrite(this->_pin, LOW);
    delay(18);                       // Wait to woke up sensor
    digitalWrite(this->_pin, HIGH);
    delayMicroseconds(40);           // Wait to woke up sensor
}

//------------------------------------------------------------------------------
// wait_reaction
//------------------------------------------------------------------------------
LIB_DHT11_ERROR DHT11::wait_reaction()
{
    pinMode(this->_pin, INPUT);

    uint32_t timeout = 0;
    while(digitalRead(this->_pin) == LOW)
        if (++timeout == 10000)
            return LIB_DHT11_ERROR_TIMEOUT;

    timeout = 0;
    while(digitalRead(this->_pin) == HIGH)
        if (++timeout == 10000)
            return LIB_DHT11_ERROR_TIMEOUT;

    return LIB_DHT11_ERROR_NO_ERROR;
}

//------------------------------------------------------------------------------
// read_data
//------------------------------------------------------------------------------
LIB_DHT11_ERROR DHT11::read_data()
{
    uint32_t timeout = 0;
    uint32_t index = 0;
    uint32_t counter = 7;

    // read 40 bits of data
    for (byte i = 0; i < 40; ++i)
    {
        // wait a LOW state
        timeout = 0;
        while(digitalRead(this->_pin) == LOW)
            if (++timeout == 10000)
                return LIB_DHT11_ERROR_TIMEOUT;

        // store current time
        unsigned long t = micros();

        // wait a HIGH state
        timeout = 0;
        while(digitalRead(this->_pin) == HIGH)
            if (++timeout == 10000)
                return LIB_DHT11_ERROR_TIMEOUT;

        if ((micros() - t) > 40)
            _buffer[index] |= (1 << counter);

        // stop
        if (counter == 0)
        {
            counter = 7; // next byte
            index++;
        }
        else
            counter--;
    }

    // checksum
    if (_buffer[4] != (_buffer[0] + _buffer[2]))
        return LIB_DHT11_ERROR_CHECKSUM;
    else
        return LIB_DHT11_ERROR_NO_ERROR;
}

