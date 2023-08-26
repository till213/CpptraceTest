cmake_minimum_required(VERSION 3.16)

project(CpptraceTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_MODULE_PREFIX "")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Third-party libraries
include(FetchContent)
FetchContent_Declare(
  cpptrace
  GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace.git
  GIT_TAG        4b11b87e4d905d003d0325a53994441cc767017a # main 2023-08-22
)
FetchContent_MakeAvailable(cpptrace)

# Application
add_executable(CpptraceTest
   src/main.cpp
)

target_link_libraries(
    CpptraceTest
    PRIVATE
        cpptrace
)

set_target_properties(
    CpptraceTest
    PROPERTIES
        MACOSX_BUNDLE FALSE
        WIN32_EXECUTABLE FALSE
)
