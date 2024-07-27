#ifndef CRC_H
#define CRC_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define POLY 0x9d7f97d6;

void init_crc32_table();
uint32_t crc32(const unsigned char *data);

#endif // CRC_H