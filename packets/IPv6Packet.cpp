
#include <cstring>
#include "IPv6Packet.h"
#include "EthernetFrame.h"
#include "../Utils.h"


void IPv6Packet::handle(std::shared_ptr<State> store) {
    displayPacket();
}

IPv6Packet::IPv6Packet(uint8_t* packet, ssize_t size) {
    parse(packet, size);
}

void IPv6Packet::parse(uint8_t *frame, ssize_t size) {
//    std::cout << Utils::decimal_format_display(frame, size) << std::endl;
    version = frame[0] >> 4;

    traffic_class = (frame[0] << 4) | (frame[1] >> 4);

    flow_label[0] = frame[1] & (uint8_t) 0x0F;
    flow_label[1] = frame[2];
    flow_label[2] = frame[3];
    memcpy(flow_label, flow_label, 3);

    payload_length = frame[5] + frame[4] * (uint16_t)0xFF;

    next_header = frame[6];

    ttl = frame[7];

    memcpy(source, frame + 8, 16);

    memcpy(destination, frame + 24, 16);

}

void IPv6Packet::displayPacket() {
    std::string version_str = std::to_string(version);
    std::string traffic_class_str = std::to_string(traffic_class);
    std::string flow_label_str = Utils::hex_format_display(flow_label, 3);

    std::string payload_length_str = std::to_string(payload_length);
    std::string next_header_str = std::to_string(next_header);
    std::string ttl_str = std::to_string(ttl);

    std::string source_str = Utils::hex_format_display(source, 16);
    std::string destination_src = Utils::hex_format_display(destination, 16);

    std::cout << "Ver: " << version_str << "\ttc: " << traffic_class_str
              << "\tFlow label: " << flow_label_str << "\tpayload: " << payload_length_str
              << "\tNext: " << next_header_str << "\t TTL: " << ttl_str << std::endl
              << "Source: " << source_str << "\tDestiantion: " << destination_src << std::endl;
}



