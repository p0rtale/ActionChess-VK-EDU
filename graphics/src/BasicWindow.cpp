#include "BasicWindow.hpp"
#include "file_path.hpp"
#include <vector>


BasicWindow& BasicWindow::get_instance(){
    static BasicWindow instance;
    return instance;
}
BasicWindow::BasicWindow()
{
    font.loadFromFile(DEFAULT_FONT_PATH);
}

BasicWindow::~BasicWindow()
{
}
