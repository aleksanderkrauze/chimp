cmake_minimum_required(VERSION 3.19)

project(chimp
  VERSION 0.0.0
  DESCRIPTION "A modern command line argument parser"
  HOMEPAGE_URL "https://github.com/aleksanderkrauze/chimp"
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

if(NOT DEFINED CMAKE_CXX_VISIBILITY_PRESET AND
   NOT DEFINED CMAKE_VISIBILITY_INLINES_HIDDEN)
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
endif()

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" IS_TOP_LEVEL)
if("${chimp_VERSION_MAJOR}" VERSION_EQUAL 0)
	set(chimp_SOVERSION "${chimp_VERSION_MAJOR}.${chimp_VERSION_MINOR}")
else()
	set(chimp_SOVERSION "${chimp_VERSION_MAJOR}")
endif()

option(CHIMP_INCLUDE_PACKAGING "Include packaging rules for chimp" ${IS_TOP_LEVEL})
# option(CHIMP_BUILD_TESTING "Build chimp tests" NO)
option(CHIMP_BUILD_DOC "Build chimp's documentation" NO)
option(CHIMP_BUILD_INTERNAL_DOC "Build internal documentation. Useful for contributors" NO)
option(CHIMP_BUILD_EXAMPLES "Build chimp examples" NO)

if(DEFINED CHIMP_SHARED_LIBS)
	set(BUILD_SHARED_LIBS "${CHIMP_SHARED_LIBS}")
endif()

if(DEFINED CHIMP_BUILD_TESTING)
	set(BUILD_TESTING "${CHIMP_BUILD_TESTING}")
endif()

file(GLOB CHIMP_SRC "src/*.cpp")

add_library(chimp "${CHIMP_SRC}")
add_library(chimp::chimp ALIAS chimp)

configure_file(cmake/config.h.in include/chimp/cmake/config.h)
generate_export_header(chimp EXPORT_FILE_NAME include/chimp/cmake/export.h)

set_target_properties(chimp PROPERTIES
	VERSION ${chimp_VERSION}
	SOVERSION ${chimp_SOVERSION}
)
target_include_directories(chimp PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_definitions(chimp PUBLIC
	$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:CHIMP_STATIC_DEFINE>
	$<$<BOOL:${BUILD_TESTING}>:CHIMP_BUILD_TESTING>
)
target_compile_features(chimp PUBLIC cxx_std_17)

# ###############################################
if(BUILD_TESTING)
  include(CTest)
  add_subdirectory(tests)
endif()

if(CHIMP_BUILD_DOC)
  add_subdirectory(doc)
endif()

if(CHIMP_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# ###############################################
if(CHIMP_INCLUDE_PACKAGING)
	if(NOT DEFINED CHIMP_INSTALL_CMAKEDIR)
		set(CHIMP_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/chimp"
	       CACHE STRING "Path to chimp CMake files")
	endif()

	install(TARGETS chimp EXPORT chimp_Targets
	        RUNTIME COMPONENT chimp_Runtime
	        LIBRARY COMPONENT chimp_Runtime
	        NAMELINK_COMPONENT chimp_Development
	        ARCHIVE COMPONENT chimp_Development
	        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
	)

	install(DIRECTORY
					"${chimp_SOURCE_DIR}/include/"
					"${chimp_BINARY_DIR}/include/"
					TYPE INCLUDE
					COMPONENT chimp_Development
	)

	if(BUILD_SHARED_LIBS)
	    set(type shared)
	else()
	    set(type static)
	endif()

	install(EXPORT chimp_Targets
					DESTINATION "${CHIMP_INSTALL_CMAKEDIR}"
	        NAMESPACE chimp::
	        FILE chimp-${type}-targets.cmake
	        COMPONENT chimp_Development
	)

	install(FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/cmake/chimpConfig.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/chimpConfigVersion.cmake"
	  DESTINATION ${CHIMP_INSTALL_CMAKEDIR}
		COMPONENT chimp_Development
	)

	write_basic_package_version_file(
	  chimpConfigVersion.cmake
	  COMPATIBILITY SameMajorVersion
	)
endif()
