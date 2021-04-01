#!/bin/bash
BUILD=build
if [ $# -gt 0 ]
	then BUILD=$1
fi
rm -rf $BUILD
mkdir -p $BUILD/{Debug,Release,conan}
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install -if build/conan .
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -G "Unix Makefiles" -B $BUILD/Debug ..
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -G "Unix Makefiles" -B $BUILD/Release ..
cmake --build $BUILD/Debug
cmake --build $BUILD/Release
cp -r $BUILD/conan/lib $BUILD/Debug
cp -r $BUILD/conan/lib $BUILD/Release
cp nordc.sh $BUILD/Debug/bin
cp nordc.sh $BUILD/Release/bin