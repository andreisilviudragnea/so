add_compile_options(-Wall -Wextra -g)
add_executable(kaio kaio.c ../utils/utils.h)
include_directories(kaio ../utils)