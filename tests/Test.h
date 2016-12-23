#ifndef ZSC_TEST_H
#define ZSC_TEST_H

#include <vector> 
#include <string>
#include <memory>
#include "../packets/RawFrame.h"

class Test {
private:
    std::vector<std::shared_ptr<RawFrame> > input;
    std::vector<std::shared_ptr<RawFrame> > output;
public:
    Test(std::vector<std::shared_ptr<RawFrame> > input, 
            std::vector<std::shared_ptr<RawFrame> > output);
    void runTest();
    void runChecksResults();
};


#endif //ZSC_TEST_H
