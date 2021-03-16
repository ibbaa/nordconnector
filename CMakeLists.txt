cmake_minimum_required(VERSION 3.5)

project (nordvpncc)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/../conan/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES 
	src/nordvpncc.cpp
	src/Main.cpp
	src/args/NVPNOptions.cpp
	src/args/CommandLineParser.cpp
	src/server/AsyncHTTPDownloader.cpp
	src/server/ServerSelector.cpp
	src/ovpn/CredentialsHelper.cpp
	src/ovpn/OVPNConfigReader.cpp
	src/util/Output.cpp
)

add_executable(nordvpncc ${SOURCES})
target_include_directories(nordvpncc PUBLIC include PRIVATE src)
target_link_libraries(nordvpncc ${CONAN_LIBS})

