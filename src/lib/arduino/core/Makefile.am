MAINTAINERCLEANFILES = Makefile.in Makefile *.a

AM_CFLAGS = -c ${ARDUINO_FLAGS} -std=gnu99
AM_CPPFLAGS = ${ARDUINO_FLAGS} -fno-exceptions
AM_ARFLAGS = rcs 

CC = ${ARDUINO_CC}
CXX = ${ARDUINO_CXX}

noinst_LTLIBRARIES = libarduino_core.la
libarduino_core_la_SOURCES = ${ARDUINO_SRC}/WInterrupts.c \
							 ${ARDUINO_SRC}/wiring_analog.c \
							 ${ARDUINO_SRC}/wiring.c \
							 ${ARDUINO_SRC}/wiring_digital.c \
							 ${ARDUINO_SRC}/wiring_pulse.c \
							 ${ARDUINO_SRC}/wiring_shift.c \
							 ${ARDUINO_SRC}/CDC.cpp \
							 ${ARDUINO_SRC}/HardwareSerial.cpp \
							 ${ARDUINO_SRC}/HID.cpp \
							 ${ARDUINO_SRC}/IPAddress.cpp \
							 ${ARDUINO_SRC}/main.cpp \
							 ${ARDUINO_SRC}/new.cpp \
							 ${ARDUINO_SRC}/Print.cpp \
							 ${ARDUINO_SRC}/Stream.cpp \
							 ${ARDUINO_SRC}/Tone.cpp \
							 ${ARDUINO_SRC}/USBCore.cpp \
							 ${ARDUINO_SRC}/WMath.cpp \
							 ${ARDUINO_SRC}/WString.cpp

all-local:
	${ARDUINO_AR} ${AM_ARFLAGS} libarduino_core.a *.o