#!/bin/sh
rm -rf build
mkdir -p build/Debug
mkdir -p build/conan
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install -if build/conan .
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -G "Unix Makefiles" -B build/Debug .
cmake --build build/Debug