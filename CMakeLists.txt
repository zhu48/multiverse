cmake_minimum_required(VERSION 3.13)

project(multiverse LANGUAGES CXX VERSION 0.0.1)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()
if(CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "Multiverse requires C++20")
endif()

#######################
# Gather Dependencies #
#######################

include(CTest)

find_program(MLTVRS_CLANG_FORMAT clang-format)

set(STARS_CLANG_FORMAT ${MLTVRS_CLANG_FORMAT})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/modules/stars)

set(CREATURE_CLANG_FORMAT ${MLTVRS_CLANG_FORMAT})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/modules/creature)

################
# Clang-Format #
################

if(MLTVRS_CLANG_FORMAT)
    message(STATUS "generating target clang_format")

    add_custom_target(clang_format)
    add_dependencies(
        clang_format
        stars_clang_format
        creature_clang_format
        test_creature_stat_clang_format
    )
else()
    message(STATUS "clang-tidy not found")
endif()
