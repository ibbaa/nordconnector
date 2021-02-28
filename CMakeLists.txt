cmake_minimum_required(VERSION 3.5)

project (nordvpncc)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/../conan/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES 
    src/main.cpp
)

add_executable(nordvpncc ${SOURCES})
target_link_libraries(nordvpncc ${CONAN_LIBS})
