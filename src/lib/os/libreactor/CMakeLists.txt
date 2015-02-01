set(
CMAKE_CXX_FLAGS
-std=c++11
)

set(
LIB_REACTOR_SRC
ReactorCallback.cpp
Reactor.cpp
)

add_library (libreactor ${LIB_REACTOR_SRC})
