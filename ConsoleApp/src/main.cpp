#include <exception>
#include <iostream>

#include <cpptrace/cpptrace.hpp>

namespace
{
    void willThrow()
    {
        throw "My deliberate exception";
    }

    void willBreakMyPromiseNotToThrow() noexcept
    {
        throw "Breaking my promise";
    }

    void handleTerminate()
    {
        std::cout << "Third trace (in termination handler):" << std::endl;
        // BUG: This will cause a segmentation fault (on macOS) when run *outside* of a debugger
        //      (regardless of whether compiled as debug or release)
        //
        //      When run *inside* a debugger then we get past this point (except that we won't
        //      get neither source names nor line numbers - but frame addresses are properly
        //      evaluated (as it seems)
        cpptrace::print_trace();
        // Instead of std::abort we call exit with some error code, as we have gracefully dealt
        // with the uncaught exception (abnormal termination)
        std::exit(-1);
    }
}

int main(int argc, char *argv[])
{
    // Setup a terminate handler in order to catch exceptions that
    // were unexpectedly - but in this example totally deliberately - thrown
    // from functions declared as "noexcept"
    std::set_terminate(::handleTerminate);

    std::cout << "First trace:" << std::endl;
    // This works
    cpptrace::print_trace();

    try {
        ::willThrow();
    } catch (...) {
        std::cout << "Second trace (in excepton handler):" << std::endl;
        // This works as well
        cpptrace::print_trace();
    }

    ::willBreakMyPromiseNotToThrow();

    return 0;
}
