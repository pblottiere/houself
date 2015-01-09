# Prelude
AC_PREREQ(2.68)
AC_INIT(dominus, 0.0.1, blottiere.paul@gmail.com)
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE(foreign -Wall -Werror 1.9)

# libtool init
LT_INIT

# define arduino stuff
AC_SUBST(ARDUINO_SHARE, /usr/share/arduino/hardware/arduino)
AC_SUBST(ARDUINO_SRC, ${ARDUINO_SHARE}/cores/arduino)
AC_SUBST(ARDUINO_PINS, ${ARDUINO_SHARE}/variants/standard)

ARDUINO_FLAGS="-mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=100 \
               -g -Os -w -Wall -ffunction-sections -fdata-sections \
               -I${ARDUINO_SRC} -I${ARDUINO_PINS}"
AC_SUBST(ARDUINO_FLAGS)

AC_SUBST(ARDUINO_CC, avr-gcc)
AC_SUBST(ARDUINO_CXX, avr-g++)
AC_SUBST(ARDUINO_AR, avr-ar)
AC_SUBST(ARDUINO_OBJCOPY, avr-objcopy)

# check for programs
AC_PROG_CXX

AC_CHECK_PROG([arduino_cc], ${ARDUINO_CC}, [yes], [no])
AM_CONDITIONAL([FOUND_ARDUINO_CC], [test "x$arduino_cc" = xyes])
AM_COND_IF([FOUND_ARDUINO_CC],
           ,
           [AC_MSG_ERROR([required program '${ARDUINO_CC}' not found.])
])

AC_CHECK_PROG([arduino_cxx], ${ARDUINO_CXX}, [yes], [no])
AM_CONDITIONAL([FOUND_ARDUINO_CXX], [test "x$arduino_cxx" = xyes])
AM_COND_IF([FOUND_ARDUINO_CXX],
           ,
           [AC_MSG_ERROR([required program '${ARDUINO_CXX}' not found.])
])

AC_CHECK_PROG([arduino_ar], ${ARDUINO_AR}, [yes], [no])
AM_CONDITIONAL([FOUND_ARDUINO_AR], [test "x$arduino_ar" = xyes])
AM_COND_IF([FOUND_ARDUINO_AR],
           ,
           [AC_MSG_ERROR([required program '${ARDUINO_AR}' not found.])
])

AC_CHECK_PROG([arduino_objcopy], ${ARDUINO_OBJCOPY}, [yes], [no])
AM_CONDITIONAL([FOUND_ARDUINO_OBJCOPY], [test "x$arduino_objcopy" = xyes])
AM_COND_IF([FOUND_ARDUINO_OBJCOPY],
           ,
           [AC_MSG_ERROR([required program '${ARDUINO_OBJCOPY}' not found.])
])

# output files
AC_OUTPUT(
        Makefile
        src/Makefile
        src/lib/Makefile
        src/lib/arduino/Makefile
        src/lib/arduino/core/Makefile
        src/lib/libtchat/Makefile
        src/tools/Makefile
        src/tools/arduino/Makefile
        src/tools/arduino/blink/Makefile
        src/tools/arduino/tchat/Makefile
)

# summary
AC_OUTPUT
