


#include <memory>
#include "Test.h"
#include "../packets/RawFrame.h"
#include "../Utils.h"
#include <iostream>

int main() {
    std::string empty = "";
    std::vector<std::shared_ptr<RawFrame> > in1;

    //ICMP
    std::cout << "TEST: ICMP" << std::endl;
    in1.push_back(Utils::hexToFrame(empty +
                "3333ffca1eaf"+"665544332211"+"86dd" + 
                "6000000000203aff"+"20010db80000000000000000c0ca1eaf"+"ff0200000000000000000001ffca1eae" + 
                "87002f2300000000"+"20010db80000000000000000c0ca1eae"+"0101"+"665544332211"));
    std::vector<std::shared_ptr<RawFrame> > out1;
    out1.push_back(Utils::hexToFrame(empty +
                "665544332211"+"102233445566"+"86dd"+
                "6000000000203aff"+"20010db80000000000000000c0ca1eae"+"20010db80000000000000000c0ca1eaf"+
                "8800554060000000"+"20010db80000000000000000c0ca1eae"+"0201"+"102233445566"));
    auto test = new Test(in1, out1);
    test->runTest();

    std::cout << "END" << std::endl;

}
