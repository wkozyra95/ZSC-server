#include "./TCPStore.h"
#include "../Utils.h"

TCPStore::getConnection(uint8_t* ip, uint16_t port) {
    auto key = Utils::hex_format_displayi(ip, 16) + Utils::hex_format_display(&port, 2)

    return this->mapping[key]; 
}


TCPStore::createConnection(uint8_t* ip, uint16_t port) {
    
}

