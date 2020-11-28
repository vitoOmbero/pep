cmake_minimum_required (VERSION 3.16)

project(app.out)

set(APP_SOURCES
        main.cpp
        application.cpp
        assets_loader.cpp
        fpc.cpp)

add_executable(${PROJECT_NAME} ${APP_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE    
    ${PROJECT_SOURCE_DIR}/include
)

set (LDFLAGS "-Wl,-rpath,.")

target_link_libraries(${PROJECT_NAME} PRIVATE
    sub::load_engine 
    sub::load_game
    dl
    ${LDFLAGS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
        )

if(PEP_BUILD_APP)
    set (PEP_INSTALL_PATH_BIN ${CMAKE_SOURCE_DIR}/../install/bin/${CMAKE_BUILD_TYPE})

    install(TARGETS ${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION ${PEP_INSTALL_PATH_BIN}/
        RUNTIME DESTINATION ${PEP_INSTALL_PATH_BIN}/
        LIBRARY DESTINATION ${PEP_INSTALL_PATH_BIN}/
        ARCHIVE DESTINATION ${PEP_INSTALL_PATH_BIN}/
    )
endif(PEP_BUILD_APP)

if(PEP_BUILD_TESTS)
    set (PEP_INSTALL_PATH_TESTS ${CMAKE_SOURCE_DIR}/../install/bin/Tests/${CMAKE_BUILD_TYPE})

    target_link_libraries(${PROJECT_NAME} PRIVATE sub::engine sub::game)

    install(TARGETS ${PROJECT_NAME}
            PUBLIC_HEADER DESTINATION ${PEP_INSTALL_PATH_TESTS}/
            RUNTIME DESTINATION ${PEP_INSTALL_PATH_TESTS}/
            LIBRARY DESTINATION ${PEP_INSTALL_PATH_TESTS}/
            ARCHIVE DESTINATION ${PEP_INSTALL_PATH_TESTS}/
        )

endif(PEP_BUILD_TESTS)
