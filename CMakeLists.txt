cmake_minimum_required(VERSION 3.15)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 main.cpp Classes/Message.cpp Classes/Message.h Classes/DurationLogger.cpp Classes/DurationLogger.h Classes/MessageStore.cpp Classes/MessageStore.h)