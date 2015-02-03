set(
LIB_TCHAT_SRC
TchatBuffer.cpp
TchatMsg.cpp
TchatMsgLed.cpp
TchatMsgServo.cpp
)

add_library (dominus_tchat ${LIB_TCHAT_SRC})
