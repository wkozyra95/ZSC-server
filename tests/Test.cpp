#include "Test.h"
#include "MockDevice.h"
#include "MockRunner.h"

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
}

void Test::runChecksResults() {

}
