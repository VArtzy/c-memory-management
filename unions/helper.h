#include <stdint.h>

typedef struct TCP {
    uint16_t src_port; // 2 byte
    uint16_t dest_port; // 2 byte
    uint32_t seq_num; // 4 byte
} tcp_header_t;

typedef union PacketHeader{
    tcp_header_t tcp_header; // 8 byte
    uint8_t raw[8]; // 1*8 = 8 byte
} packet_header_t;
