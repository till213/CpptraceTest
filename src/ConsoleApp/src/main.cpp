#include <exception>
#include <iostream>

#include <StackTrace/StackTrace.h>

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
        // FIXED: This is fixed with cpptrace commit d72e30a ("path with white space") and
        //         0977253 ("segmentation fault on macOS")
        StackTrace::generate();
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
    StackTrace::generate();

    try {
        ::willThrow();
    } catch (...) {
        std::cout << "Second trace (in excepton handler):" << std::endl;
        // This works as well
        StackTrace::generate();
    }

    ::willBreakMyPromiseNotToThrow();

    return 0;
}
