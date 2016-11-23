# ZSC - server
This is re-implementation of TCP/IP stack in scope minimal to coumunicate beetween two devices conected to network.

### Frame/packet format
##### Ethernet frame
- destination address   [6B]
- source address        [6B]
- type/length           [2B]
- payload

##### Packet IPv6
- Ver                   [0.5B, 4b]
- Traffic class         [1B, 8b]
- Flow Label            [2.5B, 20b]
- Payload length        [2B]
- Next header           [1B]
- HoopLimit             [1B]
- Source                [16B]
- Destination           [16B]

##### ICMPv6 packet
- type          1B
- code          1B
- checksum      2B
- message body  4B

##### TCP packet
- source port       2B
- dest port         2B
- sequnce number    4B
- ACK number(ifset) 4B
- 2B
- window size       2B
- checksum          4B
- urgent pointer    2B

### Initial steps

##### Neighbor solicitation ICMPv6
- ethernet 
destination: multicast ipv6
type: 0x86DD(ipv6)
- ipv6 packet
nextHeader: 58 (ICMPv6)
destination: FF02:0:0:0:0:0:0:1	All Neighbors Address
- icmp
type: 133(Neighbor solicitation)
code: 0