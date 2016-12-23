
#ifndef ZSC_MOCKRUNNER_H
#define ZSC_MOCKRUNNER_H

#include "../store/State.h"
#include <memory>

class MockRunner {
    private:
        std::shared_ptr<State> state;
    public:
        MockRunner(std::shared_ptr<Device> device);
        void run();
};


#endif //ZSC_MOCKRUNNER_H
