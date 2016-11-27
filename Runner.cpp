

#include <memory>
#include "Runner.h"
#include "store/Device.h"
#include "store/EthernetStore.h"
#include "store/IPv6Store.h"

void Runner::run() {
    for(int i = 0; i<10; i++) {
        auto raw_frame = state->device->listen();
        auto eth_frame = raw_frame->handle(state);

        eth_frame->handle(state);

        //state->ipv6Store->handleAll();

    }
}
