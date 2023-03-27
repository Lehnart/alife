cmake_minimum_required(VERSION 3.16)
project(alife C)

add_executable(langton langton.c ../../tools/cell_array.c ../../tools/tools.c ../../tools/cell_array_rule.c ../../tools/window.c ../../tools/cell_array_drawer.c ../../tools/cell_array_drawer.h)

target_link_libraries(langton ${SDL2_LIBRARIES})
