cmake_minimum_required(VERSION 3.0)
project(ZSC)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=gnu99 -g -Wall")

add_executable(app main.c ethernet/ethernet.c ethernet/eth_utils.c ethernet/eth_utils.h)
