/**
 * @file DmnWifi.hpp
 * @author Paul Blottiere
 * @date  23/06/2016
 */

#pragma once

#include <dominus/board/core/DmnSerial.hpp>

/**
 * @class DmnWifi
 * @brief Wifi brick.
 */
namespace dominus
{
  namespace core
  {
    class DmnWifi : public DmnSerial
    {
      public:
        /**
         * @brief Constructor
         * @param baudrate : the baudrate of the port
         * @param logger : the logger to use
         */
        DmnWifi( int baudrate, DmnLogger &logger );

        /**
         * @brief connect the device to a wifi network
         * @param essid : the ESSID of the network
         * @param pw : the password
         */
        virtual bool connect( String essid, String pw ) = 0;

        /**
         * @brief send data over the network.
         * @param ip : IP adress where data has to be sent
         * @param port : port of the server
         * @param data : data to send over the network
         */
        virtual bool sendDataOverNetwork( String ip, int port, String data ) = 0;

      protected:
        bool _connected;
    };
  }
}
