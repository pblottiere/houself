#ifndef SERVER_HPP
#define SERVER_HPP

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
// global include
#include <Arduino.h>
#include <SoftwareSerial/SoftwareSerial.h>

// dominus include
#include <libdht11/DHT11.hpp>
#include <libesp8266/ESP8266.hpp>
#include <config.h>

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
