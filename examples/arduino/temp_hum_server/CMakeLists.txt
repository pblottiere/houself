# BUILD STATIC LIB FOR ARDUINO
libarduino_fix_flags()
include_directories (
  ${DOMINUS_INCLUDE_DIR}
  ${COMMON_SRC_DIR}
  ${LIBDHT11_SRC_DIR}/..
)

set(
  LIB_ARDUINO_SERVER_SRC
  ${TCHAT_SRC_DIR}/TchatMsg.cpp
  ${TCHAT_SRC_DIR}/TchatBuffer.cpp
  ${TCHAT_SRC_DIR}/TchatMsgTempHum.cpp
  ${LIBDHT11_SRC_DIR}/DHT11.cpp
  ${LIBESP8266_SRC_DIR}/ESP8266.cpp
  server.cpp
)
add_library (
  arduino_server
  ${LIB_ARDUINO_SERVER_SRC}
)

# BUILD BINARY
set(SRC main)

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
    COMMAND ${CMD_BUILD_O} -I${LIBDHT11_SRC_DIR}/.. -I${DOMINUS_INCLUDE_DIR}
    COMMAND ${CMD_BUILD_ELF} ${CMAKE_CURRENT_BINARY_DIR}/libarduino_server.a ${CMAKE_CURRENT_BINARY_DIR}/../../../src/lib/arduino/core/libdominuscore.a
    COMMAND ${CMD_BUILD_HEX}
)

add_subdirectory( mock )
