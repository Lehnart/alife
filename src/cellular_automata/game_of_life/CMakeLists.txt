cmake_minimum_required(VERSION 3.16)
project(alife C)

add_executable(game_of_life game_of_life.c ../../tools/cell_array.c ../../tools/tools.c ../../tools/cell_array_rule.c ../../tools/window.c ../../tools/cell_array_drawer.c ../../tools/cell_array_drawer.h)

target_link_libraries(game_of_life ${SDL2_LIBRARIES})
