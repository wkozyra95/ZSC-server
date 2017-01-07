
#ifndef ZSC_ICMPPACKET_H
#define ZSC_ICMPPACKET_H


#include "../store/State.h"

class IcmpPacket {
private:
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint8_t* payload;
    ssize_t payload_length;
public:

    IcmpPacket(uint8_t* packet, uint16_t payload_length);
    IcmpPacket(uint8_t type, uint8_t code, uint8_t *packet, ssize_t size);

    void handle(std::shared_ptr<State> state, uint8_t* sourceipv6);
    void respond(std::shared_ptr<State> state, uint8_t* destinationipv6);
    void parse(uint8_t* packet, uint16_t length);
    void displayPacket();
};


#endif //ZSC_ICMPPACKET_H
