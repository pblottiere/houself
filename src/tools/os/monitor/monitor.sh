#!/bin/sh

if [ $# -eq 1 ]
then
    sudo ARDUINO_PORT=$1 screen -c screenrc
    sudo kill -9 $(ps -a | grep monitor_ack | awk '{print $1}')
else
    echo "ERROR: usage is ./monitor.sh device"
fi
