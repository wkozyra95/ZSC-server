cmake_minimum_required(VERSION 3.0)
project(ZSC)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
set(CMAKE_C_COMPILER g++)
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -g -Wall")
add_compile_options(-std=c++14)

add_executable(
        app
        main.cpp
        Runner.cpp Runner.h
        Utils.cpp Utils.h

        store/State.cpp store/State.h

        packets/RawFrame.cpp packets/RawFrame.h
        packets/EthernetFrame.cpp packets/EthernetFrame.h
        packets/IPv6Packet.cpp packets/IPv6Packet.h
        packets/IcmpPacket.cpp packets/IcmpPacket.h
        packets/TCPPacket.cpp packets/TCPPacket.h

        store/Device.cpp store/Device.h
        store/EthernetStore.cpp store/EthernetStore.h
        store/IPv6Store.cpp store/IPv6Store.h
        store/TCPStore.cpp store/TCPStore.h
)


add_executable(
        tests
        tests/tests.cpp tests/Test.cpp tests/Test.h
        tests/MockRunner.cpp tests/MockRunner.h
        tests/MockDevice.cpp tests/MockDevice.h

        Utils.cpp Utils.h

        store/State.cpp store/State.h

        packets/RawFrame.cpp packets/RawFrame.h
        packets/EthernetFrame.cpp packets/EthernetFrame.h
        packets/IPv6Packet.cpp packets/IPv6Packet.h
        packets/IcmpPacket.cpp packets/IcmpPacket.h
        packets/TCPPacket.cpp packets/TCPPacket.h

        store/EthernetStore.cpp store/EthernetStore.h
        store/IPv6Store.cpp store/IPv6Store.h
        store/TCPStore.cpp store/TCPStore.h

)
