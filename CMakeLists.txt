cmake_minimum_required(VERSION 3.1)
project(Ray_Tracer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Werror -Wall -g")

include (CTest)

add_subdirectory(src)
