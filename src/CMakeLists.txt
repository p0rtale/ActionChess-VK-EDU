project(graphics)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)


find_package(SFML REQUIRED COMPONENTS system window graphics)
include_directories(${SFML_INCLUDE_DIR} *.cpp *.hpp)

add_library(src STATIC "*.cpp" "*.hpp")

target_link_libraries(src PUBLIC sfml-graphics sfml-window sfml-system) 
