#!/bin/bash
rm -rf build
mkdir -p build/{Debug,Release,conan}
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install -if build/conan .
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -G "Unix Makefiles" -B build/Debug ..
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -G "Unix Makefiles" -B build/Release ..
cmake --build build/Debug
cmake --build build/Release
cp -r build/conan/lib build/Debug
cp -r build/conan/lib build/Release
cp nordc.sh build/Debug/bin
cp nordc.sh build/Release/bin