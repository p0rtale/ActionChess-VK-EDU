cmake_minimum_required(VERSION 3.0.0)
project(chess)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("${CMAKE_SOURCE_DIR}/vendor/rapidjson.cmake")

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CLIENT_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CLIENT_LIB_LIBRARIES})













set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror")

add_subdirectory(board)
add_subdirectory(Figure)
add_subdirectory(GroupFigure)
add_subdirectory(Engine)

add_executable(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${BOARD_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${BOARD_LIB_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${FIGURE_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FIGURE_LIB_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${GROUPFIGURE_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GROUPFIGURE_LIB_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ENGINE_LIB_LIBRARIES})