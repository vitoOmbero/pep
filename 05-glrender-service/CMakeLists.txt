cmake_minimum_required(VERSION 3.17)
project(05_glrender_service)

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
        src/engine/service/game_level_logic_processor.cpp
        src/engine/service/game_variables_service.cpp
        src/engine/service/text_world_object_processor.cpp
        src/engine/service/variables_storage.cpp
        src/engine/engine.cpp
        src/engine/pep.cpp

        src/game_guess_num/g_number_logic.cpp

        src/game_guess_num_console_app/assets_loader.cpp
        )


add_executable(${PROJECT_NAME}
        # src/game_guess_num_console_app/main.cpp
        src/gl_demo_sdl_app/main.cpp
        ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/../00-common/include/
        )

find_package(sdl2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
find_library(SDL2_LIB libSDL2.a)

if(UNIX)
    target_link_libraries( ${PROJECT_NAME}
            ${SDL2_LIB}
            -lSDL2 -Wl,--no-undefined -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple -lpulse -lX11 -lXext -lXcursor -lXinerama -lXi -lXrandr -lXss -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -lpthread -lrt


            )
elseif(MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
endif()


