cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PATH_DIR "C:/PATH")
set(GLOBAL_INCLUDES ${PATH_DIR}/include)

set(SFML_DIR "${PATH_DIR}/SFML-3.0.0/lib/cmake/SFML")

include_directories(${GLOBAL_INCLUDES})

find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System)

add_subdirectory(Engine)
add_subdirectory(Editor)

