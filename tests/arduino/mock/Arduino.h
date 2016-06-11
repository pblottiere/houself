#ifndef ARDUINO_H
#define ARDUINO_H

// defined
#define OUTPUT 0
#define LOW 1
#define INPUT 2
#define HIGH 3

// includes
#include <list>
#include "WString.h"

// types
typedef int byte;

// serial
class SerialLink
{
  public:
    void println( const String );
    bool find( const String );
    void begin( int );
    void setTimeout( int );

    int _speed;
    int _timeout;
};

// pin
void pinMode( int, int );
void digitalWrite( int, int );
int digitalRead( int );

// time
void delay( int );
void delayMicroseconds( int );
unsigned long micros();

// string
String dtostrf( float f, int, int, char* );

// mock arduino
void summary( int pin = -1 );

struct MockPin
{
  int pin;
  int way; // INPUT/OUTPUT
  int status; //LOW/HIGH
};

struct MockArduino
{
  std::list<MockPin*> pins;
};

// static stuff
static MockArduino mockArduino;
static SerialLink Serial;

#endif
