#ifndef LIB_DHT11
#define LIB_DHT11

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <stdint.h>
#include "Arduino.h"

//------------------------------------------------------------------------------
// enum, const
//------------------------------------------------------------------------------
const int32_t LIB_DHT11_BUFFER_SIZE = 5;

enum LIB_DHT11_ERROR
{
    LIB_DHT11_ERROR_UNKNOWN,
    LIB_DHT11_ERROR_NO_ERROR,
    LIB_DHT11_ERROR_TIMEOUT,
    LIB_DHT11_ERROR_CHECKSUM
};

//------------------------------------------------------------------------------
// Class LibDHT11
//------------------------------------------------------------------------------
namespace libdht11 {
    class DHT11
    {
    public:
        DHT11(uint8_t pin);

        LIB_DHT11_ERROR get_data(uint8_t &temperature, uint8_t &humidity);

    private:
        // methods
        void woke_up();
        LIB_DHT11_ERROR wait_reaction();
        LIB_DHT11_ERROR read_data();

        // attr
        uint8_t _pin;
        uint8_t _pin_bitmask;
        uint8_t _pin_port;
        volatile uint8_t *_register_ddr;
        volatile uint8_t *_register_out;
        volatile uint8_t *_register_in;
        uint8_t _buffer[LIB_DHT11_BUFFER_SIZE] = {};
    };
}

#endif
