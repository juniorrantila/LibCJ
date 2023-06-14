#pragma once
#include "Allocator.h"
#include <CJ/Range.h>

typedef struct {
    ACAllocator allocator;

    CJRange memory;
    usize index;
} ACBump;
static_assert(__builtin_offsetof(ACBump, allocator) == 0, "Must be at top");

static inline CJRange ACBump_alloc(ACBump* self, usize size);
static inline void ACBump_free(ACBump* self, CJRange range);

static inline ACBump ACBump_make(CJRange range)
{
    return (ACBump) {
        .allocator = ACAllocator_make((ACAllocFn)ACBump_alloc, (ACFreeFn)ACBump_free),
        .memory = range,
        .index = 0,
    };
}

static inline ACAllocator* ACBump_as_allocator(ACBump* self)
{
    return &self->allocator;
}

static inline usize ACBump_state(ACBump const* self)
{
    return self->index;
}

static inline void ACBump_reset(ACBump* self, usize state)
{
    self->index = state;
}

typedef struct {
    ACBump* self;
    ACBump state;
} ACBumpDeferReset;
static inline void ACBump_defer_reset(void* ctx)
{
    ACBumpDeferReset* args = (ACBumpDeferReset*)(ctx);
    *args->self = args->state;
}

static inline CJRange ACBump_alloc(ACBump* self, usize size)
{
    if (self->index >= self->memory.size)
        return CJRange_invalid();

    u8* start = self->memory.data + self->index;
    self->index += size;
    return CJRange_make(start, size);
}

static inline void ACBump_free(ACBump* self, CJRange range)
{
    if (self->memory.data + self->index - range.size != range.data)
        return;
    self->index -= range.size;
}
