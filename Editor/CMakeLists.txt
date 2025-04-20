project(Pseudo3DEditor)

set(sources
    source/main.cpp

    ${GLOBAL_INCLUDES}/imgui/imgui.cpp
    ${GLOBAL_INCLUDES}/imgui/imgui_widgets.cpp
    ${GLOBAL_INCLUDES}/imgui/imgui_draw.cpp
    ${GLOBAL_INCLUDES}/imgui/imgui-SFML.cpp
)

add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE ../Engine/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLOBAL_INCLUDES}/imgui)

target_link_libraries(${PROJECT_NAME} 
    SFML::Graphics
    SFML::Window
    SFML::System

    opengl32.lib

    Pseudo3D 
    ${GLOBAL_INCLUDES}/imgui/ImGui-SFML.lib
)
