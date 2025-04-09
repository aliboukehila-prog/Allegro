cmake_minimum_required(VERSION 3.29)
project(Allegro_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(Allegro_2 main.c)
target_link_libraries(Allegro_2 -lmingw32 -lalleg44)
