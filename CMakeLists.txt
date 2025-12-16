cmake_minimum_required(VERSION 4.1)
project(GerbangkertosusilaTransport)

set(CMAKE_CXX_STANDARD 20)

add_executable(GerbangkertosusilaTransport main.cpp
        common.h
        transport.cpp
        transport.h
        region.cpp
        region.h
)
