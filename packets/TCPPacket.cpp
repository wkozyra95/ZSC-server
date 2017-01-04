#include "TCPPacket.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "IPv6Packet.h"
#include "../store/TCPStore.h"
#include "../store/IPv6Store.h"
#include "../Utils.h"

TCPPacket::TCPPacket(uint8_t *packet, ssize_t size) {
    parse(packet, size);
    displayPacket();
}

TCPPacket::TCPPacket(
        uint16_t source_port,
        uint16_t destination_port,
        uint32_t sequence_number,
        uint32_t ack_number,
        uint8_t data_offset,
        uint8_t flags,
        uint8_t NSflag,
        uint16_t window_size,
        uint16_t urgent_pointer,
        uint8_t* payload,
        ssize_t payload_length
        ) {
    this->source_port = source_port;
    this->destination_port = destination_port;
    this->seq_number = sequence_number;
    this->ack_number = ack_number;
    this->data_offset = data_offset;
    this->isCWR = (flags & F_CWR) != 0;
    this->isECE = (flags & F_ECE) != 0;
    this->isURG = (flags & F_URG) != 0;
    this->isACK = (flags & F_ACK) != 0;
    this->isPSH = (flags & F_PSH) != 0;
    this->isRST = (flags & F_RST) != 0;
    this->isSYN = (flags & F_SYN) != 0;
    this->isFIN = (flags & F_FIN) != 0;
    this->isNS = NSflag != 0;
    this->window_size = window_size;
    this->urgent_pointer = urgent_pointer;

    this->payload = new uint8_t[payload_length];
    memcpy(this->payload, payload, payload_length);
    this->payload_length = payload_length;
    displayPacket();
}

void TCPPacket::parse(uint8_t *packet, ssize_t size) {
    std::cout << Utils::hex_format_display(packet, size) << std::endl; 
    this->source_port = (uint16_t) (packet[1] + (packet[0] * 0x100));
    this->destination_port = (uint16_t) (packet[3] + (packet[2] * 0x100));

    this->seq_number = (uint32_t) (
            packet[7]
            + packet[6] * 0x100
            + packet[5] * 0x10000
            + packet[4] * 0x1000000);

    this->ack_number = (uint32_t) (
            packet[11]
            + packet[10] * 0x100
            + packet[9] * 0x10000
            + packet[8] * 0x1000000);

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
    auto connection = state->tcpStore->getConnection(source_ip, source_port, destination_port);
    if( this->isSYN ) { // listen for connection request
        connection->state = LISTEN;
        connection->initial_seq_sender = this->seq_number;
        connection->initial_seq_receiver = 0x12131415;
        connection->seq_number = connection->initial_seq_receiver + 1 ; 
        connection->ack_seq_number = connection->initial_seq_receiver;        
        connection->ack_index = this->seq_number + 1;
        //accept connection 
        std::make_shared<TCPPacket>(
                this->destination_port,
                this->source_port,
                connection->initial_seq_receiver,
                connection->ack_index,
                20,
                F_SYN | F_ACK,
                0,
                1000,
                0x0000,
                nullptr,
                0
                )->respond(state, source_ip);
    } else if( this->isACK && connection->state == LISTEN ) { // listen for ack of
        connection->state = ESTABLISHED;
        if(this->seq_number != connection->ack_index) {
            std::cout << "ERROR: MISSING PREVIOUS ACK retransmit" << std::endl;
        }
        connection->ack_seq_number = this->seq_number + 1;
    } else if (connection->state == ESTABLISHED && this->isACK && this->isPSH) {
        std::vector<uint8_t> data(payload, payload + this->payload_length);
        connection->payload.insert(
                connection->payload.end(),
                data.begin(),
                data.end()
                );
        connection->ack_index = this->seq_number + payload_length;
        std::make_shared<TCPPacket>( //send ack
                this->destination_port,
                this->source_port,
                connection->seq_number,
                connection->ack_index,
                20,
                F_ACK,
                0,
                1000,
                0x0000,
                nullptr,
                0
                )->respond(state, source_ip);
    }

}

