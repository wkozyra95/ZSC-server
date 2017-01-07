#include "Test.h"
#include "MockDevice.h"
#include "MockRunner.h"
#include "../Utils.h"
#include <iostream>

Test::Test(
        std::vector<std::shared_ptr<RawFrame> > input,
        std::vector<std::shared_ptr<RawFrame> > output) {

    this->input = input;
    this->output = output;
}

void Test::runTest() {
    auto device = std::make_shared<Device>(this->input);
    auto runner = std::make_shared<MockRunner>(device);
    runner->run();

    runChecksResults(device->getReceivedFrames());
}

void Test::runChecksResults(std::vector<std::shared_ptr<RawFrame> > result) {
    bool testResult = true; // test successful
    int min_size = result.size()>output.size() ? output.size() : result.size();
    
    std::cout << "\033[33mexpected frames: " << output.size() << std::endl << "received: " << result.size() << "\033[0m" << std::endl << std::endl;
    for(int i = 0; i< min_size ; i++) {
        auto expected = Utils::hex_format_display(output[i]->frame, output[i]->size);
        auto received = Utils::hex_format_display(result[i]->frame, result[i]->size);
        if(expected.compare(received) != 0 ) {
            std::cout << "\033[31me: " + expected << std::endl << "r: " + received << "\033[0m" << std::endl << std::endl;
            testResult = false;
        }
    }
    if(result.size() > output.size()) {
        std::cout << "\033[31mReceived additional frames" << std::endl;
        for(unsigned int i = min_size ; i< result.size(); i++) {
            std::cout << Utils::hex_format_display(result[i]->frame, result[i]->size) << std::endl;
        }
        std::cout << "\033[0m" << std::endl;
        testResult = false;
    }

    if(result.size() < output.size()) {
        std::cout<< "\033[31mMissing frames" << std::endl;
        for(unsigned int i = min_size; i< output.size(); i++) {
            std::cout << Utils::hex_format_display(output[i]->frame, output[i]->size) << std::endl;
        }
        std::cout << "\033[0m" << std::endl;
        testResult = false;
    }

    if(testResult) {
        std::cout << "\033[32mTest completed successfully\033[0m" << std::endl;
    }
}
