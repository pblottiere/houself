set( CMAKE_CXX_FLAGS
  -std=c++11 )

set( LIB_MOCK_ARDUINO_SRC
  Arduino.cpp
  SoftwareSerial/SoftwareSerial.cpp
  WString.cpp )

add_library ( mock_arduino SHARED ${LIB_MOCK_ARDUINO_SRC})
