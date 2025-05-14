cmake_minimum_required(VERSION 3.31)
project(cn C)

set(CMAKE_C_STANDARD 23)

add_executable(cn main.c
        notes.c
        notes.h)
target_link_libraries(cn sqlite3)
