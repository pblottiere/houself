MAINTAINERCLEANFILES = Makefile.in Makefile *.a

AM_CXXFLAGS = -I ${top_srcdir}/src/lib/os

bin_PROGRAMS = monitor_cmd
monitor_cmd_LDADD = -lzmq -L${top_srcdir}/src/lib/os/libreactor -lreactor \
                    -L${top_srcdir}/src/lib/os/libserial -lserial 

monitor_cmd_SOURCES = main.cpp