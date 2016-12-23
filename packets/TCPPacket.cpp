#include "TCPPacket.h"


TCPPacket::TCPPacket(uint8_t *packet, ssize_t size) {}

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
