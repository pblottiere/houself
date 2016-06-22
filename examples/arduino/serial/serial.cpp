#include "serial.h"
//#include "Arduino.h"
//#include <SoftwareSerial/SoftwareSerial.h>

//int led = 13;

void setup()
{
    setup_server();
    //pinMode(led, OUTPUT);
}

void loop()
{
    loop_server();
    //digitalWrite(led, HIGH);
    //delay(1000);
    //digitalWrite(led, LOW);
    //delay(1000);
}
