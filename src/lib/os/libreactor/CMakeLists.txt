set(
CMAKE_CXX_FLAGS
-std=c++11
)

set(
LIB_REACTOR_SRC
ReactorCallback.cpp
Reactor.cpp
)

add_library (os_reactor ${LIB_REACTOR_SRC})
