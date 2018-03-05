add_library(bounds_static STATIC max.c min.c)
add_executable(bounds_static_main bounds.c)
target_link_libraries(bounds_static_main bounds_static)

add_library(bounds_dynamic SHARED max.c min.c)
add_executable(bounds_dynamic_main bounds.c)
target_link_libraries(bounds_dynamic_main bounds_dynamic)
