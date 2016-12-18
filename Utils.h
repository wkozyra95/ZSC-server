#ifndef ZSC_UTILS_H
#define ZSC_UTILS_H

#include <string>

class Utils {
public:
    std::string static hex_format_display(uint8_t *data, ssize_t size);

    std::string static decimal_format_display(uint8_t *data, ssize_t size);

    uint16_t static checksum(uint8_t* data, int len);
};


#endif //ZSC_UTILS_H
