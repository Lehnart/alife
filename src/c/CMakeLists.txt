cmake_minimum_required(VERSION 3.16)
project(alife C)

find_package(SDL2 REQUIRED SDL2)

set(CMAKE_C_STANDARD 11)
#set(SDL2_LIBRARIES "C:/Users/User/Desktop/SDL2-2.0.20/lib/x64/SDL2.lib;C:/Users/User/Desktop/SDL2-2.0.20/lib/x64/SDL2main.lib")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
#set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")

#include_directories(".")
add_executable(alife spiral.c cell_array.c spiral_rule.c)
target_link_libraries(alife ${SDL2_LIBRARIES})
