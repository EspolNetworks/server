#include "tcp.h"

ethernet_frame create_ethernet_frame(unsigned char payload[MAX_PAYLOAD_LEN])
{
    ethernet_frame frame;

    // TODO: set the real source and destination MAC addresses
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

ipv4_header create_ipv4_header()
{

    ipv4_header header;
    header.version[0] = 0x04;
    header.type_service[0] = 0x00;
    header.total_length[0] = 0x00;
    header.total_length[1] = 0x14;
    header.identification[0] = 0x00;
    header.identification[1] = 0x00;
    header.flags[0] = 0x40;
    header.flags[1] = 0x00;
    header.time_to_live[0] = 0x40;
    header.protocol[0] = 0x06;
    header.header_checksum[0] = 0x00;
    header.header_checksum[1] = 0x00;
    // TODO: set the real source and destination IP addresses
    header.source_ip[0] = 0x7F;
    header.source_ip[1] = 0x00;
    header.source_ip[2] = 0x00;
    header.source_ip[3] = 0x01;
    header.dest_ip[0] = 0x7F;
    header.dest_ip[1] = 0x00;
    header.dest_ip[2] = 0x00;
    header.dest_ip[3] = 0x01;

    short checksum = calculate_ipv4_checksum(&header);

    return header;
}

short calculate_ipv4_checksum(ipv4_header *header)
{
    unsigned short checksum_in_words[10];
    checksum_in_words[0] = (header->version[0] << 8) + header->type_service[0];
    checksum_in_words[1] = (header->total_length[0] << 8) + header->total_length[1];
    checksum_in_words[2] = (header->identification[0] << 8) + header->identification[1];
    checksum_in_words[3] = (header->flags[0] << 8) + header->flags[1];
    checksum_in_words[4] = (header->time_to_live[0] << 8) + header->protocol[0];
    checksum_in_words[5] = (header->header_checksum[0] << 8) + header->header_checksum[1];
    checksum_in_words[6] = (header->source_ip[0] << 8) + header->source_ip[1];
    checksum_in_words[7] = (header->source_ip[2] << 8) + header->source_ip[3];
    checksum_in_words[8] = (header->dest_ip[0] << 8) + header->dest_ip[1];
    checksum_in_words[9] = (header->dest_ip[2] << 8) + header->dest_ip[3];

    unsigned int checksum = 0;

    for (int i = 0; i < 10; i++)
    {
        checksum += checksum_in_words[i];
    }

    if (sizeof(checksum) > 2)
    {
    }

    return checksum;
}
