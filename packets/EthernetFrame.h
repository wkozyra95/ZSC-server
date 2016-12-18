#ifndef ZSC_ETHERNETFRAME_H
#define ZSC_ETHERNETFRAME_H

#include "../store/State.h"


class EthernetFrame{
private:
    uint8_t source[6];
    uint8_t destination[6];
    uint8_t type[2];
    uint8_t *payload;
    ssize_t payloadSize;

    std::string detectSpecialAddress(std::string basic_string);
    std::string detectType(std::string basic_string);
public:
    EthernetFrame(uint8_t* frame, ssize_t ssize);
    EthernetFrame(
            uint8_t* destination,
            uint16_t type,
            uint8_t* payload,
            ssize_t payloadSize
    );
    void handle(std::shared_ptr<State> state);
    void respond(std::shared_ptr<State> state);

    void parse(uint8_t* frame, ssize_t ssize);
    void displayFrame();
    void displayFrameLong();
};


#endif //ZSC_ETHERNETFRAME_H
