file(GLOB server_sources src/*.cpp src/handler/*.cpp src/message/*.cpp src/net/*.cpp src/room/*.cpp)

add_library(server STATIC ${server_sources})

target_include_directories(server PUBLIC include/handler include/message include/net include/room include/user
                                  PRIVATE ${RAPIDJSON_INCLUDE_DIR})

# add_subdirectory(lib/game)

target_link_libraries(server PUBLIC common #[[ game ]] 
                             PRIVATE ${Boost_LIBRARIES} OpenSSL::SSL)
