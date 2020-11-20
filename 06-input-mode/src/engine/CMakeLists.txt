cmake_minimum_required(VERSION 3.16)

# TODO: static linking with engine... to fix build issues when static linking with SDL2
set(PEP_SDL_STATIC_LINKING FALSE)
set(PEP_SDL_CUSTOM_BUILD FALSE)

set(PEP_VERSION_MAJOR 0)
set(PEP_VERSION_MINOR 0)
set(PEP_VERSION_PATCH 1)
set(PEP_VERSION ${PEP_VERSION_MAJOR}.${PEP_VERSION_MINOR}.${PEP_VERSION_PATCH})
message(STATUS "PEP_VERSION: ${PEP_VERSION}")

project(engine VERSION ${PEP_VERSION} DESCRIPTION "prototype engine")

set(CMAKE_CXX_STANDARD 17)

set(ENGINE_SOURCES
        libengine.cpp
        service/game_variables_service.cpp
        service/game_level_logic_processor.cpp
        service/text_world_object_processor.cpp
        service/variables_storage.cpp
        utils/terminal.cpp pep.cpp)

add_library(${PROJECT_NAME} SHARED ${ENGINE_SOURCES})
add_library(sub::engine ALIAS ${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE PEP_VERSION_MAJOR=${PEP_VERSION_MAJOR}, PEP_VERSION_MINOR=${PEP_VERSION_MINOR}, PEP_VERSION_PATCH=${PEP_VERSION_PATCH})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PEP_VERSION}
    PUBLIC_HEADER include/engine/libengine.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
        )

target_include_directories(${PROJECT_NAME}
    PRIVATE    ${PROJECT_SOURCE_DIR}/include
                ${PROJECT_SOURCE_DIR}/include/engine
)
find_package(sdl2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})

if(PEP_SDL_STATIC_LINKING)
    if (PEP_SDL_CUSTOM_BUILD)
        find_library(SDL2_LIB
                     NAMES libSDL2.a
                     PATHS /custom_sdl2_build/
                     )
        target_link_libraries(${PROJECT_NAME} PRIVATE
                -L/usr/local/lib -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags
                -lglib-2.0 -lgobject-2.0 -lgio-2.0 -libus-1.0 -ldbus-1
                /usr/lib/x86_64-linux-gnu/libsndio.so
                -ldl -lm -Wl,--no-undefined -pthread
                #-lSDL2
                ${SDL2_LIB}
        )
    else()
        find_library(SDL2_LIB libSDL2.a)
        # sdl2-config --static-libs
        target_link_libraries(${PROJECT_NAME} PRIVATE
                ${SDL2_LIB}
                -Wl,--no-undefined
                -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple
                -lpulse -lX11 -lXext -lXcursor -lXinerama -lXi -lXrandr
                -lXss -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor
                -lxkbcommon -lpthread -lrt
        )
    endif()
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE sub::pep)

if(PEP_BUILD_ENGINE_LIBRARY)
    set (PEP_INSTALL_PATH_BIN ${CMAKE_SOURCE_DIR}/../install/bin/${CMAKE_BUILD_TYPE})

    install(TARGETS ${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION ${PEP_INSTALL_PATH_BIN}/
        RUNTIME DESTINATION ${PEP_INSTALL_PATH_BIN}/
        LIBRARY DESTINATION ${PEP_INSTALL_PATH_BIN}/
        ARCHIVE DESTINATION ${PEP_INSTALL_PATH_BIN}/
    )
endif(PEP_BUILD_ENGINE_LIBRARY)

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
add_subdirectory(pep_ho_lib)
