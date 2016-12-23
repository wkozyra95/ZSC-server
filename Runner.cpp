

#include <memory>
#include <cstring>
#include <iostream>
#include "Runner.h"
#include "packets/IcmpPacket.h"

void Runner::run() {
    for(int i = 0; i<3; i++) {
//        auto raw_frame = state->device->listen();
//        auto eth_frame = raw_frame->handle(state);
//
//        eth_frame->handle(state);
        uint8_t ip[] = {
                0x20, 0x01,
                0x0d, 0xb8,
                0x00, 0x00,
                0x00, 0x00,
                0x00, 0x00,
                0x00, 0x00,
                0xc0, 0xca,
                0x1e, 0xaf
        };
        uint8_t flow[] = {0x02,0x02,0x02};
        uint8_t payload[] = {0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03};
        
         std::make_shared<IcmpPacket>(
            135,
            0,
            payload,
            28
        )->handle(state, ip);


// IPv6 test
//        std::make_shared<IPv6Packet>(
//                dest,
//                (uint8_t) 6,
//                (uint8_t) 0,
//                flow,
//                payload,
//                28
//        )->respond(state);
        //state->ipv6Store->handleAll();

    }
}
