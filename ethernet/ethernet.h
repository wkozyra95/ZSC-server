#ifndef INIT_DEVICE_H
#define INIT_DEVICE_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct eth_frame {
    unsigned char dest[6];
    unsigned char source[6];
    unsigned char type[2];
    unsigned char* payload;
    ssize_t payloadSize;
};

struct eth_frame_raw {
    unsigned char* frame;
    ssize_t framesize;
};


void init_ethernet();
struct eth_frame* get_next_frame();


#endif /* INIT_DEVICE_H */
