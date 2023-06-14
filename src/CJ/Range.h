#pragma once
#include "Base.h"

typedef struct {
    u8* data;
    usize size;
} CJRange;
static_assert(sizeof(CJRange) == 2 * sizeof(void*), "");

static inline CJRange CJRange_make(u8* data, usize size)
{
    return (CJRange) {
        .data = data,
        .size = size,
    };
}

#define CJRange_make_static(size) ({ \
        static u8 buf[size]; \
        CJRange_make(buf, size); \
    })

static inline bool CJRange_is_valid(CJRange range)
{
    return range.data != 0;
}

static inline CJRange CJRange_invalid(void)
{
    return CJRange_make(0, 0);
}
