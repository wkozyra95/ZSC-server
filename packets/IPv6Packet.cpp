

#include <iostream>
#include <cstring>
#include "../Utils.h"
#include "../store/EthernetStore.h"
#include "../store/IPv6Store.h"
#include "../store/TCPStore.h"
#include "IcmpPacket.h"
#include "IPv6Packet.h"
#include "EthernetFrame.h"
#include "TCPPacket.h"

void IPv6Packet::handle(std::shared_ptr<State> store, uint8_t* mac) {
    store->ethernetStore->registerMAC(source, mac);
    //displayPacket();
    if(next_header == 58){
       std::make_shared<IcmpPacket>(payload, payload_length)->handle(store, source);
    }
    if(next_header == 6){
        std::make_shared<TCPPacket>(this->payload, this->payload_length)->handle(store, source);
        std::cout << "\ntcp\n" << std::endl;
    }
}

void IPv6Packet::respond(std::shared_ptr<State> store) {
    uint8_t* ethernet_payload = new uint8_t[payload_length + 40];
    // version
    ethernet_payload[0] = version << 4;
    // traffic_class
    ethernet_payload[0] = ethernet_payload[0] | (traffic_class >> 4);
    ethernet_payload[1] = traffic_class << 4;

    // flow_label
    ethernet_payload[1] = ethernet_payload[1] | (flow_label[0]);
    ethernet_payload[2] = flow_label[1];
    ethernet_payload[3] = flow_label[2];
    
    // payload_length
    ethernet_payload[4] = (uint8_t) payload_length >> 8;
    ethernet_payload[5] = (uint8_t) payload_length ;

    // next_header
    ethernet_payload[6] = next_header;

    // ttl
    ethernet_payload[7] = ttl;

    memcpy(ethernet_payload + 8, store->ipv6Store->getMyIp(), 16);
    memcpy(ethernet_payload + 24, destination, 16);

    memcpy(ethernet_payload + 40, payload, payload_length);

    auto ethernetFrame = std::make_shared<EthernetFrame>(
            store->ethernetStore->getMacForIP(destination),
            0x86DD,
            ethernet_payload,
            payload_length + 40
    );
    ethernetFrame->respond(store);
}

IPv6Packet::IPv6Packet(uint8_t* packet, ssize_t size) {
    parse(packet, size);
}

IPv6Packet::IPv6Packet(
        uint8_t* destination, uint8_t type, uint8_t traffic_class, 
        uint8_t* flow_label, uint8_t* payload, uint16_t payload_length) {

    version = 6;
    this->traffic_class = traffic_class;
    memcpy(this->flow_label, flow_label, 3);
    this->payload_length = payload_length;
    this->next_header = type;
    this->ttl = 255;

    memcpy(this->destination, destination, 16);
    this->payload = new uint8_t[payload_length];
    memcpy(this->payload, payload, payload_length);

}
        
void IPv6Packet::parse(uint8_t *frame, ssize_t size) {
    parse_header(frame, size);
}

void IPv6Packet::parse_header(uint8_t *frame, ssize_t size) {
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

    payload = new uint8_t[payload_length];
    memcpy(payload, frame + 40, payload_length);

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



