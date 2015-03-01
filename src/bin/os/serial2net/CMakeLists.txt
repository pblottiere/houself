# FLAGS
include_directories (${CMAKE_SOURCE_DIR}/src/lib/os)
set(
  CMAKE_CXX_FLAGS
  -std=c++11
)

# SOURCES
set(
  BIN_SERIAL_NET_SRC
  main.cpp
  FromNetToSerialCB.cpp
)

# BUILD BIN
add_executable(dominus_serial2net ${BIN_SERIAL_NET_SRC})
target_link_libraries(
  dominus_serial2net 
  ${ZMQ_LIBRARIES} 
  dominus_serial
  dominus_reactor
)

# INSTALL BIN
install (PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/dominus_serial2net DESTINATION bin)