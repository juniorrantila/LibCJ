#include <Watcher.h>

static WatcherHandle WatcherHandle_invalid(void)
{
    unimplemented();
}

WatcherHandle WatcherHandle_create(int capacity)
{
    (void)capacity;
    unimplemented();
}

void WatcherHandle_destroy(WatcherHandle* handle)
{
    (void)handle;
    unimplemented();
}

int WatcherHandle_add_watch(WatcherHandle* watch, c_string path, FSWatchFlags flags, CJLambda lambda)
{
    (void)watch;
    (void)path;
    (void)flags;
    (void)lambda;
    unimplemented();
}

int WatcherHandle_run(WatcherHandle* watch)
{
    (void)watch;
    unimplemented();
}
