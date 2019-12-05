cmake_minimum_required(VERSION 3.16.0)
project(AdventOfCode2019)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_subdirectory("./intcode")

add_subdirectory("./day01")
add_subdirectory("./day02")
add_subdirectory("./day03")
add_subdirectory("./day04")
add_subdirectory("./day05")