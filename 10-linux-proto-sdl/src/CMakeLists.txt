cmake_minimum_required(VERSION 3.16)
project(10-linux-proto-sdl)

# options
message("Set project options:")

option(PEP_DEBUG "Turn on debug features" OFF)
option(PEP_VERBOSE "Turn on inlined stdout logger" ON)

set(verboseLevels Lvl1 Lvl2 ALL)
set(verboseLevel ALL CACHE STRING "Level of logging")
set_property(CACHE verboseLevel PROPERTY STRINGS ${verboseLevels})

message(STATUS "PEP_DEBUG: ${PEP_DEBUG}")
message(STATUS "PEP_VERBOSE: ${PEP_VERBOSE}")

if(NOT verboseLevel IN_LIST verboseLevels)
    message(FATAL_ERROR "verboseLevel must be one of ${verboseLevels}")
endif()

message("Project options are set.")

# compilation
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(${PROJECT_NAME} main.cxx)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

find_package(sdl2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

# install
install(TARGETS ${PROJECT_NAME} 
        RUNTIME DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../../install/
        LIBRARY DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../../install/
        ARCHIVE DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../../install/)
