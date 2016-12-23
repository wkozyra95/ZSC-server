


#include <memory>
#include "Test.h"
#include "../packets/RawFrame.h"
#include "../Utils.h"

int main() {
    std::vector<std::shared_ptr<RawFrame> > in1;

    //ICMP
    in1.push_back(Utils::hexToFrame("3333ffca1eaf448a5bef702486dd6000000000203aff20010db80000000000000000c0ca1eaeff0200000000000000000001ffca1eaf87002f230000000020010db80000000000000000c0ca1eaf0101448a5bef7024"));
    std::vector<std::shared_ptr<RawFrame> > out1;
    auto test = new Test(in1, out1);
    test->runTest();


}
