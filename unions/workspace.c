#include <assert.h>
#include "helper.h"

void test_packet_header_size() {
    assert(sizeof(packet_header_t) == 8);
}

void test_tcp_header_fields() {
    packet_header_t header;
    header.tcp_header.src_port = 0x1234;
    header.tcp_header.dest_port = 0x5678;
    header.tcp_header.seq_num = 0x9ABCDEF0;

    assert(header.tcp_header.src_port == 0x1234);
    assert(header.tcp_header.dest_port == 0x5678);
    assert(header.tcp_header.seq_num == 0x9ABCDEF0);
}

void test_field_raw_size() {
    assert(sizeof(((packet_header_t *)0)->raw) == 8);
}

void test_field_to_raw_consistency() {
    packet_header_t header = {0};
    header.tcp_header.src_port = 0x1234;
    header.tcp_header.dest_port = 0x5678;
    header.tcp_header.seq_num = 0x9ABCDEF0;

    assert(header.raw[0] == 0x34);
    assert(header.raw[1] == 0x12);
    assert(header.raw[2] == 0x78);
    assert(header.raw[3] == 0x56);
    assert(header.raw[4] == 0xF0);
    assert(header.raw[5] == 0xDE);
    assert(header.raw[6] == 0xBC);
    assert(header.raw[7] == 0x9A);
}

int main() {
    test_packet_header_size();
    test_tcp_header_fields();
    test_field_raw_size();
    test_field_to_raw_consistency();
    return 0;
}
