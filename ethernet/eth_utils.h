#ifndef ZSC_ETH_UTILS_H
#define ZSC_ETH_UTILS_H

#include <stdint.h>
#include "ethernet.h"



struct eth_frame* raw_to_eth(struct eth_frame_raw* frame);
struct eth_frame_raw* eth_to_raw(struct eth_frame* frame);
void display_eth_frame(struct eth_frame* frame);
void display_raw(struct eth_frame_raw* frame);


#endif //ZSC_ETH_UTILS_H
