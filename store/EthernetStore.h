
#ifndef ZSC_ETHERNETSTORE_H
#define ZSC_ETHERNETSTORE_H


#include <cstdint>
#include <unordered_map>
#include <vector>

class EthernetStore {
    std::unordered_map<std::string, std::vector<uint8_t> > mapping; // (ip, mac)
public:
    EthernetStore(){};
    void registerMAC(uint8_t* ip, uint8_t* mac);
    uint8_t* getMacForIP(uint8_t* ip);
};


#endif //ZSC_ETHERNETSTORE_H
