cmake_minimum_required(VERSION 3.19)

project(cxx_flags_warnings)

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE lib.cpp)
target_link_libraries(${PROJECT_NAME} chimp::chimp)
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
