######################################################################
# CT_PBR BUILD SYSTEM
# Welcome to the CMake build system for CT_PBR.
# This is the main file where we prepare the general build environment
# and provide build configuration options.
######################################################################

cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GAMERENDERENGINE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#配置cmake全局变量
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE__CXX_EXTENSIONS OFF)

project(Project)

if(WIN32)
	set(PLATFORM "Windows")
	add_compile_definitions(WIN32=1)	
elseif(UNIX)

endif()

include(cmake/files.cmake)

add_subdirectory(OpenGL)





