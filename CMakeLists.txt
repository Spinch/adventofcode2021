cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(advcode2021)

add_executable(advcode2021 main.cpp 
day1.cpp
day2.cpp
day3.cpp
day4.cpp
day5.cpp
day6.cpp
day7.cpp
day8.cpp
day9.cpp
day10.cpp
day11.cpp
day12.cpp
day13.cpp
day14.cpp
day15.cpp
day16.cpp
day17.cpp
day18.cpp
day19.cpp
day20.cpp
day21.cpp
day22.cpp
day23.cpp
day24.cpp
day25.cpp)

install(TARGETS advcode2021 RUNTIME DESTINATION bin)
