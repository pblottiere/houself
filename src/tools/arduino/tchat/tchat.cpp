#include "Arduino.h"
#include <libtchat/TchatMsg.hpp>
 
void setup() {                 
    Serial.begin(9600);
}

void loop() {
    // periodic
    delay(1000);
    
    // build msg
    TchatMsg msg;
    msg.set_type(TCHAT_TYPE_ACK);
    msg.set_target(TCHAT_TARGET_SERVO);
    
    // send serial data
    //for(size_t j=0; j<TCHAT_MSG_SIZE; j++)
    //    Serial.write(msg.get_buffer().get_byte(j));

    Serial.write(msg.get_target());
    Serial.write(msg.get_type());
}
