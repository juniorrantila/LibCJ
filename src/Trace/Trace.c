#include <CJ/StringView.h>
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>

static void segfault_handler(int sig, siginfo_t* info, void* arg)
{
    (void)sig;
    (void)info;
    (void)arg;

    static void* trace[4096 / sizeof(void*)];
    usize size = backtrace_async(trace, sizeof(trace) / sizeof(trace[0]), 0);

    CJStringView message = CJ_STRING_VIEW("SEGFAULT\n");
    write(STDERR_FILENO, message.text, message.size);
    backtrace_symbols_fd(trace, (int)size, STDERR_FILENO);
    __builtin_trap();
}

void Trace_register_segfault_handler(void)
{
    struct sigaction sa;
    __builtin_memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);
}

