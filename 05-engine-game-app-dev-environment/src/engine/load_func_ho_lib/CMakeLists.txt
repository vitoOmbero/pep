cmake_minimum_required (VERSION 3.9)

project(engine_func_load)

add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::load_engine ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/../include
)
