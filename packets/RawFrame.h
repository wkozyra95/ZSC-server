#ifndef ZSC_RAWFRAME_H
#define ZSC_RAWFRAME_H


#include <cstdint>
#include <zconf.h>
#include "AbstractPacket.h"

class RawFrame: public AbstractPacket {
public:
    uint8_t* frame;
    ssize_t size;

    RawFrame(uint8_t *frame, ssize_t size);

    virtual void handle() override;
};


#endif //ZSC_RAWFRAME_H
