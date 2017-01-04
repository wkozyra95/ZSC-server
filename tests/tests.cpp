#include <memory>
#include "Test.h"
#include "../packets/RawFrame.h"
#include "../Utils.h"
#include <iostream>
#include <algorithm>

int main() {
    std::string myMAC("102233445566");
    std::string myIP("20010db80000000000000000c0ca1eae");
    std::string myPort("2332");
    std::string otherMAC("665544332211");
    std::string otherIP("20010db80000000000000000c0ca1eaf");
    std::string otherPort("2442");

    std::string empty = "";
    std::vector<std::shared_ptr<RawFrame> > in1;

    //ICMP
    std::cout << "TEST: ICMP" << std::endl;
    in1.push_back(Utils::hexToFrame(empty +
                "3333ffca1eaf"+otherMAC+"86dd" +
                "6000000000203aff"+otherIP+"ff0200000000000000000001ffca1eae" +
                "87002f2300000000"+myIP+"0101"+otherMAC));
    std::vector<std::shared_ptr<RawFrame> > out1;
    out1.push_back(Utils::hexToFrame(empty +
                otherMAC+myMAC+"86dd"+
                "60000000" + "0020" + "3a" + "ff" +myIP+otherIP+
                "8800554060000000"+myIP+"0201"+myMAC));
    auto test = new Test(in1, out1);
    test->runTest();

    std::vector<std::shared_ptr<RawFrame>> in2;
    std::vector<std::shared_ptr<RawFrame>> out2;


    std::cout<<std::endl<< "TEST: TCP" << std::endl;
    // SYN
    in2.push_back(Utils::hexToFrame(empty
                + myMAC + otherMAC + "86dd" 
                + "60000000" + "0014" + "06" + "ff" + otherIP + myIP
                + otherPort + myPort
                + "29292929" + "00000000"
                + "5" + "0" + "02" // data/4 + res?flafNS + SYN
                + "03e8" + "63cd" + "0000"
                ));
    // SYN ACK
    out2.push_back(Utils::hexToFrame(empty
                + otherMAC + myMAC + "86dd"
                + "60000000" + "0014" + "06" + "ff"
                + myIP + otherIP 
                + myPort + otherPort
                + "12131415" + "2929292a"
                + "5" + "0" + "12" //syn and ack
                + "03e8" + "e576" + "0000"
                ));
    // ACK
    in2.push_back(Utils::hexToFrame(empty
                + myMAC + otherMAC + "86dd"
                + "60000000" + "0014" + "06" + "ff"
                + otherIP + myIP
                + otherPort + myPort
                + "2929292a" + "12131416"
                + "5" + "0" + "10" // ack
                + "03e8" + "5189" + "0000"
                ));

    // receive data ACK PSH
    in2.push_back(Utils::hexToFrame(empty
                + myMAC + otherMAC + "86dd"
                + "60000000" + "0014" + "06" + "ff"
                + otherIP + myIP
                + otherPort + myPort
                + "2929292a" + "12131416"
                + "5" + "0" + "10" // ack , psh
                + "03e8" + "5189" + "0000"
                ));
    
    std::reverse(in2.begin(), in2.end()); 
    auto test2 = new Test(in2, out2);
    test2->runTest();

    std::cout << "END" << std::endl;

}
