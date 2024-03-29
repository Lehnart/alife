cmake_minimum_required(VERSION 3.16)
project(alife C)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}//cmake/modules)
message(STATUS "module path ${CMAKE_MODULE_PATH}")

find_package(SDL2 REQUIRED SDL2)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_image REQUIRED)

set(CMAKE_C_STANDARD 11)

add_subdirectory(cellular_automata)
add_subdirectory(swarm)

add_executable(evoloop cellular_automata/evoloop/evoloop.c tools/cell_array.c tools/tools.c)
add_executable(spiral cellular_automata/spiral/spiral.c tools/cell_array.c cellular_automata/spiral/spiral_rule.c tools/tools.c)
add_executable(ipd cellular_automata/ipd/ipd.c tools/cell_array.c cellular_automata/ipd/ipd_rule.c cellular_automata/ipd/ipd.c cellular_automata/ipd/ipd_state.c tools/tools.c)
add_executable(l_systems morphogonesis/l_systems/l_systems.c morphogonesis/l_systems/turtle.c tools/tools.c)
add_executable(stochastic_l_systems morphogonesis/l_systems/stochastic_l_systems.c morphogonesis/l_systems/turtle.c tools/tools.c)
add_executable(ants animats/ants/ants.c tools/tools.c animats/ants/ant.c tools/image.c)
add_executable(bricalife projects/bricalife/bricalife.c tools/tools.c tools/cell_array.c projects/bricalife/atom.c)
add_executable(mais projects/mais/mais.c tools/tools.c projects/mais/world.c tools/image.c)

target_link_libraries(evoloop ${SDL2_LIBRARIES})
target_link_libraries(bricalife ${SDL2_LIBRARIES})
target_link_libraries(ipd ${SDL2_LIBRARIES})
target_link_libraries(spiral ${SDL2_LIBRARIES})
target_link_libraries(l_systems ${SDL2_LIBRARIES} m)
target_link_libraries(stochastic_l_systems ${SDL2_LIBRARIES} m)
target_link_libraries(boids ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES} m)
target_link_libraries(ants ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} m)
target_link_libraries(mais ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} m)
