

#include <memory>
#include "Runner.h"

void Runner::run() {
    for(int i = 0; i<10; i++) {
        std::shared_ptr<RawFrame> frame = device->listen();
        frame->handle();
    }
}

Runner::Runner() {
   device = std::make_shared<Device>();
}