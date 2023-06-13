#pragma once
#include <CJ/Base.h>

typedef struct {
    u8 const* text;
    usize size;
} FSMappedFile;

FSMappedFile FSMappedFile_open(c_string path);
void FSMappedFile_close(FSMappedFile*);

c_string FSMappedFile_error(FSMappedFile);

inline static bool FSMappedFile_is_valid(FSMappedFile file)
{
    return file.text != 0;
}

inline static FSMappedFile FSMappedFile_invalid(void)
{
    return (FSMappedFile) { 0 };
}
