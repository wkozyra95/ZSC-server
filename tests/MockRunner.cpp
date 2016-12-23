
#include "MockRunner.h"
#include "../packets/RawFrame.h"
#include "../store/State.h"
#include "../store/EthernetStore.h"
#include "../store/IPv6Store.h"
#include "./MockDevice.h"
#include <vector>
#include <iostream>

MockRunner::MockRunner(std::shared_ptr<Device> device) {
    this->state = std::make_shared<State>(
        device,
        std::make_shared<EthernetStore>(),
        std::make_shared<IPv6Store>()
    );
};

void MockRunner::run() {
    std::shared_ptr<RawFrame> frame = this->state->device->listen();
    //std::cout << "Start" << std::endl;
    while( frame != nullptr) {
        //frame->display();
        //std::cout << "ReadFrame" << std::endl;
        auto eth_frame = frame->handle(this->state);
        
        //std::cout << "ReadEthernet" << std::endl;
        eth_frame->handle(this->state);
        
        frame = this->state->device->listen();
    }
}
