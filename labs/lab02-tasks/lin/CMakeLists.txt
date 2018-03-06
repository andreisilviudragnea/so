cmake_minimum_required(VERSION 3.10)

project(lab02-tasks-lin C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(utils)
add_compile_options(
        -Wall
        -Wextra
        -g
        -Wmissing-prototypes
        -Wstrict-prototypes
        -Wmissing-declarations
        -O3
        -flto)

add_subdirectory(1-redirect)
add_subdirectory(2-lseek)
add_subdirectory(3-mcat)
add_subdirectory(4-trouble)
add_subdirectory(5-singular)
add_subdirectory(nasty)
