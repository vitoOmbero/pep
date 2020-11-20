cmake_minimum_required(VERSION 3.16)

project(game VERSION 0.0.1 DESCRIPTION "prototype game on prototype engine")

option(GNUMBER "Build Gnumber game" ON)

## default option
set(GAME_NAME "Dummy dl test")

if(GNUMBER)
    set(BUILD_G_NUMBER True)
    set(GAME_NAME "GNumber")
endif()

if(BUILD_G_NUMBER)
    set(GAME_CONTENT_SOURCES
            g_number/logic.cpp
            g_number/libgame.cpp
            )
    set(GAME_CONTENT_INCLUDE_DIR
            include/g_number
            )
endif(BUILD_G_NUMBER)

message(STATUS "GNUMBER: " ${GNUMBER})
message(STATUS "Game to build: " ${GAME_NAME})

set(GAME_SOURCES
        libgame.cpp
        ${GAME_CONTENT_SOURCES}
)

add_library(${PROJECT_NAME} SHARED ${GAME_SOURCES})
add_library(sub::game ALIAS ${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE
        PEP_DL_TEST
        )

if(GNUMBER)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
            PEP_GAME_G_NUMBER
   )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 0.0.1
    PUBLIC_HEADER include/libgame.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
        )

target_include_directories(${PROJECT_NAME}
    PRIVATE    
    ${PROJECT_SOURCE_DIR}/include
)

add_dependencies(${PROJECT_NAME} 
        sub::engine
        sub::load_engine
        sub::pep
)

set (LDFLAGS "-Wl,-rpath,.")

target_link_libraries(${PROJECT_NAME} PRIVATE
        sub::load_engine
        sub::pep
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
