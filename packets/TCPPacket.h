
#ifndef ZSC_TCPPACKET_H
#define ZSC_TCPPACKET_H


#include <cstdint>
#include <stdio.h>

class TCPPacket {
private:
    uint16_t source_port;
    uint16_t destination_port;
    uint32_t seq_number;
    uint32_t ack_number;

    uint8_t data_offset;
    bool isNS;
    bool isCWR;
    bool isECE;
    bool isURG;
    bool isACK;
    bool isPSH;
    bool isRST;
    bool isSYN;
    bool isFIN;

    uint16_t window_size;

    uint16_t checksum;
    uint16_t urgent_pointer;

    uint8_t payload;
    ssize_t payload_length;

public:

    TCPPacket(uint8_t *packet, ssize_t size);

    void parse(uint8_t* packet, ssize_t size);

};


#endif //ZSC_TCPPACKET_H
