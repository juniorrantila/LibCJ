#pragma once
#include <CJ/Arch.h>

#if has_include(<sys/event.h>)
#include "kqueue/Watcher.h"
#else
#warning "unimplemented"
#include "unimplemented/Watcher.h" // NOLINT
#endif
