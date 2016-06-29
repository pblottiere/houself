/**
 * @file DmnESP8266.hpp
 * @author Paul Blottiere
 * @date  23/06/2016
 */

#pragma once

#include <dominus/board/core/DmnWifi.hpp>

namespace dominus
{
  namespace dev
  {
    enum DMN_ESP8266_ERROR
    {
      UNKNOWN,
      NO_ERROR,
      OFFLINE,
      NOIP,
      TIMEOUT
    };

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
         */
        bool connect( String essid, String pw );

        /**
         * @brief send data over the network.
         * @param ip : IP adress where data has to be sent
         * @param port : port of the server
         * @param data : data to send over the network
         */
        bool sendDataOverNetwork( String ip, int port, String data );
    };
  }
}
