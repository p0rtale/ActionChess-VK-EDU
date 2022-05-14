project(server)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(main main.cpp )
target_include_directories(main PUBLIC  include/message 
                                  PRIVATE ${RAPIDJSON_INCLUDE_DIR} -pthread)

# add_subdirectory(lib/game)

target_link_libraries(main PRIVATE common #[[ game ]] ${Boost_LIBRARIES} OpenSSL::SSL -pthread)




