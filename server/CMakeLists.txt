cmake_minimum_required(VERSION 3.20)

project(server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(lib/server)

add_executable(main main.cpp)
target_link_libraries(main server -pthread)
