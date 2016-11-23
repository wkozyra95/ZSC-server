#ifndef ZSC_RUNNER_H
#define ZSC_RUNNER_H

#include <memory>
#include "Device.h"


class Runner {
private:
    std::shared_ptr<Device> device;
public:
    void run();
    Runner();
};



#endif //ZSC_RUNNER_H
