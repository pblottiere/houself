/**
 * @file DmnWifi.cpp
 * @author Paul Blottiere
 * @date  23/06/2016
 */

#include <dominus/board/core/DmnWifi.hpp>

using namespace dominus::core;

DmnWifi::DmnWifi( int baudrate, DmnLogger &logger )
  : DmnSerial( baudrate, logger )
  , _connected( false )
{
}
