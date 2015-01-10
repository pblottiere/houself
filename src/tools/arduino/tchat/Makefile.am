MAINTAINERCLEANFILES = Makefile.in Makefile *.o *.elf *.d *.hex .deps *.a *.la

SRC = tchat

CC = ${ARDUINO_CC}
CXX = ${ARDUINO_CXX}
AM_CXXFLAGS = -I ${top_srcdir}/src/lib/common
AM_ARFLAGS = rcs 
ARDUINO_FLAGS += ${AM_CXXFLAGS}

noinst_LTLIBRARIES = libarduino.la
libarduino_la_SOURCES = ${top_srcdir}/src/lib/common/libtchat/TchatMsg.cpp \
                        ${top_srcdir}/src/lib/common/libtchat/TchatBuffer.cpp \
                        ${top_srcdir}/src/lib/common/libtchat/TchatMsgLed.cpp

all-local:
	${ARDUINO_AR} ${AM_ARFLAGS} libarduino.a *.o

	${ARDUINO_CXX} -MM ${ARDUINO_FLAGS} -I. -std=gnu99 ${SRC}.cpp -MF ${SRC}.d \
                   -MT ${SRC}.o
	${ARDUINO_CXX} -c ${ARDUINO_FLAGS} -I. -std=gnu99 ${SRC}.cpp -o ${SRC}.o
	${ARDUINO_CXX} -mmcu=atmega328p -Wl,--gc-sections -Os -o ${SRC}.elf \
                   ${SRC}.o \
                   ${top_srcdir}/src/tools/arduino/tchat/libarduino.a \
                   ${top_srcdir}/src/lib/arduino/core/libarduino_core.a -lc -lm
	${ARDUINO_OBJCOPY} -O ihex -R .eeprom ${SRC}.elf ${SRC}.hex

clean-local:
	rm -f *.a *.la *.d