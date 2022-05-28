cmake_minimum_required(VERSION 2.8)



project(chess_test)
set(CMAKE_C_STANDARD 11)



include_directories(interfaces)
include_directories(rules)

set(FIRST_LIB   rules/tile.cpp
                interfaces/tile.h
                rules/figure.cpp
                interfaces/figure.h
                rules/pawn.cpp
                interfaces/pawn.h
                rules/rock.cpp
                interfaces/rock.h
                rules/knight.cpp
                interfaces/knight.h
                rules/bishop.cpp
                interfaces/bishop.h
                rules/field.cpp
                interfaces/field.h
                rules/figure_handler.cpp
                interfaces/figure_handler.h)



add_library(test STATIC ${FIRST_LIB})



add_executable(main_part rules/main.cpp)



target_link_libraries(main_part PRIVATE test)