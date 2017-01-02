#ifndef ZSC_TCPCONNECTION_H
#define ZSC_TCPCONNECTION_H

#include <cstdint>
#include <vector>

enum TCPState {  
    LISTEN = 1,
    SYN_SENT = 2,
    SYN_RECEIVED = 3,
    ESTABLISHED = 4,
    FIN_WAIT_ONE = 5,
    FIN_WAIT_TWO = 6,
    CLOSE_WAIT = 7,
    CLOSING = 8,
    LAST_ACK = 9,
    TIME_WAIT = 10,
    CLOSED = 11,
};

class TCPConection {
    public:
        uint16_t sender_port;
        uint16_t receiver_port;
        uint8_t* ip;
        TCPState state;
        uint32_t initial_seq_sender;
        uint32_t initial_seq_receiver;
        uint32_t ack_index; // max index received ack
        uint32_t seq_number; // max index send not necessary ack
        uint32_t ack_seq_number;
        std::vector<uint8_t> payload;
        TCPConection(uint8_t* ip, uint16_t sender_port, uint16_t receiver_port, TCPState state);
};

#endif // ZSC_TCPCONNECTION_H
