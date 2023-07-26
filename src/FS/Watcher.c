#include "Watcher.h"

#include "Arch/Watcher.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

inline static FSWatcher FSWatcher_invalid(void)
{
    return (FSWatcher) { 0 };
}

int FSWatcher_create(FSWatcher* watcher, int capacity)
{
    WatcherHandle* handle = malloc(sizeof(WatcherHandle));
    if (!handle)
        goto fi_0;
    *handle = WatcherHandle_create(capacity);
    if (handle->errno_code != 0) {
        errno = handle->errno_code;
        goto fi_1;
    }

    *watcher = (FSWatcher) {
        .handle = handle
    };
    return 0;
fi_1: free(handle);
fi_0: return -1;
}

void FSWatcher_destroy(FSWatcher* watcher)
{
    if (watcher->handle) {
        WatcherHandle_destroy(watcher->handle);
        free(watcher->handle);
    }
    *watcher = FSWatcher_invalid();
}

int FSWatcher_add_watch(FSWatcher* watcher, c_string path, FSWatchFlags flags, CJLambda lambda)
{
    return WatcherHandle_add_watch(watcher->handle, path, flags, lambda); 
}

int FSWatcher_run(FSWatcher* watcher)
{
    return WatcherHandle_run(watcher->handle);
}
