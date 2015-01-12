MAINTAINERCLEANFILES = Makefile.in Makefile *.a

AM_CXXFLAGS = -I ${top_srcdir}/src/lib/os -I ${top_srcdir}/src/lib/common

bin_PROGRAMS = monitor_ack
monitor_ack_LDADD = -lzmq -L${top_srcdir}/src/lib/os/libreactor -lreactor \
                    -L${top_srcdir}/src/lib/os/libserial -lserial \
                    -L${top_srcdir}/src/lib/common/libtchat -ltchat 

monitor_ack_SOURCES = main.cpp \
                      ArduinoCallback.cpp