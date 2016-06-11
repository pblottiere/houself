cmake_minimum_required (VERSION 2.6)
project (dominus)

#------------------------------------------------------------------------------
# CMAKE CLI OPTIONS
#------------------------------------------------------------------------------
option(OS_ONLY "OS_ONLY" OFF)

#------------------------------------------------------------------------------
# CMAKE CUSTOM COMMANDS
#------------------------------------------------------------------------------
# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

#------------------------------------------------------------------------------
# CMAKE CONFIGURATION FILE
#------------------------------------------------------------------------------
SET( ESSID "YOUR_ESSID" CACHE STRING "Access point name")
SET( PASSWORD "YOUR_PASSWORD" CACHE STRING "Wifi password")
SET( SERVER_IP "SERVER_IP" CACHE STRING "The domoticz server IP")
SET( SERVER_PORT "SERVER_PORT" CACHE STRING "The dommoticz server port")
CONFIGURE_FILE(
    ${CMAKE_SOURCE_DIR}/config.h.cmake
    ${CMAKE_SOURCE_DIR}/config.h
)

#------------------------------------------------------------------------------
# ARDUINO STUFFS
#------------------------------------------------------------------------------
# global vars
set(ARDUINO_SHARE /usr/share/arduino/hardware/arduino)
set(ARDUINO_SHARE2 /usr/share/arduino/libraries)
set(ARDUINO_SRC ${ARDUINO_SHARE}/cores/arduino)
set(ARDUINO_PINS ${ARDUINO_SHARE}/variants/standard)
set(ARDUINO_FLAGS_LIST "-mmcu=atmega328p;-DF_CPU=16000000L;-DARDUINO=100;-g;-Os;-w;-Wall;-ffunction-sections;-fdata-sections;-I${ARDUINO_SRC};-I${ARDUINO_PINS};-I${ARDUINO_SHARE2}"
)
string(REGEX REPLACE ";" " " ARDUINO_FLAGS_STR "${ARDUINO_FLAGS_LIST}")

# flags
set(ARDUINO_C_FLAGS_LIB "-c ${ARDUINO_FLAGS_STR} -std=gnu99")
set(ARDUINO_CXX_FLAGS_LIB "${ARDUINO_FLAGS_STR} -fno-exceptions")
set(ARDUINO_AR_FLAGS_LIB "rcs")

# compilers
set(ARDUINO_CC avr-gcc)
set(ARDUINO_CXX avr-g++)
set(ARDUINO_AR avr-ar)
set(ARDUINO_OBJCOPY avr-objcopy)

#------------------------------------------------------------------------------
# CMAKE PATH
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)

set (SERVER_SRC_DIR ${PROJECT_SOURCE_DIR}/src/bin/arduino/server)

set (COMMON_SRC_DIR ${PROJECT_SOURCE_DIR}/src/lib/common)

set (MOCK_SRC_DIR ${PROJECT_SOURCE_DIR}/tests/arduino/mock)

set (TCHAT_SRC_DIR ${COMMON_SRC_DIR}/libtchat)

set (LIBCORE_SRC_DIR ${PROJECT_BINARY_DIR}/src/lib/arduino/libcore/)
set (
  LIBCORE_SRC_FILES
  ${ARDUINO_SRC}/WInterrupts.c
  ${ARDUINO_SRC}/wiring_analog.c
  ${ARDUINO_SRC}/wiring.c
  ${ARDUINO_SRC}/wiring_digital.c
  ${ARDUINO_SRC}/wiring_pulse.c
  ${ARDUINO_SRC}/wiring_shift.c
  ${ARDUINO_SRC}/CDC.cpp
  ${ARDUINO_SRC}/HardwareSerial.cpp
  ${ARDUINO_SRC}/HID.cpp
  ${ARDUINO_SRC}/IPAddress.cpp
  ${ARDUINO_SRC}/main.cpp
  ${ARDUINO_SRC}/new.cpp
  ${ARDUINO_SRC}/Print.cpp
  ${ARDUINO_SRC}/Stream.cpp
  ${ARDUINO_SRC}/Tone.cpp
  ${ARDUINO_SRC}/USBCore.cpp
  ${ARDUINO_SRC}/WMath.cpp
  ${ARDUINO_SRC}/WString.cpp
)

