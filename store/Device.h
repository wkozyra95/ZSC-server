#ifndef ZSC_DEVICE_H
#define ZSC_DEVICE_H


#include "../packets/RawFrame.h"

class Device {
private:
    int socketfd;
    uint8_t MAC[6];
    uint8_t deviceBuffer[1600];
    void init();
public:
    std::shared_ptr<RawFrame> listen();
    uint8_t* getMAC();

    Device();
};


#endif //ZSC_DEVICE_H
