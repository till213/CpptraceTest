# Application
qt_add_executable(CpptraceWindowTest
    MANUAL_FINALIZATION
    src/main.cpp
)

target_link_libraries(
    CpptraceWindowTest
    PRIVATE
        Qt6::Widgets
        cpptrace::cpptrace
)
set_target_properties(
    CpptraceWindowTest
    PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

qt_finalize_executable(CpptraceWindowTest)
