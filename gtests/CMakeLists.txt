include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(GTest REQUIRED)

add_executable(${TEST_NAME}
test.cpp
)

target_link_libraries(${TEST_NAME} 
  GTest::GTest ${CORE_NAME})

add_test(actions_gtests ${TEST_NAME})