cmake_minimum_required(VERSION 3.19)
project(5gscramble)

set(CMAKE_CXX_STANDARD 14)

add_executable(5gscramble main.cpp functions.h functions.cpp)
target_link_libraries(5gscramble fftw3)