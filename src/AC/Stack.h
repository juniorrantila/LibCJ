#include <CJ/Base.h>
#include <CJ/Range.h>

#define ACStack_alloc(size)                                     \
    ({                                                          \
        usize __size = (size);                                  \
        CJRange_make((u8*)__builtin_alloca(__size), __size);    \
    })
