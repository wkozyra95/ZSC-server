#ifndef ZSC_TCPCONNECTION_H
#define ZSC_TCPCONNECTION_H

#include <cstdint>

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
    private:
        uint16_t sender_port;
        uint16_t receiver_port;
        uint8_t* ip;
        TCPState state;       
    public:
        TCPConection(uint8_t* ip, uint16_t sender_port, uint16_t receiver_port, TCPState state);
        void changeState(TCPState state);
};

#endif // ZSC_TCPCONNECTION_H
