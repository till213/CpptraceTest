#include <iostream>

#include <cpptrace/cpptrace.hpp>

#include "StackTrace.h"

// PUBLIC

void StackTrace::generate()
{
    std::cout << "Stack frame addresses:" << std::endl;
    const auto trace = cpptrace::generate_trace(0);
    for(const auto &frame : trace) {
        std::cout << std::hex << frame.address << std::endl;
    }
    std::cout << "Cpptrace output:" << std::endl;
    cpptrace::print_trace();
}
