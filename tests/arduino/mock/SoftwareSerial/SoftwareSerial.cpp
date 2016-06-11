#include "SoftwareSerial.h"
#include <iostream>

SoftwareSerial::SoftwareSerial( int rx, int tx )
  : _rx( rx )
  , _tx( tx )
  , _baudrate( 0 )
{
}

void SoftwareSerial::println( String str )
{
  std::cout << "[SoftwareSerial, " << _rx << "] " << str.c_str() << std::endl << std::endl;
}

void SoftwareSerial::print( String str )
{
  std::cout << "[SoftwareSerial, " << _rx << "] " << str.c_str() << std::endl;
}

void SoftwareSerial::begin( int baudrate )
{
  _baudrate = baudrate;
}
