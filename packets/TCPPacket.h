
#ifndef ZSC_TCPPACKET_H
#define ZSC_TCPPACKET_H

#define F_NS  0x01
#define F_FIN 0x01
#define F_SYN 0x02
#define F_RST 0x04
#define F_PSH 0x08
#define F_ACK 0x10
#define F_URG 0x20
#define F_ECE 0x40
#define F_CWR 0x80

#include <cstdint>
#include <stdio.h>
#include "../store/State.h"


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

        uint8_t* payload;
        ssize_t payload_length;

    public:

        TCPPacket(uint8_t *packet, ssize_t size);
        TCPPacket(
                uint16_t source_port,
                uint16_t destination_port,
                uint32_t sequence_number,
                uint32_t ack_number,
                uint8_t data_offset,
                uint8_t flags,
                uint8_t NSflag,
                uint16_t window_size,
                uint16_t urgent_pointer,
                uint8_t* payload,
                ssize_t payload_length
                );

        void handle(std::shared_ptr<State> state, uint8_t* source_ip);
        void respond(std::shared_ptr<State> state, uint8_t* destination_ip);

        void parse(uint8_t* packet, ssize_t size);
        void displayPacket();
};


#endif //ZSC_TCPPACKET_H
