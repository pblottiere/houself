# BUILD STATIC LIB FOR ARDUINO
libarduino_fix_flags()

include_directories(
  ${DOMINUS_INCLUDE_DIR}
  ${ARDUINO_SHARE2}/SoftwareSerial
  )

set(
  LIB_ARDUINO_DOMINUS_CORE_SRC
  ${LIBCORE_SRC_FILES}
  ${ARDUINO_SHARE2}/SoftwareSerial/SoftwareSerial.cpp
  ${DOMINUS_CORE_DIR}/DmnBrick.cpp
  ${DOMINUS_CORE_DIR}/DmnLogger.cpp
  ${DOMINUS_CORE_DIR}/DmnSerial.cpp
  ${DOMINUS_CORE_DIR}/DmnWifi.cpp
)

add_library (
  dominuscore
  ${LIB_ARDUINO_DOMINUS_CORE_SRC}
)

install ( TARGETS dominuscore DESTINATION lib )
