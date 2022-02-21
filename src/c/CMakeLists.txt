cmake_minimum_required(VERSION 3.16)
project(alife C)

find_package(SDL2 REQUIRED SDL2)

set(CMAKE_C_STANDARD 11)

add_executable(alife spiral.c cell_array.c cell_array.h spiral_rule.c spiral_rule.h cell_neighborhood.h)
target_link_libraries(alife ${SDL2_LIBRARIES})