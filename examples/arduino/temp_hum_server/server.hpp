#ifndef SERVER_HPP
#define SERVER_HPP

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
// dominus include
#include <dominus/config.h>
#include <dominus/board/core/DmnLogger.hpp>

#include <libdht11/DHT11.hpp>
#include <libesp8266/ESP8266.hpp>

//=============================================================================
//
// Custom functions
//
//=============================================================================
void arduino_reset();
String float_to_str(const float f);
String build_json_msg(String value1);

//-----------------------------------------------------------------------------
// update_temperature
//-----------------------------------------------------------------------------
void update_temperature();

//=============================================================================
//
// Arduino builtin functions
//
//=============================================================================
void setup_server();
void loop_server();

#endif
