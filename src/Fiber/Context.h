#pragma once
#include <CJ/Arch.h>

#if ARCH(x86_64) && (OS(darwin) || OS(linux))

typedef struct {
    void* rip;
    void* rsp;
    void* rbx;
    void* rbp;
    void* r12;
    void* r13;
    void* r14;
    void* r15;
} FiberContext;

#else
#error "Unsupported architecture or OS"
#endif

int FiberContext_save(FiberContext*);
void FiberContext_load(FiberContext const*);
void FiberContext_swap(FiberContext* save, FiberContext const* load);
