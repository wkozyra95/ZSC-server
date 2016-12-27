#include "TCPPacket.h"
#include <cstring>

TCPPacket::TCPPacket(uint8_t *packet, ssize_t size) {}

TCPPacket::TCPPacket(
        uint16_t source_port,
        uint16_t destination_port,
        uint32_t sequence_number,
        uint32_t ack_number,
        uint8_t data_offset,
        uint8_t flags,
        uint8_t NSflag,
        uint16_t window_size,
        uint16_t checksum,
        uint16_t urgent_pointer,
        uint8_t* payload,
        ssize_t payload_length
        ) {
    this->source_port = source_port;
    this->destination_port = destination_port;
    this->seq_number = sequence_number;
    this->ack_number = ack_number;
    this->data_offset = data_offset;
    this->isCWR = (flags & CWR) != 0;
    this->isECE = (flags & ECE) != 0;
    this->isURG = (flags & URG) != 0;
    this->isACK = (flags & ACK) != 0;
    this->isPSH = (flags & PSH) != 0;
    this->isRST = (flags & RST) != 0;
    this->isSYN = (flags & SYN) != 0;
    this->isFIN = (flags & FIN) != 0;
    this->isNS = NSflag != 0;
    this->window_size = window_size;
    this->checksum = checksum;
    this->urgent_pointer = urgent_pointer;

    this->payload = new uint8_t[payload_length];
    memcpy(this->payload, payload, payload_length);
    this->payload_length = payload_length;
}

void TCPPacket::parse(uint8_t *packet, ssize_t size) {

    this->source_port = (uint16_t) (packet[0] + (packet[1] * 0xFF));
    this->destination_port = (uint16_t) (packet[2] + (packet[3] * 0xFF));


    this->seq_number = (uint32_t) (
            packet[4]
            + packet[5] * 0xFF
            + packet[6] * 0xFFFF
            + packet[7] * 0xFFFFFF);

    this->ack_number = (uint32_t) (
            packet[8]
            + packet[9] * 0xFF
            + packet[10] * 0xFFFF
            + packet[11] * 0xFFFFFF);

    this->data_offset = packet[12] >> 4;

    this->isNS = (packet[12] & 1) == 1;
    this->isCWR = (packet[13] & 128) == 128;
    this->isECE = (packet[13] & 64) == 64;
    this->isURG = (packet[13] & 32) == 32;
    this->isACK = (packet[13] & 16) == 16;
    this->isPSH = (packet[13] & 8) == 8;
    this->isRST = (packet[13] & 4) == 4;
    this->isSYN = (packet[13] & 2) == 2;
    this->isFIN = (packet[13] & 1) == 1;


    this->window_size = (uint16_t) (packet[14] + (packet[15] * 0xFF));

    this->checksum = (uint16_t) (packet[16] + (packet[17] * 0xFF));
    this->urgent_pointer = (uint16_t) (packet[18] + (packet[19] * 0xFF));

}

void TCPPacket::handle(std::shared_ptr<State> state, uint8_t* source_ip) {
    


}

void TCPPacket::respond(std::shared_ptr<State> state, uint8_t* destination_ip) {

}



