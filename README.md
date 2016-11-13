ethernet frame
     - 6B mac destination
     - 6B mac source
     - 2B typ długość
     - data
     - 4B FCS

ipv6 packet
    - Ver             0.5B    4b      == 6
    - Traffic class   1B      8b
    - Flow Label      2.5B    20b

    - Payload length  2B
    - Next header     1B
    - HoopLimit       1B

    - Source          16B
    - Destination     16B

ICMPv6 packet
    - type          1B
    - code          1B
    - checksum      2B
    - message body  4B

TCP packet
    - source port       2B
    - dest port         2B
    - sequnce number    4B
    - ACK number(ifset) 4B
    - 2B
    - window size       2B
    - checksum          4B
    - urgent pointer    2B


Router solicitation ICMPv6
    ethernet multicast ipv6
        dest: 33-33-xx-xx-xx-xx
        type: 0x86DD
    ipv6 packet
        nextHeader: 58 (ICMPv6)
        destination: FF02:0:0:0:0:0:0:2	All Routers Address
    icmp
        type 133(Router solicitation)
        code 0

Neighbor solicitation ICMPv6
    ethernet multicast ipv6
        dest: 33-33-xx-xx-xx-xx
        type: 0x86DD
    ipv6 packet
        nextHeader: 58 (ICMPv6)
        destination: FF02:0:0:0:0:0:0:1	All Neighbors Address
    icmp
        type 133(Neighbor solicitation)
        code 0