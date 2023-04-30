#!/bin/bash
BUILD=build
if [ $# -gt 0 ]
	then BUILD=$1
fi
rm -rf $BUILD
mkdir -p $BUILD/{Debug,Release}
conan profile detect --force
conan install . --output-folder=build --build=missing --settings=build_type=Release --settings=compiler.cppstd=gnu17 
conan install . --output-folder=build --build=missing --settings=build_type=Debug --settings=compiler.cppstd=gnu17 
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -DCMAKE_TOOLCHAIN_FILE=./build/conan_toolchain.cmake -G "Unix Makefiles" -B $BUILD/Debug .
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -DCMAKE_TOOLCHAIN_FILE=./build/conan_toolchain.cmake -G "Unix Makefiles" -B $BUILD/Release .
cmake --build $BUILD/Debug
cmake --build $BUILD/Release
tar -czvf $BUILD/Release/binary.tar.gz -C $BUILD/Release nordc
