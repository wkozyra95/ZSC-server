#include <string>
#include "Utils.h"

std::string Utils::hex_format_display(uint8_t *data, ssize_t size) {
    char* dataDisplay = new char[size*3];
    for(int i = 0; i<size; i++) {
        sprintf(dataDisplay + i*3, "%02X:", data[i]);
    }
    std::string str(dataDisplay);
    delete[] dataDisplay; //TODO not working
    return str;
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

uint16_t checksum (uint8_t data[], int len)
{
    uint16_t *addr = (uint16_t*)data;
    int len16 = (len + 1) / 2;
    uint32_t sum = 0;
    uint16_t result = 0;

    while (len16 > 1) {
        sum += *(addr++);
        len16 -= 2;
    }

    if (len16 > 0) {
        sum += *(uint8_t *) addr;
    }

    while (sum >> 16) {
        sum = (sum & 0xffff) + (sum >> 16);
    }

    result = ~sum;

    return (result);
}