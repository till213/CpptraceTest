# Application
add_executable(CpptraceConsoleTest
   src/main.cpp
)

target_link_libraries(
    CpptraceConsoleTest
    PRIVATE
        cpptrace::cpptrace
)
set_target_properties(
    CpptraceConsoleTest
    PROPERTIES
        MACOSX_BUNDLE FALSE
        WIN32_EXECUTABLE FALSE
)
