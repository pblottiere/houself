# FLAGS
include_directories (${CMAKE_SOURCE_DIR}/src/lib/common)
include_directories (${CMAKE_SOURCE_DIR}/src/lib/os)
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${CURLPP_INCLUDE_DIRS})
include_directories(${ZMQ_INCLUDE_DIRS})

# SOURCES
set(
  BIN_MONITOR_SRC
  DominusCallback.cpp
  main.cpp
)

# BUILD BIN
add_executable(dominus ${BIN_MONITOR_SRC})
target_link_libraries(
  dominus
  ${CURL_LIBRARIES} 
  ${CURLPP_LIBRARIES}
  ${ZMQ_LIBRARIES} 
  dominus_reactor 
  dominus_serial 
  dominus_tchat
)

# INSTALL BIN
install (PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/dominus DESTINATION bin)
