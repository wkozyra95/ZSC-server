
#ifndef ZSC_ETHERNETSTORE_H
#define ZSC_ETHERNETSTORE_H


#include <cstdint>
#include <unordered_map>

class EthernetStore {
    uint8_t* mapping;
public:
    EthernetStore();

    uint8_t* getMacForIP(uint8_t* ip);
};


#endif //ZSC_ETHERNETSTORE_H
