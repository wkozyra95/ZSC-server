#include <cstring>
#include "IPv6Store.h"

uint8_t *IPv6Store::getMyIp() {
    return myIP;
}

IPv6Store::IPv6Store() {
    const uint8_t ip[] = {
            0x20, 0x01,
            0x0d, 0xb8,
            0x00, 0x00,
            0x00, 0x00,
            0x00, 0x00,
            0x00, 0x00,
            0xc0, 0xca,
            0x1e, 0xaf
    };
    myIP = new uint8_t[16];
    memcpy(myIP, ip, 16);
}

IPv6Store::IPv6Store(uint8_t* ip) {
    myIP = new uint8_t[16];
    memcpy(myIP, ip, 16);
}


