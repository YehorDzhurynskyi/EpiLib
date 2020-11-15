#include "Hash.h"

epiHash_t crc32(const char* str, const epiSize_t idx)
{
    // TODO: make it work with len(str) > 32
    epiAssert(strlen(str) <= 32);

    if (idx == -1)
    {
        return 0xFFFFFFFF;
    }

    return (crc32(str, idx - 1) >> 8) ^ crc_table[(crc32(str, idx - 1) ^ str[idx]) & 0x000000FF];
}
