#pragma once
#include "Base.h"
#include "Range.h"

typedef struct {
    u8* bytes;
    usize size;
} CJBits;

inline static CJBits CJBits_from_range(CJRange range)
{
    __builtin_memset(range.data, 0, range.size);
    return (CJBits) {
        .bytes = range.data,
        .size = range.size,
    };
}

inline static CJRange CJBits_to_range(CJBits bits)
{
    return CJRange_make(bits.bytes, bits.size);
}

inline static void CJBits_set_impl(CJBits bits, u32 index, c_string file, u32 line)
{
    ensure(index < bits.size, file, line);
    const u32 byte_index = index / 8;
    const u8 bit_index = index % 8;
    bits.bytes[byte_index] |= 1 << bit_index;
}
#define CJBits_set(bits, index) CJBits_set_impl(bits, index, __FILE__, __LINE__)

inline static void CJBits_unset_impl(CJBits bits, u32 index, c_string file, u32 line)
{
    ensure(index < bits.size, file, line);
    const u32 byte_index = index / 8;
    const u8 bit_index = index % 8;
    bits.bytes[byte_index] &= ~(1 << bit_index);
}
#define CJBits_unset(bits, index) CJBits_unset_impl(bits, index, __FILE__, __LINE__)

inline static bool CJBits_is_set_impl(CJBits bits, u32 index, c_string file, u32 line)
{
    ensure(index < bits.size, file, line);
    const u32 byte_index = index / 8;
    const u8 bit_index = index % 8;
    return (bits.bytes[byte_index] & (1 << bit_index)) != 0;
}
#define CJBits_is_set(bits, index) CJBits_is_set_impl(bits, index, __FILE__, __LINE__)
