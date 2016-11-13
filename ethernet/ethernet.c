#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <linux/if_ether.h>
#include "eth_utils.h"


static int listen_socket;
static unsigned char* frame_buffer;

void init_ethernet() {
    char* if_name = "lo";

    struct ifreq ifopts;
    memcpy(ifopts.ifr_name, if_name, IFNAMSIZ-1);

    /*
     * AF_PACKET - low level packets
     * SOCK_RAW - packets are passed to and from the device driver without any
       changes in the packet data
       ETH_P_ALL - all packets
     */
    if ((listen_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1) {
        perror("listener: socket");
        exit(-1);
    }


    ioctl(listen_socket, SIOCGIFFLAGS, &ifopts); //get flags
    printf("%d\n", ifopts.ifr_flags);

    ifopts.ifr_flags |= IFF_PROMISC;
    printf("%d\n", ifopts.ifr_flags);
    ioctl(listen_socket, SIOCSIFFLAGS, &ifopts); //set flags
    printf("%d\n", ifopts.ifr_flags);

    int sockopt = 1;
    if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt) == -1) {
        perror("setsockopt");
        close(listen_socket);
        exit(EXIT_FAILURE);
    }

    /* Bind to device */
    if (setsockopt(listen_socket, SOL_SOCKET, SO_BINDTODEVICE, if_name, IFNAMSIZ - 1) == -1)	{
        perror("SO_BINDTODEVICE");
        close(listen_socket);
        exit(EXIT_FAILURE);
    }

    frame_buffer = malloc(1600);
}

struct eth_frame* get_next_frame() {
    printf("listener: Waiting to recvfrom...\n");
    ssize_t numbytes = recvfrom(listen_socket, frame_buffer, 1600, 0, NULL, NULL);
    struct eth_frame_raw frame;
    frame.frame = frame_buffer;
    frame.framesize = numbytes;

    struct eth_frame* parsed = raw_to_eth(&frame);
    display_eth_frame(parsed);
    return parsed;
}