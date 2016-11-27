
#include "State.h"
#include "EthernetStore.h"
#include "Device.h"
#include "IPv6Store.h"

State::State() {
    ethernetStore = std::make_shared<EthernetStore>();
    device = std::make_shared<Device>();
    ipv6Store = std::make_shared<IPv6Store>();
}
