cmake_minimum_required(VERSION 3.5)

project (nordc)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/../conan/conanbuildinfo.cmake)
conan_basic_setup()

# find_package(Poco REQUIRED)
# find_package(cxxopts REQUIRED)

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
target_link_libraries(nordc -static-libgcc -static-libstdc++ ${CONAN_LIBS})
# target_link_libraries(nordc -static-libgcc -static-libstdc++ ${CONAN_LIBS} Poco::Poco cxxopts::cxxopts)
