#include "crc.h"

uint32_t crc_table[256];

void init_crc32_table()
{
    uint32_t crc;
    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 8; j > 0; j--)
        {
            if (crc & 1)
            {
                crc = (crc >> 1) ^ POLY;
            }
            else
            {
                crc >>= 1;
            }
        }
        crc_table[i] = crc;
    }
}

uint32_t crc32(unsigned const char *data)
{
    size_t length = sizeof(data);
    uint32_t crc = 0xffffffff;
    while (length--)
    {
        crc = (crc >> 8) ^ crc_table[(crc ^ *data++) & 0xff];
    }
    return crc ^ 0xffffffff;
}

