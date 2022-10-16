project(scorewarrior)
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_COMPILER "clang")
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME scorewarrior)

include_directories(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${PROJECT_NAME} 
    main.cpp
    utils/ActionsReader.cpp
    utils/InputChecker.cpp
    models/Map.cpp
    models/Tick.cpp
    models/actions/CreateMap.cpp
    models/actions/Finish.cpp
    models/actions/March.cpp
    models/actions/Spawn.cpp
    models/actions/Wait.cpp
    models/actions/builders/ActionBuilder.cpp
    models/actions/builders/ActionFactory.cpp
    controller/Controller.cpp
)


target_link_libraries(${PROJECT_NAME} stdc++ m)