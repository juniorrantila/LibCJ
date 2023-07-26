#pragma once
#include <assert.h>

typedef unsigned char u8;
static_assert(sizeof(u8) == 1, "");

typedef signed int i32;
typedef unsigned int u32;
static_assert(sizeof(i32) == 4, "");
static_assert(sizeof(u32) == 4, "");

typedef __SIZE_TYPE__ usize;

typedef char const* c_string;

#if defined(__STDC_VERSION__) && __STDC_VERSION__ <= 202000L
#    include <stdbool.h>
#endif

#define verify_impl(expr, file, line)                                              \
    do {                                                                           \
        if (!(expr)) {                                                             \
            __builtin_printf("%s:%u: ASSERTION FAILED '%s'\n", file, line, #expr); \
            __builtin_trap();                                                      \
        }                                                                          \
    } while (0)
#define verify(expr) verify_impl(expr, __FILE__, __LINE__)

#ifndef NDEBUG
#define ensure(expr, file, line) verify_impl(expr, file, line)
#else
#define ensure(expr, file, line)    \
    do {                            \
        (void)file;                 \
        (void)line;                 \
        bool __result = !(expr);    \
        __builtin_assume(__result); \
    } while (0)
#endif

#define unimplemented() verify(!"unimplemented")
