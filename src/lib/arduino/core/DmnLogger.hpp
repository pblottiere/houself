#ifndef DMNLOGGER_HPP
#define DMNLOGGER_HPP

#include <Arduino.h>
#include <SoftwareSerial/SoftwareSerial.h>

class DmnLogger
{
  public:
    DmnLogger(  int rx, int tx );
    ~DmnLogger();

    void log( String msg );

  private:
    SoftwareSerial _serial;
};

#endif
