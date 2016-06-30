set( CMAKE_CXX_COMPILER g++ )
add_definitions( -DMOCK )
set(CMAKE_CXX_FLAGS -std=c++11)

# BUILD STATIC LIB FOR ARDUINO
include_directories (
  ${CMAKE_SOURCE_DIR}
  ${COMMON_SRC_DIR}
  ../
  ${CMAKE_SOURCE_DIR}/tests/arduino/mock
  ${LIBDHT11_SRC_DIR}/..
  ${LIBESP8266_SRC_DIR}/..
)

# BUILD BINARY
set(SRC
  ${TCHAT_SRC_DIR}/TchatMsg.cpp
  ${TCHAT_SRC_DIR}/TchatBuffer.cpp
  ${TCHAT_SRC_DIR}/TchatMsgTempHum.cpp
  ${LIBDHT11_SRC_DIR}/DHT11.cpp
  ${LIBESP8266_SRC_DIR}/ESP8266.cpp
  ${DOMINUS_CORE_DIR}/DmnLogger.cpp
  ../server.cpp
  main.cpp)

add_executable( dmn_mock_server ${SRC} )
target_link_libraries( dmn_mock_server mock_arduino )
