#include "Watcher.h"

#include <CJ/Lambda.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/event.h>
#include <sys/fcntl.h>
#include <unistd.h>

static WatcherHandle WatcherHandle_invalid(void)
{
    return (WatcherHandle) { 0 };
}

static WatcherHandle make_error(int errno_code)
{
    return (WatcherHandle) {
        .errno_code = errno_code,
    };
}

WatcherHandle WatcherHandle_create(int capacity)
{
    int kq = kqueue();
    if (kq < 0)
        goto fi_0;

    struct kevent* changelist = malloc(capacity * sizeof(struct kevent));
    if (!changelist)
        goto fi_1;

    CJLambda* lambdas = malloc(capacity * sizeof(CJLambda));
    if (!lambdas)
        goto fi_2;

    return (WatcherHandle){
        .changelist = changelist,
        .lambdas = lambdas,

        .size = 0,
        .capacity = capacity,

        .kq = kq,
        .errno_code = 0,
    };

fi_2: free(changelist);
fi_1: close(kq);
fi_0: return make_error(errno);
}

void WatcherHandle_destroy(WatcherHandle* handle)
{
    free(handle->lambdas);
    for (int i = 0; i < handle->size; i++)
        close((int)handle->changelist[i].ident);
    free(handle->changelist);
    close(handle->kq);
    *handle = WatcherHandle_invalid();
}

int WatcherHandle_add_watch(WatcherHandle* watch, c_string path, FSWatchFlags flags, CJLambda lambda)
{
    if (watch->size >= watch->capacity) {
        errno = ENOMEM;
        return -1;
    }
    int fd = open(path, O_RDONLY);
    if (fd < 0)
        return -1;

    int id = watch->size++;
    watch->lambdas[id] = lambda;

    int kqueue_flags = 0;
    if (flags & FSWatchFlags_Write)
        kqueue_flags |= NOTE_WRITE;

    watch->changelist[id] = (struct kevent) {
        .ident = fd,
        .filter = EVFILT_VNODE,
        .flags = EV_ADD | EV_ONESHOT,
        .fflags = kqueue_flags,
        .udata = &watch->lambdas[id],
    };

    return 0;
}

int WatcherHandle_run(WatcherHandle* watch)
{
    while (1) {
        struct kevent event_result = { 0 };
        if (kevent(watch->kq, watch->changelist, watch->size, &event_result, 1, NULL) < 0)
            return -1;
        if (event_result.flags & EV_ERROR) {
            errno = (int)event_result.data;
            return -1;
        }
        CJLambda_call(*(CJLambda*)event_result.udata);
    }
}
