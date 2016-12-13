#include "IPv6Store.h"

uint8_t *IPv6Store::getMyIp() {
    return myIP;
}

IPv6Store::IPv6Store() {
    myIP = new uint8_t[16];
}
