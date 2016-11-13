#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "eth_utils.h"
#include "ethernet.h"

void printHex(unsigned char* text, ssize_t length);

struct eth_frame* create_eth_frame (
        unsigned char* destMac, unsigned char* sourceMac, unsigned char* type,
        unsigned char* payload, int payloadSize
    )  {

    struct eth_frame* frame = malloc(sizeof(struct eth_frame));

    memcpy(frame->dest, destMac, 6);
    memcpy(frame->source, sourceMac, 6);
    memcpy(frame->type, type, 2);

    frame->payload = malloc(payloadSize * sizeof(unsigned char));
    memcpy(frame->payload, payload, payloadSize * sizeof(unsigned char));
    frame->payloadSize = payloadSize;

    return frame;
}

/*
 * Parse ethernet frame from binary data
 */
struct eth_frame* raw_to_eth(struct eth_frame_raw* frame) {
    unsigned char* dest = frame->frame;
    unsigned char* source = frame->frame + 6;
    unsigned char* type = frame->frame + 12;
    unsigned char* payload = frame->frame + 14;
    ssize_t payload_length = frame->framesize - 14;

    return create_eth_frame(dest, source, type, payload, payload_length);
}

/*
 * Create raw ethernet frame
 */
struct eth_frame_raw* eth_to_raw(struct eth_frame* frame ) {
    ssize_t frame_length = 14 + frame->payloadSize;
    unsigned char* rawFrame = malloc(sizeof(unsigned char) * frame_length);

    memcpy(frame->dest, rawFrame, 6);
    memcpy(frame->source, rawFrame + 6, 6);
    memcpy(frame->dest, rawFrame + 12, 2);
    memcpy(frame->dest, rawFrame + 14, (unsigned int) frame->payloadSize);
}

/*
 * Display ethernet
 */
void display_eth_frame(struct eth_frame* frame) {
    puts("Ethernet frame:");
    printf("size: %zi \t data size: %zi\n", 14+frame->payloadSize, frame->payloadSize);
    puts("Destination mac:");
    printHex(frame->dest, 6);
    puts("\nSource mac:");
    printHex(frame->source, 6);
    puts("\nType:");
    printHex(frame->type, 2);
    puts("\nPayload:");
    printHex(frame->payload, frame->payloadSize);
    puts("\n");
}

void display_raw(struct eth_frame_raw* frame) {
    printHex(frame->frame, frame->framesize);
}

void printHex(unsigned char* text, ssize_t length) {
    for(int i = 0; i<length; i++) {
        printf("%02x:", text[i]);
    }
}
