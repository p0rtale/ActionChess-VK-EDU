cmake_minimum_required(VERSION 3.20)

project(action-chess)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("${CMAKE_SOURCE_DIR}/vendor/rapidjson.cmake")

add_subdirectory(common)
add_subdirectory(server)
