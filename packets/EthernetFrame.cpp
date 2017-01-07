#include <cstring>
#include <iostream>
#include <unordered_map>
#include "../Utils.h"

#include "../store/Device.h"
#include "EthernetFrame.h"
#include "IPv6Packet.h"

void EthernetFrame::parse(uint8_t* frame, ssize_t size) {
    uint8_t * dest = frame;
    uint8_t * source = frame + 6;
    uint8_t * type = frame + 12;
    uint8_t * payload = frame + 14;
    ssize_t payload_length = size - 14;

    memcpy(this->destination, dest, 6);
    memcpy(this->source, source, 6);
    memcpy(this->type, type, 2);

    this->payload = new uint8_t[payload_length];
    memcpy(this->payload, payload, payload_length * sizeof(uint8_t));
    this->payloadSize = payload_length;
}

EthernetFrame::EthernetFrame(uint8_t* frame, ssize_t ssize) {
    parse(frame, ssize);
}

EthernetFrame::EthernetFrame(uint8_t *destination, uint16_t type, uint8_t *payload, ssize_t payloadSize) {
    memcpy(this->destination, destination, 6);

    this->type[0] = (uint8_t) (type >> 8);
    this->type[1] = (uint8_t) type;


    this->payload = new uint8_t[payloadSize];
    memcpy(this->payload, payload, payloadSize);

    this->payloadSize = payloadSize;
}


void EthernetFrame::respond(std::shared_ptr<State> state) {
    auto raw_frame = new uint8_t[payloadSize + 14];
    memcpy(raw_frame, destination, 6);
    memcpy(raw_frame + 6, state->device->getMAC(), 6);
    memcpy(raw_frame + 12, type, 2);
    memcpy(raw_frame + 14, payload, payloadSize);

    auto result = std::make_shared<RawFrame>(
            raw_frame,
            payloadSize + 14
    );

    result->send(state);
}


void EthernetFrame::handle(std::shared_ptr<State> state) {
    // displayFrameLong();
    std::string type = Utils::hex_format_display(this->type, 2);
    if(type == "08:00:") {
//        printf("IPv4 packet\n");
//        displayFrameLong();
//        printf("\n");
    } else if( type == "86:DD:") {
        //printf("IPv6 packet\n");
        //displayFrameLong();
        auto fragment = std::make_shared<IPv6Packet>(payload, payloadSize);
        fragment->handle(state, this->source);
        //printf("\n");
    } else {
//        printf("Unknown packet\n");
//        displayFrameLong();
        //printf("\n");
    }
}

std::unordered_map<std::string, std::string> ethernet_types = {
        {"08:00", "Internet Protocol version 4 (IPv4)"},
        {"08:06", "Address Resolution Protocol (ARP)"},
        {"08:42", "Wake-on-LAN[4]"},
        {"22:F3", "IETF TRILL Protocol"},
        {"60:03", "DECnet Phase IV"},
        {"80:35", "Reverse Address Resolution Protocol"},
        {"80:9B", "AppleTalk (Ethertalk)"},
        {"80:F3", "AppleTalk Address Resolution Protocol (AARP)"},
        {"81:00", "VLAN-tagged frame (IEEE 802.1Q) and Shortest Path Bridging IEEE 802.1aq[5]"},
        {"81:37", "IPX"},
        {"82:04", "QNX Qnet"},
        {"86:DD", "Internet Protocol Version 6 (IPv6)"},
        {"88:08", "Ethernet flow control"},
        {"88:19", "CobraNet"},
        {"88:47", "MPLS unicast"},
        {"88:48", "MPLS multicast"},
        {"88:63", "PPPoE Discovery Stage"},
        {"88:64", "PPPoE Session Stage"},
        {"88:7B", "HomePlug 1.0 MME"},
        {"88:8E", "EAP over LAN (IEEE 802.1X)"},
        {"88:92", "PROFINET Protocol"},
        {"88:9A", "HyperSCSI (SCSI over Ethernet)"},
        {"88:A2", "ATA over Ethernet"},
        {"88:A4", "EtherCAT Protocol"},
        {"88:A8", "Provider Bridging (IEEE 802.1ad) & Shortest Path Bridging IEEE 802.1aq[5]"},
        {"88:AB", "Ethernet Powerlink[citation needed]"},
        {"88:B8", "GOOSE (Generic Object Oriented Substation event)"},
        {"88:B9", "GSE (Generic Substation Events) Management Services"},
        {"88:CC", "Link Layer Discovery Protocol (LLDP)"},
        {"88:CD", "SERCOS III"},
        {"88:E1", "HomePlug AV MME[citation needed]"},
        {"88:E3", "Media Redundancy Protocol (IEC62439-2)"},
        {"88:E5", "MAC security (IEEE 802.1AE)"},
        {"88:E7", "Provider Backbone Bridges (PBB) (IEEE 802.1ah)"},
        {"88:F7", "Precision Time Protocol (PTP) over Ethernet (IEEE 1588)"},
        {"88:FB", "Parallel Redundancy Protocol (PRP)"},
        {"89:02", "IEEE 802.1ag Connectivity Fault Management (CFM) Protocol / ITU-T Recommendation Y.1731 (OAM)"},
        {"89:06", "Fibre Channel over Ethernet (FCoE)"},
        {"89:14", "FCoE Initialization Protocol"},
        {"89:15", "RDMA over Converged Ethernet (RoCE)"},
        {"89:1D", "TTEthernet Protocol Control Frame (TTE)"},
        {"89:2F", "High-availability Seamless Redundancy (HSR)"},
        {"90:00", "Ethernet Configuration Testing Protocol[6]"},
        {"91:00", "VLAN-tagged (IEEE 802.1Q) frame with double tagging"}
};

