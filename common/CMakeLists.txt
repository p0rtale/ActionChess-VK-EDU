file(GLOB common_sources src/message/*.cpp)

add_library(common STATIC ${common_sources})

add_dependencies(common rapidjson)

target_include_directories(common PUBLIC include/logger include/message include/user
                                  PRIVATE ${RAPIDJSON_INCLUDE_DIR})
