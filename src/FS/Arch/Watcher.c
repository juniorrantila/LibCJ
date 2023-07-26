#include <CJ/Arch.h>

#if has_include(<sys/event.h>)
#include "kqueue/Watcher.c" // NOLINT
#else
#warning "unimplemented"
#include "unimplemented/Watcher.c" // NOLINT
#endif
