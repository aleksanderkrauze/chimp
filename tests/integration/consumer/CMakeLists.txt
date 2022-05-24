cmake_minimum_required(VERSION 3.19)

project(chimp_integration_tests_consumer)

find_package(chimp REQUIRED ${chimp_consumer_components})

add_executable(consumer main.cpp)
target_link_libraries(consumer chimp::chimp)