set (LIBDHT11_SRC_DIR ${PROJECT_SOURCE_DIR}/src/lib/arduino/libdht11/)
set (LIBDHT11_BUILD_DIR ${PROJECT_BINARY_DIR}/src/lib/arduino/libdht11/)

set (LIBESP8266_SRC_DIR ${PROJECT_SOURCE_DIR}/src/lib/arduino/libesp8266/)
set (LIBESP8266_BUILD_DIR ${PROJECT_BINARY_DIR}/src/lib/arduino/libesp8266/)

#------------------------------------------------------------------------------
# MACRO
#------------------------------------------------------------------------------
# fix compiler and flags to compile a static arduino lib
macro (libarduino_fix_flags)
    # fix compiler
    set(CMAKE_C_COMPILER ${ARDUINO_CC})
    set(CMAKE_CXX_COMPILER ${ARDUINO_CXX})
    set(CMAKE_AR ${ARDUINO_AR})

    # fix flags
    set(CMAKE_C_FLAGS ${ARDUINO_C_FLAGS_LIB})
    set(CMAKE_CXX_FLAGS ${ARDUINO_CXX_FLAGS_LIB})
    set(CMAKE_AR_FLAGS ${ARDUINO_AR_FLAGS_LIB})
endmacro ()

# build command to compile c files with arduino compiler
macro (binarduino_build_cmd_c SRC CMD_BUILD_D CMD_BUILD_O CMD_BUILD_ELF CMD_BUILD_HEX)
  set (${CMD_BUILD_D} ${ARDUINO_CC} -MM ${ARDUINO_FLAGS_LIST} -I. -std=gnu99 ${CMAKE_CURRENT_SOURCE_DIR}/${SRC}.c -MF ${SRC}.d -MT ${SRC}.o)
  set (${CMD_BUILD_O} ${ARDUINO_CC} -c ${ARDUINO_FLAGS_LIST} -I. -I${CMAKE_SOURCE_DIR}/ -std=gnu99 ${CMAKE_CURRENT_SOURCE_DIR}/${SRC}.c -o ${SRC}.o)
  set (${CMD_BUILD_ELF} ${ARDUINO_CC} -mmcu=atmega328p -Wl,--gc-sections -Os -o ${SRC}.elf ${SRC}.o -lc -lm)
  set (${CMD_BUILD_HEX} ${ARDUINO_OBJCOPY} -O ihex -R .eeprom ${SRC}.elf ${SRC}.hex)
endmacro()

# build command to compile cpp files with arduino compiler
macro (binarduino_build_cmd_cpp SRC CMD_BUILD_D CMD_BUILD_O CMD_BUILD_ELF CMD_BUILD_HEX)
    set(${CMD_BUILD_D} ${ARDUINO_CXX} -MM ${ARDUINO_FLAGS_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/${SRC}.cpp -MF ${SRC}.d -MT ${SRC}.o)
    set(${CMD_BUILD_O} ${ARDUINO_CXX} -I${CMAKE_SOURCE_DIR}/ -c ${ARDUINO_FLAGS_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/${SRC}.cpp -o ${SRC}.o)
    set(${CMD_BUILD_ELF} ${ARDUINO_CXX} -mmcu=atmega328p -Wl,--gc-sections -Os -o ${SRC}.elf ${SRC}.o -lc -lm)
    set(${CMD_BUILD_HEX} ${ARDUINO_OBJCOPY} -O ihex -R .eeprom ${SRC}.elf ${SRC}.hex)
endmacro()

#------------------------------------------------------------------------------
# CHECK LIBS REQUIRED
#------------------------------------------------------------------------------
find_package(ZMQ REQUIRED)
find_package(CURL REQUIRED)
find_package(CURLpp REQUIRED)

#------------------------------------------------------------------------------
# CHECK HEADERS REQUIRED
#------------------------------------------------------------------------------
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

#------------------------------------------------------------------------------
# CHECK BIN REQUIRED
#------------------------------------------------------------------------------
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

#------------------------------------------------------------------------------
# SUBDIRS
#------------------------------------------------------------------------------
add_subdirectory (etc)
add_subdirectory (src)
add_subdirectory (tests)
add_subdirectory (tools)
