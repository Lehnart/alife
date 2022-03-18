cmake_minimum_required(VERSION 3.16)
project(alife C)

find_package(SDL2 REQUIRED SDL2)

set(CMAKE_C_STANDARD 11)

add_executable(spiral spiral.c cell_array.c spiral_rule.c  tools.c)
add_executable(ipd ipd.c cell_array.c ipd_rule.c ipd.c ipd_state.c ipd_state.h tools.c tools.h)
add_executable(l_systems l_systems.c turtle.c turtle.h tools.c)

target_link_libraries(ipd ${SDL2_LIBRARIES})
target_link_libraries(spiral ${SDL2_LIBRARIES})
target_link_libraries(l_systems ${SDL2_LIBRARIES} m)
