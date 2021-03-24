cmake_minimum_required(VERSION 3.5)

project (nordc)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/../conan/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

set(SOURCES 
    src/nordc.cpp
	src/Main.cpp
	src/args/NVPNOptions.cpp
	src/args/CommandLineParser.cpp
	src/server/AsyncHTTPDownloader.cpp
	src/server/ServerSelector.cpp
	src/config/CredentialsHelper.cpp
	src/config/OVPNConfigReader.cpp
	src/util/Output.cpp
)

add_executable(nordc ${SOURCES})
target_include_directories(nordc PUBLIC include PRIVATE src)
target_link_libraries(nordc ${CONAN_LIBS
