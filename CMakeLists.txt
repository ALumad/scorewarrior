cmake_minimum_required(VERSION 3.16)
project(scorewarrior CXX)

set(CMAKE_CXX_COMPILER "clang")
set(CMAKE_CXX_STANDARD 17)

set(CORE_NAME swcore)
set(BIN_NAME scorewarrior)
set(TEST_NAME swtest)
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/core)

add_subdirectory(src)
add_subdirectory(gtests)