#include <CJ/Base.h>
#include <CJ/Range.h>

__attribute__((always_inline)) static inline CJRange ACStack_alloc(usize size)
{
    return CJRange_make((u8*)__builtin_alloca(size), size);
}
