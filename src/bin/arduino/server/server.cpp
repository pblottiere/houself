//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <Arduino.h>

// temperature/humidity
#include <libdht11/LibDHT11.hpp>
#include <libesp8266/LibESP8266.hpp>
#include <libtchat/TchatMsg.hpp>
#include <libtchat/TchatMsgTempHum.hpp>

#include <config.h>

//------------------------------------------------------------------------------
// global var
//------------------------------------------------------------------------------
int32_t led(13);
LibESP8266 wifi;
bool ready(false);

//==============================================================================
//
// Custom functions
//
//==============================================================================
//------------------------------------------------------------------------------
// send_buffer
//------------------------------------------------------------------------------
void send_buffer(const TchatBuffer &buffer)
{
    for(size_t j=0; j<TCHAT_MSG_SIZE; j++)
        Serial.write(buffer.get_byte(j));
}

//------------------------------------------------------------------------------
// send_tchat_msg_temperature
//------------------------------------------------------------------------------
void send_tchat_msg_temperature()
{
    // read data from sensor
    uint8_t temperature = 0x00;
    uint8_t humidity = 0x00;
    LibDHT11 dht11(5);
    dht11.get_data(temperature, humidity);

    // build msg
    TchatMsgTempHum msg;
    msg.set_type(TCHAT_TYPE_ACK);
    msg.set_target(TCHAT_TARGET_TEMP_HUM);
    msg.set_pin(5);
    msg.set_temperature(temperature);
    msg.set_humidity(humidity);
    msg.format();

    // send serial data
    send_buffer(msg.get_buffer());
}

//==============================================================================
//
// Arduino builtin functions
//
//==============================================================================
//------------------------------------------------------------------------------
// setup
//------------------------------------------------------------------------------
void setup()
{
    // init wifi
    LIB_ESP8266_ERROR err = wifi.connect(ESSID, PASSWORD);
    if (err == LIB_ESP8266_ERROR_NO_ERROR)
        ready = true;
}

//------------------------------------------------------------------------------
// loop
//------------------------------------------------------------------------------
void loop()
{
    if (ready)
    {
        // send temperature
        // send_tchat_msg_temperature();
        delay(60000);
    }
}
