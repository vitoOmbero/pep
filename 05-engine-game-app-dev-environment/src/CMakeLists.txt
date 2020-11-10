cmake_minimum_required(VERSION 3.16)
project(05_guess_number)

set (CMAKE_BUILD_TYPE Debug)

# options
message("Set project options:")

option(PEP_DEBUG "Turn on debug features" ON)
option(PEP_VERBOSE "Turn on inlined stdout logger" ON)

set(verboseLevels Lvl1 Lvl2 ALL)
set(verboseLevel ALL CACHE STRING "Level of logging")
set_property(CACHE verboseLevel PROPERTY STRINGS ${verboseLevels})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "PEP_DEBUG: ON")
    else(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "PEP_DEBUG: ${PEP_DEBUG}")
endif(CMAKE_BUILD_TYPE MATCHES Debug)

message(STATUS "PEP_VERBOSE: ${PEP_VERBOSE}")

if(NOT verboseLevel IN_LIST verboseLevels)
    message(FATAL_ERROR "verboseLevel must be one of ${verboseLevels}")
endif()

if(PEP_DEBUG OR CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(PEP_DEBUG)
    if(PEP_VERBOSE)
        if (verboseLevel MATCHES ALL)
            add_compile_definitions(PEP_VERBOSE_GAME_LOGIC)
        endif()
    endif(PEP_VERBOSE)
endif(PEP_DEBUG OR CMAKE_BUILD_TYPE MATCHES Debug)

message("Project options are set.")

# set(CMAKE_VERBOSE_MAKEFILE ON)
set (DOCTEST_PROJECT_DIR ${CMAKE_SOURCE_DIR}/../../00-common/include/doctest)
set (DOCTEST_HEADER_DIR ${DOCTEST_PROJECT_DIR}/src/doctest/doctest)
include_directories(${DOCTEST_HEADER_DIR})
message(STATUS "Doctest header dir: " ${DOCTEST_HEADER_DIR})


# TODO: options
set(PEP_BUILD_TESTS 1)
set(PEP_BUILD_GAME_LIBRARY 1)
set(PEP_BUILD_ENGINE_LIBRARY 1)
set(PEP_BUILD_APP 1)

add_compile_definitions(EXTERN_C)

if (PEP_BUILD_TESTS)

    include(ExternalProject)
    find_package(Git REQUIRED)

    ExternalProject_Add(
        doctest
        PREFIX ${DOCTEST_PROJECT_DIR}
        GIT_REPOSITORY https://github.com/onqtam/doctest.git
        TIMEOUT 10
        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
    )

    # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
    ExternalProject_Get_Property(doctest source_dir)
    set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")


    add_compile_definitions(PEP_TESTS_ON)
    include_directories(${DOCTEST_INCLUDE_DIR})
    message(STATUS "Doctest include dir: " ${DOCTEST_INCLUDE_DIR})

else()
    add_compile_definitions(DOCTEST_CONFIG_DISABLE)
endif(PEP_BUILD_TESTS)

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(app)
