#ifndef ZSC_STATE_H
#define ZSC_STATE_H

#include <memory>

class EthernetStore;
class Device;
class IPv6Store;
class TCPStore;

class State {
public:
    std::shared_ptr<EthernetStore> ethernetStore;
    std::shared_ptr<Device> device;
    std::shared_ptr<IPv6Store> ipv6Store;
    std::shared_ptr<TCPStore> tcpStore;
    //...
    State();

    State(
            const std::shared_ptr<Device> device,
            const std::shared_ptr<EthernetStore> ethernetStore, 
            const std::shared_ptr<IPv6Store> ipv6Store,
            const std::shared_ptr<TCPStore> tcpStore
            );
};


#endif //ZSC_STATE_H
