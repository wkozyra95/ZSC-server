#include <string>
#include "Utils.h"

std::string Utils::hex_format_display(uint8_t *data, ssize_t size) {
    char* dataDisplay = new char[size*3];
    for(int i = 0; i<size; i++) {
        sprintf(dataDisplay + i*3, "%02X:", data[i]);
    }
    std::string str(dataDisplay);
    delete[] dataDisplay;
    return str;
}
