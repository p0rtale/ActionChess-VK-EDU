cmake_minimum_required(VERSION 3.20)

project(action)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SFML REQUIRED COMPONENTS system window graphics )
include_directories(${SFML_INCLUDE_DIR} )

file(GLOB_RECURSE sources src/*.cpp )
add_library(src STATIC ${sources})
target_link_libraries(src PUBLIC sfml-graphics sfml-window sfml-system)

add_executable(main main.cpp )
target_link_libraries(main src sfml-graphics sfml-window sfml-system)
target_include_directories(main PUBLIC "src/Engine.hpp")





