#ifndef STACKTRACELIB_H
#define STACKTRACELIB_H

#ifdef STACKTRACE_EXPORT
# define STACKTRACE_API __declspec(dllexport)
#else
# define STACKTRACE_API __declspec(dllimport)
#endif

#endif // STACKTRACELIB_H
