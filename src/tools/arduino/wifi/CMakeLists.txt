# BUILD STATIC LIB
libarduino_fix_flags()
include_directories (
  ${LIBESP8266_SRC_DIR}/..
)

set(
  LIB_WIFI
  ${ARDUINO_SHARE2}/SoftwareSerial/SoftwareSerial.cpp
  ${LIBCORE_SRC_FILES}
  ${LIBDHT11_SRC_DIR}/LibDHT11.cpp
  ${LIBESP8266_SRC_DIR}/LibESP8266.cpp
)
add_library (
  arduino_lib_wifi
  ${LIB_WIFI}
)

# BUILD BINARY
set(SRC wifi)
binarduino_build_cmd_cpp(
  ${SRC} 
  CMD_BUILD_D 
  CMD_BUILD_O 
  CMD_BUILD_ELF 
  CMD_BUILD_HEX
)

add_custom_target(
    ${SRC}
    ALL
    COMMAND ${CMD_BUILD_D}
    COMMAND ${CMD_BUILD_O} -I${LIBESP8266_SRC_DIR}/..
    COMMAND ${CMD_BUILD_ELF} ${CMAKE_CURRENT_BINARY_DIR}/libarduino_lib_wifi.a
    COMMAND ${CMD_BUILD_HEX}
)
