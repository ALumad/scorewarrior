cmake_minimum_required(VERSION 3.16)
project(scorewarrior CXX)

set(CMAKE_CXX_COMPILER "clang")
set(CMAKE_CXX_STANDARD 17)


set(PROJECT_NAME scorewarrior)
enable_testing()


include_directories(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(gtests)