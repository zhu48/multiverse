cmake_minimum_required(VERSION 3.13)

project(creature LANGUAGES CXX VERSION 0.0.1)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

##################
# Gather Sources #
##################

set(
    CREATURE_HPP_FILES
        ${CMAKE_CURRENT_LIST_DIR}/creature.hpp
)

set(
    TEST_CREATURE_STAT_CPP_FILES
        ${CMAKE_CURRENT_LIST_DIR}/test/test_creature_stat.cpp
)

##################
# Declare Target #
##################

add_library(creature INTERFACE)
target_include_directories(creature INTERFACE ${PARENT_DIR})
target_sources(creature INTERFACE ${CREATURE_HPP_FILES})

include(CTest)

if(BUILD_TESTING)
    find_package(Catch2 REQUIRED)

    add_executable(
        test_creature_stat
            ${TEST_CREATURE_STAT_CPP_FILES}
    )
    target_link_libraries(test_creature_stat PRIVATE Catch2::Catch2)
    target_link_libraries(test_creature_stat PRIVATE creature)

    add_test(NAME test_creature_stat COMMAND test_creature_stat)
endif()

################
# Clang-Format #
################

if(CREATURE_CLANG_FORMAT)
    add_custom_target(
        creature_clang_format
            COMMAND
                ${CREATURE_CLANG_FORMAT} -i ${CREATURE_HPP_FILES}
            DEPENDS
                ${CREATURE_HPP_FILES}
    )

    add_custom_target(
        test_creature_stat_clang_format
            COMMAND
                ${CREATURE_CLANG_FORMAT} -i ${TEST_CREATURE_STAT_CPP_FILES}
            DEPENDS
                ${TEST_CREATURE_STAT_CPP_FILES}
    )
endif()
