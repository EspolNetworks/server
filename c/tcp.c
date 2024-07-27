#include "tcp.h"

ethernet_frame create_ethernet_frame(unsigned char payload[MAX_PAYLOAD_LEN])
{
    ethernet_frame frame;

    frame.source_mac[0] = 0x00;
    frame.source_mac[1] = 0x00;
    frame.source_mac[2] = 0x00;
    frame.source_mac[3] = 0x00;
    frame.source_mac[4] = 0x00;
    frame.source_mac[5] = 0x00;

    frame.dest_mac[0] = 0x00;
    frame.dest_mac[1] = 0x00;
    frame.dest_mac[2] = 0x00;
    frame.dest_mac[3] = 0x00;
    frame.dest_mac[4] = 0x00;
    frame.dest_mac[5] = 0x00;

    frame.type[0] = 0x08;
    frame.type[1] = 0x00;

    for (int i = 0; i < MAX_PAYLOAD_LEN; i++)
    {
        frame.payload[i] = payload[i];
    }

    uint32_t crc = crc32(payload);

    frame.fcs[0] = crc >> 24;
    frame.fcs[1] = crc >> 16;
    frame.fcs[2] = crc >> 8;
    frame.fcs[3] = crc;

    return frame;
}

ipv4_header create_ipv4_header() {
    
}