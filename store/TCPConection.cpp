#include "./TCPConection.h"
#include <cstring>



TCPConection::TCPConection(
        uint8_t* ip, uint16_t sender_port, uint16_t receiver_port, TCPState state) {
    this->ip = new uint8_t[16];
    memcpy(this->ip, ip, 16);

    this->receiver_port = receiver_port;
    this->sender_port = sender_port;

    this->state = state;
    this->ack_index = 0;
    this->seq_number = 0;
    this->ack_seq_number = 0;
}

