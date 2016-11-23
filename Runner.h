#ifndef ZSC_RUNNER_H
#define ZSC_RUNNER_H


#include "Device.h"

enum L3protocol {IPv4, IPv6};

class Runner {
private:
    Device *device;
public:
    void run();
    Runner();
};



#endif //ZSC_RUNNER_H
