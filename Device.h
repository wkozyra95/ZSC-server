#ifndef ZSC_DEVICE_H
#define ZSC_DEVICE_H


#include "packets/RawFrame.h"

class Device {
private:
    int socketfd;
    uint8_t deviceBuffer[1600];
    void init();
public:
    RawFrame * listen();

    Device();
};


#endif //ZSC_DEVICE_H
