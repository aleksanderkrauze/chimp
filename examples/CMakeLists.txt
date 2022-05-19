cmake_minimum_required(VERSION 3.12)

project(chimp_examples)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/*.cpp)
foreach(FILENAME ${SRC})
  get_filename_component(BASENAME ${FILENAME} NAME_WLE)
  set(TARGET_NAME ${PROJECT_NAME}_${BASENAME})

  add_executable(${TARGET_NAME} ${FILENAME})
  target_link_libraries(${TARGET_NAME} chimp)
endforeach()