std::unordered_map<std::string, std::string> ethernet_multicasts = {
        {"00:00:00:00:00:00", "Invalid MAC"},
        {"FF:FF:FF:FF:FF:FF", "broadcast"},
        {"01:00:0C:CC:CC:CC", "CDP (Cisco Discovery Protocol), VTP (VLAN Trunking Protocol)"},
        {"01:00:0C:CC:CC:CD", "Cisco Shared Spanning Tree Protocol Address"},
        {"01:80:C2:00:00:00", "Spanning Tree Protocol (for bridges) IEEE 802.1D"},
        {"01:80:C2:00:00:00", "Link Layer Discovery Protocol"},
        {"01:80:C2:00:00:03", "Link Layer Discovery Protocol"},
        {"01:80:C2:00:00:0E", "Link Layer Discovery Protocol"},
        {"01:80:C2:00:00:08", "Spanning Tree Protocol (for provider bridges) IEEE 802.1ad"},
        {"01:80:C2:00:00:01", "Ethernet flow control (Pause frame) IEEE 802.3x"},
        {"01:80:C2:00:00:02", "Ethernet OAM Protocol IEEE 802.3ah (A.K.A. \"slow protocols\")"},
        {"01:80:C2:00:00:30", "Ethernet CFM Protocol IEEE 802.1ag"},
        {"01:80:C2:00:00:3F", "Ethernet CFM Protocol IEEE 802.1ag"},
        {"01:00:5E:00:00:00", "IPv4 Multicast"},
        {"33:33", "IPv6 multicast"},
        {"01:0C:CD:01:00:00", "IEC 61850-8-1 GOOSE Type 1/1A"},
        {"01:0C:CD:01:01:FF", "IEC 61850-8-1 GOOSE Type 1/1A"},
        {"01:0C:CD:02:00:00", "GSSE (IEC 61850 8-1)"},
        {"01:0C:CD:02:01:FF", "GSSE (IEC 61850 8-1)"},
        {"01:0C:CD:04:00:00", "Multicast sampled values (IEC 61850 8-1)"},
        {"01:0C:CD:04:01:FF", "Multicast sampled values (IEC 61850 8-1)"},
        {"01:1B:19:00:00:00", "Precision Time Protocol (PTP) version 2 over Ethernet (Layer-2)"},
        {"01:80:C2:00:00:0E", "Precision Time Protocol (PTP) version 2 over Ethernet (Layer-2)"},
};

void EthernetFrame::displayFrame() {
    std::string source = Utils::hex_format_display(this->source, 6);
    std::string destination = Utils::hex_format_display(this->destination, 6);
    std::string type = Utils::hex_format_display(this->type, 2);
    std::cout << "Source: " << source << "\tDestination: " << destination << "\tType: " << type << std::endl;
}

void EthernetFrame::displayFrameLong() {
    std::string source = Utils::hex_format_display(this->source, 6);
    std::string destination = Utils::hex_format_display(this->destination, 6);
    std::string type = Utils::hex_format_display(this->type, 2);
    source += detectSpecialAddress(source);
    destination += detectSpecialAddress(destination);
    type += detectType(type);

    std::cout << "Source: " << source << "\tDestination: " << destination << "\tType: " << type << std::endl
        << "Size: " << this->payloadSize << "\tPayload: " << Utils::hex_format_display(this->payload, this->payloadSize) << std::endl;
}

std::string EthernetFrame::detectSpecialAddress(std::string basic_string) {
    for (auto it = ethernet_multicasts.begin(); it != ethernet_multicasts.end(); ++it) {
        if (0 == basic_string.compare(0, it->first.length(), it->first)) {
            return "(" + it->second + ")";
        }
    }
    return "";
}

std::string EthernetFrame::detectType(std::string basic_string) {
    for (auto it = ethernet_types.begin(); it != ethernet_types.end(); ++it) {
        if (0 == basic_string.compare(0, it->first.length(), it->first)) {
            return it->second;
        }
    }
    return "";
}

