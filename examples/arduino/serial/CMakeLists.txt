# BUILD STATIC LIB
libarduino_fix_flags()

set( LIB_SERIAL_SRC
  ${LIBCORE_SRC_FILES}
)
add_library ( arduino_lib_serial
  ${LIB_SERIAL_SRC}
)

# BUILD BINARY
set( SRC serial )
binarduino_build_cmd_cpp(
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
    COMMAND ${CMD_BUILD_ELF} ${CMAKE_CURRENT_BINARY_DIR}/libarduino_lib_serial.a
    COMMAND ${CMD_BUILD_HEX}
)

add_subdirectory( mock )
