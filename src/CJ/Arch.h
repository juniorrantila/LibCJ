#pragma once

#if defined(_WIN32)
#define __CJ_OS_windows 1
#elif defined(__APPLE__)
#define __CJ_OS_darwin 1
#elif defined(__linux__)
#define __CJ_OS_linux 1
#else
#error "Unknown OS"
#endif
#define OS(query) __CJ_OS_##query


#if defined(__x86_64__)
#define __CJ_ARCH_x86_64 1
#else
#error "Unknown cpu family"
#endif
#define ARCH(query) __CJ_ARCH_##query

#ifndef has_include
#define has_include(include) __has_include(include)
#endif
