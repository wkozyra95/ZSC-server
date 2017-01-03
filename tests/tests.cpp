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

    std::vector<std::shared_ptr<RawFrame>> in2;
    std::vector<std::shared_ptr<RawFrame>> out2;


    std::cout<<std::endl<< "TEST: TCP" << std::endl;
    in2.push_back(Utils::hexToFrame(empty
                                    + "3333ffca1eaf" //destination
                                    + "665544332211" //source
                                    + "86dd" //type (ipv6)
                                    + "600000" //version and flow label
                                    + "0028" //payload length
                                    + "06" // next header (tcp)
                                    + "40" //hop limit
                                    + "20010db80000000000000000c0ca1eaf" //source
                                    + "ff0200000000000000000001ffca1eae" //destination
                                    + "c435" //source port
                                    + "0016" //destination port
                                    + "1111" //sequence number
                                    + "0000" //acknowledgement number
                                    + "a" //header length
                                    + "0" //reserved + NS
                                    + "02" // syn flag set
                                    + "7080" //window size
                                    + "todo" //checksum
                                    + "0000" //urgent pointer
                                    + "00000000000000000000" //empty options
                                     ));

    out2.push_back(Utils::hexToFrame(empty
                                     + "665544332211"
                                     + "3333ffca1eaf"
                                     + "86dd"
                                     + "600000"
                                     + "0028"
                                     + "06"
                                     + "40"
                                     + "ff0200000000000000000001ffca1eae"
                                     + "20010db80000000000000000c0ca1eaf"
                                     + "0016"
                                     + "c435"
                                     + "1234"
                                     + "1112"
                                     + "a"
                                     + "0"
                                     + "12" //syn and flag set
                                     + "6f90"
                                     + "todo" //checksum
                                     + "0000" // urgent pointer
                                     + "00000000000000000000" //empty options
                                      ));

    auto test2 = new Test(in2, out2);
    test2->runTest();

    std::cout << "END" << std::endl;

}