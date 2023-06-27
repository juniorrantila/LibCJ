#include "CJ/Range.h"
#include "Unlimited.h"
#include <sys/mman.h>
#include <unistd.h>

CJRange ACUnlimited_make(void)
{
    usize TiB = 1024UL * 1024UL * 1024UL * 1024UL;
    usize size = 1 * TiB;
    void* data = mmap(0, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE|MAP_NORESERVE, -1, 0);
    if (data == (void*)-1)
        return CJRange_invalid();
    return CJRange_make(data, size);
}
