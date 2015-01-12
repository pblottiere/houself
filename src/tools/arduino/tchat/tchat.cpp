#include "Arduino.h"
#include <libtchat/TchatMsg.hpp>
#include <libtchat/TchatMsgLed.hpp>

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
// send_tchat_msg
//------------------------------------------------------------------------------
void send_tchat_msg()
{
    // build msg
    TchatMsg msg;
    msg.set_type(TCHAT_TYPE_ACK);
    msg.set_target(TCHAT_TARGET_SERVO);
    msg.format();
    
    // send serial data
    send_buffer(msg.get_buffer());
}

//------------------------------------------------------------------------------
// send_tchat_msg_led
//------------------------------------------------------------------------------
void send_tchat_msg_led()
{
    // build msg
    TchatMsgLed msg;
    msg.set_type(TCHAT_TYPE_ACK);
    msg.set_target(TCHAT_TARGET_LED);
    msg.set_pin(13);
    msg.set_status(TCHAT_LED_STATUS_ON);
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
void setup() {                 
    Serial.begin(9600);
}

//------------------------------------------------------------------------------
// loop
//------------------------------------------------------------------------------
void loop() {
    // tchat msg
    delay(1000);
    send_tchat_msg();

    // tchat msg led
    delay(1000);
    send_tchat_msg_led();
}
