#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <unistd.h>
#include "eth_utils.h"

#define ETHER_TYPE	0x0800

static int listen_socket;
static unsigned char* frame_buffer;

void init_ethernet(char *dev)
{
    char* if_name = "lo";

    /* Open PF_PACKET socket, listening for EtherType ETHER_TYPE */
    if ((listen_socket = socket(PF_PACKET, SOCK_RAW, htons(ETHER_TYPE))) == -1) {
        perror("listener: socket");
        exit(-1);
    }
    struct ifreq ifopts;
    strncpy(ifopts.ifr_name, if_name, IFNAMSIZ-1);
    int sockopt;
    ioctl(listen_socket, SIOCGIFFLAGS, &ifopts);
    ifopts.ifr_flags |= IFF_PROMISC;
    ioctl(listen_socket, SIOCSIFFLAGS, &ifopts);

    /* Allow the socket to be reused - incase connection is closed prematurely */
    if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt) == -1) {
        perror("setsockopt");
        close(listen_socket);
        exit(EXIT_FAILURE);
    }

    /* Bind to device */
    if (setsockopt(listen_socket, SOL_SOCKET, SO_BINDTODEVICE, if_name, IFNAMSIZ-1) == -1)	{
        perror("SO_BINDTODEVICE");
        close(listen_socket);
        exit(EXIT_FAILURE);
    }

    frame_buffer = malloc(1600);

}

void get_next_frame() {
    printf("listener: Waiting to recvfrom...\n");
    ssize_t numbytes = recvfrom(listen_socket, frame_buffer, 1600, 0, NULL, NULL);
    struct eth_frame_raw frame;
    frame.frame = frame_buffer;
    frame.framesize = numbytes;

    struct eth_frame* parsed = raw_to_eth(&frame);
    display_eth_frame(parsed);
    display_raw(&frame);

}