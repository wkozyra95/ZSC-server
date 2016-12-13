
#include "EthernetStore.h"

uint8_t *EthernetStore::getMacForIP(uint8_t *ip) {
    return mapping;
}

EthernetStore::EthernetStore() {
    mapping = new uint8_t[6];
}
