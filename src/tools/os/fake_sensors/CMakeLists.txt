# FLAGS
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${CURLPP_INCLUDE_DIRS})

# SOURCES
set(
BIN_FAKE_SENSORS_SRC
main.cpp
)

# BUILD BIN
add_executable(fake_sensors ${BIN_FAKE_SENSORS_SRC})
target_link_libraries(fake_sensors ${CURL_LIBRARIES} ${CURLPP_LIBRARIES})
