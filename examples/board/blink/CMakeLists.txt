# BUILD STATIC LIB
libarduino_fix_flags()

set(
  LIB_BLINK
  ${LIBCORE_SRC_FILES}
)
add_library (
  arduino_lib_blink 
  ${LIB_BLINK}
)

# BUILD BINARY
set(SRC blink)
binarduino_build_cmd_c(
  ${SRC} 
  CMD_BUILD_D 
  CMD_BUILD_O 
  CMD_BUILD_ELF 
  CMD_BUILD_HEX
)

add_custom_target(
    ${SRC}
    ALL
    COMMAND ${CMD_BUILD_D}
    COMMAND ${CMD_BUILD_O}
    COMMAND ${CMD_BUILD_ELF} ${CMAKE_CURRENT_BINARY_DIR}/libarduino_lib_blink.a
    COMMAND ${CMD_BUILD_HEX}
)
