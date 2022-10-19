
set(CMAKE_CXX_COMPILER "clang")
set(CMAKE_CXX_STANDARD 17)

add_library(${CORE_NAME} 
    utils/ActionsReader.cpp
    utils/ActionsRunner.cpp
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
    controller/BattleController.cpp
    
)


target_link_libraries(${CORE_NAME} stdc++ m)