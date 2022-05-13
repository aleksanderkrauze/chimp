cmake_minimum_required(VERSION 3.12)

project(version_macros_test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} chimp)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
set_tests_properties(${PROJECT_NAME} PROPERTIES
  PASS_REGULAR_EXPRESSION ${chimp_VERSION}
)