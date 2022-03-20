cmake_minimum_required(VERSION 3.16)
project(alife C)

find_package(SDL2 REQUIRED SDL2)

set(CMAKE_C_STANDARD 11)

add_executable(spiral spiral/spiral.c cell_array.c spiral/spiral_rule.c tools.c)
add_executable(ipd ipd/ipd.c cell_array.c ipd/ipd_rule.c ipd/ipd.c ipd/ipd_state.c tools.c)
add_executable(l_systems l_systems/l_systems.c turtle.c tools.c)
add_executable(mais mais/mais.c graph.c array.c neural_network.c)

target_link_libraries(ipd ${SDL2_LIBRARIES})
target_link_libraries(spiral ${SDL2_LIBRARIES})
target_link_libraries(l_systems ${SDL2_LIBRARIES} m)
target_link_libraries(mais ${SDL2_LIBRARIES} m)
