/**
 * @file DmnSerial.hpp
 * @author Paul Blottiere
 * @date  22/06/2016
 */

#pragma once

#include <dominus/board/core/DmnBrick.hpp>

namespace dominus
{
  namespace core
  {
    /**
     * @class DmnSerial
     * @brief Provide an interface to the main serial port. If a logger is provided
     * during the construction, every input/output will be logged thanks to it
     */
    class DmnSerial : public DmnBrick
    {
      public:
        /**
         * @brief Constructor
         * @param baudrate : the baudrate of the port
         * @param logger : the logger to use
         */
        DmnSerial( int baudrate, DmnLogger &logger );

        /**
         * @brief Destructor
         */
        ~DmnSerial();

        /**
         * @brief Print data on the serial port
         * @param msg
         */
        void print( String msg ) const;

      private:
        DmnLogger *_logger;
    };
  }
}
