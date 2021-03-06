cmake_minimum_required(VERSION 3.13)

project(nursery LANGUAGES CXX VERSION 0.0.1)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

#######################
# Gather Dependencies #
#######################

find_package(Boost REQUIRED COMPONENTS program_options)

##################
# Gather Sources #
##################

set(
    NURSERY_HPP_FILES
        ${CMAKE_CURRENT_LIST_DIR}/nursery.hpp
)

set(
    NURSERY_CPP_FILES
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)

##################
# Declare Target #
##################

add_executable(nursery ${NURSERY_HPP_FILES} ${NURSERY_CPP_FILES})
target_include_directories(nursery PRIVATE ${PARENT_DIR})
target_link_libraries(nursery PRIVATE Boost::boost Boost::program_options)

################
# Clang-Format #
################

if(NURSERY_CLANG_FORMAT)
    add_custom_target(
        nursery_clang_format
            COMMAND
                ${NURSERY_CLANG_FORMAT} -i ${NURSERY_HPP_FILES} ${NURSERY_CPP_FILES}
            DEPENDS
                ${NURSERY_HPP_FILES}
                ${NURSERY_CPP_FILES}
    )
endif()

if(NURSERY_CLANG_TIDY)
    add_custom_target(
        nursery_clang_tidy
            COMMAND
                ${NURSERY_CLANG_TIDY}
                    -p ${CMAKE_CURRENT_BINARY_DIR}
                    ${NURSERY_CPP_FILES}
            DEPENDS
                ${NURSERY_HPP_FILES}
                ${NURSERY_CPP_FILES}
    )
endif()
