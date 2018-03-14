cmake_minimum_required(VERSION 3.10)

project(10)

include_directories(include)

add_executable(overlapped-io overlapped-io.c include/utils.h)
