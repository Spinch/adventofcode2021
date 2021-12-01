cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(advcode2021)

add_executable(advcode2021 main.cpp day1.cpp)

install(TARGETS advcode2021 RUNTIME DESTINATION bin)
