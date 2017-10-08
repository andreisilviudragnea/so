add_compile_options(-Wall -Wextra -g)
add_executable(epoll epoll.c ../utils/utils.h)
include_directories(epoll ../utils)