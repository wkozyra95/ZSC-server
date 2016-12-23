
#include "MockDevice.h"
#include <cstring>

Device::Device(std::vector<std::shared_ptr<RawFrame> > input) {
    this->input = input;
}
Device::Device() {
}

std::shared_ptr<RawFrame> Device::listen(){
    if(this->input.empty()) return nullptr;
    auto result = this->input.back();
    this->input.pop_back();
    return result;
}

void Device::sendFrame(uint8_t* payload, ssize_t payloadSize) {
    this->output.push_back(
            std::make_shared<RawFrame>(payload, payloadSize)
            );
}

std::vector<std::shared_ptr<RawFrame> > Device::getReceivedFrames() {
    return output;
}

uint8_t* Device::getMAC() {
    uint8_t mac[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
    auto result = new uint8_t[6];
    memcpy(result, mac, 6);
    return result;
}
