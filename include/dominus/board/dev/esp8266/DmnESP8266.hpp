/**
 * @file DmnESP8266.hpp
 * @author Paul Blottiere
 * @date  23/06/2016
 */

#pragma once

#include <dominus/board/core/DmnWifi.hpp>

class Message;

namespace dominus
{
  namespace dev
  {
    /**
     * @class DmnESP8266
     * @brief Implements the wifi brick for the ESP8266 device.
     */
    class DmnESP8266 : public dominus::core::DmnWifi
    {
      public:
        /**
         * @brief Constructor
         * @param logger : the logger to use
         */
        DmnESP8266( dominus::core::DmnLogger &logger );

        /**
         * @brief connect the device to a wifi network
         * @param essid : the ESSID of the network
         * @param pw : the password
         * @return a DMN_WIFI_ERROR
         */
        core::DMN_WIFI_ERROR connect( String essid, String pw ) override;

        /**
         * @brief send data over the network.
         * @param ip : IP adress where data has to be sent
         * @param port : port of the server
         * @param data : data to send over the network
         */
        bool send( String ip, int port, String data ) override;

        /**
         * @brief Reset the chipset
         */
        void reset();

      private:
        core::DMN_WIFI_ERROR is_online() const;
        core::DMN_WIFI_ERROR get_ip( const String &essid, const String &pw );
        bool write_and_wait_ack( const String &msg, const String &ack ) const;
        bool write_and_wait_ack( const Message &msg ) const;

        int32_t _retry;
    };
  }
}
