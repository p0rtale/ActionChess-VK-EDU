file(GLOB server_sources src/*.cpp src/handler/*.cpp src/message/*.cpp src/net/*.cpp src/room/*.cpp)

file(GLOB game_sources src/game/logic/*.cpp src/game/rules/*.cpp)

add_library(server STATIC ${server_sources} ${game_sources})

target_include_directories(server PUBLIC include/handler include/message include/net include/room include/user
                                         include/game/logic include/game/rules
                                  PRIVATE ${RAPIDJSON_INCLUDE_DIR})

target_link_libraries(server PUBLIC common
                             PRIVATE ${Boost_LIBRARIES} OpenSSL::SSL)
