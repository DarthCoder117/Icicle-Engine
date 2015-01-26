cmake_minimum_required(VERSION 2.8)
project(IcicleEngine)

# Version nuber.
set (ICE_VERSION_MAJOR 1)
set (ICE_VERSION_MINOR 0)

#Configuration options
option (BUILD_TESTS "Build Icicle Engine tests" ON)

#3rd party library directories
set(SFML_PATH ${CMAKE_SOURCE_DIR}/3rd-party/SFML)
link_directories ("${CMAKE_SOURCE_DIR}/3rd-party/SFML/lib")
link_directories ("${CMAKE_SOURCE_DIR}/3rd-party/physfs/lib/${CMAKE_CXX_COMPILER_ID}")

if ( WIN32 )
link_directories ("${CMAKE_SOURCE_DIR}/3rd-party/SFML/lib/${CMAKE_CXX_COMPILER_ID}")
endif ( WIN32 )

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


#Linux compile
if ( NOT WIN32 )
set( CMAKE_CXX_FLAGS "-Wall -g -std=gnu++0x" )
endif ( NOT WIN32 )

file(GLOB ICE_INCLUDES
	"${CMAKE_SOURCE_DIR}/include/core/*.h"
	"${CMAKE_SOURCE_DIR}/include/system/*.h"
	"${CMAKE_SOURCE_DIR}/include/graphics/*.h"
	)

#icicle-core
file(GLOB CORE_SOURCES 
	${ICE_INCLUDES}

	"${CMAKE_SOURCE_DIR}/source/core/*.h"
	"${CMAKE_SOURCE_DIR}/source/core/*.cpp"
	)
	
add_library(icicle-core ${CORE_SOURCES})

#icicle-system
file(GLOB SYSTEM_SOURCES 
	${ICE_INCLUDES}
	
	"${CMAKE_SOURCE_DIR}/source/system/*.h" 
	"${CMAKE_SOURCE_DIR}/source/system/*.cpp"
	)
add_library(icicle-system ${SYSTEM_SOURCES})

#icicle-graphics
file(GLOB GRAPHICS_SOURCES
	${ICE_INCLUDES}
	
	"${CMAKE_SOURCE_DIR}/source/graphics/*.h" 
	"${CMAKE_SOURCE_DIR}/source/graphics/*.cpp"
	)
add_library(icicle-graphics ${GRAPHICS_SOURCES})

#icicle-examples
file(GLOB EXAMPLES_SOURCES 
	${ICE_INCLUDES}
	
	"${CMAKE_SOURCE_DIR}/source/examples/*.h"
	"${CMAKE_SOURCE_DIR}/source/examples/*.cpp"
	)

add_executable(icicle-examples ${EXAMPLES_SOURCES})
target_link_libraries (icicle-examples icicle-core icicle-graphics icicle-system sfml-graphics sfml-window sfml-system physfs)
