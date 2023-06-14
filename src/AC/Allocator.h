#pragma once
#include <CJ/Range.h>

struct ACAllocator;
typedef CJRange (*ACAllocFn)(struct ACAllocator*, usize);
typedef CJRange (*ACFreeFn)(struct ACAllocator*, CJRange);

typedef struct ACAllocator {
    ACAllocFn alloc;
    ACFreeFn free;
} ACAllocator;

static inline ACAllocator ACAllocator_make(ACAllocFn alloc, ACFreeFn free)
{
    return (ACAllocator) {
        .alloc = alloc,
        .free = free,
    };
}

static inline CJRange ACAllocator_alloc(ACAllocator* self, usize size)
{
    return self->alloc(self, size);
}

static inline void ACAllocator_free(ACAllocator* self, CJRange range)
{
    self->free(self, range);
}

typedef struct {
    CJRange range;
    ACAllocator* allocator;
} ACAllocatorDeferFree;
static inline void ACAllocator_defer_free(void* ctx)
{
    ACAllocatorDeferFree args = *(ACAllocatorDeferFree*)ctx;
    args.allocator->free(args.allocator, args.range);
}
