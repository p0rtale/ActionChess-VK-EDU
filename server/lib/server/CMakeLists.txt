file(GLOB sources src/*.cpp src/handler/*.cpp src/message/*.cpp src/room/*.cpp)

add_library(server STATIC ${sources})
target_include_directories(server PUBLIC include include/handler include/message include/room)
target_link_libraries(server PRIVATE ${Boost_LIBRARIES} OpenSSL::SSL)
