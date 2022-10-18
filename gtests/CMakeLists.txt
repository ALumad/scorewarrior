include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(GTest REQUIRED)

add_executable(tests
test.cpp
../src/utils/ActionsReader.cpp
../src/utils/InputChecker.cpp
../src/models/Map.cpp
../src/models/Tick.cpp
../src/models/actions/CreateMap.cpp
../src/models/actions/Finish.cpp
../src/models/actions/March.cpp
../src/models/actions/Spawn.cpp
../src/models/actions/Wait.cpp
../src/models/actions/builders/ActionBuilder.cpp
../src/models/actions/builders/ActionFactory.cpp
../src/controller/Controller.cpp
)

target_link_libraries(tests
 PRIVATE
  GTest::GTest stdc++ m)

add_test(actions_gtests tests)