void TCPPacket::respond(std::shared_ptr<State> state, uint8_t* destination_ip) {
    uint16_t tcp_packet_size = this->payload_length + this->data_offset;
    auto ipv6_payload = new uint8_t[tcp_packet_size];

    ipv6_payload[0] = ((uint8_t*) &this->source_port)[1];
    ipv6_payload[1] = ((uint8_t*) &this->source_port)[0];

    ipv6_payload[2] = ((uint8_t*) &this->destination_port)[1];
    ipv6_payload[3] = ((uint8_t*) &this->destination_port)[0];

    ipv6_payload[4] = ((uint8_t*) &this->seq_number)[3];
    ipv6_payload[5] = ((uint8_t*) &this->seq_number)[2];
    ipv6_payload[6] = ((uint8_t*) &this->seq_number)[1];
    ipv6_payload[7] = ((uint8_t*) &this->seq_number)[0];

    ipv6_payload[8] = ((uint8_t*) &this->ack_number)[3];
    ipv6_payload[9] = ((uint8_t*) &this->ack_number)[2];
    ipv6_payload[10] = ((uint8_t*) &this->ack_number)[1];
    ipv6_payload[11] = ((uint8_t*) &this->ack_number)[0];

    ipv6_payload[12] = ((this->data_offset/4) << 4) | (isNS ? 1 : 0);
    ipv6_payload[13] = 
        (isCWR ? F_CWR : 0) |
        (isECE ? F_ECE : 0) |
        (isURG ? F_URG : 0) |
        (isACK ? F_ACK : 0) |
        (isPSH ? F_PSH : 0) |
        (isRST ? F_RST : 0) |
        (isSYN ? F_SYN : 0) |
        (isFIN ? F_FIN : 0);

    std::cout<< "ddddd" << window_size << std::endl;
    ipv6_payload[14] = ((uint8_t*) &this->window_size)[1];
    ipv6_payload[15] = ((uint8_t*) &this->window_size)[0];

    // checksum balnk for now [16, 17]

    ipv6_payload[18] = ((uint8_t*) &this->urgent_pointer)[1];
    ipv6_payload[19] = ((uint8_t*) &this->urgent_pointer)[0];

    // ipv6 pseudo header + checksum
    
    {
        uint8_t *checksum_base = new uint8_t[tcp_packet_size+ 40];
        memcpy(checksum_base, state->ipv6Store->getMyIp(), 16);
        memcpy(checksum_base + 16, destination_ip, 16);
        checksum_base[32] = 0;
        checksum_base[33] = 0;
        checksum_base[34] = ((uint8_t*)&tcp_packet_size)[1];
        checksum_base[35] = ((uint8_t*)&tcp_packet_size)[0];
        memset(checksum_base + 36, 0, 3);
        checksum_base[39] = 6;
        memcpy(checksum_base + 40, this->payload, (size_t) this->payload_length);

        checksum = Utils::checksum(checksum_base, (int) (tcp_packet_size + 40));
        delete checksum_base;
    }

    ipv6_payload[16] = ((uint8_t*) (&checksum))[0];
    ipv6_payload[17] = ((uint8_t*) (&checksum))[1];

    uint8_t flow[] = {0x00, 0x00, 0x00};
    std::make_shared<IPv6Packet>(
                destination_ip,
                (uint8_t) 6,
                (uint8_t) 0,
                flow,
                ipv6_payload,
                tcp_packet_size        
            )->respond(state);
}

void TCPPacket::displayPacket() {
    
    std::cout << "source port: " << this->source_port << "\tdestination port: " << this->destination_port << std::endl <<
        "seq: " << this->seq_number << "\tack: " << this->ack_number << std::endl <<
        "isACK: " << this->isACK << "\tisSYN: " << this->isSYN << "\tisPSH: " << isPSH << std::endl << std::endl;
        
}


