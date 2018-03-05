add_library(hexdump_static STATIC hexdump.c sample.c)
add_executable(main_static main.c)
target_link_libraries(main_static hexdump_static)

add_library(hexdump_dynamic SHARED hexdump.c sample.c)
add_executable(main_dynamic main.c)
target_link_libraries(main_dynamic hexdump_dynamic)
