#pragma once
#include "Base.h"
#include "Range.h"

typedef struct {
    void (*run)(void*);
    void* ctx;
} CJDeferFrame;

static inline CJDeferFrame CJDeferFrame_make(void (*run)(void*), void* ctx)
{
    return (CJDeferFrame) {
        .run = run,
        .ctx = ctx,
    };
}

static inline void CJDeferFrame_run(CJDeferFrame frame)
{
    frame.run(frame.ctx);
}

typedef struct {
    CJDeferFrame* frames;
    usize capacity;
    usize size;
} CJDefer;

static inline CJDefer CJDefer_invalid(void)
{
    return (CJDefer) {
        .frames = 0,
        .capacity = 0,
        .size = 0,
    };
}

static inline bool CJDefer_is_valid(CJDefer defer)
{
    return defer.frames != 0;
}

static inline CJDefer CJDefer_init(CJRange frames)
{
    return (CJDefer) {
        .frames = (CJDeferFrame*)frames.data,
        .capacity = frames.size / sizeof(CJDeferFrame),
        .size = 0,
    };
}

static inline void CJDefer_add_impl(CJDefer* defer, CJDeferFrame frame, char const* file, u32 line)
{
    assert(CJDefer_is_valid(*defer));
    ensure(defer->size < defer->capacity, file, line);
    defer->frames[defer->size++] = frame;
}
#define CJDefer_add(defer, frame) CJDefer_add_impl(defer, frame, __FILE__, __LINE__)

static inline void CJDefer_deinit(CJDefer* defer)
{
    assert(CJDefer_is_valid(*defer));
    for (usize i = defer->size; i-- > 0;)
        CJDeferFrame_run(defer->frames[i]);
    *defer = CJDefer_invalid();
}
