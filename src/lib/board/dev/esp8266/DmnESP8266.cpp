/**
 * @file DmnESP8266.cpp
 * @author Paul Blottiere
 * @date  23/06/2016
 */

#include <dominus/board/dev/esp8266/DmnESP8266.hpp>

// internal
#include "DmnESP8266Message.hpp"

using namespace dominus::dev;
using namespace dominus::core;

DmnESP8266::DmnESP8266( DmnLogger &logger )
  : DmnWifi( 9600, logger )
  , _retry( 10 )
{
}

DMN_WIFI_ERROR DmnESP8266::connect( String essid, String pw )
{
  DMN_WIFI_ERROR err = DMN_WIFI_ERROR_NO_ERROR;

  if ( (err = is_online()) == DMN_WIFI_ERROR_NO_ERROR )
    err = get_ip( essid, pw );

  return err;
}

bool DmnESP8266::send( String ip, int port, String data )
{
  bool rc = false;

  for (int i=0; i<_retry; i++)
  {
    // open TCP connection
    MessageOpenLink cmd( ESP8266_MODE_TCP, ip, port );
    if ( ! write_and_wait_ack( cmd ) ) // do not want to receive Error ack
    {
      String http_msg = "GET /" + data + ";1 HTTP/1.0\r\n\r\n";
      MessageSendData send_data_cmd( http_msg );

      if ( write_and_wait_ack( send_data_cmd.get_part1(),
            send_data_cmd.ack() ) )
      {
        write_and_wait_ack( send_data_cmd.get_part2(), send_data_cmd.ack() );
        break;
      }
      else
      {
        // close the connection
        MessageCloseConnection close_cmd;
        write_and_wait_ack( close_cmd );
      }
    }
  }

  return rc;
}

void DmnESP8266::reset()
{
    MessageReset rst;
    write_and_wait_ack( rst );
}

DMN_WIFI_ERROR DmnESP8266::is_online() const
{
  DMN_WIFI_ERROR err = DMN_WIFI_ERROR_OFFLINE;

  for (int i=0; i<_retry; i++)
  {
    MessageTest cmd;
    if ( write_and_wait_ack( cmd ) )
    {
      err = DMN_WIFI_ERROR_NO_ERROR;
      break;
    }
  }

  // return
  return err;
}

DMN_WIFI_ERROR DmnESP8266::get_ip( const String &essid, const String &pw )
{
  DMN_WIFI_ERROR err = DMN_WIFI_ERROR_NOIP;

  // try to get an IP
  for (int i=0; i<_retry; i++)
  {
    // set wifi mode Station + Access Point
    MessageWifiMode mode_cmd( ESP8266_WIFI_MODE_BOTH );
    write_and_wait_ack( mode_cmd );

    // join access point
    MessageJoinAP join_ap_cmd( essid, pw );
    if ( write_and_wait_ack( join_ap_cmd ) )
    {
      // single mode connection
      MessageConnectionMode conn_cmd( ESP8266_CONNECTION_MODE_SINGLE );
      write_and_wait_ack( conn_cmd );

      // set err and break loop
      err = DMN_WIFI_ERROR_NO_ERROR;
      break;
    }
  }

  return err;
}

bool DmnESP8266::write_and_wait_ack( const Message &msg ) const
{
  return write_and_wait_ack( msg.data(), msg.ack() );
}

bool DmnESP8266::write_and_wait_ack( const String &msg,
    const String &ack ) const
{
  bool rc = false;

  char ack_ptr [sizeof( ack ) ];
  ack.toCharArray( ack_ptr, sizeof( ack_ptr ) );

  print( msg );
  delay( 3000 );

  // search the acknowledgement
  if ( Serial.find( ack_ptr ) )
      rc = true;

  return rc;
}
