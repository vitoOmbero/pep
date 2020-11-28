cmake_minimum_required (VERSION 3.9)

project(game_func_load)

add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::load_game ALIAS ${PROJECT_NAME})

add_dependencies(${PROJECT_NAME} sub::game)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/../include
)
