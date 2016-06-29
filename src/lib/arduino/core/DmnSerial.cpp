/**
 * @file DmnSerial.cpp
 * @author Paul Blottiere
 * @date  22/06/2016
 */

#include <dominus/board/core/DmnSerial.hpp>

using namespace dominus::core;

DmnSerial::DmnSerial( int baudrate, DmnLogger &logger )
  : DmnBrick( logger )
{
  Serial.begin(baudrate);
  Serial.setTimeout(5000);
}

DmnSerial::~DmnSerial()
{
}

void DmnSerial::print( String msg )
{
  Serial.println( msg );

  if ( _logger )
    _logger->log( msg );
}
