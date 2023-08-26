#ifndef STACKTRACELIB_H
#define STACKTRACELIB_H

#ifdef PLATFORM_WINDOWS
#ifdef STACKTRACE_EXPORT
  #define STACKTRACE_API __declspec(dllexport)
#else
  #define STACKTRACE_API __declspec(dllimport)
#endif
#else
  #define STACKTRACE_API
#endif

#endif // STACKTRACELIB_H
