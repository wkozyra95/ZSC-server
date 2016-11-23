#ifndef ZSC_ETHERNETFRAME_H
#define ZSC_ETHERNETFRAME_H

#include <stdint.h>
#include "RawFrame.h"
#include "../Utils.h"
#include "../Runner.h"


class EthernetFrame: public AbstractPacket {
public:
    EthernetFrame(RawFrame *frame);

    uint8_t source[6];
    uint8_t destination[6];
    uint8_t type[2];
    uint8_t *payload;
    ssize_t payloadSize;

    void parse(RawFrame *pFrame);

    virtual void handle() override;

    void displayFrame();

    void displayFrameLong();

    std::string detectSpecialAddress(std::string basic_string);

    std::string detectType(std::string basic_string);
};


#endif //ZSC_ETHERNETFRAME_H
