#include <cstring>
#include <iostream>
#include "../store/State.h"
#include "RawFrame.h"

RawFrame::RawFrame(uint8_t *frame, ssize_t size) {
    this->frame = new uint8_t[size];
    memcpy(this->frame, frame, size);
    this->size = size;
}

std::shared_ptr<EthernetFrame> RawFrame::handle(std::shared_ptr<State> state) {
    return std::make_shared<EthernetFrame>(frame, size);
}
