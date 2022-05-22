project(graphics)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)


find_package(SFML REQUIRED COMPONENTS system window graphics)
include_directories(${SFML_INCLUDE_DIR} include src include/Model include/Stages include/View include/Controller src/Model src/Stages src/View src/Controller )


add_library(WindowSwitcher STATIC "./include/WindowSwitcher.hpp" "./src/WindowSwitcher.cpp")
add_library(Assets STATIC "./include/Assets.hpp" "./src/Assets.cpp")
#add_library(Model STATIC "./src/model/MenuModel.cpp" )
add_library(Stages STATIC "./src/stages/BasicStage.cpp" "./src/stages/MenuStage.cpp")
add_library(View STATIC "./src/view/BasicView.cpp" "./src/view/MenuView.cpp")
add_library(Controller STATIC "./src/controller/MenuController.cpp")


target_include_directories(WindowSwitcher PRIVATE src include)
target_link_libraries(WindowSwitcher PUBLIC sfml-graphics sfml-window sfml-system) 
target_link_libraries(WindowSwitcher PUBLIC Assets Stages View Controller) 

target_link_libraries(Assets PUBLIC sfml-graphics sfml-window sfml-system) 
target_link_libraries(Assets PUBLIC WindowSwitcher Stages View Controller) 
target_link_libraries(Stages PUBLIC sfml-graphics sfml-window sfml-system) 
target_link_libraries(Stages PUBLIC Assets WindowSwitcher View Controller) 
target_link_libraries(View PUBLIC sfml-graphics sfml-window sfml-system) 
target_link_libraries(View PUBLIC Assets Stages WindowSwitcher Controller) 
target_link_libraries(Controller PUBLIC sfml-graphics sfml-window sfml-system) 
target_link_libraries(Controller PUBLIC Assets Stages View WindowSwitcher) 


