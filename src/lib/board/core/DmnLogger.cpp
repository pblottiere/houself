/**
 * @file DmnLogger.cpp
 * @author Paul Blottiere
 * @date  22/06/2016
 */

#include <dominus/board/core/DmnLogger.hpp>

using namespace dominus::core;

DmnLogger::DmnLogger(  int rx, int tx ) :
  _serial( rx, tx )
{
  _serial.begin( 9600 );
}

DmnLogger::~DmnLogger()
{
}

void DmnLogger::log( String msg )
{
  _serial.print( "[LOG] " + msg );
}
