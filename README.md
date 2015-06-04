Dominus
=======

Dominus is a testing project that is aimed to build a full home
automation system. But watch out, Dominus will become the master of
your own house!


Keywords
--------

Home automation - Arduino - Olinuxino - Android - C/C++ - CMake


Dependencies
------------

Debian Wheezy:
- cmake
- arduino-core
- avrdude
- olinuxino cross-compiler (buildroot-a13-olinuxino)


Compile step
------------

To compile, run:
```
mkdir build
cd build
cmake ..
make
```

or just:
```
make
```

To indicate your wifi access point name, password and server IP/port, run:
```
mkdir build
cd build
cmake -DESSID=your_essid -DPASSWORD=your_password -DSERVER_IP=XXX.XXX.XXX.XXX \
      -DSERVER_PORT=XXXX ..
make
```

If you just want to compile OS libs and bins (without arduino stuff), run:
```
mkdir build
cd build
cmake -DOS_ONLY=ON ..
make
```

Monitor
-------

Type CTRL-A CTRL-D to exit from monitor.


Serial Port
-----------

Just a reminder about getting serial port settings:

  stty -F /dev/ttyXX
