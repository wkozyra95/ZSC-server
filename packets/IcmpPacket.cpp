
#include <cstring>
#include "IcmpPacket.h"
#include "IPv6Packet.h"


IcmpPacket::IcmpPacket(uint8_t* packet, uint16_t payload_length) {
    parse(packet, payload_length);
}

IcmpPacket::IcmpPacket(uint8_t type, uint8_t code, uint8_t* packet, ssize_t size) {
    this->type = type;
    this->code = code;
    this->checksum = 0;
    payload_length = size;
    this->payload = new uint8_t[size];
    memcpy(this->payload, packet, size);
}

void IcmpPacket::parse(uint8_t* packet, uint16_t length) {
    type = packet[0];
    code = packet[1];
    checksum = packet[2] * (uint8_t) 0xFF + packet[3];

    payload_length = length - 4;
    payload = new uint8_t[payload_length];
    memcpy(payload, packet + 4, payload_length);
}

void IcmpPacket::handle(std::shared_ptr<State> state, uint8_t* sourceipv6) {
    if(type == 135 && code == 0) {
        auto neighbour_solicitation = std::make_shared<IcmpPacket>(136, 0, payload, payload_length);
        neighbour_solicitation->respond(state, sourceipv6);
    }

}

void IcmpPacket::respond(std::shared_ptr<State> state, uint8_t* destinationipv6) {
    if(type == 136 && code == 0) {
        uint8_t* ip_payload = new uint8_t[payload_length + 4];
        ip_payload[0] = type;
        ip_payload[1] = code;
        ip_payload[2] = ((uint8_t*) (&checksum))[0];
        ip_payload[3] = ((uint8_t*) (&checksum))[1];

        uint8_t flags[3] = {0x66, 0x00, 0x00};
        memcpy(ip_payload + 4, flags, 3);

        // next 16B should stay the same because its in response we send our ip address
        memcpy(ip_payload + 7, payload + 3, 16);

        ip_payload[23] = 2; // type 2 - target link layer address
        ip_payload[24] = 1; // length

        memcpy(ip_payload + 24, nullptr, 6);
        
        uint8_t flow_label[] = {0x00, 0x00, 0x00};
        auto ip_packet = std::make_shared<IPv6Packet>(
                destinationipv6,
                (uint8_t) 58, //type
                (uint8_t)0,  //traffic class
                (uint8_t *) flow_label,
                ip_payload,
                (uint8_t) 32
        );
        ip_packet->respond(state);

    }
}
