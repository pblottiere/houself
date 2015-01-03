#!/bin/sh

set -e 

echo "Run aclocal..."
mkdir -p m4
aclocal -I m4
echo "Run libtoolize..."
libtoolize > /dev/null
echo "Run autoconf..."
autoconf
echo "Run automake..."
automake --add-missing
echo "Run configure..."
./configure