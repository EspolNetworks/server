#ifndef TCP_H
#define TCP_H

#define MAX_PAYLOAD_LEN 1500

#include "crc.h"

// https://en.wikipedia.org/wiki/Ethernet_frame
typedef struct ethernet // 18 bytes + payload
{
    unsigned char dest_mac[6];              
    unsigned char source_mac[6];            
    unsigned char type[2];                  
    unsigned char payload[MAX_PAYLOAD_LEN]; 
    unsigned char fcs[4];                   
} ethernet_frame;

typedef struct packet_header // 20 bytes
{
    unsigned char version[1];         
    unsigned char type_service[1];    
    unsigned char total_length[2];    
    unsigned char identification[2];  
    unsigned char flags[2];           
    unsigned char time_to_live[1];    
    unsigned char protocol[1];        
    unsigned char header_checksum[2]; 
    unsigned char source_ip[4];       
    unsigned char dest_ip[4];         
} ipv4_header;

typedef struct packet // 38 bytes + data
{
    ipv4_header header;
    ethernet_frame ethernet_frame;
} ipv4_packet;

typedef struct tcp // 24 bytes
{
    unsigned char source_port[2];     
    unsigned char dest_port[2];       
    unsigned char sequence_number[4]; 
    unsigned char ack_number[4];      
    unsigned char data_offset[2];     
    unsigned char reserved[2];        
    unsigned char flags[2];           
    unsigned char window_size[2];     
    unsigned char checksum[2];        
    unsigned char urgent_pointer[2];  
} tcp_header;

typedef struct tcp_packet // 62 bytes + data
{
    tcp_header header;
    ipv4_packet packet;
} tcp_packet;

ethernet_frame create_ethernet_frame(unsigned char payload[MAX_PAYLOAD_LEN]);
ipv4_header create_ipv4_header();

#endif // TCP_H