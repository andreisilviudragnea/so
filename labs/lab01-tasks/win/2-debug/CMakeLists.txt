add_executable(no_debug add.c main.c)

add_executable(debug add.c main.c)
target_compile_definitions(debug PUBLIC -DDEBUG__)
