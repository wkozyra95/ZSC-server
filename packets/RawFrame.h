#ifndef ZSC_RAWFRAME_H
#define ZSC_RAWFRAME_H


#include "EthernetFrame.h"
#include "../store/State.h"


class RawFrame {
private:
    uint8_t* frame;
    ssize_t size;
public:
    RawFrame(uint8_t *frame, ssize_t size);

    std::shared_ptr<EthernetFrame> handle(std::shared_ptr<State> state);
    void send(std::shared_ptr<State> state);
};


#endif //ZSC_RAWFRAME_H
