add_definitions(-D__CHECKER__)
include_directories(/usr/src/linux-headers-4.13.0-36/include)
add_library(nasty OBJECT nasty.c)
