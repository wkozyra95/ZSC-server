#ifndef ZSC_RUNNER_H
#define ZSC_RUNNER_H


#include "store/State.h"

class Runner {
private:
    const std::shared_ptr<State> state = std::make_shared<State>();
public:
    void run();
    Runner() {
    };
};



#endif //ZSC_RUNNER_H
