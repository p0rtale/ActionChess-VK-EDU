project(server)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(lib/server)

add_executable(main main.cpp)
target_link_libraries(main server -pthread)
