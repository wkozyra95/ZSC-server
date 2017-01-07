#include "Utils.h"
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
std::string Utils::hex_format_display(uint8_t *data, ssize_t size) {
    std::stringstream stream;
    for(int i = 0; i<size; i++) {
        stream << std::setfill('0') << std::setw(2)<< std::uppercase << std::hex << (int) data[i] << ":";
    }
    return stream.str();
}

std::string Utils::decimal_format_display(uint8_t *data, ssize_t size) {
    char* dataDisplay = new char[size*4];
    for(int i = 0; i<size; i++) {
        sprintf(dataDisplay + i*4, "%03d.", data[i]);
    }
    std::string str(dataDisplay);
    delete[] dataDisplay;
    return str;
}

uint16_t Utils::checksum(uint8_t* buf, int size) {
    unsigned int sum = 0;
    int i;

    /* Accumulate checksum */
    for (i = 0; i < size - 1; i += 2) {
        unsigned short word16 = *(unsigned short *) &(buf[i]);
        sum += word16;
    }

    /* Handle odd-sized case */
    if (size & 1) {
        unsigned short word16 = (unsigned char) buf[i];
        sum += word16;
    }

    /* Fold to get the ones-complement result */
    while (sum >> 16) {
        sum = (sum & 0xFFFF)+(sum >> 16);
    }

    /* Invert to get the negative in ones-complement arithmetic */
    return (uint16_t) ~sum;
};

std::shared_ptr<RawFrame> Utils::hexToFrame(std::string number) {
    if(number.length() % 2 != 0) {
        std::cout << "ERROR: Invalid frame string: " << number << std::endl;
    }

    int frame_length = (number.length() + 1)/2;
    auto frame = new uint8_t[frame_length];
    
    auto getNum = [](char i) {
        if( i>='0' && i<='9'){
            return i - '0'; 
        } else if ( i>= 'A' && i<='F') {
            return 10 + i - 'A';
        } else if( i>= 'a' && i<='f') {
            return 10 + i - 'a';
        }
        std::cout << "Invalid number" << std::endl;
        return 0;
    };

    for (unsigned int i = 0; i < number.length(); i+=2) {
        frame[i/2] = getNum(number[i])*16 + getNum(number[i+1]);
    }     

    return std::make_shared<RawFrame>(frame, frame_length);
}
