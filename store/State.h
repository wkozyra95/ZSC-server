#ifndef ZSC_STATE_H
#define ZSC_STATE_H

#include <iostream>
#include <memory>
#include "EthernetStore.h"
#include "Device.h"
#include "IPv6Store.h"

class State {
public:
    std::shared_ptr<EthernetStore> ethernetStore = std::make_shared<EthernetStore>();
    std::shared_ptr<Device> device = std::make_shared<Device>();
    std::shared_ptr<IPv6Store> ipv6Store = std::make_shared<IPv6Store>();
    //...
    State() {
    }
};


#endif //ZSC_STATE_H
