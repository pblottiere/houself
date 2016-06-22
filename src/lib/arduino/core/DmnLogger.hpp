/**
 * \file DmnLogger.hpp
 * \author Paul Blottiere
 * \date  22/06/2016
 */

#ifndef DMNLOGGER_HPP
#define DMNLOGGER_HPP

#include <Arduino.h>
#include <SoftwareSerial/SoftwareSerial.h>

/**
 * \class DmnLogger
 * \brief The logger print a message on a software serial port
 */
class DmnLogger
{
  public:
    /**
     * \brief Constructor
     * @param rx : the receiver port of the software serial port. Not used but
     * necessary to create the software serial port
     * @param tx : the transmitter port where the message is written
     */
    DmnLogger(  int rx, int tx );

    /**
     * \brief Destructor
     */
    ~DmnLogger();

    /*
     * \brief Log a message
     * @param msg the message to print on the serial port
     */
    void log( String msg );

  private:
    SoftwareSerial _serial;
};

#endif
