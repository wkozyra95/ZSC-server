
#include <cstring>
#include "EthernetStore.h"

uint8_t *EthernetStore::getMacForIP(uint8_t *ip) {
    return mapping;
}

EthernetStore::EthernetStore() {
//    uint8_t mac[] = {0x44, 0x8A, 0x5b, 0xef, 0x70, 0x21}; //TODO dynamic mapping
    uint8_t mac[] = {0x66, 0x55, 0x44, 0x33, 0x22, 0x11}; //TODO dynamic mapping
    mapping = new uint8_t[6];
    memcpy(mapping, mac, 6);
}
