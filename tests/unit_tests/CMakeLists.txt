cmake_minimum_required(VERSION 3.12)

project(unit_tests)

find_package(GTest)

if(NOT GTEST_FOUND)
  message(WARNING "GTest not found. Skipping building unit tests")
  return()
endif()

# We must compile each source file as a different test,
# because otherwise linker will throw an error saying that
# symbols defined in chimp library are defined in multiple
# places. This happens, because each source file includes chimp/chimp.h
file(GLOB SRC ${PROJECT_SOURCE_DIR}/*.cpp)
foreach(FILENAME ${SRC})
  get_filename_component(BASENAME ${FILENAME} NAME_WLE)
  set(TARGET_NAME ${PROJECT_NAME}_${BASENAME})

  add_executable(${TARGET_NAME})
  target_sources(${TARGET_NAME} PRIVATE ${FILENAME})
  target_link_libraries(${TARGET_NAME}
    chimp
    GTest::gtest
    GTest::gtest_main
  )

  add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endforeach()
