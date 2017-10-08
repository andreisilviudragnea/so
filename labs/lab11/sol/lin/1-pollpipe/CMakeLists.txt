add_compile_options(-Wall -Wextra -g)
add_executable(poll poll.c ../utils/utils.h)
include_directories(poll ../utils)