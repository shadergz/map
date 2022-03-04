cmake_minimum_required (VERSION 3.16)

project (map)

set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED True)

add_executable (map main-map.c map.c)
