#!/usr/bin/bash

set -e

mkdir -p build
cd build && rm -fr ./*

echo "Build the application ..."
cmake .. > /dev/null && make -j8 > /dev/null
./main

cd ../ && rm -fr build/
