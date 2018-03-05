add_executable(main main.c str.c)
target_compile_options(main PUBLIC -flto)
