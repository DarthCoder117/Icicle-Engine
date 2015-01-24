cmake_minimum_required(VERSION 3.1)
project(Icicle Engine)

# Version nuber.
set (ICE_VERSION_MAJOR 1)
set (ICE_VERSION_MINOR 0)

#Build options
option(BUILD_TESTS "Build Icicle Engine tests" ON)

# Generate configuration header
configure_file("${CMAKE_SOURCE_DIR}/include/IcicleConfig.h.in" "${CMAKE_SOURCE_DIR}/include/IcicleConfig.h")

#Directories
set (ENGINE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
include_directories ("${ENGINE_INCLUDE_DIR}")

#icicle-core
file(GLOB CORE_SOURCES 
	"${CMAKE_SOURCE_DIR}/include/core/*.h" 
	"${CMAKE_SOURCE_DIR}/source/core/*.h" 
	"${CMAKE_SOURCE_DIR}/source/core/*.cpp"
	)

add_library(icicle-core ${CORE_SOURCES})