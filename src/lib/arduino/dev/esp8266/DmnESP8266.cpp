/**
 * @file DmnESP8266.cpp
 * @author Paul Blottiere
 * @date  23/06/2016
 */

#include <dominus/board/dev/esp8266/DmnESP8266.hpp>

using namespace dominus::dev;
using namespace dominus::core;

DmnESP8266::DmnESP8266( DmnLogger &logger )
  : DmnWifi( 9600, logger )
{
}

bool DmnESP8266::connect( String essid, String pw )
{
  bool rc = false;

  return rc;
}

bool DmnESP8266::sendDataOverNetwork( String ip, int port, String data )
{
  bool rc = false;

  return rc;
}
