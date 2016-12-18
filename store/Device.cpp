#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <linux/if_ether.h>
#include <iostream>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>
#include "Device.h"

void Device::init() {
    const char* if_name = "eth0";



    /*
     * AF_PACKET - low level packets
     * SOCK_RAW - packets are passed to and from the device driver without any
       changes in the packet data
       ETH_P_ALL - all packets
     */
    if ((socketfd = socket(AF_PACKET, SOCK_RAW, ETH_P_ALL)) == -1) {
        perror("listener: socketfd");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    ifreq = (struct ifreq*) new uint8_t[sizeof(struct ifreq)];
    memset(ifreq, 0, sizeof(struct ifreq));
    memcpy(ifreq->ifr_name, if_name, IFNAMSIZ-1);
    ioctl(socketfd, SIOCGIFFLAGS, &ifreq); //get flags
    ifreq->ifr_flags |= IFF_PROMISC;
    ioctl(socketfd, SIOCSIFFLAGS, &ifreq); //set flags

    ifidx = (struct ifreq*) new uint8_t[sizeof(struct ifreq)];
    memset(ifidx, 0, sizeof(struct ifreq));
    memcpy(ifidx->ifr_name, if_name, IFNAMSIZ-1);
    if (ioctl(socketfd, SIOCGIFINDEX, ifidx) < 0) {
        perror("SIOCGIFINDEX");
    }

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

    // init MAC
    struct ifreq if_mac;
    memset(&if_mac, 0, sizeof(struct ifreq));
    strncpy(if_mac.ifr_name, if_name, IFNAMSIZ-1);
    if (ioctl(socketfd, SIOCGIFHWADDR, &if_mac) < 0)
        perror("SIOCGIFHWADDR");
    memcpy(MAC, if_mac.ifr_hwaddr.sa_data, 6);

    //init socket_destianation
    socket_address = new sockaddr_ll;
    socket_address->sll_ifindex = ifidx->ifr_ifindex;
    socket_address->sll_halen = ETH_ALEN;

}

std::shared_ptr<RawFrame> Device::listen() {
    ssize_t numbytes = recvfrom(socketfd, deviceBuffer, 1600, 0, NULL, NULL);
    return std::make_shared<RawFrame>(deviceBuffer, numbytes);
}

void Device::sendFrame(uint8_t *payload, ssize_t payloadSize) {

    if (sendto(socketfd, payload, payloadSize, 0, (struct sockaddr*)socket_address, sizeof(struct sockaddr_ll)) < 0)
        printf("Send failed\n");

    std::cout << "ewfe" << std::endl;

}

Device::Device() {
    uint8_t mac[] = {0x44, 0x8A, 0x5b, 0xef, 0x70, 0x24};
    memcpy(MAC, mac, 6);
    init();
}

uint8_t *Device::getMAC() {
    return MAC;
}


