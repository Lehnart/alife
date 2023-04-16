cmake_minimum_required(VERSION 3.16)
project(alife C)

add_subdirectory(langton_ant)
add_subdirectory(game_of_life)

add_executable(ca ca.c ../../tools/cell_array.c ../../tools/tools.c ../../tools/cell_array_rule.c ../../tools/window.c ../../tools/cell_array_drawer.c ../../tools/cell_array_terminal_drawer.c ../../tools/cell_array_terminal_drawer.c)

target_link_libraries(ca ${SDL2_LIBRARIES} ncurses)
