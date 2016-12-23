
#ifndef ZSC_DEVICE_H
#define ZSC_DEVICE_H

#include <vector>
#include "../packets/RawFrame.h"

class Device {
private:
    std::vector<std::shared_ptr<RawFrame> > input;
    std::vector<std::shared_ptr<RawFrame> > output;
public:
    std::shared_ptr<RawFrame> listen();
    void sendFrame(uint8_t* payload, ssize_t payloadSize);
    uint8_t* getMAC();
    std::vector<std::shared_ptr<RawFrame> > getReceivedFrames();

    Device();
    Device(std::vector<std::shared_ptr<RawFrame>> input);
};

#endif //ZSC_DEVICE_H
