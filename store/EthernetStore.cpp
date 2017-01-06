
#include <cstring>
#include "EthernetStore.h"

uint8_t *EthernetStore::getMacForIP(uint8_t *ip) {
    std::string ip_str(ip, ip+16);
//    uint8_t example_mac[] = { 0x10, 0x22, 0x33, 0x44, 0x55, 0x66 };
    auto mac = new uint8_t[6];
    std::copy(mapping[ip_str].begin(), mapping[ip_str].end(), mac);
//    memcpy(mac, example_mac, 6);
    return mac;
}



void EthernetStore::registerMAC(uint8_t* ip, uint8_t* mac) {
    std::string ip_string(ip, ip+16);
    std::vector<uint8_t> mac_vec(mac, mac+6);

    mapping[ip_string] = mac_vec;
}

