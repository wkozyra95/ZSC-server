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
        Device.cpp Device.h
        Utils.cpp Utils.h
        packets/AbstractPacket.cpp packets/AbstractPacket.h
        packets/RawFrame.cpp packets/RawFrame.h
        packets/EthernetFrame.cpp packets/EthernetFrame.h
)

target_link_libraries(app pthread)