#pragma once
#include "Base.h"

typedef struct {
    char const* text;
    usize size;
} CJStringView;
#define CJ_STRING_VIEW(s)               \
    ((CJStringView) {                   \
        .text = "" s "",                \
        .size = sizeof(s) - sizeof(""), \
    })

static inline bool CJStringView_eq(CJStringView a, CJStringView b)
{
    if (a.size != b.size)
        return false;
    if (a.text[0] != b.text[0])
        return false;
    return __builtin_memcmp(a.text + 1, b.text + 1, a.size - 1) == 0;
}
