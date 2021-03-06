cmake_minimum_required(VERSION 3.13)

project(multiverse LANGUAGES CXX VERSION 0.0.1)

option(MLTVRS_ENABLE_WALL                          OFF)
option(MLTVRS_ENABLE_WERROR                        OFF)
option(MLTVRS_ENABLE_DETAILED_CONCEPTS_DIAGNOSTICS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()
if(CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "Multiverse requires C++20")
endif()

if(MLTVRS_ENABLE_WALL)
    if(
        CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
    )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    else()
        message(SEND_ERROR  "option  : MLTVRS_ENABLE_WALL")
        message(SEND_ERROR  "compiler: ${CMAKE_CXX_COMPILER_ID}")
        message(FATAL_ERROR "enabling all warning on this compiler unsupported")
    endif()
endif()

if(MLTVRS_ENABLE_WERROR)
    if(
        CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
    )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
    else()
        message(SEND_ERROR  "option  : MLTVRS_ENABLE_WERROR")
        message(SEND_ERROR  "compiler: ${CMAKE_CXX_COMPILER_ID}")
        message(FATAL_ERROR "warnings as errors on this compiler unsupported")
    endif()
endif()

if(MLTVRS_ENABLE_DETAILED_CONCEPTS_DIAGNOSTICS)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts-diagnostics-depth=9")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS "ignoring MLTVRS_ENABLE_DETAILED_CONCEPTS_DIAGNOSTICS on clang")
    else()
        message(SEND_ERROR  "option  : MLTVRS_ENABLE_DETAILED_CONCEPTS_DIAGNOSTICS")
        message(SEND_ERROR  "compiler: ${CMAKE_CXX_COMPILER_ID}")
        message(FATAL_ERROR "concepts diagnostics on this compiler unsupported")
    endif()
endif()

#######################
# Gather Dependencies #
#######################

include(CTest)

find_program(MLTVRS_CLANG_FORMAT clang-format)
find_program(MLTVRS_CLANG_TIDY   clang-tidy)

set(STARS_CLANG_FORMAT ${MLTVRS_CLANG_FORMAT})
set(STARS_CLANG_TIDY   ${MLTVRS_CLANG_TIDY})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/modules/stars)

set(CREATURE_CLANG_FORMAT ${MLTVRS_CLANG_FORMAT})
set(CREATURE_CLANG_TIDY   ${MLTVRS_CLANG_TIDY})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/modules/creature)

################
# Clang-Format #
################

if(MLTVRS_CLANG_FORMAT)
    message(STATUS "generating target mltvrs_clang_format")

    add_custom_target(mltvrs_clang_format)
    add_dependencies(
        mltvrs_clang_format
            stars_clang_format
            creature_clang_format
            test_creature_stat_clang_format
    )
else()
    message(STATUS "clang-format not found")
endif()

##############
# Clang-Tidy #
##############

if(MLTVRS_CLANG_TIDY)
    message(STATUS "generating target mltvrs_clang_tidy")

    add_custom_target(mltvrs_clang_tidy)
    add_dependencies(
        mltvrs_clang_tidy
            test_creature_stat_clang_tidy
    )
else()
    message(STATUS "clang-tidy not found")
endif()
