cmake_minimum_required(VERSION 2.8)



project(chess_test)



include_directories(interfaces)
include_directories(rules)

set(FIRST_LIB   rules/tile.cpp
                interfaces/tile.h
                rules/figure.cpp
                interfaces/figure.h
                rules/pawn.cpp
                interfaces/pawn.h
                rules/figure_handler.cpp
                interfaces/figure_handler.h)



add_library(test STATIC ${FIRST_LIB})



add_executable(main_part rules/main.cpp)



target_link_libraries(main_part PRIVATE test)