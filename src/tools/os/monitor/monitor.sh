#!/bin/sh

if [ $# -eq 1 ]
then
    sudo ARDUINO_PORT=$1 screen -c screenrc
else
    echo "ERROR: usage is ./monitor.sh device"
fi
