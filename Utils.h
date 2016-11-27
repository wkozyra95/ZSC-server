#ifndef ZSC_UTILS_H
#define ZSC_UTILS_H

#include <string>

class Utils {
public:
    std::string static hex_format_display(uint8_t *data, ssize_t size);

    std::string static decimal_format_display(uint8_t *data, ssize_t size);
};


#endif //ZSC_UTILS_H
