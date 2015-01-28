cmake_minimum_required(VERSION 2.8)
project(IcicleEngine)

# Version nuber.
set (ICE_VERSION_MAJOR 1)
set (ICE_VERSION_MINOR 0)

#Configuration options
option (BUILD_TESTS "Build Icicle Engine tests" ON)

#3rd party library directories
link_directories ("${CMAKE_SOURCE_DIR}/3rd-party/bgfx/lib/linux")
link_directories ("${CMAKE_SOURCE_DIR}/3rd-party/physfs/lib/${CMAKE_CXX_COMPILER_ID}")
link_directories ("${CMAKE_SOURCE_DIR}/3rd-party/bgfx/lib/${CMAKE_CXX_COMPILER_ID}")
link_directories ("${CMAKE_SOURCE_DIR}/3rd-party/glfw/lib/${CMAKE_CXX_COMPILER_ID}")
link_directories ("${CMAKE_SOURCE_DIR}/3rd-party/sfml/lib/${CMAKE_CXX_COMPILER_ID}")


# Generate configuration header
configure_file("${CMAKE_SOURCE_DIR}/include/IcicleConfig.h.in" "${CMAKE_SOURCE_DIR}/include/IcicleConfig.h")

#Load custom modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/3rd-party/cmake/modules/")

#Directories
file (GLOB ENGINE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include"
			     "${CMAKE_SOURCE_DIR}/source"
)

include_directories (
	"${ENGINE_INCLUDE_DIR}"
	"${CMAKE_SOURCE_DIR}/3rd-party/sfml/include"
	"${CMAKE_SOURCE_DIR}/3rd-party/bgfx/include"
	"${CMAKE_SOURCE_DIR}/3rd-party/glfw/include"
	"${CMAKE_SOURCE_DIR}/3rd-party/glm")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_CXX_COMPILER_ID})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_CXX_COMPILER_ID})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_CXX_COMPILER_ID})

#Linux compile
if ( NOT WIN32 )

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

FIND_PACKAGE ( X11 REQUIRED )
include_directories(${X11_INCLUDE_DIR})

set( CMAKE_CXX_FLAGS "-Wall -g -std=gnu++0x" )
find_package(GLIB REQUIRED)

include_directories(${GLIB2_LIBRARIES})

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
	
	"${CMAKE_SOURCE_DIR}/source/system/unix/*.h"
	"${CMAKE_SOURCE_DIR}/source/system/unix/*.cpp"
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

if ( WIN32 )
target_link_libraries (icicle-examples opengl32 icicle-core icicle-graphics icicle-system sfml-system sfml-network glfw3 physfs psapi bgfxDebug)
endif ( WIN32 )
if ( NOT WIN32 )
target_link_libraries (icicle-examples GL icicle-core icicle-graphics icicle-system sfml-system sfml-network glfw physfs bgfxDebug X11 glib-2.0 pthread dl)
endif ( NOT WIN32 )