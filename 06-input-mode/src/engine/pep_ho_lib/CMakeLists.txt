cmake_minimum_required (VERSION 3.9)

# engine interface for gamedev
project(pep_game_engine)

add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::pep ALIAS ${PROJECT_NAME})

add_dependencies(${PROJECT_NAME}
        sub::load_engine)

target_link_libraries(${PROJECT_NAME} INTERFACE sub::load_engine)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/../include
)
