cmake_minimum_required(VERSION 3.16)
project(alife C)

add_executable(boids boids.c ../../tools/tools.c bird.c)

target_link_libraries(boids ${SDL2_LIBRARIES})
