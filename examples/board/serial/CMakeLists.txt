# BUILD STATIC LIB
libarduino_fix_flags()

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
    COMMAND ${CMD_BUILD_ELF} ${CMAKE_CURRENT_BINARY_DIR}/../../../src/lib/board/core/libdominuscore.a
    COMMAND ${CMD_BUILD_HEX}
)

add_subdirectory( mock )
