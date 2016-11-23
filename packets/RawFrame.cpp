#include <cstring>
#include <iostream>
#include "RawFrame.h"
#include "EthernetFrame.h"

RawFrame::RawFrame(uint8_t *frame, ssize_t size) {
    this->frame = new uint8_t[size];
    memcpy(this->frame, frame, size);
    this->size = size;
}

void RawFrame::handle() {
    EthernetFrame* ethernetFrame = new EthernetFrame(this);
    if(size <= 14){
        std::cout << "Invalid Frame(to short)" << std::endl;
        return;
    }
    ethernetFrame->handle();
}

