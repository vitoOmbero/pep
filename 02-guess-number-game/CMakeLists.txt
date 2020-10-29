cmake_minimum_required(VERSION 3.17)
project(01_guess_number_proto)

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

# compile

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        src/utils/terminal.cpp
        
        src/game.cpp
        src/engine.cpp
        )

add_executable(${PROJECT_NAME}
        main.cpp
        ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
        )
