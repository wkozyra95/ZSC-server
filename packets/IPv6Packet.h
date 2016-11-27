#ifndef ZSC_IPV6PACKET_H
#define ZSC_IPV6PACKET_H

#include "../store/State.h"
#include "EthernetFrame.h"

class IPv6Packet {
private:
    uint8_t version;          // older 4b
    uint8_t traffic_class;    // 1B
    uint8_t flow_label[3];    // older 20b

    uint16_t payload_length;  // 2B
    uint8_t next_header;      // 1B
    uint8_t ttl;              // 1B

    uint8_t source[16];       // 16B
    uint8_t destination[16];  // 16B
    uint8_t *payload;
public:
    IPv6Packet(uint8_t* packet, ssize_t size);

    void handle(std::shared_ptr<State> store);
    void parse(uint8_t* packet, ssize_t size);

    void displayPacket();
};


#endif //ZSC_IPV6PACKET_H
