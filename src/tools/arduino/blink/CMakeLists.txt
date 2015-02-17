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
    COMMAND ${CMD_BUILD_ELF}
    COMMAND ${CMD_BUILD_HEX}
)
