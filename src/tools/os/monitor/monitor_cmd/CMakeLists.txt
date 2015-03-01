# FLAGS
include_directories (${CMAKE_SOURCE_DIR}/src/lib/common)
include_directories (${CMAKE_SOURCE_DIR}/src/lib/os)
include_directories(${ZMQ_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS -std=c++11)

# SOURCES
set(
  BIN_MONITOR_CMD_SRC
  main.cpp
)

# BUILD BIN
add_executable(dominus_monitor_cmd ${BIN_MONITOR_CMD_SRC})
target_link_libraries(
  dominus_monitor_cmd
  ${ZMQ_LIBRARIES} 
  dominus_reactor 
  dominus_serial 
  dominus_tchat
)

# INSTALL BIN
install (PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/dominus_monitor_cmd DESTINATION bin)