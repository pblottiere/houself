#include <Arduino.h>
#include <SoftwareSerial/SoftwareSerial.h>

int led = 13;

void setup_server()
{
  pinMode(led, OUTPUT);
  Serial.begin( 9600 );
}

void loop_server()
{
  Serial.println( "COUCOU" );
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}
