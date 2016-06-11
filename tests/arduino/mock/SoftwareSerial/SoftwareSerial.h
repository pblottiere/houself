#ifndef SOFTWARESERIAL_H
#define SOFTWARESERIAL_H

#include "../WString.h"

class SoftwareSerial
{
  public:
    SoftwareSerial( int rx, int tx );

    void println( String str = "" );
    void print( String str );
    void begin( int baudrate );

  private:
    int _baudrate;
    int _rx;
    int _tx;
};

#endif
