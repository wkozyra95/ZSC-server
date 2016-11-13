#ifndef ZSC_IPV6_H
#define ZSC_IPV6_H

#include <string.h>
#include "../ethernet/ethernet.h"
const unsigned char ipv6_type[2] = {0x86, 0xDD};

struct ipv6_packet {
    unsigned char version;          // older 4b
    unsigned char traffic_class;    // 1B
    unsigned char flow_label[3];    // older 20b

    uint16_t payload_length;        // 2B
    unsigned char next_header; // 1B
    unsigned char ttl;              // 1B

    unsigned char source[16];       // 16B
    unsigned char destination[16];  // 16B
    unsigned char *payload;
};

int chceck_if_ipv6(struct eth_frame* frame);
struct ipv6_packet * eth_to_ipv6(struct eth_frame* frame);

#endif //ZSC_IPV6_H
