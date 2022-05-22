#include <stdlib.h>
#include "WindowSwitcher.hpp"

int main(){
    WindowSwitcher& MainWindow = WindowSwitcher::get_instance();
    MainWindow.init();
    MainWindow.run();
    return EXIT_SUCCESS;
}