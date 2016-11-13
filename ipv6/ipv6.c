#include "ipv6.h"

int chceck_if_ipv6(struct eth_frame* frame) {
    if(memcmp(ipv6_type, frame->type, 2) != 0) {
        return -1;
    }
    return 0;
}

void ipv6_packet_check(struct ipv6_packet *packet, ssize_t size);

struct ipv6_packet* eth_to_ipv6(struct eth_frame* frame) {
    struct ipv6_packet* packet = malloc(sizeof(struct ipv6_packet));

    unsigned char version = frame->payload[0] >> 4;
    packet->version = version;

    unsigned char trafic_class = (frame->payload[0] << 4) & (frame->payload[1] >> 4);
    packet->traffic_class = trafic_class;

    unsigned char flow_label[3];
    flow_label[0] = frame->payload[1] >> 4;
    flow_label[1] = frame->payload[2];
    flow_label[2] = frame->payload[3];
    memcpy(packet->flow_label, flow_label, 3);

    packet->payload_length = frame->payload[4] + frame->payload[5] * (uint16_t)0xFF;

    packet->next_header = frame->payload[6];

    packet->ttl = frame->payload[7];

    memcpy(packet->source, frame->payload + 8, 16);

    memcpy(packet->destination, frame->payload + 24, 16);

    ipv6_packet_check(packet, frame->payloadSize);

    return packet;
}

void ipv6_packet_check(struct ipv6_packet *packet, ssize_t size) {
    if(size != packet->payload_length + 40) {
        printf("ERROR: wrong ipv6 packet length");
    }
}

