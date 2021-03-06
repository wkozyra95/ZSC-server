
#include "State.h"
#include "EthernetStore.h"
#include "Device.h"
#include "IPv6Store.h"
#include "TCPStore.h"

State::State() {
    ethernetStore = std::make_shared<EthernetStore>();
    device = std::make_shared<Device>();
    ipv6Store = std::make_shared<IPv6Store>();
    tcpStore = std::make_shared<TCPStore>();
}

State::State(
        const std::shared_ptr<Device> device,
        const std::shared_ptr<EthernetStore> ethernetStore,
        const std::shared_ptr<IPv6Store> ipv6Store,
        const std::shared_ptr<TCPStore> tcpStore) {

    this->device = device;
    this->ethernetStore = ethernetStore;
    this->ipv6Store = ipv6Store;
    this->tcpStore = tcpStore;
}
