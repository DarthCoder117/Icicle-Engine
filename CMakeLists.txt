cmake_minimum_required(VERSION 2.8)
project(IcicleEngine)

# Version nuber.
set (ICE_VERSION_MAJOR 1)
set (ICE_VERSION_MINOR 0)

#Configuration options
option (BUILD_TESTS "Build Icicle Engine tests" ON)

#3rd party library directories
set(SFML_PATH ${CMAKE_SOURCE_DIR}/3rd-party/SFML)

#sfml-librarys
FIND_LIBRARY(sfml-graphics SFML_PATH/lib)
FIND_LIBRARY(sfml-system SFML_PATH/lib)
FIND_LIBRARY(sfml-window SFML_PATH/lib)

# Generate configuration header
configure_file("${CMAKE_SOURCE_DIR}/include/IcicleConfig.h.in" "${CMAKE_SOURCE_DIR}/include/IcicleConfig.h")

#Directories
set (ENGINE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
include_directories (
	"${ENGINE_INCLUDE_DIR}"
	"${CMAKE_SOURCE_DIR}/3rd-party/SFML/include")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_CXX_COMPILER_ID})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_CXX_COMPILER_ID})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_CXX_COMPILER_ID})



#icicle-core
file(GLOB CORE_SOURCES 
	"${CMAKE_SOURCE_DIR}/include/core/*.h" 
	"${CMAKE_SOURCE_DIR}/source/core/*.h" 
	"${CMAKE_SOURCE_DIR}/source/core/*.cpp"
	)
	
add_library(icicle-core ${CORE_SOURCES})

#icicle-examples
file(GLOB EXAMPLES_SOURCES 
	"${CMAKE_SOURCE_DIR}/include/core/*.h" 
	"${CMAKE_SOURCE_DIR}/include/test/*.h"
	"${CMAKE_SOURCE_DIR}/source/examples/*.h"
	"${CMAKE_SOURCE_DIR}/source/examples/*.cpp"
	)

add_executable(icicle-examples ${EXAMPLES_SOURCES})
target_link_libraries (icicle-examples icicle-core sfml-graphics)