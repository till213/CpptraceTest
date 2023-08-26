# Third-party libraries
include(FetchContent)
FetchContent_Declare(
  cpptrace
  GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace.git
  GIT_TAG        4b11b87e4d905d003d0325a53994441cc767017a # main 2023-08-22
)
FetchContent_MakeAvailable(cpptrace)
add_library(cpptrace::cpptrace ALIAS cpptrace)

set(LIBRARY_NAME "StackTrace")

add_library(${LIBRARY_NAME} SHARED)
add_library(${LIBRARY_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_compile_definitions(${LIBRARY_NAME}
    PRIVATE
        STACKTRACE_EXPORT
)
target_sources(${LIBRARY_NAME}
    PRIVATE
        include/StackTrace/StackTraceLib.h
        include/StackTrace/StackTrace.h src/StackTrace.cpp
)
target_include_directories(${LIBRARY_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        include/StackTrace
)
target_link_libraries(${LIBRARY_NAME}
    PRIVATE
        cpptrace::cpptrace
)
set_target_properties(${LIBRARY_NAME}
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)