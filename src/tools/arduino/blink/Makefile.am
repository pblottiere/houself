MAINTAINERCLEANFILES = Makefile.in Makefile *.o *.elf *.d *.hex .deps

SRC = blink

all-local:
	${ARDUINO_CC} -MM ${ARDUINO_FLAGS} -I. -std=gnu99 ${SRC}.c -MF ${SRC}.d \
                  -MT ${SRC}.o
	${ARDUINO_CC} -c ${ARDUINO_FLAGS} -I. -std=gnu99 ${SRC}.c -o ${SRC}.o
	${ARDUINO_CC} -mmcu=atmega328p -Wl,--gc-sections -Os -o ${SRC}.elf \
                  ${SRC}.o \
                  ${top_srcdir}/src/lib/arduino/core/libarduino_core.a -lc -lm
	${ARDUINO_OBJCOPY} -O ihex -R .eeprom ${SRC}.elf ${SRC}.hex
