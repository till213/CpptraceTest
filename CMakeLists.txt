cmake_minimum_required(VERSION 3.16)

project(CpptraceTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Binary output locations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  # Default to a debug build
  set (CMAKE_BUILD_TYPE "Debug")
endif ()

# Third-party libraries
include(FetchContent)
FetchContent_Declare(
  cpptrace
  GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace.git
  GIT_TAG        4b11b87e4d905d003d0325a53994441cc767017a # main 2023-08-22
)
FetchContent_MakeAvailable(cpptrace)
add_library(cpptrace::cpptrace ALIAS cpptrace)

add_subdirectory(ConsoleApp)

find_package(Qt6 COMPONENTS Widgets)
if (Qt6_FOUND)
    message("Found Qt: ${QT}")
    add_subdirectory(WindowApp)
else()
    message("Qt not found: skipping window test app.")
endif()
