cmake_minimum_required(VERSION 3.15)

project (nordc)

set(CMAKE_CXX_STANDARD 17)

find_package(Poco REQUIRED CONFIG)
find_package(cxxopts)

set(SOURCES 
	src/nordc.cpp
	src/Main.cpp
	src/args/Options.cpp
	src/args/CommandLineParser.cpp
	src/server/AsyncHTTPDownloader.cpp
	src/server/ServerSelector.cpp
	src/server/Server.cpp
	src/config/CredentialsHelper.cpp
	src/config/OVPNConfigReader.cpp
	src/ovpn/OVPNConnector.cpp
	src/util/Output.cpp
)

add_executable(nordc ${SOURCES})
target_include_directories(nordc PRIVATE src)
target_link_libraries(nordc -static-libgcc -static-libstdc++ Poco::Poco cxxopts::cxxopts)
