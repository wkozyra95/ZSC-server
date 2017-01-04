#include "./TCPStore.h"
#include "../Utils.h"
#include <iostream>

std::shared_ptr<TCPConection> TCPStore::getConnection(
        uint8_t* ip, 
        uint16_t port, 
        uint16_t receiver_port) {
    std::string key =         Utils::hex_format_display(ip, 14) + 
        Utils::hex_format_display(ip, 14) + 
        Utils::hex_format_display((uint8_t*) &port, 2) + 
        Utils::hex_format_display((uint8_t*) &receiver_port, 2);

    auto connection = this->mapping[key]; 
    if (connection == std::shared_ptr<TCPConection>()) {
       this->mapping[key] = std::make_shared<TCPConection>(
               ip,
               port,
               receiver_port,
               LISTEN
               );
    }

    return this->mapping[key];
}


void TCPStore::createConnection(uint8_t* ip, uint16_t port) {
    
}

