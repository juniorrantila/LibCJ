#include "MappedFile.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

static FSMappedFile make_error(int errno_code)
{
    return (FSMappedFile) {
        .text = 0,
        .size = errno_code,
    };
}

FSMappedFile FSMappedFile_open(c_string path)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0)
        return make_error(errno);

    struct stat st;
    if (fstat(fd, &st) < 0)
        return make_error(errno);

    void* map = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED)
        return make_error(errno);

    return (FSMappedFile) {
        .text = (u8 const*)map,
        .size = st.st_size,
    };
}

void FSMappedFile_close(FSMappedFile* file)
{
    munmap((void*)file->text, file->size);
     *file = FSMappedFile_invalid();
}

c_string FSMappedFile_error(FSMappedFile file)
{
    assert(!FSMappedFile_is_valid(file));
    return strerror(file.size);
}
