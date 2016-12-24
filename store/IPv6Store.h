#ifndef ZSC_IPV6STORE_H
#define ZSC_IPV6STORE_H


#include <cstdint>

class IPv6Store{
    uint8_t* myIP;
public:
    IPv6Store();
    IPv6Store(uint8_t* ip);

    uint8_t* getMyIp();
};


#endif //ZSC_IPV6STORE_H
