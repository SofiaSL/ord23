cmake_minimum_required(VERSION 3.13)
project(ord23)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-march=native -mtune=native -O3 -mmmx -msse -msse2 -msse3 -pedantic -Wextra -Wshadow -Wnon-virtual-dtor -Wdelete-non-virtual-dtor -fgraphite-identity -floop-nest-optimize -fdevirtualize-at-ltrans -fipa-pta -fno-semantic-interposition -flto=9 -fuse-linker-plugin -pipe -falign-functions=32")

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(mp++ REQUIRED)
find_package(Threads)

include(FetchContent)

FetchContent_Declare(
    nanobench
    GIT_REPOSITORY https://github.com/martinus/nanobench.git
    GIT_TAG v4.1.0
    GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(nanobench)

add_executable(ord23 main.cpp
    utils.cpp utils.h
    factor.cpp factor.h longlong.h primes.h)

target_link_libraries(ord23 mp++::mp++ Threads::Threads)

add_executable(tests tests.cpp
    utils.cpp utils.h
    factor.cpp factor.h
    catch.cpp catch.hpp)

target_link_libraries(tests mp++::mp++ Threads::Threads)

add_executable(profiling profiling.cpp
               nanobench.h
               utils.cpp utils.h
               factor.cpp factor.h)

target_link_libraries(profiling nanobench)