project(Pseudo3D)

set(SOURCES
    source/map.cpp 
    source/player.cpp
    source/camera.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include )

target_link_libraries(${PROJECT_NAME} 
    SFML::Graphics
    SFML::Window
    SFML::System
)