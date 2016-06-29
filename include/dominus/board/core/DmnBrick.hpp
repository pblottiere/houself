/**
 * @file DmnBrick.hpp
 * @author Paul Blottiere
 * @date  23/06/2016
 */

#pragma once

#include <dominus/board/core/DmnLogger.hpp>

namespace dominus
{
  namespace core
  {
    /**
     * @class DmnBrick
     * @brief Brick of base for all Dominus element
     */
    class DmnBrick
    {
      public:
        /**
         * @brief Constructor
         */
        DmnBrick();

        /**
         * @brief Constructor
         * @param logger : the logger to use
         */
        DmnBrick( DmnLogger &logger );

      private:
        DmnLogger *_logger;
    };
  }
}
