#include <cstring>
#include <iostream>

#include "RawFrame.h"
#include "../store/Device.h"
#include "../Utils.h"

RawFrame::RawFrame(uint8_t *frame, ssize_t size) {
    this->frame = new uint8_t[size + 4];
    memcpy(this->frame, frame, size);
    this->size = size;
}

std::shared_ptr<EthernetFrame> RawFrame::handle(std::shared_ptr<State> state) {
    return std::make_shared<EthernetFrame>(frame, size);
}

void RawFrame::send(std::shared_ptr<State> state) {
    state->device->sendFrame(this->frame, this->size);

}

void RawFrame::display() {
    std::cout << Utils::hex_format_display(this->frame, this->size) << std::endl;
}
