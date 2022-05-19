cmake_minimum_required(VERSION 3.12)

project(chimp
  VERSION 0.0.0
  DESCRIPTION "A modern command line argument parser"
  HOMEPAGE_URL "https://github.com/aleksanderkrauze/chimp"
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(IS_TOPLEVEL_PROJECT TRUE)
else()
  set(IS_TOPLEVEL_PROJECT FALSE)
endif()

option(CHIMP_BUILD_TESTING "Build chimp tests" ${IS_TOPLEVEL_PROJECT})
option(CHIMP_BUILD_DOC "Build chimp's documentation" ${IS_TOPLEVEL_PROJECT})
option(CHIMP_BUILD_INTERNAL_DOC
  "Build internal documentation. Useful for contributors"
  OFF
)
option(CHIMP_BUILD_EXAMPLES "Build chimp examples" ${IS_TOPLEVEL_PROJECT})

configure_file(
  cmake/cmake_config.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/chimp/cmake_config.h
)

add_library(chimp INTERFACE)

target_include_directories(chimp INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(chimp INTERFACE cxx_std_17)
if(CHIMP_BUILD_TESTING)
  target_compile_definitions(chimp INTERFACE CHIMP_BUILD_TESTING)
endif()

if(CHIMP_BUILD_TESTING AND BUILD_TESTING)
  include(CTest)
  add_subdirectory(tests)
endif()

if(CHIMP_BUILD_DOC)
  add_subdirectory(doc)
endif()

if(CHIMP_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

write_basic_package_version_file(
  "${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMinorVersion
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION
  ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(FILES
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/chimp DESTINATION include)
