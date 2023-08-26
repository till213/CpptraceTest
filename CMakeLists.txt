cmake_minimum_required(VERSION 3.16)
include(CMakePrintHelpers)

project(CpptraceTest VERSION 0.1 LANGUAGES CXX)
set(PROJECT_APPLICATION_NAME "Sky Dolly")
set(PROJECT_ORGANISATION_NAME till213)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform identifiers

# https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Write-Platform-Checks
string(COMPARE EQUAL "Windows" ${CMAKE_SYSTEM_NAME} PLATFORM_IS_WINDOWS)
string(COMPARE EQUAL "Darwin" ${CMAKE_SYSTEM_NAME} PLATFORM_IS_MACOS)
string(COMPARE EQUAL "Linux" ${CMAKE_SYSTEM_NAME} PLATFORM_IS_LINUX)
cmake_print_variables(CMAKE_SYSTEM_NAME)

# Binary output locations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  # Default to a debug build
  set (CMAKE_BUILD_TYPE "Debug")
endif()

# Definitions

# Debug output
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

if (PLATFORM_IS_WINDOWS)
    add_compile_definitions(PLATFORM_WINDOWS)
endif()

add_subdirectory(src)
