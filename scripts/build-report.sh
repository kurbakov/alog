#!/bin/bash

echo "======================================================="
echo "BUILD gcc ............................................."
echo "======================================================="
mkdir -p report/build-gcc && cd report/build-gcc
cmake -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ ../.. -D CMAKE_CXX_FLAGS="-O3" > cmake.log
make -j8 > make.log

echo "Run unit tests:"
ctest .

echo "Run benchmark tests:"
./alog_bt

cd ../../

echo "======================================================="
echo "BUILD clang ..........................................."
echo "======================================================="
mkdir -p report/build-clang && cd report/build-clang
cmake -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ ../.. -D CMAKE_CXX_FLAGS="-O3" > cmake.log
make -j8 > make.log

echo "Run unit tests:"
ctest .

echo "Run benchmark tests:"
./alog_bt

cd ../../

echo "======================================================="
echo "BUILD integration test ................................"
echo "======================================================="
mkdir -p report/build-integr && cd report/build-integr
cp -f ../../test/integr/* ./
./build.sh
cd ../../

echo "======================================================="
echo "BUILD gcc address sanitizer ..........................."
echo "======================================================="
mkdir -p report/build-gcc-asan && cd report/build-gcc-asan
cmake -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ ../.. -DADDR_SAN=ON > cmake.log
make -j8 > make.log
find ./ -type f -name "*.ft" -exec {} \; > asan.log
cd ../../

echo "======================================================="
echo "BUILD gcc Leak sanitizer .............................."
echo "======================================================="
mkdir -p report/build-gcc-lsan && cd report/build-gcc-lsan
cmake -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ ../.. -DLEAK_SAN=ON > cmake.log
make -j8 > make.log
find ./ -type f -name "*.ft" -exec {} \; > lsan.log
cd ../../

echo "======================================================="
echo "BUILD gcc UB sanitizer ................................"
echo "======================================================="
mkdir -p report/build-gcc-ubsan && cd report/build-gcc-ubsan
cmake -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ ../.. -DUB_SAN=ON > cmake.log
make -j8 > make.log
find ./ -type f -name "*.ft" -exec {} \; > ubsan.log
cd ../../

# For thread sanitiser use clang compiler as GCC has some bug:
# see: https://github.com/google/sanitizers/issues/1716
echo "======================================================="
echo "BUILD clang thread sanitizer .........................."
echo "======================================================="
mkdir -p report/build-gcc-tsan && cd report/build-gcc-tsan
cmake -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ ../.. -DTHREAD_SAN=ON > cmake.log
make -j8 > make.log
find ./ -type f -name "*.ft" -exec {} \; > tsan.log
cd ../../

rm -fr report
