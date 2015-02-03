set(
LIB_TCHAT_SRC
TchatBuffer.cpp
TchatMsg.cpp
TchatMsgLed.cpp
TchatMsgServo.cpp
)

add_library (common_tchat ${LIB_TCHAT_SRC})
