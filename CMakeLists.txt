cmake_minimum_required(VERSION 3.28)
project(sheduler)

set(CMAKE_CXX_STANDARD 17)

add_executable(sheduler main.cpp
        dispatcher.cpp
        dispatcher.h
        request.cpp
        request.h
        abstract_request.cpp
        abstract_request.h
        Worker.cpp
        Worker.h)
