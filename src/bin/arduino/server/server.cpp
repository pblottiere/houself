//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include "Arduino.h"

// temperature/humidity
#include <libdht11/LibDHT11.hpp>
#include <libtchat/TchatMsg.hpp>
#include <libtchat/TchatMsgTempHum.hpp>

int led = 13;

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
    // init serial line   
    pinMode(led, OUTPUT);  
    Serial.begin(9600);

    if(Serial)
        digitalWrite(led, HIGH);
}

//------------------------------------------------------------------------------
// loop
//------------------------------------------------------------------------------
void loop() 
{
    // digitalWrite(led, HIGH);
    // delay(1000);
    // digitalWrite(led, LOW);
    // delay(1000);

    // 
    send_tchat_msg_temperature();
    delay(2000);
}
