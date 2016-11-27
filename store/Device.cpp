#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <linux/if_ether.h>

#include "Device.h"

void Device::init() {
    const char* if_name = "eth0";

    struct ifreq ifopts;
    memcpy(ifopts.ifr_name, if_name, IFNAMSIZ-1);

    /*
     * AF_PACKET - low level packets
     * SOCK_RAW - packets are passed to and from the device driver without any
       changes in the packet data
       ETH_P_ALL - all packets
     */
    if ((socketfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1) {
        perror("listener: socketfd");
        close(socketfd);
        exit(EXIT_FAILURE);
    }


    ioctl(socketfd, SIOCGIFFLAGS, &ifopts); //get flags
    ifopts.ifr_flags |= IFF_PROMISC;
    ioctl(socketfd, SIOCSIFFLAGS, &ifopts); //set flags

    int sockopt = 1;
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt) == -1) {
        perror("setsockopt");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    /* Bind to device */
    if (setsockopt(socketfd, SOL_SOCKET, SO_BINDTODEVICE, if_name, IFNAMSIZ - 1) == -1) {
        perror("SO_BINDTODEVICE");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

}

std::shared_ptr<RawFrame> Device::listen() {
    ssize_t numbytes = recvfrom(socketfd, deviceBuffer, 1600, 0, NULL, NULL);
    return std::make_shared<RawFrame>(deviceBuffer, numbytes);
}

Device::Device() {
    init();
}
