#! /bin/sh
wget http://curlpp.googlecode.com/files/curlpp-0.7.3.tar.gz
tar zxf curlpp-0.7.3.tar.gz
cd curlpp-0.7.3
./configure
make
sudo make install
