#pragma once
#include "WatchFlags.h"

#include <CJ/Base.h>
#include <CJ/Defer.h>
#include <CJ/Lambda.h>

typedef struct {
    void* handle;
} FSWatcher;

int FSWatcher_create(FSWatcher*, int capacity);
void FSWatcher_destroy(FSWatcher*);

inline static void FSFileWatcher_defer_destroy(void* watcher)
{
    FSWatcher_destroy(watcher);
}

inline static CJDeferFrame FSWatcher_defer_destroy_frame(FSWatcher* watcher)
{
    return CJDeferFrame_make(FSFileWatcher_defer_destroy, watcher);
}

int FSWatcher_add_watch(FSWatcher*, c_string, FSWatchFlags, CJLambda);
int FSWatcher_run(FSWatcher*);
