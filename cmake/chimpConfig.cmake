cmake_minimum_required(VERSION 3.19)

set(chimp_known_comps static shared)
set(chimp_comp_static NO)
set(chimp_comp_shared NO)
foreach(chimp_comp IN LISTS ${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS)
    if(chimp_comp IN_LIST chimp_known_comps)
        set(chimp_comp_${chimp_comp} YES)
    else()
        set(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE
            "chimp does not recognize component `${chimp_comp}`.")
        set(${CMAKE_FIND_PACKAGE_NAME}_FOUND FALSE)
        return()
    endif()
endforeach()

if(chimp_comp_static AND chimp_comp_shared)
    set(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE
        "chimp `static` and `shared` components are mutually exclusive.")
    set(${CMAKE_FIND_PACKAGE_NAME}_FOUND FALSE)
    return()
endif()

set(chimp_static_targets "${CMAKE_CURRENT_LIST_DIR}/chimp-static-targets.cmake")
set(chimp_shared_targets "${CMAKE_CURRENT_LIST_DIR}/chimp-shared-targets.cmake")

macro(chimp_load_targets type)
    if(NOT EXISTS "${chimp_${type}_targets}")
        set(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE
            "chimp `${type}` libraries were requested but not found.")
        set(${CMAKE_FIND_PACKAGE_NAME}_FOUND FALSE)
        return()
    endif()
    include("${chimp_${type}_targets}")
endmacro()

if(chimp_comp_static)
    chimp_load_targets(static)
elseif(chimp_comp_shared)
    chimp_load_targets(shared)
	elseif(DEFINED CHIMP_SHARED_LIBS AND CHIMP_SHARED_LIBS)
    chimp_load_targets(shared)
	elseif(DEFINED CHIMP_SHARED_LIBS AND NOT CHIMP_SHARED_LIBS)
    chimp_load_targets(static)
elseif(BUILD_SHARED_LIBS)
    if(EXISTS "${chimp_shared_targets}")
        chimp_load_targets(shared)
    else()
        chimp_load_targets(static)
    endif()
else()
    if(EXISTS "${chimp_static_targets}")
        chimp_load_targets(static)
    else()
        chimp_load_targets(shared)
    endif()
endif()
