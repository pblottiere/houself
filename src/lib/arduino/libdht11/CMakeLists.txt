# FIX COMPILER/FLAGS
libarduino_fix_flags()
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/..)

# SOURCES
set(
  LIB_DHT11_SRC
  LibDHT11.cpp
)

# BUILD LIB
add_library (arduino_dht11 ${LIB_DHT11_SRC})