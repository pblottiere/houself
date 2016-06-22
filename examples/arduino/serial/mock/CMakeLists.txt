set( CMAKE_CXX_COMPILER g++ )
add_definitions( -DMOCK )
set(CMAKE_CXX_FLAGS -std=c++11)

# BUILD STATIC LIB FOR ARDUINO
include_directories (
  ${CMAKE_SOURCE_DIR}/tests/arduino/mock
)

# BUILD BINARY
set( SRC_MOCK
  mock_serial.cpp )

add_executable( dmn_mock_serial ${SRC_MOCK} )
target_link_libraries( dmn_mock_serial mock_arduino )
