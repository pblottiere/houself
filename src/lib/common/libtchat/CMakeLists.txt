set(
LIB_TCHAT_SRC
TchatBuffer.cpp
TchatMsg.cpp
TchatMsgLed.cpp
TchatMsgTemperature.cpp
TchatMsgServo.cpp
)

add_library (dominus_tchat ${LIB_TCHAT_SRC})
