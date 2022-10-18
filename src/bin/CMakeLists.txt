
set(CMAKE_CXX_COMPILER "clang")
set(CMAKE_CXX_STANDARD 17)

add_executable(${BIN_NAME} 
    main.cpp
)


target_link_libraries(${BIN_NAME} ${CORE_NAME})