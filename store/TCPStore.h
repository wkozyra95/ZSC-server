#ifndef ZSC_TCPSTORE_H
#define ZSC_TCPSTORE_H

#include <unordered_map>
#include <memory>
#include <string>
#include "./TCPConection.h"

class TCPStore {
    private:
        std::unordered_map<
            std::string,
            std::shared_ptr<TCPConection>
            > mapping;
    public:
        void getConnection(uint8_t* ip, uint16_t port);
        void createConnection(uint8_t*ip, uint16_t port);

};

#endif //ZSC_TCPSTORE_H
