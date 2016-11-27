#ifndef ZSC_IPV6PACKET_H
#define ZSC_IPV6PACKET_H

#include "../store/State.h"
#include "EthernetFrame.h"

class IPv6Packet {
private:
    int8_t protocol_version;
public:
    IPv6Packet(std::shared_ptr<EthernetFrame>);

    void handle();
};


#endif //ZSC_IPV6PACKET_H
