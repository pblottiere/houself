cmake_minimum_required (VERSION 2.6)
project (dominus)

#-------------------------------------------------------------------------------
# CMAKE PATH
#-------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#-------------------------------------------------------------------------------
# CMAKE CLI OPTIONS
#-------------------------------------------------------------------------------
option(OS_ONLY "OS_ONLY" OFF)

#-------------------------------------------------------------------------------
# ARDUINO STUFFS
#-------------------------------------------------------------------------------
set(ARDUINO_SHARE /usr/share/arduino/hardware/arduino)
set(ARDUINO_SRC ${ARDUINO_SHARE}/cores/arduino)
set(ARDUINO_PINS ${ARDUINO_SHARE}/variants/standard)
set(
ARDUINO_FLAGS 
"-mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=100 -g -Os -w -Wall -ffunction-sections -fdata-sections -I${ARDUINO_SRC} -I${ARDUINO_PINS}"
)
set(ARDUINO_CC avr-gcc)
set(ARDUINO_CXX avr-g++)
set(ARDUINO_AR avr-ar)
set(ARDUINO_OBJCOPY avr-objcopy)

#-------------------------------------------------------------------------------
# CHECK LIBS REQUIRED
#-------------------------------------------------------------------------------
find_package(ZMQ REQUIRED)
find_package(CURL REQUIRED)
find_package(CURLpp REQUIRED)

#-------------------------------------------------------------------------------
# CHECK HEADERS REQUIRED
#-------------------------------------------------------------------------------
include (CheckIncludeFiles)

if(NOT OS_ONLY)
  # arduino header
  set(ARDUINO_H "${ARDUINO_SRC}/Arduino.h")
  if(NOT EXISTS ${ARDUINO_H})
    message(FATAL_ERROR "Unable to find ${ARDUINO_SRC}/Arduino.h")
  else()
    message(STATUS "Found ${ARDUINO_H}")
  endif(NOT EXISTS ${ARDUINO_H})

  # arduino pins header
  set(ARDUINO_PINS_H "${ARDUINO_PINS}/pins_arduino.h")
  if(NOT EXISTS ${ARDUINO_PINS_H})
    message(FATAL_ERROR "Unable to find ${ARDUINO_PINS}/pins_arduino.h")
  else()
    message(STATUS "Found ${ARDUINO_PINS_H}")
  endif(NOT EXISTS ${ARDUINO_PINS_H})
endif(NOT OS_ONLY)

#-------------------------------------------------------------------------------
# CHECK BIN REQUIRED
#-------------------------------------------------------------------------------
if(NOT OS_ONLY)
  # arduino c compiler
  find_program(BIN_ARDUINO_CC ${ARDUINO_CC})
  if(NOT BIN_ARDUINO_CC)
    message(FATAL_ERROR "Unable to find '${ARDUINO_CC}' program")
  else()
    message(STATUS "Found '${ARDUINO_CC}': " ${BIN_ARDUINO_CC})
  endif(NOT BIN_ARDUINO_CC)

  # arduino cxx compiler
  find_program(BIN_ARDUINO_CXX ${ARDUINO_CXX})
  if(NOT BIN_ARDUINO_CXX)
    message(FATAL_ERROR "Unable to find '${ARDUINO_CXX}' program")
  else()
    message(STATUS "Found '${ARDUINO_CXX}': " ${BIN_ARDUINO_CXX})
  endif(NOT BIN_ARDUINO_CXX)

  # arduino ar
  find_program(BIN_ARDUINO_AR ${ARDUINO_AR})
  if(NOT BIN_ARDUINO_AR)
    message(FATAL_ERROR "Unable to find '${ARDUINO_AR}' program")
  else()
    message(STATUS "Found '${ARDUINO_AR}': " ${BIN_ARDUINO_AR})
  endif(NOT BIN_ARDUINO_AR)

  # arduino objcopy
  find_program(BIN_ARDUINO_OBJCOPY ${ARDUINO_OBJCOPY})
  if(NOT BIN_ARDUINO_OBJCOPY)
    message(FATAL_ERROR "Unable to find '${ARDUINO_OBJCOPY}' program")
  else()
    message(STATUS "Found '${ARDUINO_OBJCOPY}': " ${BIN_ARDUINO_OBJCOPY})
  endif(NOT BIN_ARDUINO_OBJCOPY)
endif(NOT OS_ONLY)

# screen
find_program(SCREEN screen)
if(NOT SCREEN)
  message(FATAL_ERROR "Unable to find 'screen' program")
else()
  message(STATUS "Found 'screen': " ${SCREEN})
endif(NOT SCREEN)

#-------------------------------------------------------------------------------
# SUBDIRS
#-------------------------------------------------------------------------------
add_subdirectory (src)
