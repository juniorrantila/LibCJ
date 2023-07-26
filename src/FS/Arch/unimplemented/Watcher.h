#pragma once
#include <CJ/Base.h>
#include <CJ/Lambda.h>
#include <FS/WatchFlags.h>

typedef struct {
    int dummy;
} WatcherHandle;

WatcherHandle WatcherHandle_create(int capacity);
void WatcherHandle_destroy(WatcherHandle*);

int WatcherHandle_add_watch(WatcherHandle*, c_string, FSWatchFlags, CJLambda);
int WatcherHandle_run(WatcherHandle*);
