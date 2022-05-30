#include <stdlib.h>
#include "WindowSwitcher.hpp"
#include <pthread.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <optional>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include "rapidjson/writer.h"
#include <boost/asio/ssl.hpp>
#include <memory>
#include <optional>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <bitset>
#include <X11/Xlib.h>

int main(){
    XInitThreads();
    boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
    ctx.load_verify_file("./settings/server.crt");
    boost::asio::io_context io_context;
    std::string server= "127.0.0.1";
    std::string port= "8080";
    std::string path ="";
    std::optional<boost::asio::ip::tcp::socket> socket3;

    Client c(io_context, server, port, path,&ctx);
    boost::thread t(boost::bind(&boost::asio::io_context::run, &io_context));
    WindowSwitcher& MainWindow = WindowSwitcher::get_instance();
    MainWindow.init(&c);
    MainWindow.run();
    io_context.stop();
    t.join() ;//TODO: разобраться 
    return EXIT_SUCCESS;
}