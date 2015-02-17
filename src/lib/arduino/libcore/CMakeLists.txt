# FIX COMPILER/FLAGS
libarduino_fix_flags()
include_directories (${CMAKE_CURRENT_SOURCE_DIR})

# SOURCES
set(
  LIB_CORE_SRC
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

# BUILD LIB
add_library (arduino_core ${LIB_CORE_SRC})