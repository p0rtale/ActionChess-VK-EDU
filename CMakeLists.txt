cmake_minimum_required(VERSION 3.20)

project(action-chess-client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

find_package(SFML REQUIRED COMPONENTS system window graphics )
include_directories(${SFML_INCLUDE_DIR} )
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)



file(GLOB_RECURSE sources graphics/*.cpp )
add_library(graphic STATIC ${sources})
target_include_directories(graphic PUBLIC  graphics  "./graphics/include" "./graphics/include/Widgets"  "./graphics/include/Model" "./graphics/include/Stages" "./graphics/include/View" "./graphics/include/Controller")
target_link_libraries(graphic PUBLIC sfml-graphics sfml-window sfml-system)
#add_subdirectory(graphics)
#add_subdirectory(server)
add_executable(main main.cpp )
target_link_libraries(main graphic sfml-graphics sfml-window sfml-system)

