

#include "Runner.h"
#include "packets/RawFrame.h"

void Runner::run() {
    for(int i = 0; i<10; i++) {
        RawFrame* frame = device->listen();
        frame->handle();
    }
}

Runner::Runner() {
   device = new Device();
}