cmake_minimum_required(VERSION 3.16)

project(game VERSION 0.0.1 DESCRIPTION "prototype game on prototype engine")

set(CMAKE_CXX_STANDARD 17)

set(GAME_SOURCES
        libgame.cpp
)

add_library(${PROJECT_NAME} SHARED ${GAME_SOURCES})
add_library(sub::game ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 0.0.1
    PUBLIC_HEADER include/game/libgame.h
)

target_include_directories(${PROJECT_NAME}
    PRIVATE    
    ${PROJECT_SOURCE_DIR}/include
)

add_compile_definitions(PEP_DEBUG)

add_dependencies(${PROJECT_NAME} 
    sub::engine
    sub::load_engine
)

set (LDFLAGS "-Wl,-rpath,.")

target_link_libraries(${PROJECT_NAME} PRIVATE
    sub::load_engine
    dl
    ${LDFLAGS}
)

if(PEP_BUILD_GAME_LIBRARY)
    set (PEP_INSTALL_PATH_BIN ${CMAKE_SOURCE_DIR}/../install/bin/${CMAKE_BUILD_TYPE})

    install(TARGETS ${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION ${PEP_INSTALL_PATH_BIN}/
        RUNTIME DESTINATION ${PEP_INSTALL_PATH_BIN}/
        LIBRARY DESTINATION ${PEP_INSTALL_PATH_BIN}/
        ARCHIVE DESTINATION ${PEP_INSTALL_PATH_BIN}/
    )
endif(PEP_BUILD_GAME_LIBRARY)

if(PEP_BUILD_TESTS)

    set (PEP_INSTALL_PATH_TESTS ${CMAKE_SOURCE_DIR}/../install/bin/Tests/${CMAKE_BUILD_TYPE})

    install(TARGETS ${PROJECT_NAME}
            PUBLIC_HEADER DESTINATION ${PEP_INSTALL_PATH_TESTS}/
            RUNTIME DESTINATION ${PEP_INSTALL_PATH_TESTS}/
            LIBRARY DESTINATION ${PEP_INSTALL_PATH_TESTS}/
            ARCHIVE DESTINATION ${PEP_INSTALL_PATH_TESTS}/
        )

endif(PEP_BUILD_TESTS)


add_subdirectory(load_func_ho_lib)

