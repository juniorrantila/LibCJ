#pragma once
#include <CJ/Base.h>
#include <CJ/Lambda.h>
#include <FS/WatchFlags.h>
#include <sys/event.h>

typedef struct {
    struct kevent* changelist;
    CJLambda* lambdas;

    int size;
    int capacity;

    int kq;

    int errno_code;
} WatcherHandle;

WatcherHandle WatcherHandle_create(int capacity);
void WatcherHandle_destroy(WatcherHandle*);

int WatcherHandle_add_watch(WatcherHandle*, c_string, FSWatchFlags, CJLambda);
int WatcherHandle_run(WatcherHandle*);
