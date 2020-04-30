cmake_minimum_required(VERSION 3.13)

project(stars LANGUAGES CXX VERSION 0.0.1)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

##################
# Gather Sources #
##################

set(
    STARS_HPP_FILES
        ${CMAKE_CURRENT_LIST_DIR}/concepts.hpp
)

##################
# Declare Target #
##################

add_library(stars INTERFACE)
target_include_directories(stars INTERFACE ${PARENT_DIR})
target_sources(stars INTERFACE ${STARS_HPP_FILES})

################
# Clang-Format #
################

if(STARS_CLANG_FORMAT)
    add_custom_target(
        stars_clang_format
            COMMAND
                ${STARS_CLANG_FORMAT} -i ${STARS_HPP_FILES}
            DEPENDS
                ${STARS_HPP_FILES}
    )
endif()
