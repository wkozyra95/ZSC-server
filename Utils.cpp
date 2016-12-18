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

uint16_t Utils::checksum(uint8_t* buf, int size) {

    unsigned sum = 0;
    int i;

    /* Accumulate checksum */
    for (i = 0; i < size - 1; i += 2)
    {
        unsigned short word16 = *(unsigned short *) &buf[i];
        sum += word16;
    }

    /* Handle odd-sized case */
    if (size & 1)
    {
        unsigned short word16 = (unsigned char) buf[i];
        sum += word16;
    }

    /* Fold to get the ones-complement result */
    while (sum >> 16) sum = (sum & 0xFFFF)+(sum >> 16);

    /* Invert to get the negative in ones-complement arithmetic */
    return (uint16_t) ~sum;
}