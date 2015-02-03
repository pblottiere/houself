cmake_minimum_required (VERSION 2.6)
project (dominus)

# CMAKE PATH
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ARDUINO STUFFS
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

# CHECK REQUIRED
find_package(ZMQ REQUIRED)

# SUBDIRS
add_subdirectory (src)
