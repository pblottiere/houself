libarduino_fix_flags()

include_directories (
  ${DOMINUS_INCLUDE_DIR}
)

set (
  LIB_DOMINUS_ESP8266_SRC
  DmnESP8266.cpp
)

add_library (
  dominusdev_esp8266
  ${LIB_DOMINUS_ESP8266_SRC}
)
