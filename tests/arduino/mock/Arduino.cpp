#include "Arduino.h"
#include <iostream>
#include <unistd.h>

void summary( int spin )
{
  std::list<MockPin*> pins = mockArduino.pins;
  for ( MockPin *pin : pins )
  {
    if ( spin == -1 || spin == pin->pin )
    {
      std::string way = "INPUT";
      if ( pin->way == OUTPUT )
        way = "OUTPUT";

      std::string status = "HIGH";
      if ( pin->status == LOW )
        status = "LOW";

      std::cout << "[MockArduino, " << pin->pin << ", " << way << ", "
        << status << "]" << std::endl;
    }
  }

  std::cout << std::endl;
}

// serial
void SerialLink::println( const String str )
{
  std::cout << "[Serial, " << _speed << ", " << _timeout << "] "
    << str.c_str() << std::endl;
};

bool SerialLink::find( const String ack )
{
  std::string ack_str = ack.c_str();
  if ( ack_str == "Error" )
    return false;
  else if ( ack_str == ">" )
    return true;
  else
    return true;
};

void SerialLink::begin( int speed )
{
  _speed = speed;
};

void SerialLink::setTimeout( int timeout )
{
  _timeout = timeout;
};

// pin
void pinMode( int p, int w )
{
  MockPin *pin = new MockPin;
  pin->pin = p;
  pin->way = w;

  mockArduino.pins.insert( mockArduino.pins.begin(), pin );
  summary( p );
}

void digitalWrite( int p, int status )
{
  std::list<MockPin*> pins = mockArduino.pins;
  for ( MockPin *pin : pins )
    if ( pin->pin == p )
      pin->status = status;

  summary( p );
}

int digitalRead( int )
{
}

// time
void delay( int sec )
{
  std::cout << "[MockArduino] delay for " << sec << " sec" << std::endl;
  sleep(1);
}

void delayMicroseconds( int msec )
{
  std::cout << "[MockArduino] delay for " << msec << " msec" << std::endl;
  sleep(1);
}

unsigned long micros()
{
}

// string
String dtostrf( float f, int, int, char* val )
{
  std::string stdstr = std::to_string( f );
  strcpy( val, stdstr.c_str());
  return stdstr.c_str();
}
