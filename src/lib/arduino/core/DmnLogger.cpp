#include "DmnLogger.hpp"

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
  _serial.print( "[LOG] " );
  _serial.println( msg );
}
