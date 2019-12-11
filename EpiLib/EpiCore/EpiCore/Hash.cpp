#include "EpiCore/pch.h"
#include "Hash.h"

epiHash_t crc32(const char* str, const epiSize_t idx)
{
    if (idx == -1)
    {
        return 0xFFFFFFFF;
    }

    return
        (crc32(str, idx - 1) >> 8) ^
        crc_table[(crc32(str, idx - 1) ^ str[idx]) & 0x000000FF];
}
