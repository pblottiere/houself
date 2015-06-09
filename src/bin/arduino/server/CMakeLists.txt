# BUILD STATIC LIB FOR ARDUINO
libarduino_fix_flags()
include_directories (
  ${COMMON_SRC_DIR}
  ${LIBDHT11_SRC_DIR}/..
  ${LIBESP8266_SRC_DIR}/..
  ${ARDUINO_SHARE2}/SoftwareSerial
)

set(
  LIB_ARDUINO_SERVER_SRC
  ${ARDUINO_SHARE2}/SoftwareSerial/SoftwareSerial.cpp
  ${LIBCORE_SRC_FILES}
  ${TCHAT_SRC_DIR}/TchatMsg.cpp
  ${TCHAT_SRC_DIR}/TchatBuffer.cpp
  ${TCHAT_SRC_DIR}/TchatMsgTempHum.cpp
  ${LIBDHT11_SRC_DIR}/DHT11.cpp
  ${LIBESP8266_SRC_DIR}/ESP8266.cpp
)
add_library (
  arduino_server
  ${LIB_ARDUINO_SERVER_SRC}
)

# BUILD BINARY
set(SRC server)
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
    COMMAND ${CMD_BUILD_O} -I${COMMON_SRC_DIR} -I${LIBDHT11_SRC_DIR}/.. -I.
    COMMAND ${CMD_BUILD_ELF} ${CMAKE_CURRENT_BINARY_DIR}/libarduino_server.a
    COMMAND ${CMD_BUILD_HEX}
)
